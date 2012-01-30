// Copyright (C) 2011-2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Functions:
//     Push(value)
//         Pushes an argument onto the stack (not the actual stack - real push is
//         done when you Call() a function). The arguments are pushed from left
//         to right.
//     PushString(const string[])
//         Same as Push() but for strings. This is cheap as it only pushes the
//         address - no string copying performed.
//     Pop(&value = 0)
//         Pops the argument from the top of the argument pseudo-stack. Takes an
///        optional parameter to store the popped value in.
//     Call(address)
//         Calls a function located at the specified address. The address can be
//         obtained with GetFunctionAddress(), see below.
//     GetFunctionAddress(const name[])
//         Looks up the address of the specified public function by its name.
//         Returns 0 if the function is not found.
//     CallFunction(const name[], {Float,_}:...)
//         Same as SA-MP's CallLocalFunction() but doesn't need a format string.
//         You have to use addressofs() to pass strings and addressof() for references.
//     CallNative(address)
//         Calls a native function. The address can be obtained with GetNativeFunctionAddress(),
//         see below.
//     GetNativeFunctionAddress(const name[])
//         Searches for a native function with a given name in native table and
//         returns its address if found, or 0 otherwise.
//     CallNativeFunction(const name[], {Float,_}:...)
//         Similar to CallFunction but for natives.

#include <a_samp>

#include "amx_hdr"
#include "memory"

#if !defined MAX_FUN_ARGS
	#define MAX_FUN_ARGS 256
#endif

static stock g_nargs = 0;
static stock g_args[MAX_FUN_ARGS];

stock bool:Push(arg) {
	if (g_nargs < sizeof(g_args)) {
		g_args[g_nargs++] = arg;
		return true;
	}
	return false;
}

stock bool:PushString(const string[]) {
	new address;
	#emit load.s.pri string
	#emit stor.s.pri address
	return Push(address);
}

stock bool:Pop(&arg = 0) {
	if (g_nargs > 0) {
		arg = g_args[--g_nargs];
		return true;
	}
	return false;
}

stock Call(address, bool:auto_pop = true) {
	new arg = 0;
	new index = g_nargs;
	new bytes = g_nargs * 4;

	while (--index >= 0) {
		arg = g_args[index];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	#emit lctrl 6
	#emit add.c 0x1c
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl 6

	if (auto_pop) {
		while (Pop()) {}
	}
}

stock GetFunctionAddress(const name[]) {
	static amxhdr[AMX_HDR];
	static publics, num_publics, defsize;

	static bool:initialized = false;
	if (!initialized) {
		GetAMXHeader(amxhdr);
		publics = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
		defsize = amxhdr[AMX_HDR_DEFSIZE];
		num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;
	}

	// Binary search
	new first = 0;
	new last = num_publics - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		// Table record offset
		new offset = publics + mid*defsize;

		new address;
		#emit lref.s.pri offset
		#emit stor.s.pri address
		offset += 4;

		new nameofs;
		#emit lref.s.pri offset
		#emit stor.s.pri nameofs
		//offset += 4;

		// Copy public's name
		new public_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			public_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (public_name[index] != '\0' && ++index < sizeof(public_name));

		new cmp = strcmp(name, public_name);
		if (cmp > 0) {
			last = mid - 1;
		} else if (cmp < 0) {
			first = mid + 1;
		} else {
			return address;
		}
	}

	return 0;
}

stock CallFunction(const name[], {Float,_}:...) {
	// Obtain function address
	new address = GetFunctionAddress(name);
	if (address == 0) {
		return 0;
	}

	new arg_bytes, arg_begin, arg_end;

	// Get number of bytes passed
	#emit load.s.pri 0x8
	#emit const.alt 4
	#emit sub
	#emit stor.s.pri arg_bytes
	// Store in ALT
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT)
	#emit lctrl 5
	#emit add.c 0xc
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10
	#emit lctrl 5
	#emit add.c 0x10
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i // Variable arguments are passed by reference
		#emit push.pri
		arg -= 4;
	}

	// Call the function
	#emit push.s arg_bytes
	#emit lctrl 6
	#emit add.c 0x1c
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl 6
	// Arguments are popped by callee

	// Pop locals and return
	#emit stack 0x14
	#emit retn
	return 0;
}

stock CallNative(address, bool:auto_pop = true) {
	new arg = 0;
	new index = g_nargs;
	new bytes = g_nargs * 4;
	new tmp;

	while (--index >= 0) {
		arg = g_args[index];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl 0  // COD
	#emit move.alt
	#emit lctrl 6  // CIP
	#emit add
	#emit move.alt
	#emit lctrl 1 // DAT
	#emit sub.alt
	#emit add.c 0x5c
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit const.pri 135
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c 4
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	// Pop native arguments
	#emit lctrl 4 // Get STK
	#emit load.s.alt bytes
	#emit add
	#emit add.c 4 // One extra cell for params[0]
	#emit sctrl 4

	if (auto_pop) {
		while (Pop()) {}
	}
}

stock GetNativeFunctionAddress(const name[]) {
	static amxhdr[AMX_HDR];
	static natives, num_natives, defsize;

	static bool:initialized = false;
	if (!initialized) {
		GetAMXHeader(amxhdr);
		natives = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];
		defsize = amxhdr[AMX_HDR_DEFSIZE];
		num_natives = (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / defsize;
	}

	// Binary search
	new first = 0;
	new last = num_natives - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		// Table record offset
		new offset = natives + mid*defsize;

		new address;
		#emit lref.s.pri offset
		#emit stor.s.pri address
		offset += 4;

		new nameofs;
		#emit lref.s.pri offset
		#emit stor.s.pri nameofs
		//offset += 4;

		// Copy native's name
		new native_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			native_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (native_name[index] != '\0' && ++index < sizeof(native_name));

		new cmp = strcmp(name, native_name);
		if (cmp > 0) {
			last = mid - 1;
		} else if (cmp < 0) {
			first = mid + 1;
		} else {
			return address;
		}
	}

	return 0;
}

stock CallNativeFunction(const name[], {Float,_}:...) {
	// Obtain function address
	new address = GetNativeFunctionAddress(name);
	if (address == 0) {
		return 0;
	}

	new arg_bytes, arg_begin, arg_end;

	// Get number of bytes passed
	#emit load.s.pri 0x8
	#emit const.alt 4
	#emit sub
	#emit stor.s.pri arg_bytes
	// Store in ALT
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT)
	#emit lctrl 5
	#emit add.c 0xc
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10
	#emit lctrl 5
	#emit add.c 0x10
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	new tmp;

	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i // Variable arguments are passed by reference
		#emit push.pri
		arg -= 4;
	}

	// Push number of arguments * 4 (which is params[0])
	#emit push.s arg_bytes

	// Call the function
	// We use sysreq.d for this purpose

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl 0  // COD
	#emit move.alt
	#emit lctrl 6  // CIP
	#emit add
	#emit move.alt
	#emit lctrl 1 // DAT
	#emit sub.alt
	#emit add.c 0x5c
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit const.pri 135
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c 4
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	// Pop native arguments
	#emit lctrl 4 // Get STK
	#emit load.s.alt arg_bytes
	#emit add
	#emit add.c 4 // One extra cell for params[0]
	#emit sctrl 4

	// Pop locals and return
	#emit stack 0x18
	#emit retn
	return 0;
}


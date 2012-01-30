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
//         Similar to CallLocalFunction() but doesn't take a format string.

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

	#emit load.s.pri address
	#emit call.pri

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
	new i = 0;
	new j = num_publics - 1;
	new k;

	while (i <= j) {
		k = (i + j) / 2;

		// Table record offset
		new offset = publics + k*defsize;

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
			//printf("%s > %s", name, public_name);
			i = k + 1;
		} else if (cmp < 0) {
			//printf("%s < %s", name, public_name);
			j = k - 1;
		} else {
			//printf("%s == %s", name, public_name);
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
		//printf("arg = %d", arg);
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

	#emit stack 0x14
	#emit retn
	return 0;
}

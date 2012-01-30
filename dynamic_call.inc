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
	static begin, end;

	static bool:initialized = false;
	if (!initialized) {
		GetAMXHeader(amxhdr);
		begin = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
		end   = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];
	}

	for (new i = begin; i < end;) {
		new address;
		#emit lref.s.pri i
		#emit stor.s.pri address
		i += 4;

		new nameofs;
		#emit lref.s.pri i
		#emit stor.s.pri nameofs
		i += 4;

		// Copy public's name
		new public_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			public_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (public_name[index] != '\0' && ++index < sizeof(public_name));

		if (strcmp(name, public_name) == 0) {
			return address;
		}
	}

	return 0;
}

stock CallFunction(const name[], const format[], {Float,_}:...) {
	// Obtain function address
	new address = GetFunctionAddress(name);
	if (address == 0) {
		printf("CallFunction(): Cannot find public function %s", name);
		return 0;
	}

	new arg_bytes, arg_begin, arg_end;

	// Get the size of arguments
	#emit load.s.pri 0x8
	#emit const.alt 8
	#emit sub
	#emit stor.s.pri arg_bytes
	// Store in ALT
	#emit move.alt

	// Last argument is at FRM + 0x10 + arg_bytes (which is in ALT)
	#emit lctrl 5
	#emit add.c 0x10
	#emit add
	#emit stor.s.pri arg_end

	// First argument is at FRM + 0x14
	#emit lctrl 5
	#emit add.c 0x14
	#emit stor.s.pri arg_begin

	// Check parameter count
	new format_len = strlen(format);
	if (arg_bytes/4 != format_len) {
		printf("CallFunction(): Expected %d arguments but got %d", format_len, arg_bytes/4);
		return 0;
	}

	// Push the arguments
	new cur_arg = arg_end;
	new cur_idx = format_len - 1;
	while (cur_arg >= arg_begin) {
		switch (format[cur_idx--]) {
			case 'i', 'd': {
				#emit lref.s.pri cur_arg
				#emit load.i // Variable arguments are passed by reference
				#emit push.pri
			}
			case 's': {
				#emit lref.s.pri cur_arg
				#emit push.pri
			}
		}
		cur_arg -= 4;
	}

	// Call the function
	#emit push.s arg_bytes
	#emit lctrl 6
	#emit add.c 0x1c
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl 6
	// Arguments are popped by callee

	#emit stack 0x1c
	#emit retn
	return 0;
}

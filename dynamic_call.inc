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
//         Calls a native function. The address can be obtained with GetPublicAddressByName()
//         from natives.inc.
//     Sysreq(address)
//         Calls a native function. The address can be obtained with GetNativeAddressByName()
//         from natives.inc.

#include <a_samp>

#include "amx_hdr"
#include "memory"
#include "natives"
#include "publics"

#if !defined MAX_FUN_ARGS
	#define MAX_FUN_ARGS 256
#endif

#define MAX_FUN_NAME 32

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

stock Sysreq(address, bool:auto_pop = true) {
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

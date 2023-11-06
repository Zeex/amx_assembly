// Copyright (C) 2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#if defined OS_INC
	#endinput
#endif
#define OS_INC

/**
 * <library name="amx_assembly os" summary="AMX Assembly Library: Determine the host OS type.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

/// <library>amx_assembly os</library>
enum OS {
	OS_UNKNOWN,
	OS_LINUX,
	OS_WINDOWS
};

/// <library>amx_assembly os</library>
const OS:OS__ = OS;

#if !defined __register_names
	const __cod = 0;
	const __dat = 1;
	const __hea = 2;
	const __stp = 3;
	const __stk = 4;
	const __frm = 5;
	const __cip = 6;
	const __jit = 7;
	const __jmp = 8;
	const __flg = 9;
	#define __register_names
#endif

/// <library>amx_assembly os</library>
stock OS:GetOS() {
	new
		val = 0;
	// The code at address 0 is always `HALT` so load and check it.
	// Based on code originally in fixes.inc.
	#emit lctrl __cod
	#emit move.alt
	#emit lctrl __dat
	#emit sub.alt
	#emit stor.s.pri val
	#emit lref.s.alt val
	#emit stor.s.alt val
	// Hard-coded opcode of `120` to avoid including `opcode.inc`.
	return val == 120 ? OS_WINDOWS : OS_LINUX;
}

/// <library>amx_assembly os</library>
stock bool:IsWindows() {
	return GetOS() == OS_WINDOWS;
}

/// <library>amx_assembly os</library>
stock bool:IsLinux() {
	return GetOS() == OS_LINUX;
}


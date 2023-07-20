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

#if defined AMX_JIT_INC
	#endinput
#endif
#define AMX_JIT_INC

/**
 * <library name="amx_assembly amx_jit" summary="AMX Assembly Library: JIT plugin address relocations.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

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

/// <library>amx_assembly amx_jit</library>
stock GetJITGeneratorVersion() {
	#emit zero.pri
	#emit lctrl __jit
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_jit</library>
stock GetAmxJITBaseAddress() {
	// Only works when the jit is installed, otherwise returns 0.  The code is
	// so short, checking if it had been done before would have been longer than
	// just repeating the calculation.
	#emit zero.pri
	#emit lctrl __jmp
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_jit</library>
stock ResolveJITAddress(addr) {
	// Converts an address to a JIT address, if there is a JIT.  Otherwise does
	// nothing.  Could make it try detect if this is already JIT resolved, i.e.
	// is a return address.
	#emit load.s.pri addr
	#emit lctrl __jmp
	#emit retn
	return 0;
}


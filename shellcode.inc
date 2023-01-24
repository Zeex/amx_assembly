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

#if defined SHELLCODE_INC
	#endinput
#endif
#define SHELLCODE_INC

/**
 * <library name="amx_assembly shellcode" summary="AMX Assembly Library: Execute arbitrary x86 assembly.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "amx_header"
#include "dynamic_call"
#include "phys_memory"

/// <library>amx_assembly shellcode</library>
stock RunShellcode(code_ptr, bool:align = true) {
	if (align) {
		code_ptr = ((code_ptr + 15) >>> 4) << 4;
	}
	return SysreqD(code_ptr);
}

stock RunShellcodeWide(code_ptr, wide_ptr, bool:align = true) {
	if (align) {
		code_ptr = ((code_ptr + 15) >>> 4) << 4;
	}
	return SysreqDWide(code_ptr, wide_ptr);
}


// Copyright (C) 2011-2012 Zeex
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

#if defined AMX_BASE_INC
	#endinput
#endif
#define AMX_BASE_INC

/**
 * <library name="amx_assembly amx_base" summary="AMX Assembly Library: Script load address determination.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

/// <library>amx_assembly amx_base</library>
static stock GetAmxBaseAddress_helper() {
	return 0;
}

/// <library>amx_assembly amx_base</library>
/// <summary>
///   Returns the AMX base address i.e. <c>amx-&gt;base</c>.
/// </summary>
stock GetAmxBaseAddressNow() {
	new cod = 0, dat = 0;
	#emit lctrl 0
	#emit stor.s.pri cod
	#emit lctrl 1
	#emit stor.s.pri dat

	// Get code section start address relative to data.
	new code_start = cod - dat;

	// Get address of GetAmxBaseAddress_helper().
	new fn_addr = 0;
	#emit const.pri GetAmxBaseAddress_helper
	#emit stor.s.pri fn_addr

	// Get absolute address from the CALL instruction.
	new fn_addr_reloc = 0, call_addr = 0;
	GetAmxBaseAddress_helper();
	#emit lctrl 6
	#emit stor.s.pri call_addr
	call_addr = call_addr - 12 + code_start;
	#emit lref.s.pri call_addr
	#emit stor.s.pri fn_addr_reloc

	return fn_addr_reloc - fn_addr - cod;
}

/// <library>amx_assembly amx_base</library>
stock GetAmxBaseAddress() {
	static amx_base = 0;
	if (amx_base == 0) {
		amx_base = GetAmxBaseAddressNow();
	}
	return amx_base;
}


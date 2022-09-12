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

#if defined AMX_INC
	#endinput
#endif
#define AMX_INC

/**
 * <library name="amx_assembly amx" summary="AMX Assembly Library: `AMX*` struct pointer determination.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "phys_memory"
#include "shellcode"

/// <library>amx_assembly amx</library>
const AMX_OFFSET_BASE = 0;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_DATA = 4;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_CALLBACK = 8;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_DEBUG = 12;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_CIP = 16;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_FRM = 20;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_HEA = 24;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_HLW = 28;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_STK = 32;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_STP = 36;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_FLAGS = 40;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_USERTAGS = 44;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_USERDATA = 60;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_ERROR = 76;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_PARAMCOUNT = 80;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_PRI = 84;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_ALT = 88;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_RESET_STK = 92;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_RESET_HEA = 96;

/// <library>amx_assembly amx</library>
const AMX_OFFSET_SYSREQ_D = 100;

/// <library>amx_assembly amx</library>
/// <summary>
///   Returns the address of the AMX struct instance in memory that corresponds
///   to this script.  This function works only on Windows!
/// </summary>
stock GetAmxAddress() {
	static address = 0;
	if (address == 0) {
		#if cellbits == 32
			static const code[] = {
				0x90909090, 0x90909090, 0x90909090, 0x90909090, // for alignment
				0x0424448B, 0xC3C3C3C3
				// 8B 44 24 04 - MOV  eax, [esp + arg_0]
				// C3          - RETN
			};
		#elseif cellbits == 64
			static const code[] = {
				0x9090909090909090, 0x9090909090909090, // for alignment
				0xC3C3C3C30424448B
				// 8B 44 24 04 - MOV  eax, [esp + arg_0]
				// C3          - RETN
			};
		#else
			#error Unsupported `cellbits`.
		#endif
		address = RunShellcode(refabs(code));
	}
	return address;
}

/// <library>amx_assembly amx</library>
/// <summary>
///   Reads a cell from the AMX struct.
/// </summary>
stock ReadAmxCell(offset) {
	new amx = GetAmxAddress();
	return ReadPhysMemoryCell(amx + offset);
}

/// <library>amx_assembly amx</library>
/// <summary>
///   Writes a cell to the AMX struct.
/// </summary>
stock WriteAmxCell(offset, value) {
	new amx = GetAmxAddress();
	WritePhysMemoryCell(amx + offset, value);
}


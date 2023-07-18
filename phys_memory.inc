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

#if defined PHYS_MEMORY_INC
	#endinput
#endif
#define PHYS_MEMORY_INC

/**
 * <library name="amx_assembly phys_memory" summary="AMX Assembly Library: Read and write real server addresses.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include <core>

#include "amx_base"

/// <library>amx_assembly phys_memory</library>
static stock GetDat() {
	#emit lctrl __dat
	#emit retn
	return 0; // make compiler happy
}

/// <library>amx_assembly phys_memory</library>
static stock AbsToRel(address) {
	if (HasReloc()) {
		return address - (GetAmxBaseAddress() + GetDat());
	}
	return 0;
}

/// <library>amx_assembly phys_memory</library>
static stock RelToAbs(address) {
	if (HasReloc()) {
		return address + (GetAmxBaseAddress() + GetDat());
	}
	return 0;
}

/// <library>amx_assembly phys_memory</library>
static stock RelToWide(address, &wide) {
	// I don't think we can actually write this function, since relocations are
	// disabled in 64-bit compatibility mode.
	if (HasReloc()) {
		wide = 0;
		return address + (GetAmxBaseAddress() + GetDat());
	}
	return 0;
}

/// <library>amx_assembly phys_memory</library>
/// <summary>
///   Returns the absolute address of a variable/array.
/// </summary>
stock refabs(...) {
	const cells0 = 3 * cellbytes;
	assert(numargs() == 1);
	new address = 0;
	#emit load.s.pri cells0
	#emit stor.s.pri address
	return RelToAbs(address);
}

/// <library>amx_assembly phys_memory</library>
/// <summary>
///   Returns the absolute address of a variable/array.
/// </summary>
stock refwide(&wide, ...) {
	const cells0 = 4 * cellbytes;
	assert(numargs() == 2);
	new address = 0;
	#emit load.s.pri cells0
	#emit stor.s.pri address
	return RelToWide(address, wide);
}

/// <library>amx_assembly phys_memory</library>
stock ReadPhysMemory(address, dest[], num = sizeof(dest)) {
	const cells0 = 3 * cellbytes;
	new rel_addr = AbsToRel(address);

	// Current destination cell address.
	new cur_dest = 0;
	#emit load.s.pri dest
	#emit stor.s.pri cur_dest

	// Currently reading address.
	new cur_addr = rel_addr;

	// Read num cells to dest.
	for (new i = 0; i < num; i++, cur_addr += cellbytes, cur_dest += cellbytes) {
		#emit lref.s.pri cur_addr
		#emit sref.s.pri cur_dest
	}

	#emit stack cells0
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly phys_memory</library>
stock WritePhysMemory(address, src[], num = sizeof(src)) {
	const cells0 = 3 * cellbytes;
	new rel_addr = AbsToRel(address);

	// Current destination cell address..
	new cur_src = 0;
	#emit load.s.pri src
	#emit stor.s.pri cur_src

	// Currently reading address.
	new cur_addr = rel_addr;

	// Write num cells from src.
	for (new i = 0; i < num; i++, cur_addr += cellbytes, cur_src += cellbytes) {
		#emit lref.s.pri cur_src
		#emit sref.s.pri cur_addr
	}

	#emit stack cells0
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly phys_memory</library>
stock ReadPhysMemoryCell(address) {
	const cells0 = 1 * cellbytes;
	new rel_addr = AbsToRel(address);
	#emit lref.s.pri rel_addr
	#emit stack cells0
	#emit retn
	return 0; // make compiler happy
}

/// <library>amx_assembly phys_memory</library>
stock WritePhysMemoryCell(address, what) {
	const cells0 = 1 * cellbytes;
	new rel_addr = AbsToRel(address);
	#emit load.s.pri what
	#emit sref.s.pri rel_addr
	#emit stack cells0
	#emit retn
	return 0; // make compiler happy
}


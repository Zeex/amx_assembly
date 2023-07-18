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

#if defined HEAP_ALLOC_INC
	#endinput
#endif
#define HEAP_ALLOC_INC

/**
 * <library name="amx_assembly heap_alloc" summary="AMX Assembly Library: Allocate space in the heap.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "amx_memory"

#define HeapAlloc HeapAllocCells

/// <library>amx_assembly heap_alloc</library>
/// <summary>
///   Allocates a block of (uninitialized) memory on the heap.
/// </summary>
stock HeapAllocBytes(nbytes) {
	new address = 0;
	#emit lctrl __hea
	#emit stor.s.pri address
	#emit load.s.alt nbytes
	#emit add
	#emit sctrl __hea
	return address;
}

/// <library>amx_assembly heap_alloc</library>
/// <summary>
///   Same as HeapAllocBytes() but operates on cells.
/// </summary>
stock HeapAllocCells(ncells) {
	return HeapAllocBytes(ncells * cellbytes);
}

/// <library>amx_assembly heap_alloc</library>
/// <summary>
///   Releases memory allocated with HeapAlloc().
/// </summary>
stock HeapRelease(address) {
	#emit load.s.pri address
	#emit sctrl __hea
	return address;
}


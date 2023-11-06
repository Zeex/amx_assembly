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

#if defined AMX_MEMORY_INC
	#endinput
#endif
#define AMX_MEMORY_INC

/**
 * <library name="amx_assembly amx_memory" summary="AMX Assembly Library: AMX data segment manipulation.">
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

#if defined __PawnBuild
	#if __PawnBuild == 0
		#undef __PawnBuild
		#define __pawn_build 0
	#else
		#define __pawn_build __PawnBuild
	#endif
#else
	#define __pawn_build 0
#endif

#if !defined cellbytes
	const cellbytes = cellbits / charbits;
#endif

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

/// <library>amx_assembly amx_memory</library>
/// <summary>
///   Returns the address of a variable/array.
/// </summary>
stock ref(...) {
	const cells0 = 3 * cellbytes;
	assert(numargs() == 1);
	#emit load.s.pri cells0 // first argument
	#emit retn
	return 0; // make compiler happy
}

/// <library>amx_assembly amx_memory</library>
/// <summary>
///   Returns an array from an address.
/// </summary>
stock deref(v) {
	const cells0 = 4 * cellbytes;
	static gFake[1];
	#emit load.s.pri  v // first argument
	#emit stor.s.pri cells0 // secret argument
	#emit retn
	return gFake; // make compiler happy
}

/// <library>amx_assembly amx_memory</library>
/// <summary>
///   Returns the address of a variable parameter.
/// </summary>
stock argref(n) {
	#emit load.s.alt 0
	#emit load.s.pri n
	#emit add.c 3
	#emit lidx
	#emit retn
	return 0; // make compiler happy
}

/// <library>amx_assembly amx_memory</library>
/// <summary>
///   Returns an array from a variable parameter.
/// </summary>
stock argderef(n) {
	const cells0 = 4 * cellbytes;
	static gFake[1];
	#emit load.s.alt 0
	#emit load.s.pri n
	#emit add.c 3
	#emit lidx
	#emit stor.s.pri cells0 // secret argument
	#emit retn
	return gFake; // make compiler happy
}

#if __pawn_build >= 10
	stock gAmxAssemblyAddress_;
	#define ReadAmxMemory(%0) __emit(load.u.pri %0, stor.pri gAmxAssemblyAddress_, lref.pri gAmxAssemblyAddress_)
	#define WriteAmxMemory(%0,%1) __emit(push.u %1, load.u.pri %0, stor.pri gAmxAssemblyAddress_, pop.pri, sref.pri gAmxAssemblyAddress_)
#endif

/// <library>amx_assembly amx_memory</library>
stock ReadAmxMemoryArray(address, values[], size = sizeof(values)) {
	for (new i = 0; i < size; i++) {
		values[i] = ReadAmxMemory(address);
		address += cellbytes;
	}
}

/// <library>amx_assembly amx_memory</library>
stock WriteAmxMemoryArray(address, const values[], size = sizeof(values)) {
	for (new i = 0; i < size; i++) {
		WriteAmxMemory(address, values[i]);
		address += cellbytes;
	}
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxNextInstructionPointer()
{
	// Saying "get the current pointer" doesn't make a huge amount of sense -
	// getting the pointer will in itself take code, so exactly where is "here"?
	// This returns its own return address, which points to the instruction
	// directly after the call.  This is at least well defined.
	const cells0 = 1 * cellbytes;
	#emit load.s.pri cells0 // Return address.
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxHeapBase() {
	const cells0 = 5 * cellbytes;
	const cells1 = -1 * cellbytes;
	const cells2 = 1 * cellbytes;
	// Initial heap pointer.  Not stored in an accessible register so read it
	// straight from the original header.
	#emit lctrl __dat  // DAT
	#emit neg          // -DAT
	#emit add.c cells0 // -DAT + 20
	#emit push.pri
	#emit lref.s.pri cells1
	#emit stack cells2
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxHeapTop()
{
	// Current heap pointer.
	#emit lctrl __hea
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxStackBase()
{
	#emit lctrl __stp
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxStackBottom() {
	const cells0 = 3 * cellbytes;
	#emit lctrl __stk
	#emit add.c cells0
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock GetAmxFrame()
{
	// Doesn't use "lctrl 5" because we want it to look like this function was
	// never called.  Doing that would only return this function's frame.
	#emit load.s.pri 0
	#emit retn
	return 0;
}

/// <library>amx_assembly amx_memory</library>
stock SetAmxHeapTop(ptr)
{
	#emit load.s.pri ptr
	#emit sctrl __hea
}

/// <library>amx_assembly amx_memory</library>
stock SetAmxStackBottom(ptr) {
	const cells0 = 1 * cellbytes;
	static cip = 0;
	// We need to be tricky here, because the return value is on the stack.
	#emit load.s.alt ptr
	// Store the return address.
	#emit load.s.pri cells0
	#emit stor.pri cip
	// Reset the frame.
	#emit load.s.pri 0
	#emit sctrl __frm
	// Modify the stack.
	#emit move.pri
	#emit sctrl __stk
	// Return.
	#emit load.pri cip
	#emit sctrl __jmp
	#emit sctrl __cip
}

/// <library>amx_assembly amx_memory</library>
stock SetAmxFrame(ptr) {
	const cells0 = 1 * cellbytes;
	const cells1 = 4 * cellbytes;
	// We need to be tricky here, because the return value is in our frame.
	// Store the return address.
	#emit load.s.alt cells0
	// Modify the frame.
	#emit load.s.pri ptr
	#emit sctrl __frm
	// Return.
	#emit move.pri
	#emit stack cells1
	#emit sctrl __jmp
	#emit sctrl __cip
}

/// <library>amx_assembly amx_memory</library>
stock SetAmxNextInstructionPointer(ptr) {
	const cells0 = 4 * cellbytes;
	#emit load.s.alt ptr
	// Reset the frame.
	#emit load.s.pri 0
	#emit sctrl __frm
	// Return.
	#emit move.pri
	#emit stack cells0
	#emit sctrl __jmp
	#emit sctrl __cip
}

#if __pawn_build >= 10
	#endinput
#endif

// After `#endif` because `#if` doesn't elide `#emit`.
/// <library>amx_assembly amx_memory</library>
stock WriteAmxMemory(address, value) {
	#emit load.s.pri value
	#emit sref.s.pri address
	#emit retn
	return 0; // make compiler happy
}

/// <library>amx_assembly amx_memory</library>
stock ReadAmxMemory(address) {
	#emit lref.s.pri address
	#emit retn
	return 0; // make compiler happy
}


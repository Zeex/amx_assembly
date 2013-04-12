// Copyright (C) 2013 Zeex
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

#if defined STACK_ALLOC_INC
	#endinput
#endif
#define STACK_ALLOC_INC

// Allocate a continuous block of (uninitialized) memory on the stack.
#define StackAllocBytes(%0) StackAlloc_SetStackPtr(StackAlloc_GetStackPtr() - (%0))
#define StackAllocCells(%0) StackAllocBytes((%0) * 4)
#define StackAlloc StackAllocCells

// Releases memory allocated with StackAllocXXX().
#define StackRelease(%0) StackAlloc_SetStackPtr(%0)

stock StackAlloc_SetStackPtr(address) {
	static arg_size;
	static ret_addr;
	static old_frm;

	// Get size of arguments from the stack.
	#emit load.s.pri 8
	#emit stor.pri arg_size

	// Get return address from the stack.
	#emit load.s.pri 4
	#emit stor.pri ret_addr

	// Get old frame address from the stack.
	#emit load.s.pri 0
	#emit stor.pri old_frm

	// Set both FRM and STK to address.
	#emit load.s.pri address
	#emit sctrl 4
	#emit sctrl 5

	// Copy our stuff to the new location.
	#emit load.pri arg_size
	#emit stor.s.pri 8
	#emit load.pri ret_addr
	#emit stor.s.pri 4
	#emit load.pri old_frm
	#emit stor.s.pri 0

	// Compute address of the newly allocated block.
	#emit lctrl 4
	#emit add.c 0xfffffff4
	#emit retn

	return 0; // make compiler happy
}

stock StackAlloc_GetStackPtr() {
	#emit lctrl 5
	#emit add.c 0xfffffff4
	#emit retn
	return 0; // make compiler happy
}

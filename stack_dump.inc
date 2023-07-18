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

#if defined STACK_DUMP_INC
	#endinput
#endif
#define STACK_DUMP_INC

/**
 * <library name="amx_assembly stack_dump" summary="AMX Assembly Library: Stack dumps.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#if !defined _samp_included
	#tryinclude <console>
#endif

//-----------------------------------------------
//                  Stack layout
//-----------------------------------------------
//          what       |   stack pointer (STK)
//-----------------------------------------------
//       <STACK TOP>   |        STP
//           ...       |      STP - 4
//           ...       |      STP - 8
//           ...       |        ...
//       argument_N    |     FRM + 4*(N+3)
//           ...       |        ...
//       argument_2    |     FRM + 16
//       argument_1    |     FRM + 12
//          4*N        |     FRM + 8
//       RET address   |     FRM + 4
//         old FRM     |     FRM
//                     |
//-------------- N E W  F R A M E ---------------
//                     |
//       local_var_1   |     FRM - 4
//       local_var_2   |     FRM - 8
//           ...       |        ...
//       local_var_M   |     FRM - 4*M
//          ...        |        ...
//          ...        |         8
//          ...        |         4
//        <BOTTOM>     |         0
//-----------------------------------------------

#include "amx_memory"
#include "frame_info"
#include "stack_trace"

/// <library>amx_assembly stack_dump</library>
stock DumpStack()
{
	new stp = 0, stk = 0;

	#emit lctrl __stp
	#emit stor.s.pri stp
	#emit lctrl __stk
	#emit stor.s.pri stk

	print("------------------------");
	print("Stack dump:");
	print("------------------------");

	// Skip locals + FRM + RETN address + paramcount.
	stk += 5 * cellbytes;

	// Don't print above the top of the stack.
	new i = stp;
	printf("[0x%08x]: TOP", i);
	i -= cellbytes;
	for ( ; i >= stk; i -= cellbytes) {
		printf("[0x%08x]: 0x%08x", i, ReadAmxMemory(i));
	}

	print("------------------------");
}

/// <library>amx_assembly stack_dump</library>
stock DumpFullStack()
{
	new stp = 0, stk = 0;

	#emit lctrl __stp
	#emit stor.s.pri stp
	#emit lctrl __stk
	#emit stor.s.pri stk

	// Skip locals + FRM + RETN address + paramcount (to this point in this
	// function, hence "3 + 2").
	stk += 5 * cellbytes;

	print("----------------------------------------");
	print("| Stack dump (bottom):                 |");
	print("----------------------------------------");

	// "next" and "previous" are going to get confusing here!  We are walking UP
	// the stack, so all the function calls are from that POV.  However, the API
	// we're using is from the POV of code execution with the stack growing
	// DOWN, so the names are reversed.
	new localSize = 0;
	new parameterSize = 0;
	new previousFrame = GetCurrentFrame();
	new currentFrame = GetFramePreviousFrame(previousFrame);
	new returnAddress = 0;
	do
	{
		previousFrame = currentFrame;
		currentFrame = GetFramePreviousFrame(previousFrame);
		returnAddress = GetFrameReturn(previousFrame);
		// Still the parameter count from the previous function.
		//localSize = previousFrame - currentFrame + (3 * cellbytes) - parameterSize;
		parameterSize = GetFrameParameterSize(previousFrame);
		// Can be done, but slower (re-iterates from the top of the stack).
		localSize = GetFrameLocalSize(previousFrame);
		
		new name[64];
		new address = GetFunctionFromReturnAddress(returnAddress);
		if (GetPublicNameFromAddress(address, name)) {
			printf("|   %32s   |", name);
		} else {
			printf("|                 ????                 |");
		}
		
		printf("| Locals (%2d):                         |", localSize / cellbytes);
		while (localSize)
		{
			printf("|     %08x: %08x               |", stk, ReadAmxMemory(stk));
			stk += cellbytes;
			localSize -= cellbytes;
		}
		
		printf("| Frame:                               |");
		printf("|     %08x: %08x               |", stk, ReadAmxMemory(stk));
		stk += cellbytes;
		printf("| Return:                              |");
		printf("|     %08x: %08x               |", stk, ReadAmxMemory(stk));
		stk += cellbytes;
		printf("| Count:                               |");
		printf("|     %08x: %08x               |", stk, ReadAmxMemory(stk));
		stk += cellbytes;
		printf("| Parameters (%2d):                     |", parameterSize / cellbytes);
		while (parameterSize > 0)
		{
			printf("|     %08x: %08x               |", stk, ReadAmxMemory(stk));
			stk += cellbytes;
			parameterSize -= cellbytes;
		}
		print("----------------------------------------");
	}
	while (currentFrame);
}


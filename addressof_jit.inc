// Copyright (C) 2016 Y_Less
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

#if defined ADDRESSOF_JIT_INC
	#endinput
#endif
#define ADDRESSOF_JIT_INC

/**
 * <library name="amx_assembly addressof_jit" summary="AMX Assembly Library: `addressof` JIT code.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
///   <remarks>
///     <c>addressof</c> works by reading data directly out of the stack to get
///     a return address, then reading information from that location in memory
///     to get the next <c>CALL</c> OpCode.  This fails with the JIT because the
///     return address is in the JITed code, not in the original p-code.
///     Instead, when the JIT is in use, use <em>codescan</em> to convert
///     runtime <c>addressof</c> calls to startup-time resolutions.  Actually,
///     there's no reason why this should be restricted to JIT only.
///   </remarks>
 * </library>
 */

/// <p/>

#include "addressof"
#include "codescan"
#include "asm"

/// <library>amx_assembly addressof_jit</library>
static stock AddressofResolveFoundStart(const scanner[CodeScanner]) {
	// Skip over now superfluous code.
	new ctx[AsmContext];
	CodeScanGetMatchAsm(scanner, ctx);
	new
		hdr[AMX_HDR];
	GetAmxHeader(hdr);
	AsmEmitJump(ctx, CodeScanGetMatchHole(scanner, 0) + GetAmxBaseAddress() + hdr[AMX_HDR_COD]);
}

/// <library>amx_assembly addressof_jit</library>
static stock AddressofResolveFoundEnd(const scanner[CodeScanner]) {
	// Write a `const` for the function address.
	new ctx[AsmContext];
	CodeScanGetMatchAsm(scanner, ctx, CodeScanGetMatchLength(scanner) - 2 * cellbytes);
	AsmEmitConstPri(ctx, CodeScanGetMatchHole(scanner, 0));
}

/// <library>amx_assembly addressof_jit</library>
stock AddressofResolve() {
	static
		bool:gAddressofResolved = false;
	if (gAddressofResolved)
		return;
	gAddressofResolved = true;
	// Scan through the entire assembly and replace calls to `addressof` with
	// just a constant.  The generated assembly is amazingly consistent between
	// different optimisation levels:
	//   
	//       push.c 0      // Make `jump l.185`
	//       call .O@A_
	//       jzer 185      // Jump target.
	//       push.c 0      // (tested function call).
	//       call .MyFunc  // (tested function call).
	//       load.pri 2950
	//       jzer 187
	//       const.pri 1
	//       jump 188
	//   l.187
	//       const.pri 2
	//   l.188
	//       jump 186
	//   l.185
	//       load.pri 2950 // Make `const.pri .MyFunc`
	//   l.186
	//   
	// We can actually use `addressof` (via `&`) in this code, since it should
	// NEVER be called after the JIT has started.  We assert that.
	assert(!GetAmxJITBaseAddress());
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	// Start.
	new csm1[CodeScanMatcher];
	CodeScanMatcherInit(csm1, &AddressofResolveFoundStart);
	CodeScanMatcherPattern(csm1,
		OP(PUSH_C,     0)
		OP(CALL,       &AddressOfGetNextCall_)
		OP(JZER,       ???)
	);
	CodeScanAddMatcher(scanner, csm1);
	
	// End.
	new csm2[CodeScanMatcher];
	CodeScanMatcherInit(csm2, &AddressofResolveFoundEnd);
	CodeScanMatcherPattern(csm2,
		OP(CALL,       ???)
		OP(LOAD_PRI,   ref(gAddressOfReturnVar_))
		OP(JZER,       ???)
		OP(CONST_PRI,  1)
		OP(JUMP,       ???)
		OP(CONST_PRI,  2)
		OP(JUMP,       ???)
		OP(LOAD_PRI,   ref(gAddressOfReturnVar_))
	);
	CodeScanAddMatcher(scanner, csm2);
	
	// End with heap.
	new csm3[CodeScanMatcher];
	CodeScanMatcherInit(csm3, &AddressofResolveFoundEnd);
	CodeScanMatcherPattern(csm3,
		OP(CALL,       ???)
		OP(HEAP,       ???)
		OP(LOAD_PRI,   ref(gAddressOfReturnVar_))
		OP(JZER,       ???)
		OP(CONST_PRI,  1)
		OP(JUMP,       ???)
		OP(CONST_PRI,  2)
		OP(JUMP,       ???)
		OP(LOAD_PRI,   ref(gAddressOfReturnVar_))
	);
	CodeScanAddMatcher(scanner, csm3);
	
	// Run the scanner.
	CodeScanRunFast(scanner, &AddressOfGetNextCall_);
}


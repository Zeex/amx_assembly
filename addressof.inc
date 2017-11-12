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

#if defined ADDRESSOF_INC
	#endinput
#endif
#define ADDRESSOF_INC

#include "frame_info"
#include "disasm"

// This code uses two nested conditionals because of:
// https://github.com/Zeex/pawn/issues/96 (this doesn't work):
//   
//   (O@A_() ? ((CALL@%1), 0) : (O@V_))
//   
// Even though it is the obvious solution when you don't want the result of
// "CALL@%1" to be used (as it may not exist), and you can't use a constant
// instead of "O@V_" because then if becomes a constant in a
// condition, which the compiler rightly complains about.  Of course, because
// "O@A_()" always returns "false", the entire other block of code
// is jumped over.
#define addressof(%1) (O@A_()?(((CALL@%1),O@V_)?1:2):(O@V_))
#define CALL@%0\32; CALL@

#define gAddressOfReturnVar_ O@V_
#define AddressOfGetNextCall_ O@A_
#define CALL@AddressOfGetNextCall_ CALL@O@A_
#define CALL@O@A_ O@A_()

#define O@A_()?(((CALL@%1<%2>),O@V_)?1:2):(O@V_) TAG@%2:(O@A_()?(((CALL@%1),O@V_)?1:2):(O@V_))
#define TAG@%0\32; TAG@

stock
	REF,
	gAddressOfReturnVar_ = 0;

stock bool:AddressOfGetNextCall_() {
	// Start reading code from the point to which this function returns, looking
	// for the next "CALL" op to signal the function call from the macro.
	new ctx[DisasmContext];
	DisasmInit(ctx, GetCurrentFrameReturn());
	while (DisasmNext(ctx)) {
		if (DisasmGetOpcode(ctx) == OP_CALL) {
			// Return the data in a global, to be repassed from the conditional.
			gAddressOfReturnVar_ = DisasmGetOperandReloc(ctx);
			return false;
		}
	}
	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}


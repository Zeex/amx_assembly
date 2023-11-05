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

/**
 * <library name="amx_assembly addressof" summary="AMX Assembly Library: `addressof` function address lookup.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "frame_info"
#include "disasm"
#include "addressof_light"

#if defined AMX_OLD_CALL
	#endinput
#endif

#define nativeidxof(%1) (_:((O@D_:O@B_())?(((CALL@%1()),O@V_)?1:2):(O@V_)))

#define NativeIdxOfGetNextCall_ O@B_
#define CALL@NativeIdxOfGetNextCall_%8() CALL@O@B_%8()
#define CALL@O@B_%8() O@B_%8()

#define O@B_())?(((CALL@%1<%2>()),O@V_)?1:2):(O@V_) O@B_())?(((_ADDR@$%1()<%2>),O@V_)?(F@_@:1):(F@_@:2)):(F@_@:O@V_)

// Convert `On` tests to string-based.
#define O@D_:%0_())?(((CALL@On%1()),O@V_)?1:2):(O@V_)) O@G_:%0@("On"#%1)))
#define O@G_:%0("On"#%1<%9>))) %0("On"#%1)))

// Generate an example call, then extract the parameters from it.
#define prototypeof(%1) (_:CALL@%1:M@:N@:O@C_:$()(F@_@:A@=F@_@:tagof(F@_@:)))

// Strip internal spaces.
#define M@:%8$(%0\32;%1)( M@:%8$(%0%1)(

// No parameters (end).
#define N@:%8$()

// Give the call a trailing comma, and start the macros.
#define O@C_:$(%0) O@E_:N@:$(%0,)

// Detect the end of the parameter list.
#define O@E_:%8$(%0,%7)( O@H_:(%0)O@E_:%8$(%7)(

// Detect common parameter types.  The extra `0` is to distinguish between `0`
// and `0.0`.  The first will have the macro name changed, the second won't.
#define O@H_:(%0) P@%00:
#define P@""0:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4s:A@=%4s:tagof(%4s:))
#define P@__REF0:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4v:A@=%4v:tagof(%4v:))
#define P@__ARR0:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4s:A@=%4s:tagof(%4s:))
#define P@0.00:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4f:A@=%4f:tagof(%4f:))
#define P@00:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4i:A@=%4i:tagof(%4i:))
#define P@true0:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4i:A@=%4i:tagof(%4i:))
#define P@false0:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4i:A@=%4i:tagof(%4i:))
#define P@__minus10:%8$(%7)(%4:A@=%4:tagof(%4:)) %8$(%7)(%4i:A@=%4i:tagof(%4i:))

#define P@Text: P@
#define P@PlayerText: P@
#define P@Float: P@
#define P@File: P@
#define P@bool: P@

// For internal tag creation.
stock A@ = 0;

/// <library>amx_assembly addressof</library>
stock bool:NativeIdxOfGetNextCall_() {
	// Start reading code from the point to which this function returns, looking
	// for the next "CALL" op to signal the function call from the macro.
	new ctx[DisasmContext];
	DisasmInit(ctx, GetCurrentFrameReturn());
	new candidate = -1;
	while (DisasmNext(ctx)) {
#if OPCODE_HAS_O2
		if (ctx[DisasmContext_opcode] == OP_SYSREQ_C || ctx[DisasmContext_opcode] == OP_SYSREQ_N) {
#else
		if (ctx[DisasmContext_opcode] == OP_SYSREQ_C) {
#endif
			// Return the data in a global, to be repassed from the conditional.
			candidate = DisasmGetOperand(ctx);
		}
		else if (ctx[DisasmContext_opcode] == OP_JZER && candidate != -1) {
			// Get the last `SYSREQ.C` before the branch.  Because some calls
			// may invoke additional natives in their stubbing, most notably
			// `float(0)` in e.g. `nativeidxof(floatmul<ii>)`.
			gAddressOfReturnVar_ = candidate;
			return false;
		}
	}
	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}


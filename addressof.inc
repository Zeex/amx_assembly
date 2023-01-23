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

// This is a horrible hack, I'm sorry for ruining your nice clean
// library with references to YSI Zeex!  It was (probably not) the only
// way to detect some issues people were having and alert them to it,
// plus it is completely optional.
#if defined __YSI_CALL_UPGRADED
	// Check if YSI is updated to the new `CALL@` syntax.
	#if defined AMX_OLD_CALL
			#error amx_assembly and YSI are correctly matched; don't use `#define AMX_OLD_CALL`.
	#endif
#elseif defined __COMPILER_PASS
	// Check if any version of YSI is included.  This macro name is ancient.
	#if !defined AMX_OLD_CALL
		#error amx_assembly and YSI are mismatched.  Update YSI, downgrade amx_assembly, or use `#define AMX_OLD_CALL`.
	#endif
#endif

#define __AMX_CALL_UPGRADED

// This code uses two nested conditionals because of:
// https://github.com/Zeex/pawn/issues/96 (this doesn't work):
//   
//   ((O@D_:O@A_()) ? ((CALL@%1()), 0) : (O@V_))
//   
// Even though it is the obvious solution when you don't want the result of
// "CALL@%1()" to be used (as it may not exist), and you can't use a constant
// instead of "O@V_" because then if becomes a constant in a
// condition, which the compiler rightly complains about.  Of course, because
// "O@A_()" always returns "false", the entire other block of code
// is jumped over.
#if defined AMX_OLD_CALL
	#define addressof(%1) (O@A_()?(((CALL@%1),O@V_)?1:2):(O@V_))
	#define CALL@%0\32; CALL@

	#define gAddressOfReturnVar_ O@V_
	#define AddressOfGetNextCall_ O@A_
	#define CALL@AddressOfGetNextCall_ CALL@O@A_
	#define CALL@O@A_ O@A_()

	#define O@A_()?(((CALL@%1<%2>),O@V_)?1:2):(O@V_) (O@A_()?(((_ADDR@$%1()<%2>),O@V_)?(F@_@:1):(F@_@:2)):(F@_@:O@V_))
#else
	#define addressof(%1) ((O@D_:O@A_())?(((CALL@%1()),O@V_)?1:2):(O@V_))
	#define CALL@%0\32; CALL@

	#define gAddressOfReturnVar_ O@V_
	#define AddressOfGetNextCall_ O@A_
	#define CALL@AddressOfGetNextCall_%8() CALL@O@A_%8()
	#define CALL@O@A_%8() O@A_%8()
	#define CALL@O@A@%8() O@A@%8("")

	#define O@A_())?(((CALL@%1<%2>()),O@V_)?1:2):(O@V_) O@A_())?(((_ADDR@$%1()<%2>),O@V_)?(F@_@:1):(F@_@:2)):(F@_@:O@V_)
#endif

// Enable parameter checks for `Func<xxx>` types.
#define _ADDR@ _ADDR@i:_ADDR@t:_ADDR@f:_ADDR@v:_ADDR@s:_ADDR@a:_ADDR@x:_ADDR@z

#define _ADDR@z$%0(%1)<%2> _ADDR@y:%0(%1)
#define _ADDR@y:%0(,%1) %0(%1)

#define _ADDR@i:%8$%0(%1)<i%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,0)<%2>),O@V_)?(%9i:1):(%9i:2)):(%9i:O@V_))
#define _ADDR@t:%8$%0(%1)<t%5:%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,%5:0)<%2>),O@V_)?(%9i:1):(%9i:2)):(%9i:O@V_))
#define _ADDR@f:%8$%0(%1)<f%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,0.0)<%2>),O@V_)?(%9f:1):(%9f:2)):(%9f:O@V_))
#define _ADDR@v:%8$%0(%1)<v%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,__REF)<%2>),O@V_)?(%9v:1):(%9v:2)):(%9v:O@V_))
#define _ADDR@s:%8$%0(%1)<s%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,__ARR)<%2>),O@V_)?(%9s:1):(%9s:2)):(%9s:O@V_))
#define _ADDR@a:%8$%0(%1)<a%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@$%0(%1,__ARR)<%2>),O@V_)?(%9a:1):(%9a:2)):(%9a:O@V_))
#define _ADDR@x:%8$%0(%1)<x%2>),O@V_)?(%9:1):(%9:2)):(%9:O@V_)) _ADDR@z$%0(%1)<>),O@V_)?(%9x:1):(%9x:2)):(%9x:O@V_))

/// <library>amx_assembly addressof</library>
stock __ARR[1] = {};

/// <library>amx_assembly addressof</library>
stock __REF = 0;

/// <library>amx_assembly addressof</library>
stock gAddressOfReturnVar_ = 0;

/// <library>amx_assembly addressof</library>
stock bool:AddressOfGetNextCall_() {
	// Start reading code from the point to which this function returns, looking
	// for the next "CALL" op to signal the function call from the macro.
	new ctx[DisasmContext];
	DisasmInit(ctx, GetCurrentFrameReturn());
	while (DisasmNext(ctx)) {
		if (ctx[DisasmContext_opcode] == OP_CALL) {
			// Return the data in a global, to be repassed from the conditional.
			gAddressOfReturnVar_ = DisasmGetOperandReloc(ctx);
			return false;
		}
	}
	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}

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
	while (DisasmNext(ctx)) {
#if OPCODE_HAS_O2
		if (ctx[DisasmContext_opcode] == OP_SYSREQ_C || ctx[DisasmContext_opcode] == OP_SYSREQ_N) {
#else
		if (ctx[DisasmContext_opcode] == OP_SYSREQ_C) {
#endif
			// Return the data in a global, to be repassed from the conditional.
			gAddressOfReturnVar_ = DisasmGetOperand(ctx);
			return false;
		}
	}
	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}


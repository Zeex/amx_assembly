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

#if defined ADDRESSOF_LIGHT_INC
	#endinput
#endif
#define ADDRESSOF_LIGHT_INC

/**
 * <library name="amx_assembly addressof_light" summary="AMX Assembly Library: `addressof` function address lookup, with fewer dependencies.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#if !defined cellbytes
	const cellbytes = cellbits / charbits;
#endif

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

// For future compiler version.  TODO: Figure out `<tTag:>` in this syntax.
//#define addressof __addressof
//#define __addressof(%0<%1>) (F@_@%1:__addressof(%0))

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

/// <library>amx_assembly addressof_light</library>
stock __ARR[1] = {};

/// <library>amx_assembly addressof_light</library>
stock __REF = 0;

/// <library>amx_assembly addressof_light</library>
stock gAddressOfReturnVar_ = 0;

/// <library>amx_assembly addressof_light</library>
forward bool:AddressOfGetNextCall_();

//stock bool:AddressOfGetNextCall_() {
//	// Start reading code from the point to which this function returns, looking
//	// for the next "CALL" op to signal the function call from the macro.
//	new ctx[DisasmContext];
//	DisasmInit(ctx, GetCurrentFrameReturn());
//	while (DisasmNext(ctx)) {
//		if (ctx[DisasmContext_opcode] == OP_CALL) {
//			// Return the data in a global, to be repassed from the conditional.
//			gAddressOfReturnVar_ = DisasmGetOperandReloc(ctx);
//			return false;
//		}
//	}
//	// ALWAYS returns false so that the function call within "OP(&func)" will
//	// never be called thanks to the conditional.
//	return false;
//}

/// <library>amx_assembly addressof_light</library>
stock bool:AddressOfGetNextCall_() {
	static OpCode:call = OpCode:0;
	static reloc = 0;
	static offset = 0;

	// Get the return address.
	new addr;
	const cellsRetn = 1 * cellbytes;

	// Get the `CALL` OpCode from two cells before this call.
	if (call) {
		#emit load.s.alt cellsRetn
		#emit load.pri offset
		#emit sub.alt
		#emit stor.s.pri addr
	} else {
		#emit lctrl 0
		#emit move.alt
		#emit lctrl 1
		#emit sub
		#emit stor.pri offset
		#emit load.s.alt cellsRetn
		#emit sub.alt
		#emit stor.s.pri addr

		// `CALL` is opcode 49, which is an odd number.  So we don't need to
		// worry about conflicts with variable's addresses.  Subtract two cells
		// from the return address to get the initial `CALL`.
		addr -= 2 * cellbytes;
		#emit lref.s.pri addr
		#emit stor.pri call

		addr += 1 * cellbytes;
		// Get the jump offset by using this function.
		#emit lref.s.pri addr
		#emit const.alt O@A_ // AddressOfGetNextCall_
		#emit sub
		#emit stor.pri reloc
	}

	for ( ; ; ) {
		// We can skip the first cell after the return.  It cannot ever be the
		// `CALL` op.
		addr += 1 * cellbytes;
		#emit lref.s.pri addr
		#emit stor.pri O@V_ // gAddressOfReturnVar_
		if (OpCode:gAddressOfReturnVar_ == call) {
			addr += 1 * cellbytes;
			// TODO: Reloc.
			#emit lref.s.pri addr
			#emit load.alt reloc
			#emit sub
			#emit stor.pri O@V_ // gAddressOfReturnVar_
			break;
		}
	}

	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}


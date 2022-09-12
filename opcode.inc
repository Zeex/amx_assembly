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

#if defined OPCODE_INC
	#endinput
#endif
#define OPCODE_INC

/**
 * <library name="amx_assembly opcode" summary="AMX Assembly Library: Information on all PAWN opcodes.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "amx_header"

#if __Pawn >= 0x30A
	// Disable the recursion warning in the Russian compiler.
	#pragma warning push
	#pragma warning disable 207
	#pragma disablerecursion
	#pragma warning pop
	
	// Disable the recursion warning in the fast compiler.
	#pragma warning disable 238
#endif

#define OPCODE_HAS_O2 0
#if defined __optimization
	#if __optimization == 2
		#undef OPCODE_HAS_O2
		#define OPCODE_HAS_O2 1
	#endif
#endif

#define OPCODE_MAX_INSN_NAME 15

/// <p/>

/// <library>amx_assembly opcode</library>
enum Opcode {
  OP_NONE,         OP_LOAD_PRI,     OP_LOAD_ALT,
  OP_LOAD_S_PRI,   OP_LOAD_S_ALT,   OP_LREF_PRI,
  OP_LREF_ALT,     OP_LREF_S_PRI,   OP_LREF_S_ALT,
  OP_LOAD_I,       OP_LODB_I,       OP_CONST_PRI,
  OP_CONST_ALT,    OP_ADDR_PRI,     OP_ADDR_ALT,
  OP_STOR_PRI,     OP_STOR_ALT,     OP_STOR_S_PRI,
  OP_STOR_S_ALT,   OP_SREF_PRI,     OP_SREF_ALT,
  OP_SREF_S_PRI,   OP_SREF_S_ALT,   OP_STOR_I,
  OP_STRB_I,       OP_LIDX,         OP_LIDX_B,
  OP_IDXADDR,      OP_IDXADDR_B,    OP_ALIGN_PRI,
  OP_ALIGN_ALT,    OP_LCTRL,        OP_SCTRL,
  OP_MOVE_PRI,     OP_MOVE_ALT,     OP_XCHG,
  OP_PUSH_PRI,     OP_PUSH_ALT,     OP_PUSH_R,
  OP_PUSH_C,       OP_PUSH,         OP_PUSH_S,
  OP_POP_PRI,      OP_POP_ALT,      OP_STACK,
  OP_HEAP,         OP_PROC,         OP_RET,
  OP_RETN,         OP_CALL,         OP_CALL_PRI,
  OP_JUMP,         OP_JREL,         OP_JZER,
  OP_JNZ,          OP_JEQ,          OP_JNEQ,
  OP_JLESS,        OP_JLEQ,         OP_JGRTR,
  OP_JGEQ,         OP_JSLESS,       OP_JSLEQ,
  OP_JSGRTR,       OP_JSGEQ,        OP_SHL,
  OP_SHR,          OP_SSHR,         OP_SHL_C_PRI,
  OP_SHL_C_ALT,    OP_SHR_C_PRI,    OP_SHR_C_ALT,
  OP_SMUL,         OP_SDIV,         OP_SDIV_ALT,
  OP_UMUL,         OP_UDIV,         OP_UDIV_ALT,
  OP_ADD,          OP_SUB,          OP_SUB_ALT,
  OP_AND,          OP_OR,           OP_XOR,
  OP_NOT,          OP_NEG,          OP_INVERT,
  OP_ADD_C,        OP_SMUL_C,       OP_ZERO_PRI,
  OP_ZERO_ALT,     OP_ZERO,         OP_ZERO_S,
  OP_SIGN_PRI,     OP_SIGN_ALT,     OP_EQ,
  OP_NEQ,          OP_LESS,         OP_LEQ,
  OP_GRTR,         OP_GEQ,          OP_SLESS,
  OP_SLEQ,         OP_SGRTR,        OP_SGEQ,
  OP_EQ_C_PRI,     OP_EQ_C_ALT,     OP_INC_PRI,
  OP_INC_ALT,      OP_INC,          OP_INC_S,
  OP_INC_I,        OP_DEC_PRI,      OP_DEC_ALT,
  OP_DEC,          OP_DEC_S,        OP_DEC_I,
  OP_MOVS,         OP_CMPS,         OP_FILL,
  OP_HALT,         OP_BOUNDS,       OP_SYSREQ_PRI,
  OP_SYSREQ_C,     OP_FILE,         OP_LINE,
  OP_SYMBOL,       OP_SRANGE,       OP_JUMP_PRI,
  OP_SWITCH,       OP_CASETBL,      OP_SWAP_PRI,
  OP_SWAP_ALT,     OP_PUSH_ADR,     OP_NOP,
  OP_SYSREQ_D,     OP_SYMTAG,       OP_BREAK,
#if OPCODE_HAS_O2
  OP_PUSH2_C,      OP_PUSH2,        OP_PUSH2_S,
  OP_PUSH2_ADR,    OP_PUSH3_C,      OP_PUSH3,
  OP_PUSH3_S,      OP_PUSH3_ADR,    OP_PUSH4_C,
  OP_PUSH4,        OP_PUSH4_S,      OP_PUSH4_ADR,
  OP_PUSH5_C,      OP_PUSH5,        OP_PUSH5_S,
  OP_PUSH5_ADR,    OP_LOAD_BOTH,    OP_LOAD_S_BOTH,
  OP_CONST,        OP_CONST_S,      OP_SYSREQ_N,
#endif
  OP_LAST_
};

/// <library>amx_assembly opcode</library>
const Opcode:Opcode__ = Opcode;

// Doesn't work inline.
#if OPCODE_HAS_O2
	#define OPCODE_O2_PARAMETER_COUNTS , 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 2, 2, 2, 2, 2
#else
	#define OPCODE_O2_PARAMETER_COUNTS
#endif

/// <library>amx_assembly opcode</library>
stock const gAMXOpcodeParameterCounts[] = {
	0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1,
	0, 1, 1, 0, 0, 1, 0, 1, 1, 0
	OPCODE_O2_PARAMETER_COUNTS
};

// Doesn't work inline.
#if OPCODE_HAS_O2
	#define OPCODE_O2_NEEDS_RELOC , false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false, false
#else
	#define OPCODE_O2_NEEDS_RELOC
#endif

/// <library>amx_assembly opcode</library>
stock const gAMXOpcodeNeedsReloc[] = {
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, true , false, true ,
	false, true , true , true , true , true , true , true , true , true , true , true , true ,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, false,
	false, false, false, false, false, false, false, false, false, false, false, false, true ,
	true , false, false, false, false, false, false, false
	OPCODE_O2_NEEDS_RELOC
};

// Doesn't work inline.
#if OPCODE_HAS_O2
	#define OPCODE_O2_NAMES , "push2.c", "push2", "push2.s", "push2.adr", "push3.c", "push3", "push3.s", "push3.adr", "push4.c", "push4", "push4.s", "push4.adr", "push5.c", "push5", "push5.s", "push5.adr", "load.both", "load.s.both", "const", "const.s", "sysreq.n"
#else
	#define OPCODE_O2_NAMES
#endif

/// <library>amx_assembly opcode</library>
stock const gAMXOpcodeNames[][OPCODE_MAX_INSN_NAME] = {
	"none", "load.pri", "load.alt", "load.s.pri", "load.s.alt", "lref.pri", "lref.alt",
	"lref.s.pri", "lref.s.alt", "load.i", "lodb.i", "const.pri", "const.alt", "addr.pri",
	"addr.alt", "stor.pri", "stor.alt", "stor.s.pri", "stor.s.alt", "sref.pri", "sref.alt",
	"sref.s.pri", "sref.s.alt", "stor.i", "strb.i", "lidx", "lidx.b", "idxaddr", "idxaddr.b",
	"align.pri", "align.alt", "lctrl", "sctrl", "move.pri", "move.alt", "xchg", "push.pri",
	"push.alt", "push.r", "push.c", "push", "push.s", "pop.pri", "pop.alt", "stack", "heap", "proc",
	"ret", "retn", "call", "call.pri", "jump", "jrel", "jzer", "jnz", "jeq", "jneq", "jless",
	"jleq", "jgrtr", "jgeq", "jsless", "jsleq", "jsgrtr", "jsgeq", "shl", "shr", "sshr",
	"shl.c.pri", "shl.c.alt", "shr.c.pri", "shr.c.alt", "smul", "sdiv", "sdiv.alt", "umul", "udiv",
	"udiv.alt", "add", "sub", "sub.alt", "and", "or", "xort", "not", "neg", "invert", "add.c",
	"smul.c", "zero.pri", "zero.alt", "zero", "zero.s", "sign.pri", "sign.alt", "eq", "neq", "less",
	"leq", "grtr", "geq", "sless", "sleq", "sgrtr", "sgeq", "eq.c.pri", "eq.c.alt", "inc.pri",
	"inc.alt", "inc", "inc.s", "inc.i", "dec.pri", "dec.alt", "dec", "dec.s", "dec.i", "movs",
	"cmps", "fill", "halt", "bounds", "sysreq.pri", "sysreq.c", "file", "line", "symbol", "srange",
	"jump.pri", "switch", "casetbl", "swap.pri", "swap.alt", "push.adr", "nop", "sysreq.d",
	"symtag", "break"
	OPCODE_O2_NAMES
};

// Doesn't work inline.
#if OPCODE_HAS_O2
	#define OPCODE_O2_BASE_SIZES , 3 * cellbytes, 3 * cellbytes, 3 * cellbytes, 3 * cellbytes, 4 * cellbytes, 4 * cellbytes, 4 * cellbytes, 4 * cellbytes, 5 * cellbytes, 5 * cellbytes, 5 * cellbytes, 5 * cellbytes, 6 * cellbytes, 6 * cellbytes, 6 * cellbytes, 6 * cellbytes, 3 * cellbytes, 3 * cellbytes, 3 * cellbytes, 3 * cellbytes, 3 * cellbytes
#else
	#define OPCODE_O2_BASE_SIZES
#endif

/// <library>amx_assembly opcode</library>
stock const gAMXOpcodeBaseSizes[] = {
	1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes,
	2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes,
	2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes,
	1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes, 2 * cellbytes,
	1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes, 1 * cellbytes, 2 * cellbytes, 1 * cellbytes, 2 * cellbytes, 2 * cellbytes, 1 * cellbytes
	OPCODE_O2_BASE_SIZES
};

/// <library>amx_assembly opcode</library>
const NUM_OPCODES = _:OP_LAST_;

/// <library>amx_assembly opcode</library>
static stock Opcode:ReadOpcodeNearThis(offset = 0) {
	const cells0 = 1 * cellbytes;
	const cells1 = 1 * cellbytes;
	new ret_addr = 0;

	// Get return address + COD - DAT + offset.
	#emit load.s.alt cells0
	#emit lctrl 0
	#emit add
	#emit move.alt
	#emit lctrl 1
	#emit xchg
	#emit sub
	#emit load.s.alt offset
	#emit add

	#emit stor.s.pri ret_addr
	#emit lref.s.pri ret_addr

	#emit stack cells1
	#emit retn

	return OP_NONE; // make compiler happy
}

/// <library>amx_assembly opcode</library>
static stock bool:HaveToRelocateOpcodes() {
	return ReadOpcodeNearThis(-2 * cellbytes) != OP_CALL;
}

/// <library>amx_assembly opcode</library>
/// <remarks>
///   Separate the macro opcodes for `-O2`.
/// </remarks>
#if OPCODE_HAS_O2
	forward Opcode:RelocateMacroOpcodeNow(Opcode:opcode);
#endif

/// <library>amx_assembly opcode</library>
/// <remarks>
///   Based on this idea: http://forum.sa-mp.com/showthread.php?t=358084
/// </remarks>
stock Opcode:RelocateOpcodeNow(Opcode:opcode) {
	if (!HaveToRelocateOpcodes()) {
		return opcode;
	}
	switch (opcode) {
		case OP_LOAD_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.pri 0
		}
		case OP_LOAD_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.alt 0
		}
		case OP_LOAD_S_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.s.pri 0
		}
		case OP_LOAD_S_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.s.alt 0
		}
		case OP_LREF_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lref.pri 0
		}
		case OP_LREF_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lref.alt 0
		}
		case OP_LREF_S_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lref.s.pri 0
		}
		case OP_LREF_S_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lref.s.alt 0
		}
		case OP_LOAD_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.i
		}
		case OP_LODB_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lodb.i 1
		}
		case OP_CONST_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit const.pri 0
		}
		case OP_CONST_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit const.alt 0
		}
		case OP_ADDR_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit addr.pri 0
		}
		case OP_ADDR_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit addr.alt 0
		}
		case OP_STOR_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stor.pri 0
		}
		case OP_STOR_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stor.alt 0
		}
		case OP_STOR_S_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stor.s.pri 0
		}
		case OP_STOR_S_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stor.s.alt 0
		}
		case OP_SREF_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sref.pri 0
		}
		case OP_SREF_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sref.alt 0
		}
		case OP_SREF_S_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sref.s.pri 0
		}
		case OP_SREF_S_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sref.s.alt 0
		}
		case OP_STOR_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stor.i
		}
		case OP_STRB_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit strb.i 1
		}
		case OP_LIDX: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lidx
		}
		case OP_LIDX_B: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lidx.b 0
		}
		case OP_IDXADDR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit idxaddr
		}
		case OP_IDXADDR_B: {
			return ReadOpcodeNearThis(cellbytes);
			#emit idxaddr.b 0
		}
		case OP_ALIGN_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit align.pri 0
		}
		case OP_ALIGN_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit align.alt 0
		}
		case OP_LCTRL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit lctrl 0
		}
		case OP_SCTRL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sctrl 0
		}
		case OP_MOVE_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit move.pri
		}
		case OP_MOVE_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit move.alt
		}
		case OP_XCHG: {
			return ReadOpcodeNearThis(cellbytes);
			#emit xchg
		}
		case OP_PUSH_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push.pri
		}
		case OP_PUSH_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push.alt
		}
		case OP_PUSH_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push.c 0
		}
		case OP_PUSH: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push 0
		}
		case OP_PUSH_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push.s 0
		}
		case OP_POP_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit pop.pri
		}
		case OP_POP_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit pop.alt
		}
		case OP_STACK: {
			return ReadOpcodeNearThis(cellbytes);
			#emit stack 0
		}
		case OP_HEAP: {
			return ReadOpcodeNearThis(cellbytes);
			#emit heap 0
		}
		case OP_PROC: {
			return ReadOpcodeNearThis(cellbytes);
			#emit proc
		}
		case OP_RET: {
			return ReadOpcodeNearThis(cellbytes);
			#emit ret
		}
		case OP_RETN: {
			return ReadOpcodeNearThis(cellbytes);
			#emit retn
		}
		case OP_CALL: {
			// We can't do just "#emit call 0" - this will crash compiler for some reason (bug?).
			return ReadOpcodeNearThis(-2 * cellbytes);
		}
		case OP_JUMP: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jump 0
		}
		case OP_JZER: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jzer 0
		}
		case OP_JNZ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jnz 0
		}
		case OP_JEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jeq 0
		}
		case OP_JNEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jneq 0
		}
		case OP_JLESS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jless 0
		}
		case OP_JLEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jleq 0
		}
		case OP_JGRTR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jgrtr 0
		}
		case OP_JGEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jgeq 0
		}
		case OP_JSLESS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jsless 0
		}
		case OP_JSLEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jsleq 0
		}
		case OP_JSGRTR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jsgrtr 0
		}
		case OP_JSGEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit jsgeq 0
		}
		case OP_SHL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shl
		}
		case OP_SHR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shr
		}
		case OP_SSHR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sshr
		}
		case OP_SHL_C_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shl.c.pri 0
		}
		case OP_SHL_C_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shl.c.alt 0
		}
		case OP_SHR_C_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shr.c.pri 0
		}
		case OP_SHR_C_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit shr.c.alt 0
		}
		case OP_SMUL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit smul
		}
		case OP_SDIV: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sdiv
		}
		case OP_SDIV_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sdiv.alt
		}
		case OP_UMUL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit umul
		}
		case OP_UDIV: {
			return ReadOpcodeNearThis(cellbytes);
			#emit udiv
		}
		case OP_UDIV_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit udiv.alt
		}
		case OP_ADD: {
			return ReadOpcodeNearThis(cellbytes);
			#emit add
		}
		case OP_SUB: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sub
		}
		case OP_SUB_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sub.alt
		}
		case OP_AND: {
			return ReadOpcodeNearThis(cellbytes);
			#emit and
		}
		case OP_OR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit or
		}
		case OP_XOR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit xor
		}
		case OP_NOT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit not
		}
		case OP_NEG: {
			return ReadOpcodeNearThis(cellbytes);
			#emit neg
		}
		case OP_INVERT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit invert
		}
		case OP_ADD_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit add.c 0
		}
		case OP_SMUL_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit smul.c 0
		}
		case OP_ZERO_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit zero.pri
		}
		case OP_ZERO_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit zero.alt
		}
		case OP_ZERO: {
			return ReadOpcodeNearThis(cellbytes);
			#emit zero 0
		}
		case OP_ZERO_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit zero.s 0
		}
		case OP_SIGN_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sign.pri
		}
		case OP_SIGN_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sign.alt
		}
		case OP_EQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit eq
		}
		case OP_NEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit neq
		}
		case OP_LESS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit less
		}
		case OP_LEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit leq
		}
		case OP_GRTR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit grtr
		}
		case OP_GEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit geq
		}
		case OP_SLESS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sless
		}
		case OP_SLEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sleq
		}
		case OP_SGRTR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sgrtr
		}
		case OP_SGEQ: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sgeq
		}
		case OP_EQ_C_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit eq.c.pri 0
		}
		case OP_EQ_C_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit eq.c.alt 0
		}
		case OP_INC_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit inc.pri
		}
		case OP_INC_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit inc.alt
		}
		case OP_INC: {
			return ReadOpcodeNearThis(cellbytes);
			#emit inc 0
		}
		case OP_INC_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit inc.s 0
		}
		case OP_INC_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit inc.i
		}
		case OP_DEC_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit dec.pri
		}
		case OP_DEC_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit dec.alt
		}
		case OP_DEC: {
			return ReadOpcodeNearThis(cellbytes);
			#emit dec 0
		}
		case OP_DEC_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit dec.s 0
		}
		case OP_DEC_I: {
			return ReadOpcodeNearThis(cellbytes);
			#emit dec.i
		}
		case OP_MOVS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit movs 0
		}
		case OP_CMPS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit cmps 0
		}
		case OP_FILL: {
			return ReadOpcodeNearThis(cellbytes);
			#emit fill 0
		}
		case OP_HALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit halt 0
		}
		case OP_BOUNDS: {
			return ReadOpcodeNearThis(cellbytes);
			#emit bounds 0
		}
		case OP_SYSREQ_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sysreq.c 0
		}
		case OP_SWITCH: {
			static T = 1;
			#if debug > 0
				if (T) return ReadOpcodeNearThis(3 * cellbytes);
			#else
				if (T) return ReadOpcodeNearThis(2 * cellbytes);
			#endif
			#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
				// Disable `switch control expression is constant`.
				#pragma warning push
				#pragma warning disable 243
			#endif
			switch (0) {
				case 0: {}
			}
			#if ((__Pawn & 0x0F) >= 0x0A) || ((__Pawn & 0xF0) >= 0xA0)
				#pragma warning pop
			#endif
		}
		case OP_CASETBL: {
			new x = 0;
			switch (x) { case 0: return ReadOpcodeNearThis(5 * cellbytes); }
		}
		case OP_SWAP_PRI: {
			return ReadOpcodeNearThis(cellbytes);
			#emit swap.pri
		}
		case OP_SWAP_ALT: {
			return ReadOpcodeNearThis(cellbytes);
			#emit swap.alt
		}
		case OP_PUSH_ADR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push.adr 0
		}
		case OP_NOP: {
			return ReadOpcodeNearThis(cellbytes);
			#emit nop
		}
		case OP_SYSREQ_D: {
			if (HasSysreqD()) {
				// Since there's no way to #emit sysreq.d we have to compute its
				// address using a relative offset to another opcode, e.g. nop.
				new bool:is_crashdetect = false;
				#emit zero.pri
				#emit lctrl 0xFF
				#emit stor.s.pri is_crashdetect
				if (is_crashdetect) {
					// The offset is different when running under crashdetect as
					// it uses its own (modified) version of the VM. This value
					// value works only with crashdetect 4.13.
					return RelocateOpcodeNow(OP_NOP) - Opcode:0x1EA;
				} else {
					return RelocateOpcodeNow(OP_NOP) - Opcode:0x4F;
				}
			} else {
				return RelocateOpcodeNow(OP_NOP);
			}
		}
		case OP_BREAK: {
			return ReadOpcodeNearThis(cellbytes);
			#emit break
		}
#if OPCODE_HAS_O2
		default: {
			return RelocateMacroOpcodeNow(opcode);
		}
#endif
	}
	return opcode;
}

/// <library>amx_assembly opcode</library>
static stock Opcode:opcode_table[NUM_OPCODES];

/// <library>amx_assembly opcode</library>
static stock bool:opcode_table_is_ready = false;

/// <library>amx_assembly opcode</library>
stock bool:IsOpcodeValid(Opcode:opcode) {
	return (OP_NONE <= opcode < Opcode:NUM_OPCODES);
}

/// <library>amx_assembly opcode</library>
static stock InitOpcodeTable() {
	for (new i = 0; i < NUM_OPCODES; i++) {
		opcode_table[i] = RelocateOpcodeNow(Opcode:i);
	}
	opcode_table_is_ready = true;
}

/// <library>amx_assembly opcode</library>
stock Opcode:RelocateOpcode(Opcode:opcode) {
	if (!opcode_table_is_ready) {
		InitOpcodeTable();
	}
	return opcode_table[_:opcode];
}

/// <library>amx_assembly opcode</library>
stock bool:IsOpcodeRelocationRequired() {
	return RelocateOpcode(OP_LOAD_PRI) != OP_LOAD_PRI;
}

/// <library>amx_assembly opcode</library>
stock Opcode:UnrelocateOpcode(Opcode:opcode) {
	if (!opcode_table_is_ready) {
		InitOpcodeTable();
	}
#if OPCODE_HAS_O2
	if (opcode == OP_SYSREQ_D) {
		// These share the same raw ID in the server.
		return HasSysreqD() ? OP_SYSREQ_D : OP_SYSREQ_N;
	}
#endif
	if (OP_NONE <= opcode < Opcode:NUM_OPCODES) {
		return opcode;
	}
	for (new i = 0; i < NUM_OPCODES; i++) {
		if (opcode_table[i] == opcode) {
			return Opcode:i;
		}
	}
	return opcode;
}

/// <library>amx_assembly opcode</library>
stock GetOpcodeInstructionName(Opcode:opcode) {
	static const ret[OPCODE_MAX_INSN_NAME] = "none";
	if (OP_NONE < opcode < Opcode:NUM_OPCODES) {
		return gAMXOpcodeNames[_:opcode];
	}
	return ret;
}

/// <library>amx_assembly opcode</library>
stock GetOpcodeInstructionParameters(Opcode:opcode) {
	if (OP_NONE < opcode < Opcode:NUM_OPCODES) {
		return gAMXOpcodeParameterCounts[_:opcode];
	}
	return 0;
}

/// <library>amx_assembly opcode</library>
stock bool:GetOpcodeInstructionRelocatable(Opcode:opcode) {
	if (OP_NONE < opcode < Opcode:NUM_OPCODES) {
		return gAMXOpcodeNeedsReloc[_:opcode];
	}
	return false;
}

#if !OPCODE_HAS_O2
	// some compilers can't have `#emit` in `#if` so end the file.
	#endinput
#endif

stock Opcode:RelocateMacroOpcodeNow(Opcode:opcode)
{
	switch (opcode) {
		case OP_PUSH2_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push2.c 0 0
		}
		case OP_PUSH2: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push2 0 0
		}
		case OP_PUSH2_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push2.s 0 0
		}
		case OP_PUSH2_ADR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push2.adr 0 0
		}
		case OP_PUSH3_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push3.c 0 0 0
		}
		case OP_PUSH3: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push3 0 0 0
		}
		case OP_PUSH3_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push3.s 0 0 0
		}
		case OP_PUSH3_ADR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push3.adr 0 0 0
		}
		case OP_PUSH4_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push4.c 0 0 0 0
		}
		case OP_PUSH4: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push4 0 0 0 0
		}
		case OP_PUSH4_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push4.s 0 0 0 0
		}
		case OP_PUSH4_ADR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push4.adr 0 0 0 0
		}
		case OP_PUSH5_C: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push5.c 0 0 0 0 0
		}
		case OP_PUSH5: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push5 0 0 0 0 0
		}
		case OP_PUSH5_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push5.s 0 0 0 0 0
		}
		case OP_PUSH5_ADR: {
			return ReadOpcodeNearThis(cellbytes);
			#emit push5.adr 0 0 0 0 0
		}
		case OP_LOAD_BOTH: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.both 0 0
		}
		case OP_LOAD_S_BOTH: {
			return ReadOpcodeNearThis(cellbytes);
			#emit load.s.both 0 0
		}
		case OP_CONST: {
			return ReadOpcodeNearThis(cellbytes);
			#emit const 0 0
		}
		case OP_CONST_S: {
			return ReadOpcodeNearThis(cellbytes);
			#emit const.s 0 0
		}
		case OP_SYSREQ_N: {
			return ReadOpcodeNearThis(cellbytes);
			#emit sysreq.n 0 0
		}
	}
	return opcode;
}


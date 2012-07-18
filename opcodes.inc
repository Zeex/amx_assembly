// Copyright (C) 2012 Zeex
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

#if defined OPCODES_INC
	#endinput
#endif
#define OPCODES_INC

enum Opcode {
	OP_NONE,              /* invalid opcode */
	OP_LOAD_PRI,
	OP_LOAD_ALT,
	OP_LOAD_S_PRI,
	OP_LOAD_S_ALT,
	OP_LREF_PRI,
	OP_LREF_ALT,
	OP_LREF_S_PRI,
	OP_LREF_S_ALT,
	OP_LOAD_I,
	OP_LODB_I,
	OP_CONST_PRI,
	OP_CONST_ALT,
	OP_ADDR_PRI,
	OP_ADDR_ALT,
	OP_STOR_PRI,
	OP_STOR_ALT,
	OP_STOR_S_PRI,
	OP_STOR_S_ALT,
	OP_SREF_PRI,
	OP_SREF_ALT,
	OP_SREF_S_PRI,
	OP_SREF_S_ALT,
	OP_STOR_I,
	OP_STRB_I,
	OP_LIDX,
	OP_LIDX_B,
	OP_IDXADDR,
	OP_IDXADDR_B,
	OP_ALIGN_PRI,
	OP_ALIGN_ALT,
	OP_LCTRL,
	OP_SCTRL,
	OP_MOVE_PRI,
	OP_MOVE_ALT,
	OP_XCHG,
	OP_PUSH_PRI,
	OP_PUSH_ALT,
	OP_PUSH_R,
	OP_PUSH_C,
	OP_PUSH,
	OP_PUSH_S,
	OP_POP_PRI,
	OP_POP_ALT,
	OP_STACK,
	OP_HEAP,
	OP_PROC,
	OP_RET,
	OP_RETN,
	OP_CALL,
	OP_CALL_PRI,
	OP_JUMP,
	OP_JREL,
	OP_JZER,
	OP_JNZ,
	OP_JEQ,
	OP_JNEQ,
	OP_JLESS,
	OP_JLEQ,
	OP_JGRTR,
	OP_JGEQ,
	OP_JSLESS,
	OP_JSLEQ,
	OP_JSGRTR,
	OP_JSGEQ,
	OP_SHL,
	OP_SHR,
	OP_SSHR,
	OP_SHL_C_PRI,
	OP_SHL_C_ALT,
	OP_SHR_C_PRI,
	OP_SHR_C_ALT,
	OP_SMUL,
	OP_SDIV,
	OP_SDIV_ALT,
	OP_UMUL,
	OP_UDIV,
	OP_UDIV_ALT,
	OP_ADD,
	OP_SUB,
	OP_SUB_ALT,
	OP_AND,
	OP_OR,
	OP_XOR,
	OP_NOT,
	OP_NEG,
	OP_INVERT,
	OP_ADD_C,
	OP_SMUL_C,
	OP_ZERO_PRI,
	OP_ZERO_ALT,
	OP_ZERO,
	OP_ZERO_S,
	OP_SIGN_PRI,
	OP_SIGN_ALT,
	OP_EQ,
	OP_NEQ,
	OP_LESS,
	OP_LEQ,
	OP_GRTR,
	OP_GEQ,
	OP_SLESS,
	OP_SLEQ,
	OP_SGRTR,
	OP_SGEQ,
	OP_EQ_C_PRI,
	OP_EQ_C_ALT,
	OP_INC_PRI,
	OP_INC_ALT,
	OP_INC,
	OP_INC_S,
	OP_INC_I,
	OP_DEC_PRI,
	OP_DEC_ALT,
	OP_DEC,
	OP_DEC_S,
	OP_DEC_I,
	OP_MOVS,
	OP_CMPS,
	OP_FILL,
	OP_HALT,
	OP_BOUNDS,
	OP_SYSREQ_PRI,
	OP_SYSREQ_C,
	OP_FILE,    /* obsolete */
	OP_LINE,    /* obsolete */
	OP_SYMBOL,  /* obsolete */
	OP_SRANGE,  /* obsolete */
	OP_JUMP_PRI,
	OP_SWITCH,
	OP_CASETBL,
	OP_SWAP_PRI,
	OP_SWAP_ALT,
	OP_PUSHADDR,
	OP_NOP,
	OP_SYSREQ_D,
	OP_SYMTAG,  /* obsolete */
	OP_BREAK,
	/* ----- */
	NUM_OPCODES
};

static stock Opcode:ReadOpcodeNextToThis(offset = 0) {
	// Get return address + COD - DAT + offset.
	#emit load.s.alt 4
	#emit lctrl 0
	#emit add
	#emit move.alt
	#emit lctrl 1
	#emit xchg
	#emit sub
	#emit load.s.alt offset
	#emit add

	new ret_addr;
	#emit stor.s.pri ret_addr
	#emit lref.s.pri ret_addr

	#emit stack 4
	#emit retn

	return OP_NONE; // make compiler happy
}

#define __ return ReadOpcodeNextToThis(4);

static stock Unreachable() {
	new z = 0;
	assert(z);
}

// Based on this idea: http://forum.sa-mp.com/showthread.php?t=358084
stock Opcode:RelocateOpcode(Opcode:opcode) {
	switch (opcode) {
		case OP_LOAD_PRI: { __
			#emit load.pri 0
		}
		case OP_LOAD_ALT: { __
			#emit load.alt 0
		}
		case OP_LOAD_S_PRI: { __
			#emit load.s.pri 0
		}
		case OP_LOAD_S_ALT: { __
			#emit load.s.alt 0
		}
		case OP_LREF_PRI: { __
			#emit lref.pri 0
		}
		case OP_LREF_ALT: { __
			#emit lref.alt 0
		}
		case OP_LREF_S_PRI: { __
			#emit lref.s.pri 0
		}
		case OP_LREF_S_ALT: { __
			#emit lref.s.alt 0
		}
		case OP_LOAD_I: { __
			#emit load.i
		}
		case OP_LODB_I: { __
			#emit lodb.i 1
		}
		case OP_CONST_PRI: { __
			#emit const.pri 0
		}
		case OP_CONST_ALT: { __
			#emit const.alt 0
		}
		case OP_ADDR_PRI: { __
			#emit addr.pri 0
		}
		case OP_ADDR_ALT: { __
			#emit addr.alt 0
		}
		case OP_STOR_PRI: { __
			#emit stor.pri 0
		}
		case OP_STOR_ALT: { __
			#emit stor.alt 0
		}
		case OP_STOR_S_PRI: { __
			#emit stor.s.pri 0
		}
		case OP_STOR_S_ALT: { __
			#emit stor.s.alt 0
		}
		case OP_SREF_PRI: { __
			#emit sref.pri 0
		}
		case OP_SREF_ALT: { __
			#emit sref.alt 0
		}
		case OP_SREF_S_PRI: { __
			#emit sref.s.pri 0
		}
		case OP_SREF_S_ALT: { __
			#emit sref.s.alt 0
		}
		case OP_STOR_I: { __
			#emit stor.i
		}
		case OP_STRB_I: { __
			#emit strb.i 1
		}
		case OP_LIDX: { __
			#emit lidx
		}
		case OP_LIDX_B: { __
			#emit lidx.b 0
		}
		case OP_IDXADDR: { __
			#emit idxaddr
		}
		case OP_IDXADDR_B: { __
			#emit idxaddr.b 0
		}
		case OP_ALIGN_PRI: { __
			#emit align.pri 0
		}
		case OP_ALIGN_ALT: { __
			#emit align.alt 0
		}
		case OP_LCTRL: { __
			#emit lctrl 0
		}
		case OP_SCTRL: { __
			#emit sctrl 0
		}
		case OP_MOVE_PRI: { __
			#emit move.pri
		}
		case OP_MOVE_ALT: { __
			#emit move.alt
		}
		case OP_XCHG: { __
			#emit xchg
		}
		case OP_PUSH_PRI: { __
			#emit push.pri
		}
		case OP_PUSH_ALT: { __
			#emit push.alt
		}
		case OP_PUSH_C: { __
			#emit push.c 0
		}
		case OP_PUSH: { __
			#emit push 0
		}
		case OP_PUSH_S: { __
			#emit push.s 0
		}
		case OP_POP_PRI: { __
			#emit pop.pri
		}
		case OP_POP_ALT: { __
			#emit pop.alt
		}
		case OP_STACK: { __
			#emit stack 0
		}
		case OP_HEAP: { __
			#emit heap 0
		}
		case OP_PROC: { __
			#emit proc
		}
		case OP_RET: { __
			#emit ret
		}
		case OP_RETN: { __
			#emit retn
		}
		//case OP_CALL: { __
			//#emit call
		//}
		case OP_JUMP: { __
			#emit jump 0
		}
		case OP_JREL: { __
			#emit jrel 0
		}
		case OP_JZER: { __
			#emit jzer 0
		}
		case OP_JNZ: { __
			#emit jnz 0
		}
		case OP_JEQ: { __
			#emit jeq 0
		}
		case OP_JNEQ: { __
			#emit jneq 0
		}
		case OP_JLESS: { __
			#emit jless 0
		}
		case OP_JLEQ: { __
			#emit jleq 0
		}
		case OP_JGRTR: { __
			#emit jgrtr 0
		}
		case OP_JGEQ: { __
			#emit jgeq 0
		}
		case OP_JSLESS: { __
			#emit jsless 0
		}
		case OP_JSLEQ: { __
			#emit jsleq 0
		}
		case OP_JSGRTR: { __
			#emit jsgrtr 0
		}
		case OP_JSGEQ: { __
			#emit jsgeq 0
		}
		case OP_SHL: { __
			#emit shl
		}
		case OP_SHR: { __
			#emit shr
		}
		case OP_SSHR: { __
			#emit sshr
		}
		case OP_SHL_C_PRI: { __
			#emit shl.c.pri 0
		}
		case OP_SHL_C_ALT: { __
			#emit shl.c.alt 0
		}
		case OP_SHR_C_PRI: { __
			#emit shr.c.pri 0
		}
		case OP_SHR_C_ALT: { __
			#emit shr.c.alt 0
		}
		case OP_SMUL: { __
			#emit smul
		}
		case OP_SDIV: { __
			#emit sdiv
		}
		case OP_SDIV_ALT: { __
			#emit sdiv.alt
		}
		case OP_UMUL: { __
			#emit umul
		}
		case OP_UDIV: { __
			#emit udiv
		}
		case OP_UDIV_ALT: { __
			#emit udiv.alt
		}
		case OP_ADD: { __
			#emit add
		}
		case OP_SUB: { __
			#emit sub
		}
		case OP_SUB_ALT: { __
			#emit sub.alt
		}
		case OP_AND: { __
			#emit and
		}
		case OP_OR: { __
			#emit or
		}
		case OP_XOR: { __
			#emit xor
		}
		case OP_NOT: { __
			#emit not
		}
		case OP_NEG: { __
			#emit neg
		}
		case OP_INVERT: { __
			#emit invert
		}
		case OP_ADD_C: { __
			#emit add.c 0
		}
		case OP_SMUL_C: { __
			#emit smul.c 0
		}
		case OP_ZERO_PRI: { __
			#emit zero.pri
		}
		case OP_ZERO_ALT: { __
			#emit zero.alt
		}
		case OP_ZERO: { __
			#emit zero 0
		}
		case OP_ZERO_S: { __
			#emit zero.s 0
		}
		case OP_SIGN_PRI: { __
			#emit sign.pri
		}
		case OP_SIGN_ALT: { __
			#emit sign.alt
		}
		case OP_EQ: { __
			#emit eq
		}
		case OP_NEQ: { __
			#emit neq
		}
		case OP_LESS: { __
			#emit less
		}
		case OP_LEQ: { __
			#emit leq
		}
		case OP_GRTR: { __
			#emit grtr
		}
		case OP_GEQ: { __
			#emit geq
		}
		case OP_SLESS: { __
			#emit sless
		}
		case OP_SLEQ: { __
			#emit sleq
		}
		case OP_SGRTR: { __
			#emit sgrtr
		}
		case OP_SGEQ: { __
			#emit sgeq
		}
		case OP_EQ_C_PRI: { __
			#emit eq.c.pri 0
		}
		case OP_EQ_C_ALT: { __
			#emit eq.c.alt 0
		}
		case OP_INC_PRI: { __
			#emit inc.pri
		}
		case OP_INC_ALT: { __
			#emit inc.alt
		}
		case OP_INC: { __
			#emit inc 0
		}
		case OP_INC_S: { __
			#emit inc.s 0
		}
		case OP_INC_I: { __
			#emit inc.i
		}
		case OP_DEC_PRI: { __
			#emit dec.pri
		}
		case OP_DEC_ALT: { __
			#emit dec.alt
		}
		case OP_DEC: { __
			#emit dec 0
		}
		case OP_DEC_S: { __
			#emit dec.s 0
		}
		case OP_DEC_I: { __
			#emit dec.i
		}
		case OP_MOVS: { __
			#emit movs 0
		}
		case OP_CMPS: { __
			#emit cmps 0
		}
		case OP_FILL: { __
			#emit fill 0
		}
		case OP_HALT: { __
			#emit halt 0
		}
		case OP_BOUNDS: { __
			#emit bounds 0
		}
		case OP_SYSREQ_PRI: { __
			#emit sysreq.pri
		}
		case OP_SYSREQ_C: { __
			#emit sysreq.c 0
		}
		case OP_SWITCH: { __
			#emit switch 0
		}
		case OP_SWAP_PRI: { __
			#emit swap.pri
		}
		case OP_SWAP_ALT: { __
			#emit swap.alt
		}
		case OP_PUSHADDR: { __
			#emit push.adr 0
		}
		case OP_NOP: { __
			#emit nop
		}
		case OP_BREAK: { __
			#emit break
		}
	}
	Unreachable();
	return OP_NONE;
}

static stock Opcode:opcode_list[_:NUM_OPCODES];
static stock bool:opcode_list_is_ready = false;

static stock InitOpcodeList() {
	for (new i = 0; i < _:NUM_OPCODES; i++) {
		opcode_list[i] = RelocateOpcode(Opcode:i);
	}
}

stock GetRelocatedOpcode(Opcode:opcode) {
	if (!opcode_list_is_ready) {
		InitOpcodeList();
	}
	return opcode_list[_:opcode];
}

stock Opcode:UnrelocateOpcode(Opcode:opcode) {
	if (!opcode_list_is_ready) {
		InitOpcodeList();
	}
	if (opcode >= OP_NONE && opcode < NUM_OPCODES) {
		return opcode;
	}
	for (new i = 0; i < _:NUM_OPCODES; i++) {
		if (opcode_list[i] == opcode) {
			return Opcode:i;
		}
	}
	return OP_NONE;
}

#undef __

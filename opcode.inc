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

#include "amx_memory"

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
  OP_LAST_
};

const NUM_OPCODES = _:OP_LAST_;

stock GetOpcodeTable() {
	#emit lctrl 1
	#emit move.alt
	#emit lctrl 0
	#emit sub
	#emit move.alt
	#emit lctrl 6
	#emit add
	#emit add.c 16
	#emit retn
	// --- BEGIN OPCODE TABLE ---
	#emit nop // none
	#emit nop
	#emit load.pri 0
	#emit load.alt 0
	#emit load.s.pri 0
	#emit load.s.alt 0
	#emit lref.pri 0
	#emit lref.alt 0
	#emit lref.s.pri 0
	#emit lref.s.alt 0
	#emit load.i
	#emit nop
	#emit lodb.i 1
	#emit const.pri 0
	#emit const.alt 0
	#emit addr.pri 0
	#emit addr.alt 0
	#emit stor.pri 0
	#emit stor.alt 0
	#emit stor.s.pri 0
	#emit stor.s.alt 0
	#emit sref.pri 0
	#emit sref.alt 0
	#emit sref.s.pri 0
	#emit sref.s.alt 0
	#emit stor.i
	#emit nop
	#emit strb.i 1
	#emit lidx
	#emit nop
	#emit lidx.b 0
	#emit idxaddr
	#emit nop
	#emit idxaddr.b 0
	#emit align.pri 0
	#emit align.alt 0
	#emit lctrl 0
	#emit sctrl 0
	#emit move.pri
	#emit nop
	#emit move.alt
	#emit nop
	#emit xchg
	#emit nop
	#emit push.pri
	#emit nop
	#emit push.alt
	#emit nop
	#emit nop // push.r (obsolete)
	#emit nop
	#emit push.c 0
	#emit push 0
	#emit push.s 0
	#emit pop.pri
	#emit nop
	#emit pop.alt
	#emit nop
	#emit stack 0
	#emit heap 0
	#emit proc
	#emit nop
	#emit ret
	#emit nop
	#emit retn
	#emit nop
	#emit nop // call (compiler bug)
	#emit nop
	#emit nop // call.pri (obsolete)
	#emit nop
	#emit jump 0
	#emit nop // jrel (obsolete)
	#emit nop
	#emit jzer 0
	#emit jnz 0
	#emit jeq 0
	#emit jneq 0
	#emit jless 0
	#emit jleq 0
	#emit jgrtr 0
	#emit jgeq 0
	#emit jsless 0
	#emit jsleq 0
	#emit jsgrtr 0
	#emit jsgeq 0
	#emit shl
	#emit nop
	#emit shr
	#emit nop
	#emit sshr
	#emit nop
	#emit shl.c.pri 0
	#emit shl.c.alt 0
	#emit shr.c.pri 0
	#emit shr.c.alt 0
	#emit smul
	#emit nop
	#emit sdiv
	#emit nop
	#emit sdiv.alt
	#emit nop
	#emit umul
	#emit nop
	#emit udiv
	#emit nop
	#emit udiv.alt
	#emit nop
	#emit add
	#emit nop
	#emit sub
	#emit nop
	#emit sub.alt
	#emit nop
	#emit and
	#emit nop
	#emit or
	#emit nop
	#emit xor
	#emit nop
	#emit not
	#emit nop
	#emit neg
	#emit nop
	#emit invert
	#emit nop
	#emit add.c 0
	#emit smul.c 0
	#emit zero.pri
	#emit nop
	#emit zero.alt
	#emit nop
	#emit zero 0
	#emit zero.s 0
	#emit sign.pri
	#emit nop
	#emit sign.alt
	#emit nop
	#emit eq
	#emit nop
	#emit neq
	#emit nop
	#emit less
	#emit nop
	#emit leq
	#emit nop
	#emit grtr
	#emit nop
	#emit geq
	#emit nop
	#emit sless
	#emit nop
	#emit sleq
	#emit nop
	#emit sgrtr
	#emit nop
	#emit sgeq
	#emit nop
	#emit eq.c.pri 0
	#emit eq.c.alt 0
	#emit inc.pri
	#emit nop
	#emit inc.alt
	#emit nop
	#emit inc 0
	#emit inc.s 0
	#emit inc.i
	#emit nop
	#emit dec.pri
	#emit nop
	#emit dec.alt
	#emit nop
	#emit dec 0
	#emit dec.s 0
	#emit dec.i
	#emit nop
	#emit movs 0
	#emit cmps 0
	#emit fill 0
	#emit halt 0
	#emit bounds 0
	#emit sysreq.pri
	#emit nop
	#emit sysreq.c 0
	#emit nop // file (obsolete)
	#emit nop
	#emit nop // line (obsolete)
	#emit nop
	#emit nop // symbol (obsolete)
	#emit nop
	#emit nop // srange (obsolete)
	#emit nop
	#emit nop // jump.pri (obsolete)
	#emit nop
	#emit switch 0
	#emit nop // casetbl (not emittable)
	#emit nop
	#emit swap.pri
	#emit nop
	#emit swap.alt
	#emit nop
	#emit push.adr 0
	#emit nop // nop itself
	#emit nop
	#emit nop // sysreq.d (not emittable)
	#emit nop
	#emit nop // symtag (obsolete)
	#emit nop
	#emit break
	#emit nop
	// --- END OPCODE TABLE ---
	return 0;
}

stock Opcode:RelocateOpcode(Opcode:opcode) {
	if (OP_NONE <= opcode < Opcode:NUM_OPCODES) {
		new opcode_table = GetOpcodeTable();
		return Opcode:ReadAmxMemory(opcode_table + _:opcode * 8);
	}
	return opcode;
}

stock Opcode:UnrelocateOpcode(Opcode:opcode) {
	if (opcode < OP_NONE || opcode >= Opcode:NUM_OPCODES) {
		new opcode_table = GetOpcodeTable();
		for (new i = 0; i < NUM_OPCODES; i++) {
			if (Opcode:ReadAmxMemory(opcode_table + i * 8) == opcode) {
				return Opcode:i;
			}
		}
	}
	return opcode;
}

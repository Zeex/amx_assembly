// Copyright (C) 2011-2012 Zeex
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

#include <string>

#include "amx_hdr"
#include "dynamic_call"
#include "memory"
#include "phys_memory"

static stock const size_of_cell = cellbits / 8;

// Opcode list from amx.c
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
	OP_NUM_OPCODES
}

#define MAX_INSN_NAME 15

enum Instruction {
	Opcode:op_code,         // opcode from the above list
	op_num_opers,           // the number of operands
	bool:needs_reloc,       // needs relocation?
	op_name[MAX_INSN_NAME]  // character representation, e.g "push.pri"
}

static stock const insn_table[][Instruction] = {
	{ OP_NONE, 0, false, "none" },
	{ OP_LOAD_PRI, 1, false, "load.pri" },
	{ OP_LOAD_ALT, 1, false, "load.alt" },
	{ OP_LOAD_S_PRI, 1, false, "load.s.pri" },
	{ OP_LOAD_S_ALT, 1, false, "load.s.alt" },
	{ OP_LREF_PRI, 1, false, "lref.pri" },
	{ OP_LREF_ALT, 1, false, "lref.alt" },
	{ OP_LREF_S_PRI, 1, false, "lref.s.pri" },
	{ OP_LREF_S_ALT, 1, false, "lref.s.alt" },
	{ OP_LOAD_I, 0, false, "load.i" },
	{ OP_LODB_I, 1, false, "lodb.i" },
	{ OP_CONST_PRI, 1, false, "const.pri" },
	{ OP_CONST_ALT, 1, false, "const.alt" },
	{ OP_ADDR_PRI, 1, false, "addr.pri" },
	{ OP_ADDR_ALT, 1, false, "addr.alt" },
	{ OP_STOR_PRI, 1, false, "stor.pri" },
	{ OP_STOR_ALT, 1, false, "stor.alt" },
	{ OP_STOR_S_PRI, 1, false, "stor.s.pri" },
	{ OP_STOR_S_ALT, 1, false, "stor.s.alt" },
	{ OP_SREF_PRI, 1, false, "sref.pri" },
	{ OP_SREF_ALT, 1, false, "sref.alt" },
	{ OP_SREF_S_PRI, 1, false, "sref.s.pri" },
	{ OP_SREF_S_ALT, 1, false, "sref.s.alt" },
	{ OP_STOR_I, 0, false, "stor.i" },
	{ OP_STRB_I, 1, false, "strb.i" },
	{ OP_LIDX, 0, false, "lidx" },
	{ OP_LIDX_B, 1, false, "lidx.b" },
	{ OP_IDXADDR, 0, false, "idxaddr" },
	{ OP_IDXADDR_B, 1, false, "idxaddr.b" },
	{ OP_ALIGN_PRI, 1, false, "align.pri" },
	{ OP_ALIGN_ALT, 1, false, "align.alt" },
	{ OP_LCTRL, 1, false, "lctrl" },
	{ OP_SCTRL, 1, false, "sctrl" },
	{ OP_MOVE_PRI, 0, false, "move.pri" },
	{ OP_MOVE_ALT, 0, false, "move.alt" },
	{ OP_XCHG, 0, false, "xchg" },
	{ OP_PUSH_PRI, 0, false, "push.pri" },
	{ OP_PUSH_ALT, 0, false, "push.alt" },
	{ OP_PUSH_R, 1, false, "push.r" },
	{ OP_PUSH_C, 1, false, "push.c" },
	{ OP_PUSH, 1, false, "push" },
	{ OP_PUSH_S, 1, false, "push.s" },
	{ OP_POP_PRI, 0, false, "pop.pri" },
	{ OP_POP_ALT, 0, false, "pop.alt" },
	{ OP_STACK, 1, false, "stack" },
	{ OP_HEAP, 1, false, "heap" },
	{ OP_PROC, 0, false, "proc" },
	{ OP_RET, 0, false, "ret" },
	{ OP_RETN, 0, false, "retn" },
	{ OP_CALL, 1, true, "call" },
	{ OP_CALL_PRI, 0, false, "call.pri" },
	{ OP_JUMP, 1, true, "jump" },
	{ OP_JREL, 1, true, "jrel" },
	{ OP_JZER, 1, true, "jzer" },
	{ OP_JNZ, 1, true, "jnz" },
	{ OP_JEQ, 1, true, "jeq" },
	{ OP_JNEQ, 1, true, "jneq" },
	{ OP_JLESS, 1, true, "jless" },
	{ OP_JLEQ, 1, true, "jleq" },
	{ OP_JGRTR, 1, true, "jgrtr" },
	{ OP_JGEQ, 1, true, "jgeq" },
	{ OP_JSLESS, 1, true, "jsless" },
	{ OP_JSLEQ, 1, true, "jsleq" },
	{ OP_JSGRTR, 1, true, "jsgrtr" },
	{ OP_JSGEQ, 1, true, "jsgeq" },
	{ OP_SHL, 0, false, "shl" },
	{ OP_SHR, 0, false, "shr" },
	{ OP_SSHR, 0, false, "sshr" },
	{ OP_SHL_C_PRI, 1, false, "shl.c.pri" },
	{ OP_SHL_C_ALT, 1, false, "shl.c.alt" },
	{ OP_SHR_C_PRI, 1, false, "shr.c.pri" },
	{ OP_SHR_C_ALT, 1, false, "shr.c.alt" },
	{ OP_SMUL, 0, false, "smul" },
	{ OP_SDIV, 0, false, "sdiv" },
	{ OP_SDIV_ALT, 0, false, "sdiv.alt" },
	{ OP_UMUL, 0, false, "umul" },
	{ OP_UDIV, 0, false, "udiv" },
	{ OP_UDIV_ALT, 0, false, "udiv.alt" },
	{ OP_ADD, 0, false, "add" },
	{ OP_SUB, 0, false, "sub" },
	{ OP_SUB_ALT, 0, false, "sub.alt" },
	{ OP_AND, 0, false, "and" },
	{ OP_OR, 0, false, "or" },
	{ OP_XOR, 0, false, "xort" },
	{ OP_NOT, 0, false, "not" },
	{ OP_NEG, 0, false, "neg" },
	{ OP_INVERT, 0, false, "invert" },
	{ OP_ADD_C, 1, false, "add.c" },
	{ OP_SMUL_C, 1, false, "smul.c" },
	{ OP_ZERO_PRI, 0, false, "zero.pri" },
	{ OP_ZERO_ALT, 0, false, "zero.alt" },
	{ OP_ZERO, 1, false, "zero" },
	{ OP_ZERO_S, 1, false, "zero.s" },
	{ OP_SIGN_PRI, 0, false, "sign.pri" },
	{ OP_SIGN_ALT, 0, false, "sign.alt" },
	{ OP_EQ, 0, false, "eq" },
	{ OP_NEQ, 0, false, "neq" },
	{ OP_LESS, 0, false, "less" },
	{ OP_LEQ, 0, false, "leq" },
	{ OP_GRTR, 0, false, "grtr" },
	{ OP_GEQ, 0, false, "geq" },
	{ OP_SLESS, 0, false, "sless" },
	{ OP_SLEQ, 0, false, "sleq" },
	{ OP_SGRTR, 0, false, "sgrtr" },
	{ OP_SGEQ, 0, false, "sgeq" },
	{ OP_EQ_C_PRI, 1, false, "eq.c.pri" },
	{ OP_EQ_C_ALT, 1, false, "eq.c.alt" },
	{ OP_INC_PRI, 0, false, "inc.pri" },
	{ OP_INC_ALT, 0, false, "inc.alt" },
	{ OP_INC, 1, false, "inc" },
	{ OP_INC_S, 1, false, "inc.s" },
	{ OP_INC_I, 0, false, "inc.i" },
	{ OP_DEC_PRI, 0, false, "dec.pri" },
	{ OP_DEC_ALT, 0, false, "dec.alt" },
	{ OP_DEC, 1, false, "dec" },
	{ OP_DEC_S, 1, false, "dec.s" },
	{ OP_DEC_I, 0, false, "dec.i" },
	{ OP_MOVS, 1, false, "movs" },
	{ OP_CMPS, 1, false, "cmps" },
	{ OP_FILL, 1, false, "fill" },
	{ OP_HALT, 1, false, "halt" },
	{ OP_BOUNDS, 1, false, "bounds" },
	{ OP_SYSREQ_PRI, 1, false, "sysreq.pri" },
	{ OP_SYSREQ_C, 1, false, "sysreq.c" },
	{ OP_FILE, -1, false, "file" }, // obsolete
	{ OP_LINE, -1, false, "line" }, // obsolete
	{ OP_SYMBOL, -1, false, "symbol" }, // obsolete
	{ OP_SRANGE, -1, false, "srange" }, // obsolete
	{ OP_JUMP_PRI, 0, false, "jump.pri" },
	{ OP_SWITCH, 1, false, "switch" },
	{ OP_CASETBL, -1, true, "casetbl" },
	{ OP_SWAP_PRI, 0, false, "swap.pri" },
	{ OP_SWAP_ALT, 0, false, "swap.alt" },
	{ OP_PUSHADDR, 1, false, "push.adr" },
	{ OP_NOP, 0, false, "nop" },
	{ OP_SYSREQ_D, 1, false, "sysreq.d" },
	{ OP_SYMTAG, 1, false, "symtag" }, // obsolete
	{ OP_BREAK, 0, false, "break" }
};

enum hex_flags (<<= 1) {
	hex_default = 0,
	hex_prefix,
	hex_sign,
	hex_pad
};

static stock ToHexStr(x, hex_flags:flags = hex_default) {
	new s[11];
	new i = 0;
	new j = 0;

	if (flags & hex_prefix) {
		strcat(s, "0x");
		i += 2;
	}
	while (i < sizeof(s) && j < 8) {
		new n = x >> (7 - j) * 4 & 0xF;
		switch (n) {
			case 0x0..0x9:
				s[i] = n + '0';
			case 0xA..0xF:
				s[i] = n + 'a' - 0xA;
		}
		i++;
		j++;
	}

	return s;
}

static stock bool:IsPrintableAscii(c) {
	return 32 <= c <= 126;
}

static stock ToPrintableAscii(c) {
	if (IsPrintableAscii(c)) {
		return c;
	}
	return ' ';
}

static stock DumpDataRowChar(File:file, start, num, max) {
	new cur = start;
	new end = start + num*size_of_cell;

	while (cur < max) {
		new p[4 char + 1];
		p[0] = @(cur);

		new u[4 + 1];
		u[0] = ToPrintableAscii(p{0});
		u[1] = ToPrintableAscii(p{1});
		u[2] = ToPrintableAscii(p{2});
		u[3] = ToPrintableAscii(p{3});
		u[4] = '\0';

		if (cur < end) {
			fwrite(file, u);
		} else {
			fwrite(file, " ");
		}
		cur += size_of_cell;
	}
}

static stock DumpDataRowHex(File:file, start, num, max) {
	new cur = start;
	new end = start + num*size_of_cell;

	while (cur < max) {
		if (cur < end) {
			fwrite(file, ToHexStr(@(cur), hex_pad));
		} else {
			fwrite(file, "        ");
		}
		fwrite(file, " ");
		cur += size_of_cell;
	}
}

// Disassemble the current AMX script.
stock Disassemble(const out_filename[]) {
	new File:file = fopen(out_filename, io_write);
	if (!file) {
		return;
	}

	new base = GetAmxBase();

	new hdr[AMX_HDR];
	GetAmxHeader(hdr);

	new dat = hdr[AMX_HDR_DAT];
	new cod = hdr[AMX_HDR_COD];
	new hea = hdr[AMX_HDR_HEA];
	new cip = cod - dat;

	// DISASSAMBLE CODE
	fwrite(file, "; CODE\n\n");

	while (cip < 0) {
		new op = @(cip);

		if (op < 0 || op >= sizeof(insn_table)) {
			fwrite(file, "Invalid instruction ");
			fwrite(file, ToHexStr(op, hex_prefix | hex_pad));
			fwrite(file, "\n");
			break;
		}

		if (op == _:OP_PROC) {
			// Beginning of a function
			fwrite(file, "\n");
		}

		fwrite(file, ToHexStr(cip + dat - cod));
		fwrite(file, "  ");
		fwrite(file, insn_table[op][op_name]);
		fwrite(file, " ");

		if (op == _:OP_PROC) {
			// Print function name if it's public
			new name[MAX_FUN_NAME];
			GetPublicNameByIndex(GetPublicIndexByAddress(cip + dat) - cod, name);
			if (strlen(name) != 0) {
				fwrite(file, "; ");
				fwrite(file, name);
			}
		}

		cip += size_of_cell;

		if (op == _:OP_CASETBL) {
			// Case table
			// Number of records follows the opcode
			new num = @(cip);
			cip += size_of_cell;
			for (new i = 0; i < num; i++) {
				fwrite(file, "\n\t");
				new addr = @(cip + size_of_cell * i * 2);
				new rel_addr = addr - (base + cod) + (cip - size_of_cell + dat - cod);
				fwrite(file, ToHexStr(rel_addr, hex_sign));
				fwrite(file, " ");
				new val = @(cip + size_of_cell * i * 2 + size_of_cell);
				fwrite(file, ToHexStr(val, hex_sign));
			}
			cip += (2 * num + 1) * size_of_cell;
			goto next;
		}

		switch (Opcode:op) {
			case OP_CALL: {
				new name[MAX_FUN_NAME];
				GetPublicNameByIndex(GetPublicIndexByAddress(@(cip) - base - cod), name);
				if (strlen(name) > 0) {
					fwrite(file, name);
					cip += size_of_cell;
					goto next;
				}
			}
			case OP_SYSREQ_C, OP_SYSREQ_D: {
				new name[100]; // native name is not limited in length but we are
				if (op == _:OP_SYSREQ_C) {
					GetNativeNameByIndex(@(cip), name);
				} else {
					GetNativeNameByIndex(GetNativeIndexByAddress(@(cip)), name);
				}
				if (strlen(name) > 0) {
					fwrite(file, name);
					cip += size_of_cell;
					goto next;
				}
			}
		}

		for (new i = 0; i < insn_table[op][op_num_opers]; i++) {
			new oper = @(cip);
			if (insn_table[op][needs_reloc]) {
				oper -= base + cod;
			}
			fwrite(file, ToHexStr(oper, hex_sign));
			cip += size_of_cell;
		}

next:
		fwrite(file, "\n");
	}

	// DUMP DATA
	fwrite(file, "\n\n; DATA\n");

	new data_end = hea - dat;

	for (new i = 0; i < data_end; i += 0x10) {
		fwrite(file, ToHexStr(i, hex_pad));
		fwrite(file, "  ");
		DumpDataRowHex(file, i, 4, min(i + 0x10, data_end));
		fwrite(file, " ");
		DumpDataRowChar(file, i, 4, min(i + 0x10, data_end));
		fwrite(file, "\n");
	}

	fclose(file);
}

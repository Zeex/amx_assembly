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

#include "amx_header"
#include "amx_memory"
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
	insn_mnemonic[MAX_INSN_NAME],
	insn_num_opers,
	bool:insn_needs_reloc
}

static stock const insn_table[][Instruction] = {
	{ "none", 0, false },
	{ "load.pri", 1, false },
	{ "load.alt", 1, false },
	{ "load.s.pri", 1, false },
	{ "load.s.alt", 1, false },
	{ "lref.pri", 1, false },
	{ "lref.alt", 1, false },
	{ "lref.s.pri", 1, false },
	{ "lref.s.alt", 1, false },
	{ "load.i", 0, false },
	{ "lodb.i", 1, false },
	{ "const.pri", 1, false },
	{ "const.alt", 1, false },
	{ "addr.pri", 1, false },
	{ "addr.alt", 1, false },
	{ "stor.pri", 1, false },
	{ "stor.alt", 1, false },
	{ "stor.s.pri", 1, false },
	{ "stor.s.alt", 1, false },
	{ "sref.pri", 1, false },
	{ "sref.alt", 1, false },
	{ "sref.s.pri", 1, false },
	{ "sref.s.alt", 1, false },
	{ "stor.i", 0, false },
	{ "strb.i", 1, false },
	{ "lidx", 0, false },
	{ "lidx.b", 1, false },
	{ "idxaddr", 0, false },
	{ "idxaddr.b", 1, false },
	{ "align.pri", 1, false },
	{ "align.alt", 1, false },
	{ "lctrl", 1, false },
	{ "sctrl", 1, false },
	{ "move.pri", 0, false },
	{ "move.alt", 0, false },
	{ "xchg", 0, false },
	{ "push.pri", 0, false },
	{ "push.alt", 0, false },
	{ "push.r", 1, false },
	{ "push.c", 1, false },
	{ "push", 1, false },
	{ "push.s", 1, false },
	{ "pop.pri", 0, false },
	{ "pop.alt", 0, false },
	{ "stack", 1, false },
	{ "heap", 1, false },
	{ "proc", 0, false },
	{ "ret", 0, false },
	{ "retn", 0, false },
	{ "call", 1, true },
	{ "call.pri", 0, false },
	{ "jump", 1, true },
	{ "jrel", 1, true },
	{ "jzer", 1, true },
	{ "jnz", 1, true },
	{ "jeq", 1, true },
	{ "jneq", 1, true },
	{ "jless", 1, true },
	{ "jleq", 1, true },
	{ "jgrtr", 1, true },
	{ "jgeq", 1, true },
	{ "jsless", 1, true },
	{ "jsleq", 1, true },
	{ "jsgrtr", 1, true },
	{ "jsgeq", 1, true },
	{ "shl", 0, false },
	{ "shr", 0, false },
	{ "sshr", 0, false },
	{ "shl.c.pri", 1, false },
	{ "shl.c.alt", 1, false },
	{ "shr.c.pri", 1, false },
	{ "shr.c.alt", 1, false },
	{ "smul", 0, false },
	{ "sdiv", 0, false },
	{ "sdiv.alt", 0, false },
	{ "umul", 0, false },
	{ "udiv", 0, false },
	{ "udiv.alt", 0, false },
	{ "add", 0, false },
	{ "sub", 0, false },
	{ "sub.alt", 0, false },
	{ "and", 0, false },
	{ "or", 0, false },
	{ "xort", 0, false },
	{ "not", 0, false },
	{ "neg", 0, false },
	{ "invert", 0, false },
	{ "add.c", 1, false },
	{ "smul.c", 1, false },
	{ "zero.pri", 0, false },
	{ "zero.alt", 0, false },
	{ "zero", 1, false },
	{ "zero.s", 1, false },
	{ "sign.pri", 0, false },
	{ "sign.alt", 0, false },
	{ "eq", 0, false },
	{ "neq", 0, false },
	{ "less", 0, false },
	{ "leq", 0, false },
	{ "grtr", 0, false },
	{ "geq", 0, false },
	{ "sless", 0, false },
	{ "sleq", 0, false },
	{ "sgrtr", 0, false },
	{ "sgeq", 0, false },
	{ "eq.c.pri", 1, false },
	{ "eq.c.alt", 1, false },
	{ "inc.pri", 0, false },
	{ "inc.alt", 0, false },
	{ "inc", 1, false },
	{ "inc.s", 1, false },
	{ "inc.i", 0, false },
	{ "dec.pri", 0, false },
	{ "dec.alt", 0, false },
	{ "dec", 1, false },
	{ "dec.s", 1, false },
	{ "dec.i", 0, false },
	{ "movs", 1, false },
	{ "cmps", 1, false },
	{ "fill", 1, false },
	{ "halt", 1, false },
	{ "bounds", 1, false },
	{ "sysreq.pri", 1, false },
	{ "sysreq.c", 1, false },
	{ "file", -1, false }, // obsolete
	{ "line", -1, false }, // obsolete
	{ "symbol", -1, false }, // obsolete
	{ "srange", -1, false }, // obsolete
	{ "jump.pri", 0, false },
	{ "switch", 1, false },
	{ "casetbl", -1, true },
	{ "swap.pri", 0, false },
	{ "swap.alt", 0, false },
	{ "push.adr", 1, false },
	{ "nop", 0, false },
	{ "sysreq.d", 1, false },
	{ "symtag", 1, false }, // obsolete
	{ "break", 0, false }
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

	new base = GetAmxBaseAddress();

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
		fwrite(file, insn_table[op][insn_mnemonic]);
		fwrite(file, " ");

		if (op == _:OP_PROC) {
			// Print function name if it's public
			new name[32];
			new address = cip + dat - cod;
			if (address == hdr[AMX_HDR_CIP]) {
				strcat(name, "main");
			} else {
				new index = GetPublicIndexFromAddress(address);
				if (index >= 0) {
					GetPublicNameFromIndex(index, name);
				}
			}
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
				new name[32];
				new address = @(cip) - base - cod;
				if (address == hdr[AMX_HDR_CIP]) {
					strcat(name, "main");
				} else {
					new index = GetPublicIndexFromAddress(address);
					if (index >= 0) {
						GetPublicNameFromIndex(index, name);
					}
				}
				if (strlen(name) > 0) {
					fwrite(file, name);
					cip += size_of_cell;
					goto next;
				}
			}
			case OP_SYSREQ_C, OP_SYSREQ_D: {
				new name[100]; // native name is not limited in length but we are
				if (op == _:OP_SYSREQ_C) {
					GetNativeNameFromIndex(@(cip), name);
				} else {
					new index = GetNativeIndexFromAddress(@(cip));
					if (index >= 0) {
						GetNativeNameFromIndex(index, name);
					}
				}
				if (strlen(name) > 0) {
					fwrite(file, name);
					cip += size_of_cell;
					goto next;
				}
			}
		}

		for (new i = 0; i < insn_table[op][insn_num_opers]; i++) {
			new oper = @(cip);
			if (insn_table[op][insn_needs_reloc]) {
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

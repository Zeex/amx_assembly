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

#if defined CODESCAN_INC
	#endinput
#endif
#define CODESCAN_INC

#include "disasm"
#include "asm"

#define SCANNER_FAIL_ON_INVALID (1)
#define SCANNER_IGNORE_NOP      (2)
#define SCANNER_IGNORE_BREAK    (4)
#define SCANNER_NAME_FUNCTIONS  (8)
#define SCANNER_IGNORE_HALT     (16)

// If we can determine a function's name, we can determine if it is a public or
// not.  If we can't name it, it is a normal one.  However, if naming is skipped
// then we will have no idea what type it is.
#define SCANNER_FUNC_AUTOMATA (1)
#define SCANNER_FUNC_PUBLIC   (2)
#define SCANNER_FUNC_OTHER    (4)
#define SCANNER_FUNC_UNKNOWN  (8)

#if !defined cellbytes
	#define cellbytes (cellbits / 8)
#endif

enum CodeScanMatch {
	CodeScanMatch_func,     // Start of the containing function.
	CodeScanMatch_size,     // Remaining code size (total).
	CodeScanMatch_type,     // Public, normal, automata, etc.
	CodeScanMatch_heap,     // At the point of this scanner.
	CodeScanMatch_stack,    // At the point of this scanner.
	CodeScanMatch_params,   // Likely unknown statically.
	CodeScanMatch_name[40], // Only publics (no -d3 info used).
	CodeScanMatch_cip       // The point of the pattern match END.
}

// All the information for scanning through an AMX and extracting lots of nice
// information about it.
enum CodeScanner {
	CodeScanner_first
}

enum CodeScanJump {
	CodeScanJump_switch, // For "CASETBL" not regular jumps.
	CodeScanJump_target, // Zero when this slot is available.
	CodeScanJump_stack,  // Sizes at the time of the jump.
	CodeScanJump_heap    // Sizes at the time of the jump.
}

enum CodeScanMatcher {
	CodeScanMatcher_func,     // A pointer to the callback.
	CodeScanMatcher_code[32], // The code to look for.
	CodeScanMatcher_len,
	CodeScanMatcher_offset,   // Where the current scanner is in this code.
	CodeScanMatcher_next,     // The next match array.
	CodeScanMatcher_flags     // Customisation.
}

static stock bool:CodeScanCheckJumpTarget(cip, deloc, &stk, &hea, jumpTargets[][CodeScanJump], minn, num = sizeof (jumpTargets))
{
	// Use "minn" to restrict the number of jump targets that we check.  Returns
	// "true" if the current address is equal to an address that any jump goes
	// to.
	new
		sip,
		count;
	while (num-- > minn) {
		if (jumpTargets[num][CodeScanJump_target]) {
			if ((sip = jumpTargets[num][CodeScanJump_switch])) {
				count = ReadAmxMemory(sip) + 1,
				sip += cellbytes;
				while (count--) {
					if (ReadAmxMemory(sip) == deloc) {
						return
							--jumpTargets[num][CodeScanJump_target],
							stk = jumpTargets[num][CodeScanJump_stack],
							hea = jumpTargets[num][CodeScanJump_heap],
							true;
					}
					sip += 2 * cellbytes;
				}
			} else if (jumpTargets[num][CodeScanJump_target] == cip) {
				return
					jumpTargets[num][CodeScanJump_target] = 0,
					stk = jumpTargets[num][CodeScanJump_stack],
					hea = jumpTargets[num][CodeScanJump_heap],
					true;
			}
		}
	}
	return false;
}

static stock CodeScanResetJumpTargets(jumpTargets[][CodeScanJump], &minn, num = sizeof (jumpTargets))
{
	minn = num;
	while (num--) {
		jumpTargets[num][CodeScanJump_target] = 0;
	}
}

static stock CodeScanAddJumpTarget(cip, stk, hea, jumpTargets[][CodeScanJump], &minn, num = sizeof (jumpTargets))
{
	while (num--) {
		// Multiple jumps to the same place?
		if (jumpTargets[num][CodeScanJump_target] == cip) {
			return;
		} else if (!jumpTargets[num][CodeScanJump_target]) {
			jumpTargets[num][CodeScanJump_switch] = 0;
			jumpTargets[num][CodeScanJump_target] = cip;
			jumpTargets[num][CodeScanJump_stack] = stk;
			jumpTargets[num][CodeScanJump_heap] = hea;
			minn = min(minn, num);
			return;
		}
	}
}

static stock CodeScanAddSwitchTarget(dctx[DisasmContext], base, stk, hea, jumpTargets[][CodeScanJump], &minn, num = sizeof (jumpTargets))
{
	new
		sip = DisasmGetOperand(dctx) - base;
	if (UnrelocateOpcode(Opcode:ReadAmxMemory(sip)) != OP_CASETBL) {
		// Can happen when we parse "RelocateOpcodeNow" because it has an
		// explicit "#emit switch 0" in.
		return;
	}
	while (num--) {
		// Multiple jumps to the same place?
		if (!jumpTargets[num][CodeScanJump_target]) {
			jumpTargets[num][CodeScanJump_switch] = sip + cellbytes,
			jumpTargets[num][CodeScanJump_target] = ReadAmxMemory(sip + cellbytes) + 1,
			jumpTargets[num][CodeScanJump_stack] = stk,
			jumpTargets[num][CodeScanJump_heap] = hea,
			minn = min(minn, num);
			return;
		}
	}
}

stock CodeScanAddMatcher(scanner[CodeScanner], searcher[CodeScanMatcher]) {
	searcher[CodeScanMatcher_next] = scanner[CodeScanner_first],
	scanner[CodeScanner_first] = ref(searcher),
	searcher[CodeScanMatcher_offset] = 0;
}

stock CodeScanMatcherInit_(searcher[CodeScanMatcher], name[], faked, flags = SCANNER_IGNORE_NOP | SCANNER_IGNORE_BREAK | SCANNER_IGNORE_HALT) {
	// All this parameter does is ensure that the callback exists.
	#pragma unused faked
	new
		idx = GetPublicIndexFromName(name);
	if (idx == -1) {
		searcher[CodeScanMatcher_func] = 0;
	} else {
		searcher[CodeScanMatcher_func] = GetPublicAddressFromIndex(idx);
	}
	searcher[CodeScanMatcher_flags] = flags,
	searcher[CodeScanMatcher_next] = -1,
	searcher[CodeScanMatcher_offset] = searcher[CodeScanMatcher_len] = 0;
}

// Will not call the function because the check will fail, but will not compile
// if the function doesn't exist, while still passing it in as a string.
#define CodeScanMatcherInit(%0,%1) CodeScanMatcherInit_((%0),(#%1),((gCodeScanCallback_always_false&0)?(%1(gCodeScanCallback_match)):0))
#define CodeScanMatcherInit_(%0,(%1,%2),%3) CodeScanMatcherInit_(%0,(%1),((gCodeScanCallback_always_false&0)?(%1(gCodeScanCallback_match)):0),%2)

stock CodeScanMatcherPattern(searcher[CodeScanMatcher], {Opcode, Float, _}:...) {
	new
		len = numargs() - 1;
	if (len > 32) {
		return;
	}
	searcher[CodeScanMatcher_len] = len;
	for (new i = 0; i != len; ++i) {
		searcher[CodeScanMatcher_code][i] = getarg(i + 1);
	}
}

stock gCodeScanCallback_always_false = 0;
stock gCodeScanCallback_matcher[CodeScanMatcher];
stock gCodeScanCallback_match[CodeScanMatch];

static stock CodeScanDeref(v) {
	#pragma unused v
	#emit load.s.pri 12 // first argument
	#emit stor.s.pri 16 // secret argument
	#emit retn
	return gCodeScanCallback_matcher; // make compiler happy
}

static stock CodeScanReset(cs[CodeScanMatcher], &next) {
	next = cs[CodeScanMatcher_next],
	cs[CodeScanMatcher_offset] = 0;
}

static stock CodeScanCheck(Opcode:op, dctx[DisasmContext], cs[CodeScanMatcher], match[CodeScanMatch], &next) {
	// Returns an address of a callback if it passes.
	next = cs[CodeScanMatcher_next];
	if (!cs[CodeScanMatcher_func]) {
		return 0;
	}
	new
		flags = cs[CodeScanMatcher_flags];
	switch (op) {
		case OP_NOP: {
			if (flags & SCANNER_IGNORE_NOP) {
				return 0;
			}
		}
		case OP_BREAK: {
			if (flags & SCANNER_IGNORE_BREAK) {
				return 0;
			}
		}
		case OP_HALT: {
			if (flags & SCANNER_IGNORE_HALT) {
				return 0;
			}
		}
	}
	new
		off = cs[CodeScanMatcher_offset],
		cnt = DisasmGetNumOperands(dctx),
		len = cs[CodeScanMatcher_len],
		i = -1;
	if (op == Opcode:cs[CodeScanMatcher_code][off]) {
		do {
			if (++off == len) {
				// Get the address of the START of the match.
				return
					match[CodeScanMatch_cip] -= len * 4,
					match[CodeScanMatch_size] += len * 4,
					// "CallFunction" doesn't work for arrays apparently.
					cs[CodeScanMatcher_func];
			}
			if (++i == cnt) {
				// Out of parameters to check (but still correct).
				return
					cs[CodeScanMatcher_offset] = off,
					false;
			}
		}
		while (cs[CodeScanMatcher_code][off] == cellmin || cs[CodeScanMatcher_code][off] == DisasmGetOperand(dctx, i));
		// "cellmin" means "any value" (including cellmin).
	}
	// The parameter is wrong.
	return
		cs[CodeScanMatcher_offset] = 0;
}

static stock bool:CodeScanGetFuncName(addr, name[])
{
	// The "name" parameter is longer than 32 (which is the maximum function
	// name length normally) beacause we append states to some.
	// Name not found.
	new
		index = GetPublicIndexFromAddress(addr);
	if (index < 0) {
		return
			name[0] = 0,
			false;
	}
	// This code will not return great results for public functions with states.
	return
		GetPublicNameFromIndex(index, name, 40),
		true;
}

stock bool:CodeScanRun(scanner[CodeScanner], flags = 0) {
	// Technically, if there are no replacements defined, then doing nothing
	// will correctly match them all, so this is not a failure.
	if (scanner[CodeScanner_first] == -1) {
		return true;
	}
	// Declare, but never initialise, large variables.  Makes the code crash.
//	goto CodeScanRun_skip_init;
	new
		cip,
		dctx[DisasmContext],
		Opcode:op,
		parseParam,
		minn,
		base,
		// This variable stores stack/heap sizes for jump targets so that we can
		// know how big the stack is at those points even when jumping forward
		// (not backwards though - since we progress purely linerarly in the
		// scan.  Although you can have huge numbers of jumps from control
		// structures, you only need an array approximately equal to the depth
		// of the most indented structures, since targets are removed after
		// being reached.  The only big exception to this is "switch",
		// statements, which can have loads of targets - they need to be done
		// specially.  We can't jump out of a function (or shouldn't do), so we
		// can reset this at the start of each function.
		jumpTargets[32][CodeScanJump],
		hdr[AMX_HDR],
//CodeScanRun_skip_init:
	// The "ignore" options are global, but can be set per-scanner as well.
		stk = 0,
		hea = 0,
		func,
		fctx[CodeScanMatch],
		bool:bFailOnINV = bool:(flags & SCANNER_FAIL_ON_INVALID),
		bool:bIgnoreNOP = bool:(flags & SCANNER_IGNORE_NOP),
		bool:bIgnoreBRK = bool:(flags & SCANNER_IGNORE_BREAK),
		bool:bIgnoreHLT = bool:(flags & SCANNER_IGNORE_HALT),
		bool:bNameFunc  = bool:(flags & SCANNER_NAME_FUNCTIONS),
		// Used for when mulitple opcodes in a row affect the parsing.  "4"
		// means "preamble", which is mostly "HALT"s and state stubs.
		parseState = 4;
	// Initialise the data structures.
	GetAmxHeader(hdr),
	DisasmInit(dctx),
	CodeScanResetJumpTargets(jumpTargets, minn),
	base = GetAmxBaseAddress() + hdr[AMX_HDR_DAT],
	fctx[CodeScanMatch_func] = DisasmGetCurIp(dctx);
	// Loop over the data.  Since our end condition is "out of data", we know
	// that any "false" returns are because of invalid data since the "< 0"
	// check is also the only other way that "false" can be returned and we pre-
	// empt that one.
	while (dctx[DisasmContext_nip] < 0) {
		if (DisasmDecodeInsn(dctx)) {
			cip = DisasmGetCurIp(dctx),
			op = DisasmGetOpcode(dctx);
			// The compiler sometimes inserts extra instructions like "NOP" and
			// "BREAK" for debugging and padding (as do we) - maybe ignore them.
			if (!CodeScanCheckJumpTarget(cip, cip + base, stk, hea, jumpTargets, minn) && parseState == 8) {
				// Unexpected operation - this follows a "RETN", but can't be jumped to.
				parseState = 16;
			}
			switch (op) {
				case OP_NOP: {
					if (bIgnoreNOP) {
						parseState &= ~3;
						continue;
					}
				}
				case OP_BREAK: {
					if (bIgnoreBRK) {
						parseState &= ~3;
						continue;
					}
				}
				case OP_HALT: {
					if (bIgnoreHLT && parseState == 4) {
						continue;
					}
				}
				case OP_PROC: {
					// This is the start of a new function.  The only functions
					// that don't start like this are the automata stubs.
					if (!bNameFunc) {
						fctx[CodeScanMatch_type] = SCANNER_FUNC_UNKNOWN;
					} else if (CodeScanGetFuncName(cip, fctx[CodeScanMatch_name])) {
						fctx[CodeScanMatch_type] = SCANNER_FUNC_PUBLIC;
					} else {
						fctx[CodeScanMatch_type] = SCANNER_FUNC_OTHER;
					}
					fctx[CodeScanMatch_func] = cip,
					fctx[CodeScanMatch_heap] = fctx[CodeScanMatch_stack] = fctx[CodeScanMatch_cip] = stk = hea = 0,
					CodeScanResetJumpTargets(jumpTargets, minn),
					fctx[CodeScanMatch_params] = cellmin,
					parseState = 0;
				}
				case OP_LOAD_PRI: {
					// If we are not in the main functions yet and this is the
					// first instruction seen, then it is the start of an
					// automata function stub.
					if (parseState == 4) {
						if (bNameFunc) {
							CodeScanGetFuncName(cip, fctx[CodeScanMatch_name]);
						}
						fctx[CodeScanMatch_type] = SCANNER_FUNC_AUTOMATA,
						fctx[CodeScanMatch_func] = cip,
						fctx[CodeScanMatch_heap] = fctx[CodeScanMatch_stack] = fctx[CodeScanMatch_cip] = stk = hea = 0,
						CodeScanResetJumpTargets(jumpTargets, minn),
						fctx[CodeScanMatch_params] = cellmin;
					}
				}
			}
			if (parseState == 16) {
				// TODO: Something?  Unexpected opcode.
				parseState = 0;
			}
			// Check the address - if it is a jump target that changes the stack
			// size BEFORE the instruction, while the instruction itself changes
			// it after.
			// Found a valid instruction that we don't want to ignore.  Finally
			// do the actual comparisons to various defined scanners.
			fctx[CodeScanMatch_heap] = hea,
			fctx[CodeScanMatch_stack] = stk,
			fctx[CodeScanMatch_cip] = DisasmGetNextIp(dctx),
			fctx[CodeScanMatch_size] = DisasmGetRemaining(dctx);
			for (new cur = scanner[CodeScanner_first]; cur != -1; ) {
				if ((func = CodeScanCheck(op, dctx, CodeScanDeref(cur), fctx, cur))) {
					// Reset to the start of the function, to reparse.
					#emit PUSH.adr   fctx
					#emit PUSH.C     4
					#emit LCTRL      6
					#emit ADD.C      28
					#emit PUSH.pri
					#emit LOAD.S.pri func
					#emit SCTRL      6
					#emit STOR.S.pri func
					// If code was written, reparse this function.
					if (func) {
						dctx[DisasmContext_nip] = fctx[CodeScanMatch_func];
						parseState = 32;
					}
					for (cur = scanner[CodeScanner_first]; cur != -1; ) {
						CodeScanReset(CodeScanDeref(cur), cur);
					}
					break;
				}
			}
			if (parseState == 4) {
				// State stubs have no stack, so don't process it at all (since
				// the two uses of "SWITCH" will probably collide).
				continue;
			}
			if (parseState == 32) {
				parseState = 0;
				continue;
			}
			// Done with parsing the code.  Update the stack and heap values
			// now.  Done AFTER any other calls so that the value passed is
			// the one at the start of the instruction, not the end.
			switch (op) {
				case OP_PUSH_PRI, OP_PUSH_ALT, OP_PUSH_R, OP_PUSH_S, OP_PUSH, OP_PUSH_ADR: {
					if (stk != cellmin) {
						stk += cellbytes;
					}
					parseState = 0;
				}
				case OP_STACK: {
					// The stack grows down, but our count is positive.
					if (stk != cellmin) {
						stk -= DisasmGetOperand(dctx);
					}
					parseState = 0;
				}
				case OP_HEAP: {
					if (hea != cellmin) {
						hea += DisasmGetOperand(dctx);
					}
					parseState = 0;
				}
				case OP_POP_PRI, OP_POP_ALT: {
					if (stk != cellmin) {
						stk -= cellbytes;
					}
					parseState = 0;
				}
				case OP_CALL, OP_CALL_PRI: {
					// Remove all the function parameters.
					if (parseState == 3) {
						stk -= parseParam;
					}
					parseState = 0;
				}
				case OP_PUSH_C: {
					// The "+ cellbytes" is because when calling a function, the
					// parameter is the number of bytes pushed, not including
					// this one, with that one implicitly popped on return.
					parseParam = DisasmGetOperand(dctx) + cellbytes;
					if (stk != cellmin) {
						stk += cellbytes,
						parseState = 3;
					}
				}
				// There is a code-get pattern of:
				// 
				//   LCTRL 5
				//   ADD.C n
				//   SCTRL 4
				// 
				// Which adjusts the stack to the correct size after "goto".  We
				// have to deal with that explcitly.  Note that the "ADD.C" may
				// be missing if there are no variables currently in scope.
				case OP_LCTRL: {
					if (DisasmGetOperand(dctx) == 5) {
						parseState = 1;
					} else {
						parseState = 0;
					}
				}
				case OP_ADD_C: {
					if (parseState == 1) {
						parseParam = -DisasmGetOperand(dctx),
						parseState = 2;
					} else {
						parseState = 0;
					}
				}
				case OP_SCTRL: {
					// This is the tricky one, since it can mess up the stack in
					// strange ways.  Deal with the case where it comes from
					// "goto", even though that is generally considered bad.
					switch (DisasmGetOperand(dctx)) {
						case 2: {
							hea = cellmin;
						}
						case 4: {
							switch (parseState) {
								case 1: {
									stk = 0;
								}
								case 2: {
									stk = parseParam;
								}
								default: {
									stk = cellmin;
								}
							}
						}
						case 5: {
							stk = cellmin;
						}
					}
					parseState = 0;
				}
				case OP_JUMP, OP_JZER, OP_JNZ, OP_JEQ, OP_JNEQ, OP_JLESS, OP_JLEQ, OP_JGRTR, OP_JGEQ, OP_JSLESS, OP_JSLEQ, OP_JSGRTR, OP_JSGEQ: {
					// Add a jump target.  These require relocation as they are
					// translated to absolute RAM locations.  "DisasmNeedReloc"
					// will return "true", but we don't need to call it.
					// Relocate it relative to "dat" not "cod" for simpler
					// comparisons - just see if the read address matches
					// instead of the true code address.
					//   
					//   val = val - (base + cod) + (cod - dat);
					//   val = val - base - cod + cod - dat;
					//   val = val - base - dat;
					//   val = val - (base + dat);
					//   
					// Only jumps that go forwards.
					parseParam = DisasmGetOperand(dctx) - base,
					parseState = 0;
					if (parseParam > cip) {
						CodeScanAddJumpTarget(parseParam, stk, hea, jumpTargets, minn);
					}
				}
				case OP_JREL: {
					// Add a jump target.  Only jumps that go forwards.
					parseParam = DisasmGetOperand(dctx) + cip,
					parseState = 0;
					if (parseParam > cip) {
						CodeScanAddJumpTarget(parseParam, stk, hea, jumpTargets, minn);
					}
				}
				case OP_SWITCH: {
					// Add a jump target.  These are always forwards.
					CodeScanAddSwitchTarget(dctx, base, stk, hea, jumpTargets, minn),
					parseState = 0;
				}
				case OP_RET, OP_RETN: {
					// MAY be the end of a function.
					parseState = 8;
				}
				default: {
					parseState = 0;
				}
			}
		} else if (bFailOnINV) {
			return false;
		} else {
			// Found an invalid instruction that we want to ignore.
			dctx[DisasmContext_nip] += cellbytes;
			parseState = 0;
		}
	}
	return true;
}

stock CodeScanInit(scanner[CodeScanner]) {
	// I debated inlining DisasmInit to avoid two calls to "GetAmxHeader", but
	// it isn't worth the effort and code duplication.  No "start" and "end"
	// parameters, so scans the entire code range.
	scanner[CodeScanner_first] = -1;
}

stock CodeScanGetFunctionDisasm(func[CodeScanner], ret[DisasmContext]) {
	// Doesn't do any decompilation, just gets the information for decompiling
	// the whole of the current function.
}


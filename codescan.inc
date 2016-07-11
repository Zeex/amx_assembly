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

#if defined CODESCAN_INC
	#endinput
#endif
#define CODESCAN_INC

/*

// Example:

forward TailCall_FoundCallback(m[CodeScanner])

main()
{
	new scanner[CodeScanner];
	CodeScanInit(scanner);
	
	new csm0[CodeScanMatcher];
	CodeScanMatcherInit(csm0, &TailCall_FoundCallback);
	CodeScanMatcherPattern(csm0,
		OP(PUSH_C, ???)
		OP(CALL,   &MyFunc)
		OP(RETN)
	);
	CodeScanAddMatcher(scan, csm0);
	
	// Add other matcher patterns here.
	
	// Run all the scanners in parallel.
	CodeScanRun(scan);
}

public TailCall_FoundCallback(m[CodeScanner])
{
	// Do something with the found address (of the START of the match), and the
	// stack size (of the END of the match) - different for reasons...
}

// Create a default call for this function, so that we can include it in the AMX
// and take the address in "OP".  Note that you do NOT need to do this for
// scanner callbacks if you only use their address in "CodeScanMatcherInit".
#define CALL@MyFunc MyFunc(0, "")
stock MyFunc(a, b[], ...)
{
	// Normal function.
}

*/

#include "frame_info"
#include "disasm"
#include "asm"

#define SCANNER_FAIL_ON_INVALID (1)
#define SCANNER_IGNORE_NOP      (2)
#define SCANNER_IGNORE_BREAK    (4)
#define SCANNER_NAME_FUNCTIONS  (8)
#define SCANNER_IGNORE_HALT     (16)
#define SCANNER_IGNORE_BOUNDS   (32)
#define SCANNER_MATCH_ALL       (64)

#define O@I_ (0) // Type integer.
#define O@U_ (1) // Type unknown (???).
#define O@F_ (2) // Type function (&func).
#define O@N_ (3) // Type none.
#define O@O_ (4) // Type opcode.
#define O@S_ (5) // Type skipped.

#define OP_TYPE_INTEGER_  (O@I_) // Type integer.
#define OP_TYPE_UNKNOWN_  (O@U_) // Type unknown (???).
#define OP_TYPE_FUNCTION_ (O@F_) // Type function (&func).
#define OP_TYPE_NONE_     (O@N_) // Type none.
#define OP_TYPE_OPCODE_   (O@O_) // Type opcode.
#define OP_TYPE_SKIP_     (O@S_) // Type skipped.

// If we can determine a function's name, we can determine if it is a public or
// not.  If we can't name it, it is a normal one.  However, if naming is skipped
// then we will have no idea what type it is.
#define SCANNER_FUNC_PUBLIC   (1)
#define SCANNER_FUNC_OTHER    (2)
#define SCANNER_FUNC_AUTOMATA (3)
#define SCANNER_FUNC_HALT     (4)
#define SCANNER_FUNC_UNKNOWN  (5)
#define SCANNER_FUNC_AUTOMATA_NO_NAME (7)
#define SCANNER_FUNC_HALT_NO_NAME     (8)

// The "OP()" macro is used to easilly define code patterns to scan for:
//   
//   new csm[CodeScanMatcher];
//   CodeScanMatcherInit(csm,
//       OP(CONST_PRI, 42)
//       OP(ADD_C,     ???)
//       OP(CALL,      &my_func)
//   )
//   
// Any function that you want to take the address of in this way must have its
// call pattern defined as:
//   
//   #define CALL@my_func my_func(0, "hi", false)
//   
// Because otherwise a) the code can't guarantee that the function will be in
// the final amx, and b) we need a call to it from which to extract the addr.
// 
// You can use this style explcitly within an "OP" scanner, or there is a new
// dedicated keyword for it - "addressof(func)" (note the lack of "&" there).
// 
#define OP(%0) ,(_:O@T_:O@O_),(Opcode:O@X_:O@Y_:O@W_:$OP_%0)
#define OP_%0\32;%1) OP_%0%1)

#define O@X_:%9$%0,%1,%2) %0),(_:O@1_:O@2_:O@3_:$%1|||,%2)
#define O@Y_:%9$%0,%1)    %0),(_:O@1_:O@2_:O@3_:$%1|||)
#define O@Z_:%9$%0)       %0)
#define O@W_:%9$%0)       %0),(O@N_),(0)

#define O@T_:O@O_),(Opcode:O@X_:O@Y_:O@Z_:$OP_???%0) O@S_),(0)

#define O@1_:%9$%0???%1|||%2) O@U_ ),(_:O@X_:O@Y_:O@Z_:$0%2)
#define O@2_:%9$%0&%1|||%2)   O@F_),(O@A_()?(((CALL@%1),O@V_)?1:2):_:O@X_:O@Y_:O@Z_:$(O@V_)%2)
#define O@3_:%9$%1|||%2)      O@I_ ),(_:O@X_:O@Y_:O@Z_:$(%1)%2)

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

#if !defined cellbytes
	#define cellbytes (cellbits / 8)
#endif

#if !defined CODE_SCAN_MAX_PATTERN
	#define CODE_SCAN_MAX_PATTERN (12)
#endif
#define CODE_SCAN_MAX_PATTERN_ARRAY (CODE_SCAN_MAX_PATTERN * 3)

#if !defined CODE_SCAN_MAX_PARALLEL
	#define CODE_SCAN_MAX_PARALLEL (2)
#endif

#if !defined CODE_SCAN_MAX_JUMP_TARGETS
	#define CODE_SCAN_MAX_JUMP_TARGETS (32)
#endif

// All the information for scanning through an AMX and extracting lots of nice
// information about it.
enum CodeScanner {
	CodeScanMatch_func,     // Start of the containing function.
	CodeScanMatch_size,     // Size of the match.
	CodeScanMatch_type,     // Public, normal, automata, etc.
	CodeScanMatch_heap,     // At the point of this scanner.
	CodeScanMatch_stack,    // At the point of this scanner.
	CodeScanMatch_params,   // Likely unknown statically.
	CodeScanMatch_cip,      // The point of the pattern match END.
	CodeScanMatch_holes[CODE_SCAN_MAX_PATTERN_ARRAY / 2], // Results of "???"s.
	CodeScanMatch_name[32 char],
	CodeScanner_first,
	CodeScanner_minn,
	CodeScanner_jump_switch[CODE_SCAN_MAX_JUMP_TARGETS], // For "CASETBL" not regular jumps.
	CodeScanner_jump_target[CODE_SCAN_MAX_JUMP_TARGETS], // Zero when this slot is available.
	CodeScanner_jump_stack [CODE_SCAN_MAX_JUMP_TARGETS], // Sizes at the time of the jump.
	CodeScanner_jump_heap  [CODE_SCAN_MAX_JUMP_TARGETS], // Sizes at the time of the jump.
	CodeScanner_state,
	CodeScanner_param
}

enum CodeScanMatcher {
	CodeScanMatcher_func,     // A pointer to the callback.
	CodeScanMatcher_code[CODE_SCAN_MAX_PATTERN_ARRAY], // The code to look for.
	CodeScanMatcher_len,
	CodeScanMatcher_offset[CODE_SCAN_MAX_PARALLEL], // Where the current scanner is in this code.
	CodeScanMatcher_start[CODE_SCAN_MAX_PARALLEL],
	CodeScanMatcher_holeidx[CODE_SCAN_MAX_PARALLEL],
	CodeScanMatcher_holes[CODE_SCAN_MAX_PARALLEL * CODE_SCAN_MAX_PATTERN_ARRAY / 2],
	CodeScanMatcher_next,      // The next match array.
	CodeScanMatcher_flags      // Customisation.
}

#define gCodeScanReturnVar_ O@V_
#define CodeScanGetNextCall_ O@A_
#define CALL@CodeScanGetNextCall_ CALL@O@A_
#define CALL@O@A_ O@A_()

stock
	gCodeScanReturnVar_ = 0,
	gCodeScanCallback_matcher[CodeScanMatcher],
	gCodeScanCallback_match[CodeScanner];

static stock
	gHdr[AMX_HDR],
	gBase,
	gDat;

stock bool:CodeScanGetNextCall_() {
	// Start reading code from the point to which this function returns, looking
	// for the next "CALL" op to signal the function call from the macro.
	new ctx[DisasmContext];
	DisasmInit(ctx, GetCurrentFrameReturn());
	while (DisasmNext(ctx)) {
		if (DisasmGetOpcode(ctx) == OP_CALL) {
			// Return the data in a global, to be repassed from the conditional.
			gCodeScanReturnVar_ = DisasmGetOperandReloc(ctx);
			return false;
		}
	}
	// ALWAYS returns false so that the function call within "OP(&func)" will
	// never be called thanks to the conditional.
	return false;
}

static stock bool:CodeScanCheckJumpTarget(cip, deloc, &stk, &hea, jumpTargets[CodeScanner], num = CODE_SCAN_MAX_JUMP_TARGETS)
{
	// Use "minn" to restrict the number of jump targets that we check.  Returns
	// "true" if the current address is equal to an address that any jump goes
	// to.
	new
		minn = jumpTargets[CodeScanner_minn],
		sip,
		count;
	while (num-- > minn) {
		if (jumpTargets[CodeScanner_jump_target][num]) {
			if ((sip = jumpTargets[CodeScanner_jump_switch][num])) {
				count = ReadAmxMemory(sip) + 1,
				sip += cellbytes;
				while (count--) {
					if (ReadAmxMemory(sip) == deloc) {
						return
							--jumpTargets[CodeScanner_jump_target][num],
							stk = jumpTargets[CodeScanner_jump_stack][num],
							hea = jumpTargets[CodeScanner_jump_heap][num],
							true;
					}
					sip += 2 * cellbytes;
				}
			} else if (jumpTargets[CodeScanner_jump_target][num] == cip) {
				return
					jumpTargets[CodeScanner_jump_target][num] = 0,
					stk = jumpTargets[CodeScanner_jump_stack][num],
					hea = jumpTargets[CodeScanner_jump_heap][num],
					true;
			}
		}
	}
	return false;
}

static stock CodeScanResetJumpTargets(jumpTargets[CodeScanner], num = CODE_SCAN_MAX_JUMP_TARGETS)
{
	jumpTargets[CodeScanner_minn] = num;
	while (num--) {
		jumpTargets[CodeScanner_jump_target][num] = 0;
	}
}

static stock CodeScanAddJumpTarget(cip, stk, hea, jumpTargets[CodeScanner], num = CODE_SCAN_MAX_JUMP_TARGETS)
{
	while (num--) {
		// Multiple jumps to the same place?
		if (jumpTargets[CodeScanner_jump_target][num] == cip) {
			return;
		} else if (!jumpTargets[CodeScanner_jump_target][num]) {
			jumpTargets[CodeScanner_jump_switch][num] = 0;
			jumpTargets[CodeScanner_jump_target][num] = cip;
			jumpTargets[CodeScanner_jump_stack][num] = stk;
			jumpTargets[CodeScanner_jump_heap][num] = hea;
			jumpTargets[CodeScanner_minn] = min(jumpTargets[CodeScanner_minn], num);
			return;
		}
	}
}

static stock CodeScanAddSwitchTarget(dctx[DisasmContext], stk, hea, jumpTargets[CodeScanner], num = CODE_SCAN_MAX_JUMP_TARGETS)
{
	new
		sip = DisasmGetOperand(dctx) - gBase,
		codepos = sip + gHdr[AMX_HDR_DAT] - gHdr[AMX_HDR_COD];
	if (codepos < 0 || codepos > gHdr[AMX_HDR_DAT] || UnrelocateOpcode(Opcode:ReadAmxMemory(sip)) != OP_CASETBL) {
		// Can happen when we parse "RelocateOpcodeNow" because it has an
		// explicit "#emit switch 0" in.
		return;
	}
	while (num--) {
		// Multiple jumps to the same place?
		if (!jumpTargets[CodeScanner_jump_target][num]) {
			jumpTargets[CodeScanner_jump_switch][num] = sip + cellbytes,
			jumpTargets[CodeScanner_jump_target][num] = ReadAmxMemory(sip + cellbytes) + 1,
			jumpTargets[CodeScanner_jump_stack][num] = stk,
			jumpTargets[CodeScanner_jump_heap][num] = hea,
			jumpTargets[CodeScanner_minn] = min(jumpTargets[CodeScanner_minn], num);
			return;
		}
	}
}

static stock CodeScanReset(cs[CodeScanMatcher], &next) {
	static
		lReset[CODE_SCAN_MAX_PARALLEL];
	next = cs[CodeScanMatcher_next],
	cs[CodeScanMatcher_offset] = lReset,
	cs[CodeScanMatcher_holeidx] = lReset;
	if (!cs[CodeScanMatcher_func]) {
		cs[CodeScanMatcher_len] = 0;
	}
}

stock CodeScanAddMatcher(scanner[CodeScanner], searcher[CodeScanMatcher]) {
	searcher[CodeScanMatcher_next] = scanner[CodeScanner_first],
	scanner[CodeScanner_first] = ref(searcher);
}

stock CodeScanMatcherInit_(searcher[CodeScanMatcher], name[], faked, flags = SCANNER_IGNORE_NOP | SCANNER_IGNORE_BOUNDS | SCANNER_IGNORE_BREAK | SCANNER_IGNORE_HALT) {
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
	searcher[CodeScanMatcher_len] = 0,
	CodeScanReset(searcher, flags);
}

// Will not call the function because the check will fail, but will not compile
// if the function doesn't exist, while still passing it in as a string.
#define CodeScanMatcherInit(%0,&%1) CodeScanMatcherInit_((%0),(#%1),((O@V_&0)?(%1(gCodeScanCallback_match)):0))
#define CodeScanMatcherInit_(%0,(%1,%2),%3) CodeScanMatcherInit_(%0,(%1),((O@V_&0)?(%1(gCodeScanCallback_match)):0),%2)

stock CodeScanMatcherPattern_(searcher[CodeScanMatcher], {Opcode, Float, _}:...) {
	new
		len = numargs() - 1;
	if (len > CODE_SCAN_MAX_PATTERN_ARRAY) {
		return;
	}
	searcher[CodeScanMatcher_len] = len;
	for (new i = 0; i != len; ++i) {
		searcher[CodeScanMatcher_code][i] = getarg(i + 1);
	}
}

// Note the lack of trailing comma.  This is to make the code patterns work.
#define CodeScanMatcherPattern(%0, CodeScanMatcherPattern_(%0

static stock CodeScanDeref(v) {
	#pragma unused v
	#emit load.s.pri 12 // first argument
	#emit stor.s.pri 16 // secret argument
	#emit retn
	return gCodeScanCallback_matcher; // make compiler happy
}

static stock CodeScanCheck(Opcode:op, dctx[DisasmContext], cs[CodeScanMatcher], fctx[CodeScanner], &next) {
	// Returns an address of a callback if it passes.
	next = cs[CodeScanMatcher_next];
	if (!cs[CodeScanMatcher_len]) {
		return 0;
	}
	new
		bool:zero = true,
		off,
		flags = cs[CodeScanMatcher_flags];
	if (flags) {
		// To deal with differences in different compilation modes, we just mark
		// these opcodes as fully ignorable (because they are mostly used for
		// debugging and not real user code).
		switch (op) {
			case OP_NOP: {
				if (flags & SCANNER_IGNORE_NOP) {
					return 0;
				}
			}
			case OP_BOUNDS: {
				if (flags & SCANNER_IGNORE_BOUNDS) {
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
	}
	new
		cnt = DisasmGetNumOperands(dctx),
		len = cs[CodeScanMatcher_len];
	for (new idx = 0; idx != CODE_SCAN_MAX_PARALLEL; ++idx) {
		off = cs[CodeScanMatcher_offset][idx];
		// Ensure that only one of the parallel scanners starts from the
		// beginning on each instruction.
		if (off) {
		} else if (zero) {
			// Get the start point of this match.
			cs[CodeScanMatcher_start][idx] = DisasmGetCurIp(dctx),
			zero = false;
		} else {
			continue;
		}
		if (cs[CodeScanMatcher_code][off] == OP_TYPE_SKIP_) {
			off += 2;
			if (off == len) {
				return
					memcpy(fctx[CodeScanMatch_holes], cs[CodeScanMatcher_holes], idx * (CODE_SCAN_MAX_PATTERN_ARRAY / 2), cs[CodeScanMatcher_holeidx][idx] * cellbytes, (CODE_SCAN_MAX_PATTERN_ARRAY / 2)),
					fctx[CodeScanMatch_cip] = cs[CodeScanMatcher_start][idx],
					fctx[CodeScanMatch_size] = DisasmGetNextIp(dctx) - cs[CodeScanMatcher_start][idx],
					cs[CodeScanMatcher_func];
			} else if (cs[CodeScanMatcher_code][off] == OP_TYPE_OPCODE_ && Opcode:cs[CodeScanMatcher_code][off + 1] == op) {
				// Found the match after the current "missing" instruction.
				goto CodeScanCheck_pass;
			} else {
				// The "== op" check is done twice because in this case we don't
				// want to fail the scanner if it doesn't match.
				continue;
			}
		}
		if (cs[CodeScanMatcher_code][off] == OP_TYPE_OPCODE_ && (flags & SCANNER_MATCH_ALL)) {
			fctx[CodeScanMatch_size] = DisasmGetNextIp(dctx) - cs[CodeScanMatcher_start][idx];
			fctx[CodeScanMatch_cip] = cs[CodeScanMatcher_start][idx];
			return cs[CodeScanMatcher_func];
		}
		if (cs[CodeScanMatcher_code][off] == OP_TYPE_OPCODE_ && Opcode:cs[CodeScanMatcher_code][off + 1] == op) {
CodeScanCheck_pass:
			// Check if there are enough parameters for this opcode.
			off += 2;
			if ((len - off) / 2 < cnt) {
				goto CodeScanCheck_fail;
			}
			if (cnt) {
				for (new i = 0; i != cnt; ++i) {
					switch (cs[CodeScanMatcher_code][off++]) {
						// Because we now abstract relocations to the disasm system,
						// we don't need to differentiate between fixed parameters
						// and function parameters any more - they are always fully
						// resolved.
						case OP_TYPE_INTEGER_, OP_TYPE_FUNCTION_: {
							if (cs[CodeScanMatcher_code][off++] != DisasmGetOperandReloc(dctx, i)) {
								goto CodeScanCheck_fail;
							}
						}
						case OP_TYPE_UNKNOWN_: {
							// Save the parameter.
							++off,
							cs[CodeScanMatcher_holes][idx * (CODE_SCAN_MAX_PATTERN_ARRAY / 2) + cs[CodeScanMatcher_holeidx][idx]++] = DisasmGetOperandReloc(dctx, i);
						}
						case OP_TYPE_NONE_, OP_TYPE_OPCODE_, OP_TYPE_SKIP_: {
							goto CodeScanCheck_fail;
						}
					}
				}
			} else if (cs[CodeScanMatcher_code][off] == OP_TYPE_NONE_) {
				// No parameters expected, none given.
				off += 2;
			} else {
				goto CodeScanCheck_fail;
			}
			if (off == len) {
				// Get the address of the START of the match.
				return
					memcpy(fctx[CodeScanMatch_holes], cs[CodeScanMatcher_holes][idx * (CODE_SCAN_MAX_PATTERN_ARRAY / 2)], 0, cs[CodeScanMatcher_holeidx][idx] * cellbytes, (CODE_SCAN_MAX_PATTERN_ARRAY / 2)),
					fctx[CodeScanMatch_cip] = cs[CodeScanMatcher_start][idx],
					fctx[CodeScanMatch_size] = DisasmGetNextIp(dctx) - cs[CodeScanMatcher_start][idx],
					// "CallFunction" doesn't work for arrays apparently.
					cs[CodeScanMatcher_func];
			} else {
				// Out of parameters to check but still looking correct.
				cs[CodeScanMatcher_offset][idx] = off;
				continue;
			}
		}
CodeScanCheck_fail:
		// The parameter is wrong.
		cs[CodeScanMatcher_holeidx][idx] = cs[CodeScanMatcher_offset][idx] = 0;
	}
	return 0;
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
		GetPublicNameFromIndex(index, name, 32),
		true;
}

static stock bool:CodeScanStepInternal(dctx[DisasmContext], csState[CodeScanner], &parseState, &parseParam) {
	// Loop over the data.  Since our end condition is "out of data", we know
	// that any "false" returns are because of invalid data since the "< 0"
	// check is also the only other way that "false" can be returned and we pre-
	// empt that one.
	switch (DisasmNext(dctx)) {
		case DISASM_OK: {
			new
				stk = csState[CodeScanMatch_stack],
				hea = csState[CodeScanMatch_heap],
				cip = DisasmGetCurIp(dctx),
				Opcode:op = DisasmGetOpcode(dctx);
			// The compiler sometimes inserts extra instructions like "NOP" and
			// "BREAK" for debugging and padding (as do we) - maybe ignore them.
			CodeScanCheckJumpTarget(cip, cip + gBase, stk, hea, csState);
			switch (op) {
				case OP_HALT: {
					if (parseState == 4) {
						csState[CodeScanMatch_type] = SCANNER_FUNC_HALT_NO_NAME,
						csState[CodeScanMatch_func] = cip,
						stk = hea = 0,
						CodeScanResetJumpTargets(csState);
					}
				}
				case OP_PROC: {
					// This is the start of a new function.  The only functions
					// that don't start like this are the automata stubs.
					csState[CodeScanMatch_type] = SCANNER_FUNC_UNKNOWN,
					csState[CodeScanMatch_func] = cip,
					CodeScanResetJumpTargets(csState),
					stk = hea = parseState = 0;
				}
				case OP_LOAD_PRI: {
					// If we are not in the main functions yet and this is the
					// first instruction seen, then it is the start of an
					// automata function stub.
					if (parseState == 4) {
						csState[CodeScanMatch_type] = SCANNER_FUNC_AUTOMATA_NO_NAME,
						csState[CodeScanMatch_func] = cip,
						stk = hea = 0,
						CodeScanResetJumpTargets(csState);
					}
				}
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
					//   base = base + dat;
					//   val = val - base;
					//   
					// Only jumps that go forwards.
					parseParam = DisasmGetOperand(dctx) - gBase,
					parseState = 0;
					if (parseParam > cip) {
						CodeScanAddJumpTarget(parseParam, stk, hea, csState);
					}
				}
				case OP_JREL: {
					// Add a jump target.  Only jumps that go forwards.
					parseParam = DisasmGetOperand(dctx) + cip,
					parseState = 0;
					if (parseParam > cip) {
						CodeScanAddJumpTarget(parseParam, stk, hea, csState);
					}
				}
				case OP_SWITCH: {
					// Add a jump target.  These are always forwards.
					CodeScanAddSwitchTarget(dctx, stk, hea, csState),
					parseState = 0;
				}
				default: {
					parseState = 0;
				}
			}
			csState[CodeScanMatch_stack] = stk,
			csState[CodeScanMatch_heap] = hea;
		}
		case DISASM_DONE: {
			return false;
		}
		case DISASM_NOP: {
			parseState = 0;
		}
	}
	return true;
}

stock bool:CodeScanStep(dctx[DisasmContext], csState[CodeScanner]) {
	return CodeScanStepInternal(dctx, csState, csState[CodeScanner_state], csState[CodeScanner_param]);
}

stock bool:CodeScanRun(csState[CodeScanner]) {
	if (csState[CodeScanner_first] == -1) {
		return true;
	}
	new
		dctx[DisasmContext],
		func,
		cur,
		Opcode:op,
		parseState = 4,
		parseParam;
	DisasmInit(dctx);
	for (cur = csState[CodeScanner_first]; cur != -1; CodeScanReset(CodeScanDeref(cur), cur)) { }
	while (CodeScanStepInternal(dctx, csState, parseState, parseParam)) {
		// Check the address - if it is a jump target that changes the stack
		// size BEFORE the instruction, while the instruction itself changes
		// it after.
		// Found a valid instruction that we don't want to ignore.  Finally
		// do the actual comparisons to various defined scanners.
		for (cur = csState[CodeScanner_first], op = DisasmGetOpcode(dctx); cur != -1; ) {
			if ((func = CodeScanCheck(op, dctx, CodeScanDeref(cur), csState, cur))) {
				// Reset to the start of the function, to reparse.
				#emit PUSH.S     csState
				#emit PUSH.C     4
				#emit LCTRL      6
				#emit ADD.C      28
				#emit PUSH.pri
				#emit LOAD.S.pri func
				#emit SCTRL      6
				#emit STOR.S.pri func
				// If code was written, reparse this function.
				if (func) {
					dctx[DisasmContext_nip] = csState[CodeScanMatch_func];
				}
				for (cur = csState[CodeScanner_first]; cur != -1; CodeScanReset(CodeScanDeref(cur), cur)) { }
				break;
			}
		}
	}
	return true;
}

stock CodeScanInit(scanner[CodeScanner]) {
	// I debated inlining DisasmInit to avoid two calls to "GetAmxHeader", but
	// it isn't worth the effort and code duplication.  No "start" and "end"
	// parameters, so scans the entire code range.
	GetAmxHeader(gHdr),
	gBase = GetAmxBaseAddress() + gHdr[AMX_HDR_DAT],
	gDat = gHdr[AMX_HDR_COD] - gHdr[AMX_HDR_DAT],
	CodeScanResetJumpTargets(scanner),
	scanner[CodeScanMatch_type] = 0,
	scanner[CodeScanMatch_params] = cellmin,
	scanner[CodeScanner_first] = -1,
	scanner[CodeScanner_param] = 0,
	scanner[CodeScanner_state] = 4;
}

stock CodeScanGetFunctionDisasm(csm[CodeScanner], ret[DisasmContext]) {
	// Doesn't do any decompilation, just gets the information for decompiling
	// the whole of the current function.
	ret[DisasmContext_end_ip] = 0,
	ret[DisasmContext_start_ip] = ret[DisasmContext_nip] = ret[DisasmContext_cip] = csm[CodeScanMatch_func];
}

stock CodeScanGetMatchDisasm(csm[CodeScanner], ret[DisasmContext]) {
	// Doesn't do any decompilation, just gets the information for decompiling
	// the currently found match.
	ret[DisasmContext_end_ip] = 0,
	ret[DisasmContext_start_ip] = ret[DisasmContext_nip] = ret[DisasmContext_cip] = csm[CodeScanMatch_cip];
}

stock CodeScanGetFunctionAsm(csm[CodeScanner], ret[AsmContext]) {
	// Doesn't do any decompilation, just gets the information for decompiling
	// the whole of the current function.
	AsmInitPtr(ret, csm[CodeScanMatch_func], cellmax);
}

stock CodeScanGetMatchAsm(csm[CodeScanner], ret[AsmContext]) {
	// Doesn't do any decompilation, just gets the information for decompiling
	// the currently found match.
	AsmInitPtr(ret, csm[CodeScanMatch_cip], cellmax);
}

stock CodeScanGetMatchFunc(csm[CodeScanner]) {
	// The stored value is relative to "DAT", return relative to "COD".
	return csm[CodeScanMatch_func] - gDat;
}

stock CodeScanGetMatchAddress(csm[CodeScanner]) {
	// The stored value is relative to "DAT", return relative to "COD".
	return csm[CodeScanMatch_cip] - gDat;
}

stock CodeScanGetMatchLength(csm[CodeScanner]) {
	return csm[CodeScanMatch_size];
}

stock CodeScanGetMatchType(csm[CodeScanner]) {
	// Lazilly get the names and types of functions when requested.
	if (csm[CodeScanMatch_type] >= SCANNER_FUNC_UNKNOWN) {
		csm[CodeScanMatch_name][0] = '\0';
		if (CodeScanGetFuncName(csm[CodeScanMatch_func], csm[CodeScanMatch_name])) {
			csm[CodeScanMatch_type] -= 4;
		} else {
			csm[CodeScanMatch_type] /= 2;
			// We could check for functions that are state implementations.
			// Currently public functions with states will only get their names
			// for the state stub, not for the various implementations.
		}
	}
	return csm[CodeScanMatch_type];
}

stock CodeScanGetMatchHeap(csm[CodeScanner]) {
	return csm[CodeScanMatch_heap];
}

stock CodeScanGetMatchStack(csm[CodeScanner]) {
	return csm[CodeScanMatch_stack];
}

stock CodeScanGetMatchHole(csm[CodeScanner], idx) {
	return csm[CodeScanMatch_holes][idx];
}

stock CodeScanGetMatchName(csm[CodeScanner], name[]) {
	if (csm[CodeScanMatch_type] >= SCANNER_FUNC_UNKNOWN) {
		// We get the type, because the type is based on the name.
		CodeScanGetMatchType(csm);
	}
	name[0] = '\0',
	strcat(name, csm[CodeScanMatch_name], 32);
}


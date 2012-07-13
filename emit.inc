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

#include "amx_header"
#include "amx_memory"
#include "dynamic_call"
#include "opcodes"
#include "phys_memory"

enum EmitError {
	EMIT_ERROR_NONE,
	EMIT_ERROR_OPCODE,
	EMIT_ERROR_OPERAND,
	EMIT_ERROR_SPACE,
};

enum EmitContext {
	EmitContext_buffer,
	EmitContext_buffer_size,
	EmitContext_buffer_offset,
	EmitContext_error_handler  // ErrorHandler(ctx[EmitContext], EmitError:error)
};

stock const EMIT_ARGUMENTS_OFFSET    =  0x0C;
stock const EMIT_LOCALS_OFFSET       = -0x04;
stock const EMIT_CALLER_FRAME_OFFSET =  0x00;
stock const EMIT_RETURN_ADDR_OFFSET  =  0x04;

stock const EMIT_CTRL_COD = 0;
stock const EMIT_CTRL_DAT = 1;
stock const EMIT_CTRL_HEA = 2;
stock const EMIT_CTRL_STP = 3;
stock const EMIT_CTRL_STK = 4;
stock const EMIT_CTRL_FRM = 5;
stock const EMIT_CTRL_CIP = 6;

// Internal functions:

static stock EmitError:EmitRaiseError(const ctx[EmitContext], EmitError:error) {
	if (error != EMIT_ERROR_NONE) {
		new fn = ctx[EmitContext_error_handler];
		if (fn != 0) {
			CallFunction(ctx[EmitContext_error_handler], ref(ctx), _:error);
		}
	}
	return error;
}

static stock EmitError:EmitCell(ctx[EmitContext], value) {
	if (ctx[EmitContext_buffer_offset] >= ctx[EmitContext_buffer_size]) {
		return EmitRaiseError(ctx, EMIT_ERROR_SPACE);
	}

	WriteAmxMemory(ctx[EmitContext_buffer] + ctx[EmitContext_buffer_offset], value);
	ctx[EmitContext_buffer_offset] += 4;

	return EMIT_ERROR_NONE;
}

static stock EmitError:EmitOpcode(ctx[EmitContext], Opcode:opcode) {
	if (opcode <= OP_NONE || opcode >= NUM_OPCODES) {
		return EmitRaiseError(ctx, EMIT_ERROR_OPCODE);
	}
	return EmitCell(ctx, _:opcode);
}

static stock EmitError:EmitOperand(ctx[EmitContext], value) {
	return EmitCell(ctx, value);
}

stock EmitError:EmitInstruction(ctx[EmitContext], Opcode:opcode, ...) {
	new EmitError:error = EMIT_ERROR_NONE;

	error = EmitOpcode(ctx, opcode);
	if (error != EMIT_ERROR_NONE) {
		return error;
	}

	static const STATIC_ARGS = 2;
	new num_opers = numargs() - STATIC_ARGS;

	for (new i = 0; i < num_opers; i++) {
		error = EmitOperand(ctx, getarg(STATIC_ARGS + i));
		if (error != EMIT_ERROR_NONE) {
			return error;
		}
	}

	return EMIT_ERROR_NONE;
}

static stock EmitGetJumpAddressFromOffset(ctx[EmitContext], offset) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new next_offset = 2 * 4; // offset to the next instruction
	new base = GetAmxBaseAddress() + amxhdr[AMX_HDR_DAT];
	new dest = ctx[EmitContext_buffer] + ctx[EmitContext_buffer_offset] + next_offset + offset;

	return base + dest;
}

static stock EmitJumpInstruction(ctx[EmitContext], opcode, offset) {
	return EmitInstruction(ctx, opcode, EmitGetJumpAddressFromOffset(ctx, offset));
}

// Core function:

stock EmitError:EmitInit(ctx[EmitContext], buffer[], size = sizeof(buffer)) {
	ctx[EmitContext_buffer] = ref(buffer);
	ctx[EmitContext_buffer_size] = size;
	ctx[EmitContext_buffer_offset] = 0;
	ctx[EmitContext_error_handler] = 0;
	return EMIT_ERROR_NONE;
}

stock EmitError:EmitSetErrorHandler(ctx[EmitContext], error_handler) {
	ctx[EmitContext_error_handler] = error_handler;
	return EMIT_ERROR_NONE;
}

stock EmitGetErrorHandler(const ctx[EmitContext]) {
	return ctx[EmitContext_error_handler];
}

stock EmitGetCode(const ctx[EmitContext]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);
	return ctx[EmitContext_buffer] + amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
}

stock EmitGetCodeSize(const ctx[EmitContext]) {
	return ctx[EmitContext_buffer_offset];
}

// Low level functions:

stock EmitError:EmitAdd(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_ADD);
}

stock EmitError:EmitAddC(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_ADD_C, value);
}

stock EmitError:EmitAddrAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_ADDR_ALT, offset);
}

stock EmitError:EmitAddrPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_ADDR_PRI, offset);
}

stock EmitError:EmitAlignAlt(ctx[EmitContext], number) {
	return EmitInstruction(ctx, OP_ALIGN_ALT, number);
}

stock EmitError:EmitAlignPri(ctx[EmitContext], number) {
	return EmitInstruction(ctx, OP_ALIGN_PRI, number);
}

stock EmitError:EmitAnd(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_AND);
}

stock EmitError:EmitBounds(ctx[EmitContext], bound) {
	return EmitInstruction(ctx, OP_BOUDNS, bound);
}

stock EmitError:EmitCall(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_CALL, address);
}

stock EmitError:EmitCmps(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_CMPS, nbytes);
}

stock EmitError:EmitConstAlt(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_CONST_ALT, value);
}

stock EmitError:EmitConstPri(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_CONST_PRI, value);
}

stock EmitError:EmitDec(ctx[EmitContext], addess) {
	return EmitInstruction(ctx, OP_DEC, address);
}

stock EmitError:EmitDecAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_DEC_ALT);
}

stock EmitError:EmitDecI(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_DEC_I);
}

stock EmitError:EmitDecPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_DEC_PRI);
}

stock EmitError:EmitDecS(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_DEC_S, offset);
}

stock EmitError:EmitFill(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_FILL, nbytes);
}

stock EmitError:EmitHalt(ctx[EmitContext], code) {
	return EmitInstruction(ctx, OP_HALT, code);
}

stock EmitError:EmitHeap(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_HEAP, nbytes);
}

stock EmitError:EmitIdxaddr(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_IDXADDR);
}

stock EmitError:EmitIdxaddrB(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_IDXADDR_B, shift);
}

stock EmitError:EmitInc(ctx[EmitContext], addess) {
	return EmitInstruction(ctx, OP_INC, address);
}

stock EmitError:EmitIncAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_INC_ALT);
}

stock EmitError:EmitIncI(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_INC_I);
}

stock EmitError:EmitIncPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_INC_PRI);
}

stock EmitError:EmitIncS(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_INC_S, offset);
}

stock EmitError:EmitInvert(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_INVERT);
}

stock EmitError:EmitJump(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JUMP, offset);
}

stock EmitError:EmitJzer(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JZER, offset);
}

stock EmitError:EmitJnz(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JNZ, offset);
}

stock EmitError:EmitJeq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JEQ, offset);
}

stock EmitError:EmitJneq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JNEQ, offset);
}

stock EmitError:EmitJless(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JLESS, offset);
}

stock EmitError:EmitJleq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JLEQ, offset);
}

stock EmitError:EmitJgrtr(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JGRTR, offset);
}

stock EmitError:EmitJgeq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JGEQ, offset);
}

stock EmitError:EmitJsless(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JSLESS, offset);
}

stock EmitError:EmitJsleq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JSLEQ, offset);
}

stock EmitError:EmitJsgrtr(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JSTRTR, offset);
}

stock EmitError:EmitJsgeq(ctx[EmitContext], offset) {
	return EmitJumpInstruction(ctx, OP_JSGEQ, offset);
}

stock EmitError:EmitLctrl(ctx[EmitContext], index) {
	assert(index >= 0 && index <= 6);
	return EmitInstruction(ctx, OP_LCTRL, index);
}

stock EmitError:EmitLidx(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_LIDX);
}

stock EmitError:EmitLidxB(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_LIDX_B, shift);
}

stock EmitError:EmitLoadAlt(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock EmitError:EmitLoadPri(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LOAD_PRI, address);
}

stock EmitError:EmitLoad(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock EmitError:EmitLoadI(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_LOAD_I);
}

stock EmitError:EmitLoadSAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LOAD_S_ALT, offset);
}

stock EmitError:EmitLoadSPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LOAD_S_PRI, offset);
}

stock EmitError:EmitLodbI(ctx[EmitContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return EmitInstruction(ctx, OP_LODB_I, nbytes);
}

stock EmitError:EmitLrefAlt(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LREF_ALT, address);
}

stock EmitError:EmitLrefPri(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LREF_PRI, address);
}

stock EmitError:EmitLrefSAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LREF_S_ALT, offset);
}

stock EmitError:EmitLrefSPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LREF_S_PRI, offset);
}

stock EmitError:EmitMoveAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_MOVE_ALT);
}

stock EmitError:EmitMovePri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_MOVE_PRI);
}

stock EmitError:EmitMovs(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_MOVS, nbytes);
}

stock EmitError:EmitNeg(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_NEG);
}

stock EmitError:EmitNop(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_NOP);
}

stock EmitError:EmitNot(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_NOT);
}

stock EmitError:EmitOr(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_OR);
}

stock EmitError:EmitPopAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_POP_ALT);
}

stock EmitError:EmitPopPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_POP_PRI);
}

stock EmitError:EmitProc(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PROC);
}

stock EmitError:EmitPushAddr(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_PUSH_ADDR, offset);
}

stock EmitError:EmitPushAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PUSH_ALT);
}

stock EmitError:EmitPushC(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_PUSH_C, value);
}

stock EmitError:EmitPushPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PUSH_PRI);
}

stock EmitError:EmitPush(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_PUSH, address);
}

stock EmitError:EmitPushS(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_PUSH_S, offset);
}

stock EmitError:EmitRet(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_RET);
}

stock EmitError:EmitRetn(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_RETN);
}

stock EmitError:EmitSctrl(ctx[EmitContext], index) {
	assert(index == 2 || index == 4 || index == 6);
	return EmitInstruction(ctx, OP_SCTRL, index);
}

stock EmitError:EmitSdiv(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SDIV);
}

stock EmitError:EmitSdivAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SDIV_ALT);
}

stock EmitError:EmitShl(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SHL);
}

stock EmitError:EmitShlCAlt(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

stock EmitError:EmitShlCPri(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

stock EmitError:EmitShrCAlt(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

stock EmitError:EmitShrCPri(ctx[EmitContext], shift) {
	return EmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

stock EmitError:EmitShr(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SHR);
}

stock EmitError:EmitSignAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SIGN_ALT);
}

stock EmitError:EmitSignPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SIGN_PRI);
}

stock EmitError:EmitSmul(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SMUL);
}

stock EmitError:EmitSmulC(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_SMUL_C, value);
}

stock EmitError:EmitSshr(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SSHR);
}

stock EmitError:EmitSrefAlt(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_SREF_ALT, address);
}

stock EmitError:EmitSrefPri(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_SREF_PRI, address);
}

stock EmitError:EmitSrefSAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_SREF_S_ALT, offset);
}

stock EmitError:EmitSrefSPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_SREF_S_PRI, offset);
}

stock EmitError:EmitStack(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_STACK, nbytes);
}

stock EmitError:EmitStorAlt(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_STOR_ALT, address);
}

stock EmitError:EmitStorPri(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_STOR_PRI, address);
}

stock EmitError:EmitStorI(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_STOR_I);
}

stock EmitError:EmitStorSAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_STOR_S_ALT, offset);
}

stock EmitError:EmitStorSPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_STOR_S_PRI, offset);
}

stock EmitError:EmitStrbI(ctx[EmitContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return EmitInstruction(ctx, OP_STRB_I, nbytes);
}

stock EmitError:EmitSub(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SUB);
}

stock EmitError:EmitSubAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SUB_ALT);
}

stock EmitError:EmitSwapAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SWAP_ALT);
}

stock EmitError:EmitSwapPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SWAP_PRI);
}

stock EmitError:EmitSysreqC(ctx[EmitContext], index) {
	return EmitInstruction(ctx, OP_SYSREQ_C, index);
}

stock EmitError:EmitSysreqD(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_SYSREQ_D, address);
}

stock EmitError:EmitSysreqPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_SYSREQ_PRI);
}

stock EmitError:EmitUdiv(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_UDIV);
}

stock EmitError:EmitUdivAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_UDIV_ALT);
}

stock EmitError:EmitUmul(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_UMUL);
}

stock EmitError:EmitXchg(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_XCHG);
}

stock EmitError:EmitXor(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_XOR);
}

stock EmitError:EmitZero(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_ZERO, address);
}

stock EmitError:EmitZeroAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_ZERO_ALT);
}

stock EmitError:EmitZeroPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_ZERO_PRI);
}

stock EmitError:EmitZeroS(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_ZERO_S, offset);
}

// Higher level functions:

stock EmitError:EmitCallNative(ctx[EmitContext], const name[]) {
	return EmitSysreqC(ctx, GetNativeIndexFromName(name));
}

stock EmitError:EmitPopArgs(ctx[EmitContext], n) {
	return EmitStack(ctx, (n + 1) * 4);
}

stock EmitError:EmitPushNumArgs(ctx[EmitContext], n) {
	return EmitPushC(ctx, 4 * n);
}

// Helpers:

stock EmitGetArgOffset(n) {
	return EMIT_ARGUMENTS_OFFSET + 4 * n;
}

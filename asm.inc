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

#if defined ASM_INC
	#endinput
#endif
#define ASM_INC

#include "amx_base"
#include "amx_header"
#include "amx_memory"
#include "dynamic_call"
#include "opcode"

#define asm_emit_add         AsmEmitAdd
#define asm_emit_add_c       AsmEmitAddC
#define asm_emit_addr_alt    AsmEmitAddrAlt
#define asm_emit_addr_pri    AsmEmitAddrPri
#define asm_emit_align_alt   AsmEmitAlignAlt
#define asm_emit_align_pri   AsmEmitAlignPri
#define asm_emit_and         AsmEmitAnd
#define asm_emit_bounds      AsmEmitBounds
#define asm_emit_call        AsmEmitCall
#define asm_emit_cmps        AsmEmitCmps
#define asm_emit_const_alt   AsmEmitConstAlt
#define asm_emit_const_pri   AsmEmitConstPri
#define asm_emit_dec         AsmEmitDec
#define asm_emit_dec_alt     AsmEmitDecAlt
#define asm_emit_dec_i       AsmEmitDecI
#define asm_emit_dec_pri     AsmEmitDecPri
#define asm_emit_dec_s       AsmEmitDecS
#define asm_emit_eq          AsmEmitEq
#define asm_emit_eq_c_alt    AsmEmitEqCAlt
#define asm_emit_eq_c_pri    AsmEmitEqCPri
#define asm_emit_fill        AsmEmitFill
#define asm_emit_geq         AsmEmitGeq
#define asm_emit_grtr        AsmEmitGrtr
#define asm_emit_halt        AsmEmitHalt
#define asm_emit_heap        AsmEmitHeap
#define asm_emit_idxaddr     AsmEmitIdxaddr
#define asm_emit_idxaddr_b   AsmEmitIdxaddrB
#define asm_emit_inc         AsmEmitInc
#define asm_emit_inc_alt     AsmEmitIncAlt
#define asm_emit_inc_i       AsmEmitIncI
#define asm_emit_inc_pri     AsmEmitIncPri
#define asm_emit_inc_s       AsmEmitIncS
#define asm_emit_invert      AsmEmitInvert
#define asm_emit_jeq         AsmEmitJeq
#define asm_emit_jgeq        AsmEmitJgeq
#define asm_emit_jgrtr       AsmEmitJgrtr
#define asm_emit_jleq        AsmEmitJleq
#define asm_emit_jless       AsmEmitJless
#define asm_emit_jneq        AsmEmitJneq
#define asm_emit_jnz         AsmEmitJnz
#define asm_emit_jsgeq       AsmEmitJsgeq
#define asm_emit_jsgrtr      AsmEmitJsgrtr
#define asm_emit_jsleq       AsmEmitJsleq
#define asm_emit_jsless      AsmEmitJsless
#define asm_emit_jump        AsmEmitJump
#define asm_emit_jzer        AsmEmitJzer
#define asm_emit_lctrl       AsmEmitLctrl
#define asm_emit_leq         AsmEmitLeq
#define asm_emit_less        AsmEmitLess
#define asm_emit_lidx        AsmEmitLidx
#define asm_emit_lidx_b      AsmEmitLidxB
#define asm_emit_load_alt    AsmEmitLoadAlt
#define asm_emit_load_i      AsmEmitLoadI
#define asm_emit_load_pri    AsmEmitLoadPri
#define asm_emit_load_s_alt  AsmEmitLoadSAlt
#define asm_emit_load_s_pri  AsmEmitLoadSPri
#define asm_emit_lodb_i      AsmEmitLodbI
#define asm_emit_lref_alt    AsmEmitLrefAlt
#define asm_emit_lref_pri    AsmEmitLrefPri
#define asm_emit_lref_s_alt  AsmEmitLrefSAlt
#define asm_emit_lref_s_pri  AsmEmitLrefSPri
#define asm_emit_move_alt    AsmEmitMoveAlt
#define asm_emit_move_pri    AsmEmitMovePri
#define asm_emit_movs        AsmEmitMovs
#define asm_emit_neg         AsmEmitNeg
#define asm_emit_neq         AsmEmitNeq
#define asm_emit_nop         AsmEmitNop
#define asm_emit_not         AsmEmitNot
#define asm_emit_or          AsmEmitOr
#define asm_emit_pop_alt     AsmEmitPopAlt
#define asm_emit_pop_pri     AsmEmitPopPri
#define asm_emit_proc        AsmEmitProc
#define asm_emit_push        AsmEmitPush
#define asm_emit_push_addr   AsmEmitPushAddr
#define asm_emit_push_alt    AsmEmitPushAlt
#define asm_emit_push_c      AsmEmitPushC
#define asm_emit_push_pri    AsmEmitPushPri
#define asm_emit_push_s      AsmEmitPushS
#define asm_emit_ret         AsmEmitRet
#define asm_emit_retn        AsmEmitRetn
#define asm_emit_sctrl       AsmEmitSctrl
#define asm_emit_sdiv        AsmEmitSdiv
#define asm_emit_sdiv_alt    AsmEmitSdivAlt
#define asm_emit_sgeq        AsmEmitSgeq
#define asm_emit_sgrtr       AsmEmitSgrtr
#define asm_emit_shl         AsmEmitShl
#define asm_emit_shl_c_alt   AsmEmitShlCAlt
#define asm_emit_shl_c_pri   AsmEmitShlCPri
#define asm_emit_shr         AsmEmitShr
#define asm_emit_shr_c_alt   AsmEmitShrCAlt
#define asm_emit_shr_c_pri   AsmEmitShrCPri
#define asm_emit_sign_alt    AsmEmitSignAlt
#define asm_emit_sign_pri    AsmEmitSignPri
#define asm_emit_sleq        AsmEmitSleq
#define asm_emit_sless       AsmEmitSless
#define asm_emit_smul        AsmEmitSmul
#define asm_emit_smul_c      AsmEmitSmulC
#define asm_emit_sref_alt    AsmEmitSrefAlt
#define asm_emit_sref_pri    AsmEmitSrefPri
#define asm_emit_sref_s_alt  AsmEmitSrefSAlt
#define asm_emit_sref_s_pri  AsmEmitSrefSPri
#define asm_emit_sshr        AsmEmitSshr
#define asm_emit_stack       AsmEmitStack
#define asm_emit_stor_alt    AsmEmitStorAlt
#define asm_emit_stor_i      AsmEmitStorI
#define asm_emit_stor_pri    AsmEmitStorPri
#define asm_emit_stor_s_alt  AsmEmitStorSAlt
#define asm_emit_stor_s_pri  AsmEmitStorSPri
#define asm_emit_strb_i      AsmEmitStrbI
#define asm_emit_sub         AsmEmitSub
#define asm_emit_sub_alt     AsmEmitSubAlt
#define asm_emit_swap_alt    AsmEmitSwapAlt
#define asm_emit_swap_pri    AsmEmitSwapPri
#define asm_emit_sysreq_c    AsmEmitSysreqC
#define asm_emit_sysreq_d    AsmEmitSysreqD
#define asm_emit_udiv        AsmEmitUdiv
#define asm_emit_udiv_alt    AsmEmitUdivAlt
#define asm_emit_umul        AsmEmitUmul
#define asm_emit_xchg        AsmEmitXchg
#define asm_emit_xor         AsmEmitXor
#define asm_emit_zero        AsmEmitZero
#define asm_emit_zero_alt    AsmEmitZeroAlt
#define asm_emit_zero_pri    AsmEmitZeroPri
#define asm_emit_zero_s      AsmEmitZeroS

enum AsmError {
	ASM_ERROR_NONE,
	ASM_ERROR_OPCODE,
	ASM_ERROR_OPERAND,
	ASM_ERROR_SPACE,
};

enum AsmContext {
	AsmContext_buffer,
	AsmContext_buffer_size,
	AsmContext_buffer_offset,
	AsmContext_error_handler  // ErrorHandler(ctx[AsmContext], AsmError:error)
};

stock const ASM_ARGUMENTS_OFFSET    =  0x0C;
stock const ASM_LOCALS_OFFSET       = -0x04;
stock const ASM_CALLER_FRAME_OFFSET =  0x00;
stock const ASM_RETURN_ADDR_OFFSET  =  0x04;

stock const ASM_CTRL_COD = 0;
stock const ASM_CTRL_DAT = 1;
stock const ASM_CTRL_HEA = 2;
stock const ASM_CTRL_STP = 3;
stock const ASM_CTRL_STK = 4;
stock const ASM_CTRL_FRM = 5;
stock const ASM_CTRL_CIP = 6;

// Internal functions:

static stock AsmError:AsmRaiseError(const ctx[AsmContext], AsmError:error) {
	if (error != ASM_ERROR_NONE) {
		new fn = ctx[AsmContext_error_handler];
		if (fn != 0) {
			CallFunction(ctx[AsmContext_error_handler], ref(ctx), _:error);
		}
	}
	return error;
}

static stock AsmError:AsmEmitCell(ctx[AsmContext], value) {
	if (ctx[AsmContext_buffer_offset] >= ctx[AsmContext_buffer_size]) {
		return AsmRaiseError(ctx, ASM_ERROR_SPACE);
	}

	WriteAmxMemory(ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset], value);
	ctx[AsmContext_buffer_offset] += 4;

	return ASM_ERROR_NONE;
}

static stock AsmError:AsmEmitOpcode(ctx[AsmContext], Opcode:opcode) {
	if (opcode <= OP_NONE || _:opcode >= NUM_OPCODES) {
		return AsmRaiseError(ctx, ASM_ERROR_OPCODE);
	}
	return AsmEmitCell(ctx, _:RelocateOpcode(opcode));
}

static stock AsmError:AsmEmitOperand(ctx[AsmContext], value) {
	return AsmEmitCell(ctx, value);
}

static stock AsmError:AsmEmitInstruction(ctx[AsmContext], Opcode:opcode, ...) {
	new AsmError:error = ASM_ERROR_NONE;

	error = AsmEmitOpcode(ctx, opcode);
	if (error != ASM_ERROR_NONE) {
		return error;
	}

	static const STATIC_ARGS = 2;
	new num_opers = numargs() - STATIC_ARGS;

	for (new i = 0; i < num_opers; i++) {
		error = AsmEmitOperand(ctx, getarg(STATIC_ARGS + i));
		if (error != ASM_ERROR_NONE) {
			return error;
		}
	}

	return ASM_ERROR_NONE;
}

static stock AsmGetJumpAddressFromOffset(ctx[AsmContext], offset) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);

	new next_offset = 2 * 4; // offset to the next instruction
	new base = GetAmxBaseAddress() + amxhdr[AMX_HDR_DAT];
	new dest = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + next_offset + offset;

	return base + dest;
}

static stock AsmEmitJumpInstruction(ctx[AsmContext], opcode, offset) {
	return AsmEmitInstruction(ctx, opcode, AsmGetJumpAddressFromOffset(ctx, offset));
}

// Core functions:

stock AsmError:AsmInit(ctx[AsmContext], buffer[], size = sizeof(buffer)) {
	AsmInitPtr(ctx, ref(buffer), size)
}

stock AsmError:AsmInitPtr(ctx[AsmContext], buffer, size) {
	ctx[AsmContext_buffer] = buffer;
	ctx[AsmContext_buffer_size] = size;
	ctx[AsmContext_buffer_offset] = 0;
	ctx[AsmContext_error_handler] = 0;
	return ASM_ERROR_NONE;
}

stock AsmError:AsmSetErrorHandler(ctx[AsmContext], error_handler) {
	ctx[AsmContext_error_handler] = error_handler;
	return ASM_ERROR_NONE;
}

stock AsmGetErrorHandler(const ctx[AsmContext]) {
	return ctx[AsmContext_error_handler];
}

stock AsmGetCode(const ctx[AsmContext]) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	return ctx[AsmContext_buffer] + amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
}

stock AsmGetCodeSize(const ctx[AsmContext]) {
	return ctx[AsmContext_buffer_offset];
}

// Low level functions:

stock AsmError:AsmEmitAdd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ADD);
}

stock AsmError:AsmEmitAddC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_ADD_C, value);
}

stock AsmError:AsmEmitAddrAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_ALT, offset);
}

stock AsmError:AsmEmitAddrPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_PRI, offset);
}

stock AsmError:AsmEmitAlignAlt(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_ALT, number);
}

stock AsmError:AsmEmitAlignPri(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_PRI, number);
}

stock AsmError:AsmEmitAnd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_AND);
}

stock AsmError:AsmEmitBounds(ctx[AsmContext], bound) {
	return AsmEmitInstruction(ctx, OP_BOUDNS, bound);
}

stock AsmError:AsmEmitCall(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_CALL, address);
}

stock AsmError:AsmEmitCmps(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_CMPS, nbytes);
}

stock AsmError:AsmEmitConstAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_ALT, value);
}

stock AsmError:AsmEmitConstPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_PRI, value);
}

stock AsmError:AsmEmitDec(ctx[AsmContext], addess) {
	return AsmEmitInstruction(ctx, OP_DEC, address);
}

stock AsmError:AsmEmitDecAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_ALT);
}

stock AsmError:AsmEmitDecI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_I);
}

stock AsmError:AsmEmitDecPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_PRI);
}

stock AsmError:AsmEmitDecS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_DEC_S, offset);
}

stock AsmError:AsmEmitEq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_EQ);
}

stock AsmError:AsmEmitEqCAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_ALT, value);
}

stock AsmError:AsmEmitEqCPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_PRI, value);
}

stock AsmError:AsmEmitFill(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_FILL, nbytes);
}

stock AsmError:AsmEmitGeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GEQ);
}

stock AsmError:AsmEmitGrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GRTR);
}

stock AsmError:AsmEmitHalt(ctx[AsmContext], code) {
	return AsmEmitInstruction(ctx, OP_HALT, code);
}

stock AsmError:AsmEmitHeap(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_HEAP, nbytes);
}

stock AsmError:AsmEmitIdxaddr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_IDXADDR);
}

stock AsmError:AsmEmitIdxaddrB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_IDXADDR_B, shift);
}

stock AsmError:AsmEmitInc(ctx[AsmContext], addess) {
	return AsmEmitInstruction(ctx, OP_INC, address);
}

stock AsmError:AsmEmitIncAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_ALT);
}

stock AsmError:AsmEmitIncI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_I);
}

stock AsmError:AsmEmitIncPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_PRI);
}

stock AsmError:AsmEmitIncS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_INC_S, offset);
}

stock AsmError:AsmEmitInvert(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INVERT);
}

stock AsmError:AsmEmitJump(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JUMP, address);
}

stock AsmError:AsmEmitJumpRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JUMP, offset);
}

stock AsmError:AsmEmitJzer(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JZER, offset);
}

stock AsmError:AsmEmitJzerRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JZER, offset);
}

stock AsmError:AsmEmitJnz(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNZ, address);
}

stock AsmError:AsmEmitJnzRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNZ, offset);
}

stock AsmError:AsmEmitJeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JEQ, address);
}

stock AsmError:AsmEmitJeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JEQ, offset);
}

stock AsmError:AsmEmitJneq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNEQ, address);
}

stock AsmError:AsmEmitJneqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNEQ, offset);
}

stock AsmError:AsmEmitJless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLESS, address);
}

stock AsmError:AsmEmitJlessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLESS, offset);
}

stock AsmError:AsmEmitJleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLEQ, address);
}

stock AsmError:AsmEmitJleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLEQ, offset);
}

stock AsmError:AsmEmitJgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGRTR, address);
}

stock AsmError:AsmEmitJgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGRTR, offset);
}

stock AsmError:AsmEmitJgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGEQ, address);
}

stock AsmError:AsmEmitJgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGEQ, offset);
}

stock AsmError:AsmEmitJsless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLESS, address);
}

stock AsmError:AsmEmitJslessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLESS, offset);
}

stock AsmError:AsmEmitJsleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLEQ, address);
}

stock AsmError:AsmEmitJsleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLEQ, offset);
}

stock AsmError:AsmEmitJsgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSTRTR, address);
}

stock AsmError:AsmEmitJsgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSTRTR, offset);
}

stock AsmError:AsmEmitJsgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSGEQ, address);
}

stock AsmError:AsmEmitJsgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSGEQ, offset);
}

stock AsmError:AsmEmitLctrl(ctx[AsmContext], index) {
	assert(index >= 0 && index <= 6);
	return AsmEmitInstruction(ctx, OP_LCTRL, index);
}

stock AsmError:AsmEmitLeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LEQ);
}

stock AsmError:AsmEmitLess(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LESS);
}

stock AsmError:AsmEmitLidx(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LIDX);
}

stock AsmError:AsmEmitLidxB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_LIDX_B, shift);
}

stock AsmError:AsmEmitLoadAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock AsmError:AsmEmitLoadPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_PRI, address);
}

stock AsmError:AsmEmitLoad(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock AsmError:AsmEmitLoadI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LOAD_I);
}

stock AsmError:AsmEmitLoadSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_ALT, offset);
}

stock AsmError:AsmEmitLoadSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_PRI, offset);
}

stock AsmError:AsmEmitLodbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_LODB_I, nbytes);
}

stock AsmError:AsmEmitLrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_ALT, address);
}

stock AsmError:AsmEmitLrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_PRI, address);
}

stock AsmError:AsmEmitLrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_ALT, offset);
}

stock AsmError:AsmEmitLrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_PRI, offset);
}

stock AsmError:AsmEmitMoveAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_ALT);
}

stock AsmError:AsmEmitMovePri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_PRI);
}

stock AsmError:AsmEmitMovs(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_MOVS, nbytes);
}

stock AsmError:AsmEmitNeg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEG);
}

stock AsmError:AsmEmitNeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEQ);
}

stock AsmError:AsmEmitNop(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOP);
}

stock AsmError:AsmEmitNot(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOT);
}

stock AsmError:AsmEmitOr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_OR);
}

stock AsmError:AsmEmitPopAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_ALT);
}

stock AsmError:AsmEmitPopPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_PRI);
}

stock AsmError:AsmEmitProc(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PROC);
}

stock AsmError:AsmEmitPushAddr(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_ADDR, offset);
}

stock AsmError:AsmEmitPushAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_ALT);
}

stock AsmError:AsmEmitPushC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_PUSH_C, value);
}

stock AsmError:AsmEmitPushPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_PRI);
}

stock AsmError:AsmEmitPush(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_PUSH, address);
}

stock AsmError:AsmEmitPushS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_S, offset);
}

stock AsmError:AsmEmitRet(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RET);
}

stock AsmError:AsmEmitRetn(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RETN);
}

stock AsmError:AsmEmitSctrl(ctx[AsmContext], index) {
	assert(index == 2 || index == 4 || index == 6);
	return AsmEmitInstruction(ctx, OP_SCTRL, index);
}

stock AsmError:AsmEmitSdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV);
}

stock AsmError:AsmEmitSdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV_ALT);
}

stock AsmError:AsmEmitSgeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGEQ);
}

stock AsmError:AsmEmitSgrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGRTR);
}

stock AsmError:AsmEmitShl(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHL);
}

stock AsmError:AsmEmitShlCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

stock AsmError:AsmEmitShlCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

stock AsmError:AsmEmitShrCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

stock AsmError:AsmEmitShrCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

stock AsmError:AsmEmitShr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHR);
}

stock AsmError:AsmEmitSignAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_ALT);
}

stock AsmError:AsmEmitSignPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_PRI);
}

stock AsmError:AsmEmitSleq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLEQ);
}

stock AsmError:AsmEmitSless(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLESS);
}

stock AsmError:AsmEmitSmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SMUL);
}

stock AsmError:AsmEmitSmulC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_SMUL_C, value);
}

stock AsmError:AsmEmitSshr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SSHR);
}

stock AsmError:AsmEmitSrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_ALT, address);
}

stock AsmError:AsmEmitSrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_PRI, address);
}

stock AsmError:AsmEmitSrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_ALT, offset);
}

stock AsmError:AsmEmitSrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_PRI, offset);
}

stock AsmError:AsmEmitStack(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_STACK, nbytes);
}

stock AsmError:AsmEmitStorAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_ALT, address);
}

stock AsmError:AsmEmitStorPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_PRI, address);
}

stock AsmError:AsmEmitStorI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_STOR_I);
}

stock AsmError:AsmEmitStorSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_ALT, offset);
}

stock AsmError:AsmEmitStorSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_PRI, offset);
}

stock AsmError:AsmEmitStrbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_STRB_I, nbytes);
}

stock AsmError:AsmEmitSub(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB);
}

stock AsmError:AsmEmitSubAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB_ALT);
}

stock AsmError:AsmEmitSwapAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_ALT);
}

stock AsmError:AsmEmitSwapPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_PRI);
}

stock AsmError:AsmEmitSysreqC(ctx[AsmContext], index) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_C, index);
}

stock AsmError:AsmEmitSysreqD(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_D, address);
}

stock AsmError:AsmEmitSysreqPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_PRI);
}

stock AsmError:AsmEmitUdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV);
}

stock AsmError:AsmEmitUdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV_ALT);
}

stock AsmError:AsmEmitUmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UMUL);
}

stock AsmError:AsmEmitXchg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XCHG);
}

stock AsmError:AsmEmitXor(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XOR);
}

stock AsmError:AsmEmitZero(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_ZERO, address);
}

stock AsmError:AsmEmitZeroAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_ALT);
}

stock AsmError:AsmEmitZeroPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_PRI);
}

stock AsmError:AsmEmitZeroS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ZERO_S, offset);
}

// Higher level functions:

stock AsmError:AsmEmitCallNative(ctx[AsmContext], const name[]) {
	return AsmEmitSysreqD(ctx, GetNativeAddressFromName(name));
}

stock AsmError:AsmEmitPopArgs(ctx[AsmContext], n) {
	return AsmEmitStack(ctx, (n + 1) * 4);
}

stock AsmError:AsmEmitPushNumArgs(ctx[AsmContext], n) {
	return AsmEmitPushC(ctx, 4 * n);
}

stock AsmError:AsmEmitPushArg(ctx[AsmContext], n) {
	return AsmEmitPushS(ctx, AsmGetArgOffset(n));
}

// Helpers:

stock AsmGetArgOffset(n) {
	return ASM_ARGUMENTS_OFFSET + 4 * n;
}

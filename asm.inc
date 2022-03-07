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

#if defined ASM_INC
	#endinput
#endif
#define ASM_INC

/**
 * <library name="amx_assembly asm" summary="AMX Assembly Library: Assembly code generation.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include <core>

#include "amx_base"
#include "amx_header"
#include "amx_memory"
#include "asm_macros"
#include "dynamic_call"
#include "opcode"

#if !defined ASM_MAX_LABELS
	#define ASM_MAX_LABELS (8)
#endif

/// <p/>

/// <library>amx_assembly asm</library>
enum AsmError {
	ASM_ERROR_NONE,
	ASM_ERROR_OPCODE,
	ASM_ERROR_OPERAND,
	ASM_ERROR_SPACE,
	ASM_ERROR_LABEL_OVERFLOW,
	ASM_ERROR_LABEL_DUPLICATE,
};

/// <library>amx_assembly asm</library>
const AsmError:AsmError__ = AsmError;

/// <library>amx_assembly asm</library>
enum AsmContext {
	AsmContext_buffer,
	AsmContext_buffer_size,
	AsmContext_buffer_offset,
	AsmContext_error,
	AsmContext_error_handler,  // ErrorHandler(ctx[AsmContext])
	AsmContext_label_names[ASM_MAX_LABELS],
	// All labels in PAWN should be 4-byte-aligned (1 cell in 32-bit).  This
	// means the bottom two bits are always `0b00`.  We re-use this data to
	// store two bits of information - is this label resolved (i.e. do we know
	// the true address yet), and is this use of the label relative or absolute?
	// 
	// If the label is NOT resolved, the current value is the start pointer of a
	// linked list of jump-ahead uses of the label (relative to DAT), i.e. jumps
	// waiting to know the label's address when it is eventually defined.  If
	// the label IS resolved, it is just the absolute address of the label
	// (relative to COD) so that any new uses can be resolved instantly.  The
	// lowest bit determines which.
	// 
	// If a jump to an unknown label is emitted, the value is the next item in
	// the linked list (potentially NULL), and the bottom bit is instead used to
	// determine which jump type this is - relative (1) or absolute (0).
	AsmContext_labels[ASM_MAX_LABELS],
};

/// <library>amx_assembly asm</library>
const AsmContext:AsmContext__ = AsmContext;

/// <library>amx_assembly asm</library>
stock const ASM_ARGUMENTS_OFFSET    =  0x0C;

/// <library>amx_assembly asm</library>
stock const ASM_LOCALS_OFFSET       = -0x04;

/// <library>amx_assembly asm</library>
stock const ASM_CALLER_FRAME_OFFSET =  0x00;

/// <library>amx_assembly asm</library>
stock const ASM_RETURN_ADDR_OFFSET  =  0x04;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_COD = 0;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_DAT = 1;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_HEA = 2;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_STP = 3;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_STK = 4;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_FRM = 5;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_CIP = 6;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_JIT = 7;

/// <library>amx_assembly asm</library>
stock const ASM_CTRL_JMP = 8;

/// <library>amx_assembly asm</library>
static gPreviousWriteOffset = cellmin;

// Internal functions:

/// <library>amx_assembly asm</library>
static stock AsmError:AsmRaiseError(ctx[AsmContext], AsmError:error) {
	if (error != ASM_ERROR_NONE) {
		AsmSetError(ctx, error);
		if (ctx[AsmContext_error_handler] != 0) {
			CallFunction(ctx[AsmContext_error_handler], ref(ctx));
		}
	}
	return error;
}

/// <library>amx_assembly asm</library>
static stock AsmError:AsmEmitCell(ctx[AsmContext], value) {
	if (ctx[AsmContext_buffer_offset] >= ctx[AsmContext_buffer_size]) {
		return AsmRaiseError(ctx, ASM_ERROR_SPACE);
	}

	WriteAmxMemory(ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset], value);
	ctx[AsmContext_buffer_offset] += 4;

	return ASM_ERROR_NONE;
}

// Label functions:

#define AsmIsLabelResolved(%2,%0)    (%2[AsmContext_labels][(%0)] & 1)
#define AsmIsJumpRelative(%0)        ((%0) & 1)
#define AsmSetJumpRelative(%2,%0,%1) (%2[AsmContext_labels][(%0)] & (%1))
#define AsmGetLabel(%2,%0)           (%2[AsmContext_labels][(%0)] & ~1)
#define AsmSetLabel(%2,%0,%1)        (%2[AsmContext_labels][(%0)] = (%1) | 1)

/// <library>amx_assembly asm</library>
static stock AsmHashLabel(const label[]) {
	// Return the Bernstein hash of this label.  This is NOT a cryptographically
	// secure hash, but is sufficient for our uses.
	new hash = -1;
	new i = -1;
	new ch = 0;
	while ((ch = label[++i])) {
		hash = hash * 33 + ch;
	}
	return hash;
}

/// <library>amx_assembly asm</library>
static stock AsmFindLabelIndex(const ctx[AsmContext], hash) {
	for (new i = 0; i != ASM_MAX_LABELS; ++i) {
		if (ctx[AsmContext_label_names][i] == hash) {
			return i;
		}
	}
	return -1;
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLabelStringize(ctx[AsmContext], const label[]) {
	// Everything works on the hashes - it saves storing the strings.
	new hash = AsmHashLabel(label);
	// See if this label already exists.
	new idx = AsmFindLabelIndex(ctx, hash);
	// Get the true address.  Use an offset of -8 because
	// `AsmGetJumpAddressFromOffset` assumes the jump is from the start of the
	// next instruction (8 bytes later), while we want it from right here, so
	// shift back accordingly.
	new datAddr = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset];
	new codAddr = AsmGetJumpAddressFromOffset(ctx, -8);
	if (idx == -1) {
		// Doesn't exist.  Get a free slot.
		idx = AsmFindLabelIndex(ctx, 0);
		if (idx == -1) {
			return AsmRaiseError(ctx, ASM_ERROR_LABEL_OVERFLOW);
		}
		ctx[AsmContext_label_names][idx] = hash;
	}
	if (AsmIsLabelResolved(ctx, idx)) {
		// Check that no other labels have the same name.
		return AsmRaiseError(ctx, ASM_ERROR_LABEL_DUPLICATE);
	} else {
		// Loop over all the pending items in the linked list.
		new cur = AsmGetLabel(ctx, idx);
		while (cur) {
			new next = ReadAmxMemory(cur);
			if (AsmIsJumpRelative(next)) {
				WriteAmxMemory(cur, datAddr - cur - 4);
			} else {
				WriteAmxMemory(cur, codAddr);
			}
			cur = next & ~1;
		}
	}
	// Store the label's absolute address, along with a flag to mark that it is
	// resolved.
	AsmSetLabel(ctx, idx, codAddr);
	return ASM_ERROR_NONE;
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJumpStringize(ctx[AsmContext], const label[], bool:relative) {
	new hash = AsmHashLabel(label);
	new idx = AsmFindLabelIndex(ctx, hash);
	new datAddr = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset];
	new AsmError:error = ASM_ERROR_NONE;
	if (idx == -1) {
		// Doesn't exist.  Get a free slot.
		idx = AsmFindLabelIndex(ctx, 0);
		if (idx == -1) {
			return AsmRaiseError(ctx, ASM_ERROR_LABEL_OVERFLOW);
		}
		ctx[AsmContext_label_names][idx] = hash;
	}
	if (AsmIsLabelResolved(ctx, idx)) {
		// The label was in the past, jump to that.
		new cur = AsmGetLabel(ctx, idx);
		if (relative) {
			error = AsmEmitCell(ctx, cur - datAddr - 4);
		} else {
			error = AsmEmitCell(ctx, cur);
		}
	} else {
		// The label is not yet known, store this use in the list.
		new cur = AsmGetLabel(ctx, idx);
		if (relative) {
			error = AsmEmitCell(ctx, cur | 1);
		} else {
			error = AsmEmitCell(ctx, cur);
		}
		if (error == ASM_ERROR_NONE) {
			// Store to the list only if the output was successful.
			ctx[AsmContext_labels][idx] = datAddr;
		}
	}
	return error;
}

// Core functions:

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitOpcode(ctx[AsmContext], Opcode:opcode) {
	if (opcode <= OP_NONE || _:opcode >= NUM_OPCODES) {
		return AsmRaiseError(ctx, ASM_ERROR_OPCODE);
	}
	return AsmEmitCell(ctx, _:RelocateOpcode(opcode));
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitOperand(ctx[AsmContext], value) {
	return AsmEmitCell(ctx, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitInstruction(ctx[AsmContext], Opcode:opcode, ...) {
	// if there's an error while writing then backtracking is useful
	gPreviousWriteOffset = ctx[AsmContext_buffer_offset];

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

/// <library>amx_assembly asm</library>
stock AsmGetJumpAddressFromOffset(const ctx[AsmContext], offset) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);

	new next_offset = 2 * 4; // offset to the next instruction
	new base = GetAmxBaseAddress() + amxhdr[AMX_HDR_DAT];
	new dest = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset] + next_offset + offset;

	return base + dest;
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJumpInstruction(ctx[AsmContext], Opcode:opcode, offset) {
	return AsmEmitInstruction(ctx, opcode, AsmGetJumpAddressFromOffset(ctx, offset));
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJumpLabelInstruction(ctx[AsmContext], Opcode:opcode, const label[], bool:relative = false) {
	// if there's an error while writing then backtracking is useful
	gPreviousWriteOffset = ctx[AsmContext_buffer_offset];

	new AsmError:error = ASM_ERROR_NONE;

	error = AsmEmitOpcode(ctx, opcode);
	if (error != ASM_ERROR_NONE) {
		return error;
	}
	return AsmEmitJumpStringize(ctx, label, relative);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmInitPtr(ctx[AsmContext], buffer, size) {
	ctx[AsmContext_buffer] = buffer;
	ctx[AsmContext_buffer_size] = size;
	ctx[AsmContext_buffer_offset] = 0;
	ctx[AsmContext_error_handler] = 0;
	for (new i = 0; i != ASM_MAX_LABELS; ++i) {
		ctx[AsmContext_label_names][i] = 0;
		ctx[AsmContext_labels][i] = 0;
	}
	return ASM_ERROR_NONE;
}

/// <library>amx_assembly asm</library>
stock AsmGetPreviousWriteOffset() {
	return gPreviousWriteOffset;
}

/// <library>amx_assembly asm</library>
stock AsmGetBufferSize(const ctx[AsmContext]) {
	return ctx[AsmContext_buffer_size] - ctx[AsmContext_buffer_offset];
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmInit(ctx[AsmContext], buffer[], size = sizeof(buffer)) {
	AsmInitPtr(ctx, ref(buffer), size * 4);
}

/// <library>amx_assembly asm</library>
stock AsmGetCode(const ctx[AsmContext]) {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);
	return ctx[AsmContext_buffer] + amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
}

/// <library>amx_assembly asm</library>
stock AsmGetCodeSize(const ctx[AsmContext]) {
	return ctx[AsmContext_buffer_offset];
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmGetError(const ctx[AsmContext]) {
	return AsmError:ctx[AsmContext_error];
}

/// <library>amx_assembly asm</library>
stock AsmSetError(ctx[AsmContext], AsmError:error) {
	ctx[AsmContext_error] = _:error;
}

/// <library>amx_assembly asm</library>
stock AsmClearError(ctx[AsmContext]) {
	AsmSetError(ctx, ASM_ERROR_NONE);
}

/// <library>amx_assembly asm</library>
stock AsmGetErrorHandler(const ctx[AsmContext]) {
	return ctx[AsmContext_error_handler];
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmSetErrorHandler(ctx[AsmContext], error_handler) {
	ctx[AsmContext_error_handler] = error_handler;
	return ASM_ERROR_NONE;
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmSetErrorHandlerName(ctx[AsmContext], const error_handler[]) {
	ctx[AsmContext_error_handler] = GetPublicAddressFromName(error_handler);
	return ASM_ERROR_NONE;
}

/// <library>amx_assembly asm</library>
stock AsmEmitPadding(ctx[AsmContext], Opcode:op = OP_NOP) {
	// Must not have parameters, to make the padding valid.
	if (!IsOpcodeValid(op) || gAMXOpcodeParameterCounts[_:op]) {
		op = OP_NOP;
	}
	// Resolve it for speed.
	op = RelocateOpcode(op);
	new
		cur = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_offset],
		end = ctx[AsmContext_buffer] + ctx[AsmContext_buffer_size];
	while (cur < end) {
		WriteAmxMemory(cur, _:op);
		cur += 4;
	}
	ctx[AsmContext_buffer_offset] = ctx[AsmContext_buffer_size];
}

// Low level functions:

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAdd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ADD);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAddC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_ADD_C, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAddrAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_ALT, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAddrPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ADDR_PRI, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAlignAlt(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_ALT, number);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAlignPri(ctx[AsmContext], number) {
	return AsmEmitInstruction(ctx, OP_ALIGN_PRI, number);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitAnd(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_AND);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitBounds(ctx[AsmContext], bound) {
	return AsmEmitInstruction(ctx, OP_BOUNDS, bound);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitBreak(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_BREAK);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitCall(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_CALL, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitCallAbs(ctx[AsmContext], address) {
	new hdr[AMX_HDR];
	GetAmxHeader(hdr);
	return AsmEmitInstruction(ctx, OP_CALL, address + GetAmxBaseAddress() + hdr[AMX_HDR_COD]);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitCallLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_CALL, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitCmps(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_CMPS, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitConstAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_ALT, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitConstPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_CONST_PRI, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitDec(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_DEC, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitDecAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitDecI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_I);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitDecPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_DEC_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitDecS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_DEC_S, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitEq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_EQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitEqCAlt(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_ALT, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitEqCPri(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_EQ_C_PRI, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitFill(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_FILL, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitGeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GEQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitGrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_GRTR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitHalt(ctx[AsmContext], code) {
	return AsmEmitInstruction(ctx, OP_HALT, code);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitHeap(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_HEAP, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIdxaddr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_IDXADDR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIdxaddrB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_IDXADDR_B, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitInc(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_INC, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIncAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIncI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_I);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIncPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INC_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitIncS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_INC_S, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitInvert(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_INVERT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JGRTR, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JGRTR, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JLESS, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJlessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JLESS, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJneq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJneqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJnz(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JNZ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJnzRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JNZ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgeq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSGEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgeqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSGEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgrtr(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSGRTR, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgrtrRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSGRTR, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsleq(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLEQ, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsleqRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLEQ, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsless(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JSLESS, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJslessRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JSLESS, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJump(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JUMP, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJumpRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JUMP, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJzer(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_JZER, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJzerRel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JZER, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJrel(ctx[AsmContext], offset) {
	return AsmEmitJumpInstruction(ctx, OP_JREL, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JGEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJgrtrLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JGRTR, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJleqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JLEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJlessLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JLESS, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJneqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JNEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJnzLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JNZ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgeqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSGEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsgrtrLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSGRTR, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJsleqLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSLEQ, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJslessLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JSLESS, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJumpLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JUMP, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJzerLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JZER, label);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitJrelLabelStringize(ctx[AsmContext], const label[]) {
	return AsmEmitJumpLabelInstruction(ctx, OP_JREL, label, true);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLctrl(ctx[AsmContext], index) {
	assert(index >= 0 && index <= 8);
	return AsmEmitInstruction(ctx, OP_LCTRL, index);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LEQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLess(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LESS);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLidx(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LIDX);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLidxB(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_LIDX_B, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoadAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoadPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_PRI, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoad(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LOAD_ALT, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoadI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_LOAD_I);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoadSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_ALT, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLoadSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LOAD_S_PRI, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLodbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_LODB_I, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_ALT, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_LREF_PRI, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_ALT, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitLrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_LREF_S_PRI, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitMoveAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitMovePri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_MOVE_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitMovs(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_MOVS, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitNeg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEG);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitNeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NEQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitNop(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOP);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitNot(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_NOT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitOr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_OR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPopAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPopPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_POP_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitProc(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PROC);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushAdr(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_ADR, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_PUSH_C, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_PUSH_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPush(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_PUSH, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_PUSH_S, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitRet(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RET);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitRetn(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_RETN);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSctrl(ctx[AsmContext], index) {
	assert(index == 2 || 4 <= index <= 6 || index == 8);
	return AsmEmitInstruction(ctx, OP_SCTRL, index);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SDIV_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSgeq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGEQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSgrtr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SGRTR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShl(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHL);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShlCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_ALT, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShlCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHL_C_PRI, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShrCAlt(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_ALT, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShrCPri(ctx[AsmContext], shift) {
	return AsmEmitInstruction(ctx, OP_SHR_C_PRI, shift);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitShr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SHR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSignAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSignPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SIGN_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSleq(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLEQ);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSless(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SLESS);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SMUL);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSmulC(ctx[AsmContext], value) {
	return AsmEmitInstruction(ctx, OP_SMUL_C, value);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSshr(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SSHR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSrefAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_ALT, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSrefPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SREF_PRI, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSrefSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_ALT, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSrefSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_SREF_S_PRI, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStack(ctx[AsmContext], nbytes) {
	return AsmEmitInstruction(ctx, OP_STACK, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStorAlt(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_ALT, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStorPri(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_STOR_PRI, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStorI(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_STOR_I);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStorSAlt(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_ALT, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStorSPri(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_STOR_S_PRI, offset);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitStrbI(ctx[AsmContext], nbytes) {
	assert(nbytes == 1 || nbytes == 2 || nbytes == 4);
	return AsmEmitInstruction(ctx, OP_STRB_I, nbytes);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSub(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSubAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SUB_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSwapAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSwapPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SWAP_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSysreqC(ctx[AsmContext], index) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_C, index);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSysreqD(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_D, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSysreqPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_SYSREQ_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitUdiv(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitUdivAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UDIV_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitUmul(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_UMUL);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitXchg(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XCHG);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitXor(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_XOR);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitZero(ctx[AsmContext], address) {
	return AsmEmitInstruction(ctx, OP_ZERO, address);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitZeroAlt(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_ALT);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitZeroPri(ctx[AsmContext]) {
	return AsmEmitInstruction(ctx, OP_ZERO_PRI);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitZeroS(ctx[AsmContext], offset) {
	return AsmEmitInstruction(ctx, OP_ZERO_S, offset);
}

// Higher level functions:

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitSysreq(ctx[AsmContext], const name[]) {
	return AsmEmitSysreqC(ctx, GetNativeIndexFromName(name));
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPopArgs(ctx[AsmContext], n) {
	return AsmEmitStack(ctx, (n + 1) * 4);
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushArg(ctx[AsmContext], n) {
	return AsmEmitPushS(ctx, AsmGetArgOffset(n));
}

/// <library>amx_assembly asm</library>
stock AsmError:AsmEmitPushNumArgs(ctx[AsmContext], n) {
	return AsmEmitPushC(ctx, 4 * n);
}

// Helpers:

/// <library>amx_assembly asm</library>
stock AsmGetArgOffset(n) {
	return ASM_ARGUMENTS_OFFSET + 4 * n;
}


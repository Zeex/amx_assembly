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

static const size_of_cell = cellbits / 8;

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
	EmitContext_error_handler // ErrorHandler(ctx[EmitContext], EmitError:error)
};

stock const EMIT_ARGUMENTS_OFFSET    =  0x0C;
stock const EMIT_LOCALS_OFFSET       = -0x04;
stock const EMIT_CALLER_FRAME_OFFSET =  0x00;
stock const EMIT_RETURN_ADDR_OFFSET  =  0x04;

stock EmitError:EmitInit(ctx[EmitContext], buffer[], size = sizeof(buffer)) {
	ctx[EmitContext_buffer] = ref(buffer);
	ctx[EmitContext_buffer_size] = size;
	return EMIT_ERROR_NONE;
}

stock EmitError:EmitSetErrorHandler(ctx[EmitContext], error_handler) {
	ctx[EmitContext_error_handler] = error_handler;
	return EMIT_ERROR_NONE;
}

stock EmitGetErrorHandler(const ctx[EmitContext]) {
	return ctx[EmitContext_error_handler];
}

stock EmitError:EmitRaiseError(const ctx[EmitContext], EmitError:error) {
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
	ctx[EmitContext_buffer_offset] += size_of_cell;

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

stock EmitGetCode(const ctx[EmitContext]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);
	return ctx[EmitContext_buffer] + amxhdr[AMX_HDR_DAT] - amxhdr[AMX_HDR_COD];
}

stock EmitGetCodeSize(const ctx[EmitContext]) {
	return ctx[EmitContext_buffer_offset];
}

stock EmitGetArgOffset(n) {
	return EMIT_ARGUMENTS_OFFSET + size_of_cell * n;
}



stock EmitError:EmitCall(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_CALL, address);
}

stock EmitError:EmitLoadPri(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LOAD_PRI, address);
}

stock EmitError:EmitLoad(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_LOAD_ALT, address);
}

stock EmitError:EmitLoadSPri(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LOAD_S_PRI, offset);
}

stock EmitError:EmitLoadSAlt(ctx[EmitContext], offset) {
	return EmitInstruction(ctx, OP_LOAD_S_ALT, offset);
}

stock EmitError:EmitProc(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PROC);
}

stock EmitError:EmitPushPri(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PUSH_PRI);
}

stock EmitError:EmitPushAlt(ctx[EmitContext]) {
	return EmitInstruction(ctx, OP_PUSH_ALT);
}

stock EmitError:EmitPushC(ctx[EmitContext], value) {
	return EmitInstruction(ctx, OP_PUSH_C, value);
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

stock EmitError:EmitStack(ctx[EmitContext], nbytes) {
	return EmitInstruction(ctx, OP_STACK, nbytes);
}

stock EmitError:EmitSysreqC(ctx[EmitContext], index) {
	return EmitInstruction(ctx, OP_SYSREQ_C, index);
}

stock EmitError:EmitSysreqD(ctx[EmitContext], address) {
	return EmitInstruction(ctx, OP_SYSREQ_D, address);
}



stock EmitError:EmitCallNative(ctx[EmitContext], const name[]) {
	return EmitSysreqC(ctx, GetNativeAddressFromName(name));
}

stock EmitError:EmitPushNumArgs(ctx[EmitContext], n) {
	return EmitPushC(ctx, size_of_cell * n);
}

stock EmitError:EmitPopArgs(ctx[EmitContext], n) {
	return EmitStack(ctx, (n + 1) * size_of_cell);
}

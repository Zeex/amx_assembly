// Copyright (C) 2012 Y_Less
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

#if defined FRAME_INFO_INC
	#endinput
#endif
#define FRAME_INFO_INC

/**
 * <library name="amx_assembly frame_info" summary="AMX Assembly; Function call frame information.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "amx_header"
#include "amx_base"
#include "opcode"

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrame() {
	#emit load.s.pri 0
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetFramePreviousFrame(frm_addr) {
	#emit lref.s.pri frm_addr
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetFrameReturn(frm_addr) {
	const cells0 = 1 * cellbytes;
	#emit load.s.pri frm_addr
	#emit add.c cells0
	#emit load.i
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock SetFramePreviousFrame(frm_addr, addr) {
	#emit load.s.pri addr
	#emit sref.s.pri frm_addr
	#emit retn
}

/// <library>amx_assembly frame_info</library>
stock SetFrameReturn(frm_addr, addr) {
	const cells0 = 1 * cellbytes;
	#emit load.s.alt addr
	#emit load.s.pri frm_addr
	#emit add.c cells0
	#emit xchg
	#emit stor.i
	#emit retn
}

/// <library>amx_assembly frame_info</library>
stock SetFrameParameterSize(frm_addr, size) {
	const cells0 = 2 * cellbytes;
	#emit load.s.alt size
	#emit load.s.pri frm_addr
	#emit add.c cells0
	#emit xchg
	#emit stor.i
	#emit retn
}

/// <library>amx_assembly frame_info</library>
stock SetFrameParameterCount(frm_addr, count) {
	SetFrameParameterSize(frm_addr, count * cellbytes);
}

/// <library>amx_assembly frame_info</library>
stock GetFrameTotalSize(frm_addr) {
	return GetFrameLocalSize(frm_addr) + GetFrameHeaderSize(frm_addr) + GetFrameParameterSize(frm_addr);
}

/// <library>amx_assembly frame_info</library>
stock GetFrameTotalCount(frm_addr) {
	return GetFrameTotalSize(frm_addr) / cellbytes;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameNextFrame(frm_addr) {
	// this function always works because it is at the top of the stack
	// run back through the stack
	new cur_frm = GetCurrentFrame();

	while (cur_frm != 0) {
		new prev_frm = GetFramePreviousFrame(cur_frm);
		if (prev_frm == frm_addr) {
			break;
		}
		cur_frm = prev_frm;
	}

	return cur_frm;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameLocalSize(frm_addr) {
	// run back through the stack
	new next_frm = GetFrameNextFrame(frm_addr);

	// find the size of local variables in the selected frame
	new frm_bottom = next_frm + GetFrameHeaderSize(next_frm) + GetFrameParameterSize(next_frm);

	return frm_addr - frm_bottom;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameLocalCount(frm_addr) {
	return GetFrameLocalSize(frm_addr) / cellbytes;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameHeaderSize(frm_addr) {
	#pragma unused frm_addr
	return 3 * cellbytes;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameHeaderCount(frm_addr) {
	return GetFrameHeaderSize(frm_addr) / cellbytes;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameParameterSize(frm_addr) {
	const cells0 = 2 * cellbytes;
	#emit load.s.pri frm_addr
	#emit add.c cells0
	#emit load.i
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetFrameParameterCount(frm_addr) {
	return GetFrameParameterSize(frm_addr) / cellbytes;
}

/// <library>amx_assembly frame_info</library>
stock GetFrameParameter(frm_addr, param, idx = -1) {
	if (idx == -1) {
		#if cellbits == 32
			const cells0 = 2;
		#elseif cellbits == 64
			const cells0 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells1 = 3 * cellbytes;
		const cells2 = -1 * cellbytes;
		const cells3 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells0

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c cells1

		#emit push.pri
		#emit lref.s.pri cells2

		#emit stack cells3
		#emit retn
	} else {
		#if cellbits == 32
			const cells4 = 2;
		#elseif cellbits == 64
			const cells4 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells5 = 3 * cellbytes;
		const cells6 = -1 * cellbytes;
		const cells7 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells4

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c cells5

		#emit push.pri
		#emit lref.s.alt cells6

		#emit load.s.pri idx
		#emit lidx

		#emit stack cells7
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetFrameVariable(frm_addr, param, idx = -1) {
	if (idx == -1) {
		const cells0 = -1 * cellbytes;
		const cells1 = 1 * cellbytes;
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.pri cells0

		#emit stack cells1
		#emit retn
	} else {
		const cells2 = -1 * cellbytes;
		const cells3 = 1 * cellbytes;
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.alt cells2

		#emit load.s.pri idx
		#emit lidx

		#emit stack cells3
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetFrameLocal(frm_addr, param) {
	if (param < 0) {
		const cells0 = -1 * cellbytes;
		const cells1 = 1 * cellbytes;
		// probably in correct format for negative offsets
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.pri cells0

		#emit stack cells1
		#emit retn
	} else {
		#if cellbits == 32
			const cells2 = 2;
		#elseif cellbits == 64
			const cells2 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells3 = -1 * cellbytes;
		const cells4 = -1 * cellbytes;
		const cells5 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells2

		#emit add.c cells3

		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.pri cells4

		#emit stack cells5
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock SetFrameParameter(frm_addr, param, value, idx = -1) {
	if (idx == -1) {
		#if cellbits == 32
			const cells0 = 2;
		#elseif cellbits == 64
			const cells0 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells1 = 3 * cellbytes;
		const cells2 = -1 * cellbytes;
		const cells3 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells0

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c cells1

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri cells2

		#emit stack cells3
		#emit retn
	} else {
		#if cellbits == 32
			const cells4 = 2;
		#elseif cellbits == 64
			const cells4 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells5 = 3 * cellbytes;
		const cells6 = -1 * cellbytes;
		const cells7 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells4

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c cells5

		#emit push.pri
		#emit lref.s.alt cells6

		#emit load.s.pri idx
		#emit idxaddr

		#emit load.s.alt value
		#emit xchg
		#emit stor.i

		#emit stack cells7
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock SetFrameVariable(frm_addr, param, value, idx = -1) {
	if (idx == -1) {
		const cells0 = -1 * cellbytes;
		const cells1 = 1 * cellbytes;
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri cells0

		#emit stack cells1
		#emit retn
	} else {
		const cells2 = -1 * cellbytes;
		const cells3 = 1 * cellbytes;
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.alt cells2

		#emit load.s.pri idx
		#emit idxaddr

		#emit load.s.alt value
		#emit xchg
		#emit stor.i

		#emit stack cells3
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock SetFrameLocal(frm_addr, param, value) {
	if (param < 0) {
		const cells0 = -1 * cellbytes;
		const cells1 = 1 * cellbytes;
		// probably in correct format for negative offsets
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri cells0

		#emit stack cells1
		#emit retn
	} else {
		#if cellbits == 32
			const cells2 = 2;
		#elseif cellbits == 64
			const cells2 = 3;
		#else
			#error Unsupported `cellbits`.
		#endif
		const cells3 = -1 * cellbytes;
		const cells4 = -1 * cellbytes;
		const cells5 = 1 * cellbytes;
		#emit load.s.pri param
		#emit shl.c.pri cells2

		#emit add.c cells3

		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri cells4

		#emit stack cells5
		#emit retn
	}

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
static stock GetCallerFrame() {
	const cells0 = -1 * cellbytes;
	const cells1 = -2 * cellbytes;
	const cells2 = 2 * cellbytes;
	#emit lctrl __frm

	#emit push.pri
	#emit lref.s.pri cells0

	#emit push.pri
	#emit lref.s.pri cells1

	#emit stack cells2
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFramePreviousFrame() {
	return GetFramePreviousFrame(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameReturn() {
	return GetFrameReturn(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameTotalSize() {
	return GetFrameTotalSize(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameTotalCount() {
	return GetFrameTotalCount(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameLocalSize() {
	return GetFrameLocalSize(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameLocalCount() {
	return GetFrameLocalCount(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameHeaderSize() {
	return GetFrameHeaderSize(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameHeaderCount() {
	return GetFrameHeaderCount(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameParameterSize() {
	return GetFrameParameterSize(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameParameter(param, idx = -1) {
	return GetFrameParameter(GetCallerFrame(), param, idx);
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameLocal(param) {
	return GetFrameLocal(GetCallerFrame(), param);
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameParameterCount() {
	return GetFrameParameterCount(GetCallerFrame());
}

/// <library>amx_assembly frame_info</library>
stock SetCurrentFrameReturn(addr) {
	SetFrameReturn(GetCallerFrame(), addr);
}

/// <library>amx_assembly frame_info</library>
stock SetCurrentFramePreviousFrame(addr) {
	SetFramePreviousFrame(GetCallerFrame(), addr);
}

/// <library>amx_assembly frame_info</library>
stock SetCurrentParameterSize(size) {
	SetFrameParameterSize(GetCallerFrame(), size);
}

/// <library>amx_assembly frame_info</library>
stock SetCurrentParameterCount(count) {
	SetFrameParameterCount(GetCallerFrame(), count);
}

/// <library>amx_assembly frame_info</library>
stock GetFrameFunction(frm_addr) {
	// try to determine the start address of the function this frame is for
	new prev_frm = GetFramePreviousFrame(frm_addr);

	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);

	if (prev_frm == 0) {
		// public entry point
		new call_addr = GetFrameReturn(GetFrameNextFrame(frm_addr));

		// find the closest public/main
		new highest_found = 0;
		new defsize = amxhdr[AMX_HDR_DEFSIZE];
		new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;
		new off = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];

		for (new i = 0; i != num_publics; ++i) {
			new addr = ReadAmxMemory(off);
			off += defsize;

			if (highest_found < addr < call_addr) {
				highest_found = addr;
			}
		}

		if (highest_found < amxhdr[AMX_HDR_CIP] < call_addr) {
			highest_found = amxhdr[AMX_HDR_CIP];
		}

		// return the best found match
		return highest_found;
	} else {
		// called from inside the script
		new ret_addr = (GetFrameReturn(frm_addr) - cellbytes * 2) + (amxhdr[AMX_HDR_COD] - amxhdr[AMX_HDR_DAT]);

		new Opcode:opcode = UnrelocateOpcode(Opcode:ReadAmxMemory(ret_addr));

		if (opcode == OP_CALL) {
			// standard function call, get the call address
			return ReadAmxMemory(ret_addr + cellbytes) - amxhdr[AMX_HDR_COD] - GetAmxBaseAddress();

		} else if (opcode == OP_SCTRL) {
			// modified code to call a function by pointer
			opcode = UnrelocateOpcode(Opcode:ReadAmxMemory(ret_addr - cellbytes * 2));

			if (opcode == OP_LOAD_PRI) {
				ret_addr = ReadAmxMemory(ret_addr - cellbytes);
				return ReadAmxMemory(ret_addr);
			} else if (opcode == OP_LOAD_S_PRI) {
				return GetFrameVariable(prev_frm, ReadAmxMemory(ret_addr - cellbytes));
			} else if (opcode == OP_CONST_PRI) {
				return ReadAmxMemory(ret_addr - cellbytes);
			}
		}

		// guess!
		new end = amxhdr[AMX_HDR_COD] - amxhdr[AMX_HDR_DAT] + cellbytes; // "halt"
		ret_addr = GetFrameReturn(GetFrameNextFrame(frm_addr)) + end;

		opcode = RelocateOpcode(OP_RETN);
		new Opcode:proc = RelocateOpcode(OP_PROC);

		while (ret_addr >= end) {
			if (Opcode:ReadAmxMemory(ret_addr) == proc) {
				if (ret_addr == end || Opcode:ReadAmxMemory(ret_addr - cellbytes) == opcode) {
					// found a retn/proc pair.
					return ret_addr;
				}
			}
			ret_addr -= cellbytes;
		}
	}

	// give up...
	return 0;
}

/// <library>amx_assembly frame_info</library>
stock GetCurrentFrameFunction() {
	// this function gets its own caller - pointless but here for completeness
	return GetFrameFunction(GetCallerFrame());
}


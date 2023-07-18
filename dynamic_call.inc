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

#if defined DYNAMIC_CALL_INC
	#endinput
#endif
#define DYNAMIC_CALL_INC

/**
 * <library name="amx_assembly dynamic_call" summary="AMX Assembly; Call arbitrary functions by name.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include "amx_jit"
#include "amx_header"
#include "amx_memory"
#include "opcode"
#include "addressof"

#if !defined DYNAMIC_CALL_MAX_ARGS
	#define DYNAMIC_CALL_MAX_ARGS 256
#endif

forward bool:Push(arg);
forward bool:PushString(const string[]);
forward bool:Pop(&arg = 0);
forward Call(address, bool:auto_pop = true);
forward SysreqC(index, bool:auto_pop = true);
forward SysreqD(address, bool:auto_pop = true);
forward CallN(address, args_to_push, bool:auto_pop = true);
forward SysreqCN(index, args_to_push, bool:auto_pop = true);
forward SysreqDN(address, args_to_push, bool:auto_pop = true);
forward CallFunction(address, {Float,_}:...);
forward CallNative(index, {Float,_}:...);
forward CallNativeByAddress(address, {Float,_}:...);

/// <library>amx_assembly dynamic_call</library>
/// <remarks>
/// When you declare an alternative version of a function like this you end up
/// with two copies in the header.  As long as we never actually use this
/// function we can keep changing the pointer to whatever we want and call the
/// native via `SYSREQ.C`.  Note that if we do this we need to check if
/// `SYSREQ.D` is still in the server because the `SYSREQ.C` will be replaced.
/// </remarks>
native AmxSysreqDStub() = heapspace;

/// <library>amx_assembly dynamic_call</library>
static stock Opcode:UpdateSysreqDAndGetIndex(&address, wide) {
	// This function handily ensures that the function is in the header on old
	// compilers which don't insert it when used via `SYSREQ.C`.
	static index = cellmin;
	static Opcode:sysreq_c = OP_NONE;
	static Opcode:sysreq_d = OP_NONE;
	static off = 0;
	if (index == cellmin) {
		sysreq_d = RelocateOpcode(OP_SYSREQ_D);
		// `nativeidxof` is a bypass for the fact that the header may be
		// clobbered, which this new `SYSREQ.D` bypass is also for.
		index = nativeidxof(AmxSysreqDStub<>);
		sysreq_c = RelocateOpcode(OP_SYSREQ_C);
		new amxhdr[AMX_HDR];
		GetAmxHeader(amxhdr);
		off = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT] + index * amxhdr[AMX_HDR_DEFSIZE];
	}
	if (wide == 0 && HasSysreqD()) {
		return sysreq_d;
	}
	// Change where the native points.
	WriteAmxMemory(off, address);
	if (!HasReloc()) {
		WriteAmxMemory(off + cellbytes, wide);
	}
	address = index;
	return sysreq_c;
}

/// <library>amx_assembly dynamic_call</library>
static stock g_nargs = 0;

/// <library>amx_assembly dynamic_call</library>
static stock g_args[DYNAMIC_CALL_MAX_ARGS];

/// <library>amx_assembly dynamic_call</library>
stock bool:Push(arg) {
	if (g_nargs < sizeof(g_args)) {
		g_args[g_nargs++] = arg;
		return true;
	}
	return false;
}

/// <library>amx_assembly dynamic_call</library>
stock bool:PushString(const string[]) {
	new address = 0;
	#emit load.s.pri string
	#emit stor.s.pri address
	return Push(address);
}

/// <library>amx_assembly dynamic_call</library>
stock bool:Pop(&arg = 0) {
	if (g_nargs > 0) {
		arg = g_args[--g_nargs];
		return true;
	}
	return false;
}

/// <library>amx_assembly dynamic_call</library>
stock Call(address, bool:auto_pop = true) {
	const cells0 = 9 * cellbytes;
	new arg = 0;
	new index = g_nargs;
	new bytes = g_nargs * cellbytes;
	new retval = 0;

	while (--index >= 0) {
		arg = g_args[index];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	#emit lctrl __cip
	#emit add.c cells0
	#emit lctrl __jmp
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl __cip

	#emit stor.s.pri retval

	if (auto_pop) {
		g_nargs = 0;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock CallN(address, args_to_push, bool:auto_pop = true) {
	const cells0 = 9 * cellbytes;
	// Like "Call", but doesn't pass all parameters.
	new arg = 0;
	new index = g_nargs;
	new bytes = args_to_push * cellbytes;
	new end = g_nargs - args_to_push;
	new retval = 0;

	if (end < 0) {
		return cellmin;
	}

	while (--index >= end) {
		arg = g_args[index];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	#emit lctrl __cip
	#emit add.c cells0
	#emit lctrl __jmp
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl __cip

	#emit stor.s.pri retval

	if (auto_pop) {
		g_nargs = end;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock CallFunction(address, {Float,_}:...) {
	const cells_ = 2 * cellbytes;
	const cells0 = 1 * cellbytes;
	const cells1 = 3 * cellbytes;
	const cells2 = 4 * cellbytes;
	const cells3 = 9 * cellbytes;
	const cells4 = 4 * cellbytes;
	new arg_bytes = 0, arg_begin = 0, arg_end = 0;

	// Get number of bytes passed.
	#emit load.s.pri cells_
	#emit const.alt cells0
	#emit sub
	#emit stor.s.pri arg_bytes
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT).
	#emit lctrl __frm
	#emit add.c cells1
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10.
	#emit lctrl __frm
	#emit add.c cells2
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i
		#emit push.pri
		arg -= cellbytes;
	}

	// Call the function
	#emit push.s arg_bytes
	#emit lctrl __cip
	#emit add.c cells3
	#emit lctrl __jmp
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl __cip
	// Arguments are popped by callee.

	// Pop locals and return.
	#emit stack cells4
	#emit retn

	return 0; // make compiler happy
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqC(index, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = g_nargs * cellbytes;
	new tmp = 0;
	new Opcode:sysreq_c = RelocateOpcode(OP_SYSREQ_C);
	new retval = 0;

	while (--i >= 0) {
		arg = g_args[i];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to SYSREQ.C's operand>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat  // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.c
	#emit load.s.pri sysreq_c
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = index
	#emit load.s.pri index
	#emit sref.s.pri tmp

	#emit nop
	#emit nop
	// #emit sysreq.c 0

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = 0;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqD(address, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = g_nargs * cellbytes;
	new tmp = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, 0);
	new retval = 0;

	while (--i >= 0) {
		arg = g_args[i];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = 0;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqDWide(address, wide, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = g_nargs * cellbytes;
	new tmp = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, wide);
	new retval = 0;

	while (--i >= 0) {
		arg = g_args[i];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = 0;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqCN(index, args_to_push, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = args_to_push * cellbytes;
	new tmp = 0;
	new Opcode:sysreq_c = RelocateOpcode(OP_SYSREQ_C);
	new end = g_nargs - args_to_push;
	new retval = 0;

	if (end < 0) {
		return cellmin;
	}

	while (--i >= end) {
		arg = g_args[i];
		#emit push.s arg
	}
	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to SYSREQ.C's operand>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat  // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.c
	#emit load.s.pri sysreq_c
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = index
	#emit load.s.pri index
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = end;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqDN(address, args_to_push, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = args_to_push * cellbytes;
	new tmp = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, 0);
	new end = g_nargs - args_to_push;
	new retval = 0;

	if (end < 0) {
		return cellmin;
	}

	while (--i >= end) {
		arg = g_args[i];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = end;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock SysreqDNWide(address, wide, args_to_push, bool:auto_pop = true) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = 23 * cellbytes;
	const cells1 = 1 * cellbytes;
	const cells2 = 1 * cellbytes;
	new arg = 0;
	new i = g_nargs;
	new bytes = args_to_push * cellbytes;
	new tmp = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, wide);
	new end = g_nargs - args_to_push;
	new retval = 0;

	if (end < 0) {
		return cellmin;
	}

	while (--i >= end) {
		arg = g_args[i];
		#emit push.s arg
	}

	#emit load.s.pri bytes
	#emit push.pri

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells0
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells1
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt bytes
	#emit add
	#emit add.c cells2
	#emit sctrl __stk

	if (auto_pop) {
		g_nargs = end;
	}

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
stock CallNative(index, {Float,_}:...) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = -1 * cellbytes;
	const cells1 = 3 * cellbytes;
	const cells2 = 4 * cellbytes;
	const cells3 = 23 * cellbytes;
	const cells4 = 1 * cellbytes;
	const cells5 = 1 * cellbytes;
	new arg_bytes = 0, arg_begin = 0, arg_end = 0;
	new Opcode:sysreq_c = RelocateOpcode(OP_SYSREQ_C);

	// Get number of bytes passed.
	#emit load.s.pri 0x8
	#emit add.c cells0
	#emit stor.s.pri arg_bytes
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT).
	#emit lctrl __frm
	#emit add.c cells1
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10.
	#emit lctrl __frm
	#emit add.c cells2
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	new tmp = 0;
	new retval = 0;

	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i
		#emit push.pri
		arg -= cellbytes;
	}

	// Push number of arguments * 4 (which is params[0]).
	#emit push.s arg_bytes

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells3
	#emit stor.s.pri tmp

	// nop #1 = sysreq.c
	#emit load.s.pri sysreq_c
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells4
	#emit stor.s.pri tmp

	// nop #2 = index
	#emit load.s.pri index
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt arg_bytes
	#emit add
	#emit add.c cells5
	#emit sctrl __stk

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
/// <remarks>
///   Unlike CallNative(), this function calls natives directly via SYSREQ.D.
/// </remarks>
stock CallNativeByAddress(address, {Float,_}:...) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = -1 * cellbytes;
	const cells1 = 3 * cellbytes;
	const cells2 = 4 * cellbytes;
	const cells3 = 23 * cellbytes;
	const cells4 = 1 * cellbytes;
	const cells5 = 1 * cellbytes;
	new arg_bytes = 0, arg_begin = 0, arg_end = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, 0);

	// Get number of bytes passed.
	#emit load.s.pri 0x8
	#emit add.c cells0
	#emit stor.s.pri arg_bytes
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT).
	#emit lctrl __frm
	#emit add.c cells1
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10.
	#emit lctrl __frm
	#emit add.c cells2
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	new tmp = 0;
	new retval = 0;

	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i
		#emit push.pri
		arg -= cellbytes;
	}

	// Push number of arguments * 4 (which is params[0]).
	#emit push.s arg_bytes

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells3
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells4
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt arg_bytes
	#emit add
	#emit add.c cells5
	#emit sctrl __stk

	return retval;
}

/// <library>amx_assembly dynamic_call</library>
/// <remarks>
///   Unlike CallNative(), this function calls natives directly via SYSREQ.D.
///   Takes two pointers to replicate 64-bit pointers.
/// </remarks>
stock CallNativeByAddressWide(address, wide, {Float,_}:...) {
	if (GetJITGeneratorVersion()) {
		return cellmin;
	}

	const cells0 = -1 * cellbytes;
	const cells1 = 3 * cellbytes;
	const cells2 = 4 * cellbytes;
	const cells3 = 23 * cellbytes;
	const cells4 = 1 * cellbytes;
	const cells5 = 1 * cellbytes;
	new arg_bytes = 0, arg_begin = 0, arg_end = 0;
	new Opcode:sysreq = UpdateSysreqDAndGetIndex(address, wide);

	// Get number of bytes passed.
	#emit load.s.pri 0x8
	#emit add.c cells0
	#emit stor.s.pri arg_bytes
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT).
	#emit lctrl __frm
	#emit add.c cells1
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10.
	#emit lctrl __frm
	#emit add.c cells2
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	new tmp = 0;
	new retval = 0;

	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i
		#emit push.pri
		arg -= cellbytes;
	}

	// Push number of arguments * 4 (which is params[0]).
	#emit push.s arg_bytes

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl __cod  // COD
	#emit move.alt
	#emit lctrl __cip  // CIP
	#emit add
	#emit move.alt
	#emit lctrl __dat // DAT
	#emit sub.alt
	#emit add.c cells3
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit load.s.pri sysreq
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c cells4
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	#emit stor.s.pri retval

	// Pop native arguments.
	#emit lctrl __stk
	#emit load.s.alt arg_bytes
	#emit add
	#emit add.c cells5
	#emit sctrl __stk

	return retval;
}


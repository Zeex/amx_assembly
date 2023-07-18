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

#if defined PROFILER_INC
	#endinput
#endif
#define PROFILER_INC

/**
 * <library name="amx_assembly profiler" summary="AMX Assembly Library: Performance profiler.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#include <file>
#include <time>
#include <string>
#if !defined _samp_included
	#tryinclude <console>
#endif

#include "amx_base"
#include "amx_header"
#include "opcode"

// Call stack size (maximum call depth).
#if !defined PROF_MAX_CALL_STACK
	#define PROF_MAX_CALL_STACK 10
#endif

// Maximum number of profiled publics.
#if !defined PROF_MAX_PUBLICS
	#define PROF_MAX_PUBLICS 1000
#endif

/// <p/>

/// <library>amx_assembly profiler</library>
enum ProfEntryCode {
	Opcode:pec_push_c0,
	pec_push_address,
	Opcode:pec_push_c1,
	pec_push_index,
	Opcode:pec_push_c2,
	pec_push_8,
	Opcode:pec_call,
	pec_call_enter
}

/// <library>amx_assembly profiler</library>
const ProfEntryCode:ProfEntryCode__ = ProfEntryCode;

/// <library>amx_assembly profiler</library>
static stock g_pecs[PROF_MAX_PUBLICS][ProfEntryCode];

/// <library>amx_assembly profiler</library>
static stock g_num_pecs = 0;

/// <p/>

/// <library>amx_assembly profiler</library>
enum ProfCallInfo {
	pci_index,
	pci_start_time
}

/// <library>amx_assembly profiler</library>
const ProfCallInfo:ProfCallInfo__ = ProfCallInfo;

/// <p/>

/// <library>amx_assembly profiler</library>
enum ProfPublicInfo {
	ppi_child_time,
	ppi_total_time,
	ppi_num_calls
}

/// <library>amx_assembly profiler</library>
const ProfPublicInfo:ProfPublicInfo__ = ProfPublicInfo;

/// <library>amx_assembly profiler</library>
static stock g_publics[PROF_MAX_PUBLICS][ProfPublicInfo];

/// <library>amx_assembly profiler</library>
static stock g_num_publics = 0;

/// <library>amx_assembly profiler</library>
static stock g_call_stack[PROF_MAX_CALL_STACK][ProfCallInfo];

/// <library>amx_assembly profiler</library>
static stock g_call_depth = 0;

/// <library>amx_assembly profiler</library>
static stock exit_public() {
	if (--g_call_depth < sizeof(g_call_stack)) {
		new index = g_call_stack[g_call_depth][pci_index];

		new parent = -1;
		if (g_call_depth > 0) {
			parent = g_call_stack[g_call_depth-1][pci_index];
		}

		if (index < g_num_publics) {
			new i = g_call_depth;
			new tick = tickcount();
			new time = tick - g_call_stack[i][pci_start_time];
			if (time < 0) {
				// Work around negative intervals due to tick count overflow
				if (tick < 0) {
					time = (tick - cellmin) + (cellmax - g_call_stack[i][pci_start_time]);
				}
			}
			if (time > 0) {
				g_publics[index][ppi_total_time] += time;
				if (parent > 0) {
					g_publics[parent][ppi_child_time] += time;
				}
			}
			g_publics[index][ppi_num_calls]++;
		}
		//{
		//	new public_name[64];
		//	GetPublicNameByIndex(index, public_name);
		//	printf("Leaving %s", public_name);
		//}
	}

	#emit halt 0
	return 0; // make compiler happy
}

/// <library>amx_assembly profiler</library>
static stock enter_public(index, address) {
	const cells0 = 5 * cellbytes;
	const cells1 = 1 * cellbytes;
	//{
	//	new public_name[64];
	//	GetPublicNameByIndex(index, public_name);
	//	printf("Entering %s", public_name);
	//}

	if (g_call_depth < sizeof(g_call_stack)) {
		new pci[ProfCallInfo];
		pci[pci_index] = index;
		pci[pci_start_time] = tickcount();
		g_call_stack[g_call_depth] = pci;
	} else {
		printf("profiler warning: PROF_MAX_CALL_STACK is set to %d but current level is %d", PROF_MAX_CALL_STACK, g_call_depth);
	}

	// Pop locals + arguments + numbytes + return address + frm.
	#emit stack cells0

	++g_call_depth;

	// modify public's return address so it will jump to exit_public() when done
	#emit stack cells1
	#emit const.pri exit_public
	#emit lctrl __jmp
	#emit push.pri

	// jump to the public
	#emit load.s.pri address
	#emit jump.pri

	return 0; // make compiler happy
}

/// <library>amx_assembly profiler</library>
static stock new_pec(index, address, code_start) {
	if (g_num_pecs < sizeof(g_pecs)) {
		new pec[ProfEntryCode];

		pec[pec_push_c0] = RelocateOpcode(OP_PUSH_C);
		pec[pec_push_address] = address;

		pec[pec_push_c1] = RelocateOpcode(OP_PUSH_C);
		pec[pec_push_index] = index;

		pec[pec_push_c2] = RelocateOpcode(OP_PUSH_C);
		pec[pec_push_8] = 2 * cellbytes;

		new enter_proc = 0;
		#emit const.pri enter_public
		#emit stor.s.pri enter_proc
		pec[pec_call] = RelocateOpcode(OP_CALL);
		pec[pec_call_enter] = code_start + enter_proc;

		g_pecs[g_num_pecs] = pec;
		return g_num_pecs++;
	}

	return -1;
}

/// <library>amx_assembly profiler</library>
stock ProfilerInit() {
	new hdr[AMX_HDR];
	GetAmxHeader(hdr);

	new publics = hdr[AMX_HDR_PUBLICS] - hdr[AMX_HDR_DAT];
	new defsize = hdr[AMX_HDR_DEFSIZE];
	new num_publics = (hdr[AMX_HDR_NATIVES] - hdr[AMX_HDR_PUBLICS]) / defsize;

	new amx_base = GetAmxBaseAddress() + hdr[AMX_HDR_COD];

	// Redirect all public calls to ProfileHook().
	for (new i = 0, cur = publics; i < num_publics; cur += defsize, i++) {
		new address = 0;
		#emit lref.s.pri cur
		#emit stor.s.pri address

		new pec_index = new_pec(i, address, amx_base);
		if (pec_index < 0) {
			printf("profiler warning: Too many public functions (%d). Consider increasing PROF_MAX_PUBLICS.", num_publics);
			break;
		}

		// Get start address of the g_pecs sub-array at pec_index.
		new pec_start = 0;
		#emit const.alt g_pecs
		#emit load.s.pri pec_index
		#emit idxaddr
		#emit move.alt
		#emit load.i
		#emit add
		#emit stor.s.pri pec_start

		// Alter public table to redirect calls to the PEC.
		HookPublic(i, pec_start + hdr[AMX_HDR_DAT] - hdr[AMX_HDR_COD]);

		g_publics[i][ppi_child_time] = 0;
		g_publics[i][ppi_total_time] = 0;
		g_publics[i][ppi_num_calls] = 0;
		g_num_publics++;
	}
}

/// <library>amx_assembly profiler</library>
stock bool:ProfilerWriteData(const filename[]) {
	new File:file = fopen(filename, io_write);
	new buffer[100];

	if (!file) {
		return false;
	}

	fwrite(file, "+----------------------------------+----------------+----------------+----------------+\n");
	fwrite(file, "| name                             |          calls |      self_time |     total_time |\n");
	fwrite(file, "+----------------------------------+----------------+----------------+----------------+\n");

	for (new i = 0; i < g_num_publics; i++) {
			new name[64];
			GetPublicNameFromIndex(i, name);
		#if defined strformat
			strformat(buffer, sizeof(buffer), false, "| %32s |%15d |%15d |%15d |\n",
				name,
				g_publics[i][ppi_num_calls],
				g_publics[i][ppi_total_time] - g_publics[i][ppi_child_time],
				g_publics[i][ppi_total_time]
			);
		#elseif defined format
			format(buffer, sizeof(buffer), "| %32s |%15d |%15d |%15d |\n",
				name,
				g_publics[i][ppi_num_calls],
				g_publics[i][ppi_total_time] - g_publics[i][ppi_child_time],
				g_publics[i][ppi_total_time]
			);
		#else
			// Generate proper compiler errors for the missing symbols - ONLY IF the function is
			// actually used.
			format(buffer, 0, "You need this function or strformat");
			strformat(buffer, 0, false, "You need this function or format");
		#endif
			fwrite(file, buffer);
			fwrite(file, "+----------------------------------+----------------+----------------+----------------+\n");
	}

	fclose(file);
	return true;
}


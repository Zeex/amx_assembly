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

#if defined AMX_HEADER_INC
	#endinput
#endif
#define AMX_HEADER_INC

/**
 * <library name="amx_assembly amx_header" summary="AMX Assembly Library: AMX file header access.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 * </library>
 */

/// <p/>

#if !defined _samp_included
	#tryinclude <console>
#endif

#include "amx_memory"
#include "amx_base"

#define AMX_HDR_BYTES (56)
#define AMX_HDR_CELLS (AMX_HDR_BYTES / cellbytes)

// Always 32-bit.
#define AMX_TAG_LOCAL (0x80000000)
#define AMX_TAG_MASK (0x7FFFFFFF)
#define AMX_TAG_STRONG (0x40000000)

/// <p/>

/// <library>amx_assembly amx_header</library>
enum AMX_HDR {
	AMX_HDR_SIZE,
	AMX_HDR_MAGIC,
	AMX_HDR_FILE_VERSION,
	AMX_HDR_AMX_VERSION,
	AMX_HDR_FLAGS,
	AMX_HDR_DEFSIZE,
	AMX_HDR_COD,
	AMX_HDR_DAT,
	AMX_HDR_HEA,
	AMX_HDR_STP,
	AMX_HDR_CIP,
	AMX_HDR_PUBLICS,
	AMX_HDR_NATIVES,
	AMX_HDR_LIBRARIES,
	AMX_HDR_PUBVARS,
	AMX_HDR_TAGS,
	AMX_HDR_NAMETABLE
}

/// <library>amx_assembly amx_header</library>
const AMX_HDR:AMX_HDR__ = AMX_HDR;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_SIZE = 0;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_MAGIC = 4;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_FILE_VERSION = 6;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_AMX_VERSION = 7;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_FLAGS = 8;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_DEFSIZE = 10;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_COD = 12;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_DAT = 16;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_HEA = 20;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_STP = 24;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_CIP = 28;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_PUBLICS = 32;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_NATIVES = 36;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_LIBRARIES = 40;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_PUBVARS = 44;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_TAGS = 48;

/// <library>amx_assembly amx_header</library>
const AMX_HDR_OFFSET_NAMETABLE = 52;

/// <p/>

/// <library>amx_assembly amx_header</library>
enum AMX_FUNCSTUBNT {
	AMX_FUNCSTUBNT_ADDRESS,
	AMX_FUNCSTUBNT_WIDE,
	AMX_FUNCSTUBNT_NAMEOFS
}
#define AMX_FUNCSTUBNT_ID AMX_FUNCSTUBNT_ADDRESS

/// <library>amx_assembly amx_header</library>
const AMX_FUNCSTUBNT:AMX_FUNCSTUBNT__ = AMX_FUNCSTUBNT;

// Publics
forward bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPublicIndexFromAddress(address);
#define GetPublicIndexFromName funcidx
#define GetPublicAddressFromName O@A@
forward GetPublicAddressFromName(const name[]);
forward GetPublicAddressFromIndex(index);
forward bool:GetPublicNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetPublicNameFromAddress(address, name[], size = sizeof(name));
forward HookPublic(index, address);

// Tags
forward bool:GetTagInfo(index, info[AMX_FUNCSTUBNT]);
forward GetTagIndexFromID(id);
forward GetTagIndexFromName(const name[]);
forward GetTagIDFromName(const name[]);
forward GetTagIDFromIndex(index);
forward bool:GetTagNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetTagNameFromID(id, name[], size = sizeof(name));

// Natives
forward bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]);
forward GetNativeIndexFromAddress(address, wide = 0);
forward GetNativeIndexFromAddressWide(address, wide);
forward GetNativeIndexFromName(const name[]);
forward GetNativeAddressFromName(const name[], &wide = 0);
forward GetNativeAddressFromIndex(index, &wide = 0);
forward bool:GetNativeNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetNativeNameFromAddress(address, name[], size = sizeof(name));
forward bool:GetNativeNameFromAddressWide(address, wide, name[], size = sizeof(name));
forward HookNative(index, address, wide = 0, &old_wide = 0);

// Public Variables
forward bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPubVarIndexFromName(const name[]);
forward GetPubVarIndexFromAddress(address);
forward GetPubVarAddressFromName(const name[]);
forward GetPubVarAddressFromIndex(index);
forward bool:GetPubVarNameFromIndex(index, name[], size = sizeof(name));
forward bool:GetPubVarNameFromAddress(address, name[], size = sizeof(name));

// General
forward GetRawAmxHeader(plain_amxhdr[AMX_HDR_CELLS]);
forward GetAmxHeaderNow(amxhdr[AMX_HDR]);
forward GetAmxHeader(amxhdr[AMX_HDR]);
forward GetAmxHeaderComponent(AMX_HDR:comp);
forward PrintAmxHeader();

#if cellbits == 64
	#define AMX_HEADER_MAYBE_MASK(%0) ((%0) & 0xFFFFFFFF)
#else
	#define AMX_HEADER_MAYBE_MASK(%0) ((%0))
#endif

/// <library>amx_assembly amx_header</library>
stock GetRawAmxHeader(plain_amxhdr[AMX_HDR_CELLS]) {
	new address = 0;
	#emit lctrl __dat  // DAT
	#emit neg      // -DAT
	#emit stor.s.pri address

	for (new i = 0; i < AMX_HDR_CELLS; i++) {
		plain_amxhdr[i] = ReadAmxMemory(address);
		address += cellbytes;
	}
}

/// <library>amx_assembly amx_header</library>
static stock copy_1(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 1
}

/// <library>amx_assembly amx_header</library>
static stock copy_2(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 2
}

/// <library>amx_assembly amx_header</library>
static stock copy_4(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 4
}

/// <library>amx_assembly opcode</library>
static stock AmxHeaderTableSwap(addr0, addr1) {
	#if cellbits == 64
		new v0, v1, v3;
		return
			// Swap the pointers.
			v0 = ReadAmxMemory(addr0),
			v1 = ReadAmxMemory(addr1),
			WriteAmxMemory(addr1, v0),
			WriteAmxMemory(addr0, v1),
			// Move on.
			addr0 += cellbytes,
			addr1 += cellbytes,
			// Swap the names.  These pointers are always 32-bit, at least in
			// the AMX versions we deal with.  Thus we mask the upper bits.
			v0 = ReadAmxMemory(addr0),
			v1 = ReadAmxMemory(addr1),
			WriteAmxMemory(addr1, (v0 & 0x00000000FFFFFFFF) | (v1 & 0xFFFFFFFF00000000)),
			WriteAmxMemory(addr0, (v1 & 0x00000000FFFFFFFF) | (v0 & 0xFFFFFFFF00000000));
	#else
		new v0, v1;
		return
			// Swap the pointers.
			v0 = ReadAmxMemory(addr0),
			v1 = ReadAmxMemory(addr1),
			WriteAmxMemory(addr1, v0),
			WriteAmxMemory(addr0, v1),
			// Move on.
			addr0 += cellbytes,
			addr1 += cellbytes,
			// Swap the names.
			v0 = ReadAmxMemory(addr0),
			v1 = ReadAmxMemory(addr1),
			WriteAmxMemory(addr1, v0),
			WriteAmxMemory(addr0, v1);
	#endif
}

/// <library>amx_assembly amx_header</library>
static stock AmxHeaderTablePartition(low, high, dat, defsize) {
	new pivot = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(high + cellbytes)) - dat;
	new j = low;
	for (low -= defsize; j != high; j += defsize) {
		if (NtPivot(AMX_HEADER_MAYBE_MASK(ReadAmxMemory(j + cellbytes)) - dat, pivot) < 0) {
			// Swap.
			low += defsize,
			AmxHeaderTableSwap(low, j);
		}
	}
	return
		low += defsize,
		AmxHeaderTableSwap(low, high),
		low;
}

/// <library>amx_assembly amx_header</library>
static stock AmxHeaderTableQuickSort(low, high, dat, defsize) {
	if (low < high) {
		new partition = AmxHeaderTablePartition(low - dat, high - dat, dat, defsize) + dat;
		AmxHeaderTableQuickSort(low, partition - defsize, dat, defsize);
		AmxHeaderTableQuickSort(partition + defsize, high, dat, defsize);
	}
}

/// <library>amx_assembly amx_header</library>
stock GetAmxHeaderNow(amxhdr[AMX_HDR]) {
	new plain_amxhdr[AMX_HDR_CELLS];
	GetRawAmxHeader(plain_amxhdr);

	copy_4(amxhdr[AMX_HDR_SIZE], plain_amxhdr, AMX_HDR_OFFSET_SIZE);
	copy_2(amxhdr[AMX_HDR_MAGIC], plain_amxhdr, AMX_HDR_OFFSET_MAGIC);
	copy_1(amxhdr[AMX_HDR_FILE_VERSION], plain_amxhdr, AMX_HDR_OFFSET_FILE_VERSION);
	copy_1(amxhdr[AMX_HDR_AMX_VERSION], plain_amxhdr, AMX_HDR_OFFSET_AMX_VERSION);
	copy_2(amxhdr[AMX_HDR_FLAGS], plain_amxhdr, AMX_HDR_OFFSET_FLAGS);
	copy_2(amxhdr[AMX_HDR_DEFSIZE], plain_amxhdr, AMX_HDR_OFFSET_DEFSIZE);
	copy_4(amxhdr[AMX_HDR_COD], plain_amxhdr, AMX_HDR_OFFSET_COD);
	copy_4(amxhdr[AMX_HDR_DAT], plain_amxhdr, AMX_HDR_OFFSET_DAT);
	copy_4(amxhdr[AMX_HDR_HEA], plain_amxhdr, AMX_HDR_OFFSET_HEA);
	copy_4(amxhdr[AMX_HDR_STP], plain_amxhdr, AMX_HDR_OFFSET_STP);
	copy_4(amxhdr[AMX_HDR_CIP], plain_amxhdr, AMX_HDR_OFFSET_CIP);
	copy_4(amxhdr[AMX_HDR_PUBLICS], plain_amxhdr, AMX_HDR_OFFSET_PUBLICS);
	copy_4(amxhdr[AMX_HDR_NATIVES], plain_amxhdr, AMX_HDR_OFFSET_NATIVES);
	copy_4(amxhdr[AMX_HDR_LIBRARIES], plain_amxhdr, AMX_HDR_OFFSET_LIBRARIES);
	copy_4(amxhdr[AMX_HDR_PUBVARS], plain_amxhdr, AMX_HDR_OFFSET_PUBVARS);
	copy_4(amxhdr[AMX_HDR_TAGS], plain_amxhdr, AMX_HDR_OFFSET_TAGS);
	copy_4(amxhdr[AMX_HDR_NAMETABLE], plain_amxhdr, AMX_HDR_OFFSET_NAMETABLE);
	
	// Sort the tags list.  They aren't sorted, so make them so.  YSI uses tag
	// lookup a lot, so making it faster is good.  The VM searches linearly,
	// because it doesn't think they are sorted, so this won't break anything.
	AmxHeaderTableQuickSort(amxhdr[AMX_HDR_TAGS], amxhdr[AMX_HDR_NAMETABLE] - amxhdr[AMX_HDR_DEFSIZE], amxhdr[AMX_HDR_DAT], amxhdr[AMX_HDR_DEFSIZE]);
	
	// We can also sort the libraries table while we're at it.  We already have
	// the code, using it again is no hardship (which makes me question why only
	// some of the tables are sorted by the compiler, not all of them, in the
	// first place - that has the code, so surely using it is no hardship there
	// either).
	AmxHeaderTableQuickSort(amxhdr[AMX_HDR_LIBRARIES], amxhdr[AMX_HDR_PUBVARS] - amxhdr[AMX_HDR_DEFSIZE], amxhdr[AMX_HDR_DAT], amxhdr[AMX_HDR_DEFSIZE]);
	
	// Sadly we can't sort the natives table after-the-fact in this way because
	// their indexes are spread throughout the AMX.  We *could* replace all the
	// `SYSREQ.D` instances with the new indexes as well, but: a. that's hard
	// without `disasm`, which shouldn't be a dependency of this file; b. it is
	// slow; and c. it is pointless in open.mp anyway because the name pointers
	// get clobbered so you can't search the table by name after init anyway,
	// regardless of sorting.
}

/// <library>amx_assembly amx_header</library>
static gHdr[AMX_HDR];

/// <library>amx_assembly amx_header</library>
static bool:gInitialized = false;

/// <library>amx_assembly amx_header</library>
stock ResetStaticAmxHeader() {
	GetAmxHeaderNow(gHdr);
	gInitialized = true;
}

#define InitStaticAmxHeader() \
	if (!gInitialized) \
		ResetStaticAmxHeader()

/// <library>amx_assembly amx_header</library>
stock GetAmxHeader(amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();
	amxhdr = gHdr;
}

/// <library>amx_assembly amx_header</library>
stock GetAmxHeaderComponent(AMX_HDR:comp) {
	InitStaticAmxHeader();
	return gHdr[comp];
}

/// <library>amx_assembly amx_header</library>
static stock PrintAmxNameTable(start, end, defsize, decode = false, dereference = false) {
	new addr;
	new ofs;
	new name[64];
	while (start != end) {
		addr = ReadAmxMemory(start);
		ofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(start + cellbytes));
		if (ofs == 0) {
			name = "????";
		} else {
			NtCopy(ofs - GetAmxHeaderComponent(AMX_HDR_DAT), name);
		}
		if (decode) {
			printf("    %32s: 0x%08x%s%s", name, addr, (addr & AMX_TAG_STRONG) ? (" (strong)") : (""), (addr & AMX_TAG_LOCAL) ? (" (local)") : (""));
		} else if (dereference) {
			printf("    %32s: 0x%08x (%d)", name, addr, ReadAmxMemory(addr));
		} else {
			printf("    %32s: 0x%08x", name, addr);
		}
		start += defsize;
	}
}

/// <library>amx_assembly amx_header</library>
static stock PrintAmxNativesTable(start, end, defsize) {
	new addr;
	new ofs = GetFirstNativeStringOffset();
	new wide;
	new name[64];
	while (start != end) {
		addr = ReadAmxMemory(start);
		wide = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(start + cellbytes));
		if (HasReloc()) {
			if (wide == 0) {
				name = "????";
			} else {
				NtCopy(wide - GetAmxHeaderComponent(AMX_HDR_DAT), name);
			}
			printf("    %32s: 0x%08x", name, addr);
		} else {
			ofs += NtCopy(ofs, name);
			printf("    %32s: 0x%08x%08x", name, wide, addr);
		}
		start += defsize;
	}
}

/// <library>amx_assembly amx_header</library>
stock PrintAmxHeader() {
	InitStaticAmxHeader();
	new defsize = gHdr[AMX_HDR_DEFSIZE];
	print("---------------------------");
	print("AMX Header:");
	print("---------------------------");
	printf("    size         %d", gHdr[AMX_HDR_SIZE]);
	printf("    magic        %x", gHdr[AMX_HDR_MAGIC]);
	printf("    file_version %d", gHdr[AMX_HDR_FILE_VERSION]);
	printf("    amx_version  %d", gHdr[AMX_HDR_AMX_VERSION]);
	printf("    flags        %d", gHdr[AMX_HDR_FLAGS]);
	printf("    defsize      %d", gHdr[AMX_HDR_DEFSIZE]);
	printf("    cod          0x%08x", gHdr[AMX_HDR_COD]);
	printf("    dat          0x%08x", gHdr[AMX_HDR_DAT]);
	printf("    hea          0x%08x", gHdr[AMX_HDR_HEA]);
	printf("    stp          0x%08x", gHdr[AMX_HDR_STP]);
	printf("    cip          0x%08x", gHdr[AMX_HDR_CIP]);
	printf("    publics      0x%08x", gHdr[AMX_HDR_PUBLICS]);
	printf("    natives      0x%08x", gHdr[AMX_HDR_NATIVES]);
	printf("    libraries    0x%08x", gHdr[AMX_HDR_LIBRARIES]);
	printf("    pubvars      0x%08x", gHdr[AMX_HDR_PUBVARS]);
	printf("    tags         0x%08x", gHdr[AMX_HDR_TAGS]);
	printf("    nametable    0x%08x", gHdr[AMX_HDR_NAMETABLE]);
	print("---------------------------");
	new start = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT];
	new end = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT];
	print("Publics:");
	print("----------------------------------------------------------------");
	PrintAmxNameTable(start, end, defsize);
	print("----------------------------------------------------------------");
	start = end;
	end = gHdr[AMX_HDR_LIBRARIES] - gHdr[AMX_HDR_DAT];
	print("Natives:");
	print("----------------------------------------------------------------");
	PrintAmxNativesTable(start, end, defsize);
	print("----------------------------------------------------------------");
	start = end;
	end = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];
	print("Libraries:");
	print("----------------------------------------------------------------");
	PrintAmxNameTable(start, end, defsize);
	print("----------------------------------------------------------------");
	start = end;
	end = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT];
	print("Pubvars:");
	print("----------------------------------------------------------------");
	PrintAmxNameTable(start, end, defsize, .dereference = true);
	print("----------------------------------------------------------------");
	start = end;
	end = gHdr[AMX_HDR_NAMETABLE] - gHdr[AMX_HDR_DAT];
	print("Tags:");
	print("----------------------------------------------------------------");
	PrintAmxNameTable(start, end, defsize, .decode = true);
	print("----------------------------------------------------------------");
}

/// <library>amx_assembly amx_header</library>
/// <summary>
///   Compares a string stored in the name table starting at "s1" (packed) with
///   another string "s2" (unpacked).
/// </summary>
static stock NtCompare(s1, const s2[]) {
	new index = 0;
	new c1 = 0, c2 = 0;
	new diff = 0;

	do {
		c1 = ReadAmxMemory(s1) & 0xFF;
		++s1;
		c2 = s2[index++];
		diff = c1 - c2;
		if (diff != 0) {
			break;
		}
	} while ((c1 & c2));

	return diff;
}

/// <library>amx_assembly amx_header</library>
/// <summary>
///   Compares a string stored in the name table starting at "s1" (packed) with
///   another string in the name table starting at "s2" (packed).
/// </summary>
static stock NtPivot(s1, s2) {
	new c1 = 0, c2 = 0;
	new diff = 0;

	do {
		c1 = ReadAmxMemory(s1) & 0xFF;
		++s1;
		c2 = ReadAmxMemory(s2) & 0xFF;
		++s2;
		diff = c1 - c2;
		if (diff != 0) {
			break;
		}
	} while ((c1 & c2));

	return diff;
}

/// <library>amx_assembly amx_header</library>
/// <summary>
///   Copies a name from the name table to a string.  Returns the number of
///   characters copied.
/// </summary>
static stock NtCopy(src, dest[], size = sizeof(dest)) {
	new i = 0;
	new c = 0;

	do {
		c = ReadAmxMemory(src) & 0xFF;
		++src;
		dest[i++] = c;
	} while (c != '\0' && i <= size);

	dest[i] = '\0'; // terminator

	return i;
}

/// <library>amx_assembly amx_header</library>
/// <summary>
///   Returns the number of characters <b>including null</b>.
/// </summary>
static stock NtLength(src) {
	new i = 0;
	new c = 0;

	do {
		c = ReadAmxMemory(src) & 0xFF;
		++src;
		++i;
	} while (c != '\0');

	return i;
}

/// <library>amx_assembly amx_header</library>
stock GetNumPublics(const amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();

	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / amxhdr[AMX_HDR_DEFSIZE];
	return num_publics;
}

/// <library>amx_assembly amx_header</library>
stock GetPublicIndexFromAddress(address) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);
	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_publics; i++) {
		if (ReadAmxMemory(off) == address) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);

	if (index < 0 || index >= num_publics) {
		return false;
	}

	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_WIDE] = 0;
	info[AMX_FUNCSTUBNT_NAMEOFS] = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));

	return true;
}

/// <library>amx_assembly amx_header</library>
stock GetPublicAddressFromIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPublicInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

/// <library>amx_assembly amx_header</library>
stock GetPublicAddressFromName(const name[]) {
	return GetPublicAddressFromIndex(funcidx(name));
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPublicNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetPublicInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPublicNameFromAddress(address, name[], size = sizeof(name)) {
	return GetPublicNameFromIndex(GetPublicIndexFromAddress(address), name, size);
}

/// <library>amx_assembly amx_header</library>
stock HookPublic(index, address) {
	InitStaticAmxHeader();

	new num_publics = GetNumPublics(gHdr);

	if (index < 0 || index >= num_publics) {
		return 0;
	}

	new off = gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	new old_address = ReadAmxMemory(off);
	WriteAmxMemory(off, address);

	return old_address;
}

/// <library>amx_assembly amx_header</library>
stock GetNumNatives(const amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();

	return (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / amxhdr[AMX_HDR_DEFSIZE];
}

/// <library>amx_assembly amx_header</library>
static stock GetFirstNativeStringOffset() {
	new num_publics = GetNumPublics(gHdr);

	if (num_publics == 0) {
		return gHdr[AMX_HDR_NAMETABLE] - gHdr[AMX_HDR_DAT];
	} else {
		// Get the string after the last public.
		new nameofs = (gHdr[AMX_HDR_PUBLICS] - gHdr[AMX_HDR_DAT]) + ((num_publics - 1) * gHdr[AMX_HDR_DEFSIZE]);
		nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(nameofs + cellbytes)) - gHdr[AMX_HDR_DAT];
		return nameofs + NtLength(nameofs);
	}
}

/// <library>amx_assembly amx_header</library>
stock GetNativeIndexFromAddress(address, wide = 0) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);
	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		if (ReadAmxMemory(off) == address) {
			if (wide == 0 || wide == AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes))) {
				return i;
			}
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

#define GetNativeIndexFromAddressWide GetNativeIndexFromAddress

/// <library>amx_assembly amx_header</library>
stock bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	// For when "index" is not valid
	info[AMX_FUNCSTUBNT_ADDRESS] = -1;
	info[AMX_FUNCSTUBNT_WIDE] = 0;

	new num_natives = GetNumNatives(gHdr);

	if (index < 0 || index >= num_natives) {
		return false;
	}

	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_WIDE] = 0;

	if (HasReloc()) {
		info[AMX_FUNCSTUBNT_NAMEOFS] = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));
	} else {
		info[AMX_FUNCSTUBNT_WIDE] = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));
		new nameofs = GetFirstNativeStringOffset();
		while (index--) {
			nameofs += NtLength(nameofs);
		}
		info[AMX_FUNCSTUBNT_NAMEOFS] = nameofs;
	}

	return true;
}

/// <library>amx_assembly amx_header</library>
stock GetNativeIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);
	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT];

	if (HasReloc()) {
		// Linear search
		for (new i = 0; i < num_natives; i++) {
			new nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes)) - gHdr[AMX_HDR_DAT];

			new diff = NtCompare(nameofs, name);
			if (diff == 0) {
				return i;
			}

			off += gHdr[AMX_HDR_DEFSIZE];
		}
	} else {
		new nameofs = GetFirstNativeStringOffset();

		// Linear search
		for (new i = 0; i < num_natives; i++) {

			new diff = NtCompare(nameofs, name);
			if (diff == 0) {
				return i;
			}

			off += gHdr[AMX_HDR_DEFSIZE];

			// Skip this string instead of using pointers.
			nameofs += NtLength(nameofs);
		}
	}

	return -1;
}

/// <library>amx_assembly amx_header</library>
stock GetNativeAddressFromIndex(index, &wide = 0) {
	new info[AMX_FUNCSTUBNT];
	GetNativeInfo(index, info);
	wide = info[AMX_FUNCSTUBNT_WIDE];
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

/// <library>amx_assembly amx_header</library>
stock GetNativeAddressFromName(const name[], &wide = 0) {
	return GetNativeAddressFromIndex(GetNativeIndexFromName(name), wide);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetNativeNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetNativeInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetNativeNameFromAddress(address, name[], size = sizeof(name)) {
	return GetNativeNameFromIndex(GetNativeIndexFromAddress(address), name, size);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetNativeNameFromAddressWide(address, wide, name[], size = sizeof(name)) {
	return GetNativeNameFromIndex(GetNativeIndexFromAddressWide(address, wide), name, size);
}

/// <library>amx_assembly amx_header</library>
stock HookNative(index, address, wide = 0, &old_wide = 0) {
	InitStaticAmxHeader();

	new num_natives = GetNumNatives(gHdr);

	if (index < 0 || index >= num_natives) {
		return 0;
	}

	new off = gHdr[AMX_HDR_NATIVES] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	new old_address = ReadAmxMemory(off);
	WriteAmxMemory(off, address);
	if (HasReloc()) {
		old_wide = 0;
	} else {
		old_wide = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));
		WriteAmxMemory(off + cellbytes, wide);
	}

	return old_address;
}

/// <library>amx_assembly amx_header</library>
stock GetNumPubVars(const amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();

	return (amxhdr[AMX_HDR_TAGS] - amxhdr[AMX_HDR_PUBVARS]) / amxhdr[AMX_HDR_DEFSIZE];
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]) {
	InitStaticAmxHeader();

	new num_pubvars = GetNumPubVars(gHdr);

	if (index < 0 || index >= num_pubvars) {
		return false;
	}

	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = ReadAmxMemory(off);
	info[AMX_FUNCSTUBNT_WIDE] = 0;
	info[AMX_FUNCSTUBNT_NAMEOFS] = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));

	return true;
}

/// <library>amx_assembly amx_header</library>
stock GetPubVarIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new first = 0;
	new defsize = gHdr[AMX_HDR_DEFSIZE];
	new last = ((gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_PUBVARS]) / defsize) - 1;
	new mid = 0;
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Binary search
	while (first <= last) {
		mid = (first + last) / 2;
		new nameofs = off + (mid * defsize) + cellbytes;
		nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(nameofs)) - gHdr[AMX_HDR_DAT];
		nameofs = NtCompare(nameofs, name);
		if (nameofs < 0) {
			first = mid + 1;
		} else if (nameofs > 0) {
			last = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;
}

/// <library>amx_assembly amx_header</library>
stock GetPubVarIndexFromAddress(address) {
	InitStaticAmxHeader();

	new num_pubvars = GetNumPubVars(gHdr);
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_pubvars; i++) {
		if (ReadAmxMemory(off) == address) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

/// <library>amx_assembly amx_header</library>
stock GetPubVarAddressFromIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPubVarInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

/// <library>amx_assembly amx_header</library>
stock GetPubVarAddressFromName(const name[]) {
	return GetPubVarAddressFromIndex(GetPubVarIndexFromName(name));
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPubVar(const name[], &value) {
	InitStaticAmxHeader();

	new first = 0;
	new defsize = gHdr[AMX_HDR_DEFSIZE];
	new last = ((gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_PUBVARS]) / defsize) - 1;
	new mid = 0;
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Binary search
	while (first <= last) {
		mid = (first + last) / 2;
		new nameofs = off + (mid * defsize) + cellbytes;
		nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(nameofs)) - gHdr[AMX_HDR_DAT];
		nameofs = NtCompare(nameofs, name);
		if (nameofs < 0) {
			first = mid + 1;
		} else if (nameofs > 0) {
			last = mid - 1;
		} else {
			nameofs = ReadAmxMemory(off + (mid * defsize));
			value = ReadAmxMemory(nameofs);
			return true;
		}
	}
	return false;
}

/// <library>amx_assembly amx_header</library>
stock bool:SetPubVar(const name[], value) {
	InitStaticAmxHeader();

	new first = 0;
	new defsize = gHdr[AMX_HDR_DEFSIZE];
	new last = ((gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_PUBVARS]) / defsize) - 1;
	new mid = 0;
	new off = gHdr[AMX_HDR_PUBVARS] - gHdr[AMX_HDR_DAT];

	// Binary search
	while (first <= last) {
		mid = (first + last) / 2;
		new nameofs = off + (mid * defsize) + cellbytes;
		nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(nameofs)) - gHdr[AMX_HDR_DAT];
		nameofs = NtCompare(nameofs, name);
		if (nameofs < 0) {
			first = mid + 1;
		} else if (nameofs > 0) {
			last = mid - 1;
		} else {
			nameofs = ReadAmxMemory(off + (mid * defsize));
			WriteAmxMemory(nameofs, value);
			return true;
		}
	}
	return false;
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPubVarNameFromIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetPubVarInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetPubVarNameFromAddress(address, name[], size = sizeof(name)) {
	return GetPubVarNameFromIndex(GetPubVarIndexFromAddress(address), name, size);
}

/// <library>amx_assembly amx_header</library>
stock GetNumTags(const amxhdr[AMX_HDR]) {
	InitStaticAmxHeader();

	return (amxhdr[AMX_HDR_NAMETABLE] - amxhdr[AMX_HDR_TAGS]) / amxhdr[AMX_HDR_DEFSIZE];
}

/// <library>amx_assembly amx_header</library>
stock bool:GetTagInfo(index, info[AMX_FUNCSTUBNT]) {
	if (index == 0) {
		info[AMX_FUNCSTUBNT_ID] = AMX_TAG_LOCAL;
		info[AMX_FUNCSTUBNT_NAMEOFS] = 0;
		return true;
	}
	InitStaticAmxHeader();

	new num_tags = GetNumTags(gHdr);

	if (index < 0 || index >= num_tags) {
		return false;
	}

	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT] + index * gHdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ID] = ReadAmxMemory(off) | AMX_TAG_LOCAL;
	info[AMX_FUNCSTUBNT_NAMEOFS] = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(off + cellbytes));

	return true;
}

/// <library>amx_assembly amx_header</library>
stock GetTagIndexFromName(const name[]) {
	InitStaticAmxHeader();

	new first = 0;
	new defsize = gHdr[AMX_HDR_DEFSIZE];
	new last = ((gHdr[AMX_HDR_NAMETABLE] - gHdr[AMX_HDR_TAGS]) / defsize) - 1;
	new mid = 0;
	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT];

	// Binary search
	while (first <= last) {
		mid = (first + last) / 2;
		new nameofs = off + (mid * defsize) + cellbytes;
		nameofs = AMX_HEADER_MAYBE_MASK(ReadAmxMemory(nameofs)) - gHdr[AMX_HDR_DAT];
		nameofs = NtCompare(nameofs, name);
		if (nameofs < 0) {
			first = mid + 1;
		} else if (nameofs > 0) {
			last = mid - 1;
		} else {
			return mid;
		}
	}
	return -1;
}

/// <library>amx_assembly amx_header</library>
stock GetTagIndexFromID(id) {
	id &= AMX_TAG_MASK;
	if (id == 0)
		return 0;
	InitStaticAmxHeader();

	new num_tags = GetNumTags(gHdr);
	new off = gHdr[AMX_HDR_TAGS] - gHdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i <= num_tags; i++) {
		if (ReadAmxMemory(off) == id) {
			return i;
		}
		off += gHdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

/// <library>amx_assembly amx_header</library>
stock GetTagIDFromIndex(index) {
	if (index == 0)
		return AMX_TAG_LOCAL;
	new info[AMX_FUNCSTUBNT];
	GetTagInfo(index, info);
	return info[AMX_FUNCSTUBNT_ID];
}

/// <library>amx_assembly amx_header</library>
stock GetTagIDFromName(const name[]) {
	if (name[0] == '_' && name[1] == '\0')
		return AMX_TAG_LOCAL;
	return GetTagIDFromIndex(GetTagIndexFromName(name));
}

/// <library>amx_assembly amx_header</library>
stock bool:GetTagNameFromIndex(index, name[], size = sizeof(name)) {
	if (index == 0)
	{
		name[0] = '_';
		name[1] = '\0';
		return true;
	}
	new info[AMX_FUNCSTUBNT];
	if (!GetTagInfo(index, info)) {
		return false;
	}
	return (NtCopy(info[AMX_FUNCSTUBNT_NAMEOFS]
	        - GetAmxHeaderComponent(AMX_HDR_DAT), name, size) > 0);
}

/// <library>amx_assembly amx_header</library>
stock bool:GetTagNameFromID(id, name[], size = sizeof(name)) {
	if (id == 0)
	{
		name[0] = '_';
		name[1] = '\0';
		return true;
	}
	return GetTagNameFromIndex(GetTagIndexFromID(id), name, size);
}

#define AMX_ASSEMBLY_NO_BUGGED_TAGS 2

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIDStrong(tag) {
	return !!(tag & AMX_TAG_STRONG);
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIDWeak(tag) {
	return !(tag & AMX_TAG_STRONG);
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIDEmpty(tag) {
	return !(tag & AMX_TAG_MASK);
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagNameStrong(const tag[]) {
	return ('A' <= tag[0] <= 'Z');
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagNameWeak(const tag[]) {
	return !('A' <= tag[0] <= 'Z');
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagNameEmpty(const tag[]) {
	return (tag[0] == '_' && tag[1] == '\0');
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIndexStrong(tag) {
	new info[AMX_FUNCSTUBNT];
	return (GetTagInfo(tag, info) && IsTagIDStrong(info[AMX_FUNCSTUBNT_ID]));
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIndexWeak(tag) {
	new info[AMX_FUNCSTUBNT];
	return (GetTagInfo(tag, info) && IsTagIDWeak(info[AMX_FUNCSTUBNT_ID]));
}

/// <library>amx_assembly amx_header</library>
stock bool:IsTagIndexEmpty(tag) {
	return (tag == 0);
}

#undef InitStaticAmxHeader


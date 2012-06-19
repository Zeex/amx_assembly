// Copyright (C) 2011-2012 Zeex
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

#include <a_samp>
#include "amx_memory"

#define AMX_HDR_BYTES (60)
#define AMX_HDR_CELLS (AMX_HDR_BYTES / 4)

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

enum AMX_FUNCSTUBNT {
	AMX_FUNCSTUBNT_ADDRESS,
	AMX_FUNCSTUBNT_NAMEOFS
}

// Publics
forward GetPublicIndexByAddress(address);
forward GetPublicIndexByName(const name[]);
forward bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPublicAddressByName(const name[]);
forward GetPublicAddressByIndex(index);
forward bool:GetPublicNameByIndex(index, name[], size = sizeof(name));
forward bool:GetPublicNameByAddress(address, name[], size = sizeof(name));
forward HookPublic(index, address);

// Natives
forward GetNativeIndexByAddress(address);
forward GetNativeIndexByName(const name[]);
forward bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]);
forward GetNativeAddressByName(const name[]);
forward GetNativeAddressByIndex(index);
forward bool:GetNativeNameByIndex(index, name[], size = sizeof(name));
forward bool:GetNativeNameByAddress(address, name[], size = sizeof(name));

// Public Variables
forward bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]);
forward GetPubVarIndexByName(const name[]);
forward GetPubVarIndexByAddress(address);
forward GetPubVarAddressByName(const name[]);
forward GetPubVarAddressByIndex(index);
forward bool:GetPubVarNameByIndex(index, name[], size = sizeof(name));
forward bool:GetPubVarNameByAddress(address, name[], size = sizeof(name));

// General
forward GetPlainAmxHeader(plain_amxhdr[AMX_HDR_CELLS]);
forward GetAmxHeader(amxhdr[AMX_HDR]);
forward GetAmxHeaderOnce(amxhdr[AMX_HDR]);
forward PrintAmxHeader();

stock GetPlainAmxHeader(plain_amxhdr[AMX_HDR_CELLS]) {
	new address;
	#emit lctrl 1  // DAT
	#emit neg      // -DAT
	#emit stor.s.pri address

	for (new i = 0; i < AMX_HDR_CELLS; i++) {
		plain_amxhdr[i] = @(address);
		address += 4;
	}
}

static stock copy_1(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 1
}

static stock copy_2(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 2
}

static stock copy_4(&dest, const source[], start) {
	#emit load.s.pri source
	#emit load.s.alt start
	#emit add
	#emit load.s.alt dest
	#emit movs 4
}

stock GetAmxHeader(amxhdr[AMX_HDR]) {
	new plain_amxhdr[AMX_HDR_CELLS];
	GetPlainAmxHeader(plain_amxhdr);

	copy_4(amxhdr[AMX_HDR_SIZE], plain_amxhdr, 0);
	copy_2(amxhdr[AMX_HDR_MAGIC], plain_amxhdr, 4);
	copy_1(amxhdr[AMX_HDR_FILE_VERSION], plain_amxhdr, 6);
	copy_1(amxhdr[AMX_HDR_AMX_VERSION], plain_amxhdr, 7);
	copy_2(amxhdr[AMX_HDR_FLAGS], plain_amxhdr, 8);
	copy_2(amxhdr[AMX_HDR_DEFSIZE], plain_amxhdr, 10);
	copy_4(amxhdr[AMX_HDR_COD], plain_amxhdr, 12);
	copy_4(amxhdr[AMX_HDR_DAT], plain_amxhdr, 16);
	copy_4(amxhdr[AMX_HDR_HEA], plain_amxhdr, 20);
	copy_4(amxhdr[AMX_HDR_STP], plain_amxhdr, 24);
	copy_4(amxhdr[AMX_HDR_CIP], plain_amxhdr, 28);
	copy_4(amxhdr[AMX_HDR_PUBLICS], plain_amxhdr, 32);
	copy_4(amxhdr[AMX_HDR_NATIVES], plain_amxhdr, 36);
	copy_4(amxhdr[AMX_HDR_LIBRARIES], plain_amxhdr, 40);
	copy_4(amxhdr[AMX_HDR_PUBVARS], plain_amxhdr, 44);
	copy_4(amxhdr[AMX_HDR_TAGS], plain_amxhdr, 48);
	copy_4(amxhdr[AMX_HDR_NAMETABLE], plain_amxhdr, 52);
}

stock GetAmxHeaderOnce(amxhdr[AMX_HDR]) {
	static hdr[AMX_HDR];
	static bool:initialized = false;
	if (!initialized) {
		GetAmxHeader(hdr);
	}
	amxhdr = hdr;
}

stock PrintAmxHeader() {
	new amxhdr[AMX_HDR];
	GetAmxHeader(amxhdr);

	printf("------------------------");
	printf("AMX Header:");
	printf("------------------------");
	printf("size         %d", amxhdr[AMX_HDR_SIZE]);
	printf("magic        %x", amxhdr[AMX_HDR_MAGIC]);
	printf("file_version %d", amxhdr[AMX_HDR_FILE_VERSION]);
	printf("amx_version  %d", amxhdr[AMX_HDR_AMX_VERSION]);
	printf("flags        %d", amxhdr[AMX_HDR_FLAGS]);
	printf("defsize      %d", amxhdr[AMX_HDR_DEFSIZE]);
	printf("cod          0x%08x", amxhdr[AMX_HDR_COD]);
	printf("dat          0x%08x", amxhdr[AMX_HDR_DAT]);
	printf("hea          0x%08x", amxhdr[AMX_HDR_HEA]);
	printf("stp          0x%08x", amxhdr[AMX_HDR_STP]);
	printf("cip          0x%08x", amxhdr[AMX_HDR_CIP]);
	printf("publics      0x%08x", amxhdr[AMX_HDR_PUBLICS]);
	printf("natives      0x%08x", amxhdr[AMX_HDR_NATIVES]);
	printf("libraries    0x%08x", amxhdr[AMX_HDR_LIBRARIES]);
	printf("pubvars      0x%08x", amxhdr[AMX_HDR_PUBVARS]);
	printf("tags         0x%08x", amxhdr[AMX_HDR_TAGS]);
	printf("nametable    0x%08x", amxhdr[AMX_HDR_NAMETABLE]);
	printf("------------------------");
}

static stock strcpy(dest[], const source[], size = sizeof(dest)) {
	dest[0] = '\0';
	return strcat(dest, source, size);
}

// Compares a string stored in the name table starting at "s1" (packed)
// with an ordinary string "s2" (not packed).
// The address in s1 should be relative to DAT.
static stock NtNameVsString(s1, const s2[]) {
	new index;
	new c1, c2;
	new diff;

	do {
		c1 = @(s1++) & 0xFF;
		c2 = s2[index++];
		diff = c1 - c2;
		if (diff != 0) {
			break;
		}
	} while (!(c1 & c2 == 0));

	return diff;
}

// Copies a name from the name table to a usual string.
// The address in src should be relative to DAT.
// Returns the number of characters that were copied.
static stock CopyNtNameToString(src, dest[], size = sizeof(dest)) {
	new i = 0;
	new c;

	do {
		c = @(src++) & 0xFF;
		dest[i++] = c;
	} while (c != '\0' && i <= size);

	dest[i] = '\0'; // terminator

	return i;
}

stock GetNumPublics(amxhdr[AMX_HDR]) {
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / amxhdr[AMX_HDR_DEFSIZE];
	return num_publics;
}

stock GetPublicIndexByAddress(address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_publics = GetNumPublics(amxhdr);
	new off = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_publics; i++) {
		if (@(off) == address) {
			return i;
		}
		off += amxhdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_publics = GetNumPublics(amxhdr);

	if (index < 0 || index >= num_publics) {
		return false;
	}

	new off = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT] + index * amxhdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = @(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = @(off + 4);

	return true;
}

stock GetPublicIndexByName(const name[]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_publics = GetNumPublics(amxhdr);

	// Binary search
	new first = 0;
	new last = num_publics - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		new off = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT] + mid * amxhdr[AMX_HDR_DEFSIZE];
		new nameofs = @(off + 4) - amxhdr[AMX_HDR_DAT];

		new diff = NtNameVsString(nameofs, name);
		if (diff < 0) {
			first = mid + 1;
		} else if (diff > 0) {
			last = mid - 1;
		} else {
			return mid;
		}
	}

	return -1;
}

stock GetPublicAddressByIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPublicInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

stock GetPublicAddressByName(const name[]) {
	return GetPublicAddressByIndex(GetPublicIndexByName(name));
}

stock bool:GetPublicNameByIndex(index, name[], size = sizeof(name)) {
	if (index == -1) {
		strcpy(name, "main", size);
		return true;
	}

	new info[AMX_FUNCSTUBNT];
	if (!GetPublicInfo(index, info)) {
		return false;
	}

	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat

	return (CopyNtNameToString(info[AMX_FUNCSTUBNT_NAMEOFS] - dat, name, size) > 0);
}

stock bool:GetPublicNameByAddress(address, name[], size = sizeof(name)) {
	return GetPublicNameByIndex(GetPublicIndexByAddress(address), name, size);
}

// Replace public's address in publics table and return the original address
stock HookPublic(index, address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_publics = GetNumPublics(amxhdr);

	if (index < 0 || index >= num_publics) {
		return 0;
	}

	new off = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT] + index * amxhdr[AMX_HDR_DEFSIZE];
	new old_address = @(off);
	write@(off, address);

	return old_address;
}

stock GetNumNatives(amxhdr[AMX_HDR]) {
	return (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / amxhdr[AMX_HDR_DEFSIZE];
}

stock GetNativeIndexByAddress(address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_natives = GetNumNatives(amxhdr);
	new off = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		if (@(off) == address) {
			return i;
		}
		off += amxhdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_natives = GetNumNatives(amxhdr);

	if (index < 0 || index >= num_natives) {
		return false;
	}

	new off = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT] + index * amxhdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = @(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = @(off + 4);

	return true;
}

stock GetNativeIndexByName(const name[]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_natives = GetNumNatives(amxhdr);
	new off = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		new nameofs = @(off + 4) - amxhdr[AMX_HDR_DAT];

		new diff = NtNameVsString(nameofs, name);
		if (diff == 0) {
			return i;
		}

		off += amxhdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetNativeAddressByIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetNativeInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}

stock GetNativeAddressByName(const name[]) {
	return GetNativeAddressByIndex(GetNativeIndexByName(name));
}

stock bool:GetNativeNameByIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetNativeInfo(index, info)) {
		return false;
	}

	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat

	return (CopyNtNameToString(info[AMX_FUNCSTUBNT_NAMEOFS] - dat, name, size) > 0);
}

stock bool:GetNativeNameByAddress(address, name[], size = sizeof(name)) {
	return GetNativeNameByIndex(GetNativeIndexByAddress(address), name, size);
}

stock GetNumPubVars(amxhdr[AMX_HDR]) {
	return (amxhdr[AMX_HDR_TAGS] - amxhdr[AMX_HDR_PUBVARS]) / amxhdr[AMX_HDR_DEFSIZE];
}

stock bool:GetPubVarInfo(index, info[AMX_FUNCSTUBNT]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_pubvars = GetNumPubVars(amxhdr);

	if (index < 0 || index >= num_pubvars) {
		return false;
	}

	new off = amxhdr[AMX_HDR_PUBVARS] - amxhdr[AMX_HDR_DAT] + index * amxhdr[AMX_HDR_DEFSIZE];
	info[AMX_FUNCSTUBNT_ADDRESS] = @(off);
	info[AMX_FUNCSTUBNT_NAMEOFS] = @(off + 4);

	return true;
}

stock GetPubVarIndexByName(const name[]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_pubvars = GetNumPubVars(amxhdr);

	// Binary search
	new first = 0;
	new last = num_pubvars - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		new off = amxhdr[AMX_HDR_PUBVARS] - amxhdr[AMX_HDR_DAT] + mid * amxhdr[AMX_HDR_DEFSIZE];
		new nameofs = @(off + 4) - amxhdr[AMX_HDR_DAT];

		new diff = NtNameVsString(nameofs, name);
		if (diff < 0) {
			first = mid + 1;
		} else if (diff > 0) {
			last = mid - 1;
		} else {
			return mid;
		}
	}

	return -1;
}

stock GetPubVarIndexByAddress(address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new num_pubvars = GetNumPubVars(amxhdr);
	new off = amxhdr[AMX_HDR_PUBVARS] - amxhdr[AMX_HDR_DAT];

	// Linear search
	for (new i = 0; i < num_pubvars; i++) {
		if (@(off) == address) {
			return i;
		}
		off += amxhdr[AMX_HDR_DEFSIZE];
	}

	return -1;
}

stock GetPubVarAddressByIndex(index) {
	new info[AMX_FUNCSTUBNT];
	GetPubVarInfo(index, info);
	return info[AMX_FUNCSTUBNT_ADDRESS];
}


stock GetPubVarAddressByName(const name[]) {
	return GetPubVarAddressByIndex(GetPubVarIndexByName(name));
}

stock bool:GetPubVarNameByIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	if (!GetPubVarInfo(index, info)) {
		return false;
	}

	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat

	return (CopyNtNameToString(info[AMX_FUNCSTUBNT_NAMEOFS] - dat, name, size) > 0);
}

stock bool:GetPubVarNameByAddress(address, name[], size = sizeof(name)) {
	return GetPubVarNameByIndex(GetPubVarIndexByAddress(address), name, size);
}

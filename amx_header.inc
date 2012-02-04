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

// List of functions:
//   General:
//     GetPlainAmxHeader(plain_amxhdr[AMX_HDR_CELLS])
//     GetAmxHeader(amxhdr[AMX_HDR])
//     GetAmxHeaderOnce(amxhdr[AMX_HDR])
//     PrintAmxHeader()
//     GetPublicIndexByAddress(address)
//   Publics:
//     bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT])
//     GetPublicIndexByName(const name[])
//     GetPublicAddressByName(const name[])
//     GetPublicAddressByIndex(index);
//     GetPublicNameByIndex(index, name[], size = sizeof(name))
//     CallPublic(address, {Float,_}:...)
//   Natives:
//     GetNativeIndexByAddress(address)
//     bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT])
//     GetNativeIndexByName(const name[]);
//     GetNativeAddressByName(const name[])
//     GetNativeAddressByIndex(index);
//     GetNativeNameByIndex(index, name[], size = sizeof(name))
//     CallNative(address, {Float,_}:...)

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

stock GetPlainAmxHeader(plain_amxhdr[AMX_HDR_CELLS]) {
	new address;
	#emit lctrl 1  // DAT
	#emit neg      // -DAT
	#emit stor.s.pri address

	for (new i = 0; i < AMX_HDR_CELLS; i++) {
		new cell;
		#emit lref.s.pri address
		#emit stor.s.pri cell
		plain_amxhdr[i] = cell;
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
	GetAMXHeader(amxhdr);

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

stock GetPublicIndexByAddress(address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new publics = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;

	// Linear search
	for (new i = 0; i < num_publics; i++) {
		// Table record offset
		new offset = publics + i*defsize;

		new public_address;
		#emit lref.s.pri offset
		#emit stor.s.pri public_address
		offset += 4;

		if (public_address == address) {
			return i;
		}
	}

	return -1;
}

stock bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new publics = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;

	if (index < 0 || index >= num_publics) {
		return false;
	}

	// Table record offset
	new offset = publics + index*defsize;

	new address;
	#emit lref.s.pri offset
	#emit stor.s.pri address
	offset += 4;

	new nameofs;
	#emit lref.s.pri offset
	#emit stor.s.pri nameofs

	info[AMX_FUNCSTUBNT_ADDRESS] = address;
	info[AMX_FUNCSTUBNT_NAMEOFS] = nameofs;

	return true;
}

stock GetPublicIndexByName(const name[]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new publics = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;

	// Binary search
	new first = 0;
	new last = num_publics - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		// Table record offset
		new offset = publics + mid*defsize;

		new address;
		#emit lref.s.pri offset
		#emit stor.s.pri address
		offset += 4;

		new nameofs;
		#emit lref.s.pri offset
		#emit stor.s.pri nameofs
		//offset += 4;

		// Copy public's name
		new cur_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			cur_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (cur_name[index] != '\0' && ++index < sizeof(cur_name));

		new cmp = strcmp(name, cur_name);
		if (cmp > 0) {
			first = mid + 1;
		} else if (cmp < 0) {
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

stock GetPublicNameByIndex(index, name[], size = sizeof(name)) {
	if (index == -1) {
		strcpy(name, "main", size);
		return 1;
	}

	new info[AMX_FUNCSTUBNT];
	GetPublicInfo(index, info);

	new nameofs = info[AMX_FUNCSTUBNT_NAMEOFS];

	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat

	new i = 0;
	nameofs -= dat;
	do {
		name[i] = @(nameofs) & 0xFF;
		++nameofs;
	} while (name[i] != '\0' && ++i < size);
	name[size - 1] = '\0'; // terminator

	return 1;
}

stock CallPublic(address, {Float,_}:...) {
	if (address <= 0) {
		printf("CallPublic(): Invalid public address %x", address);
		return 0;
	}

	new arg_bytes, arg_begin, arg_end;

	// Get number of bytes passed
	#emit load.s.pri 0x8
	#emit const.alt 4
	#emit sub
	#emit stor.s.pri arg_bytes
	// Store in ALT
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT)
	#emit lctrl 5
	#emit add.c 0xc
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10
	#emit lctrl 5
	#emit add.c 0x10
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i // Variable arguments are passed by reference
		#emit push.pri
		arg -= 4;
	}

	// Call the function
	#emit push.s arg_bytes
	#emit lctrl 6
	#emit add.c 0x1c
	#emit push.pri
	#emit load.s.pri address
	#emit sctrl 6
	// Arguments are popped by callee

	// Pop locals and return
	#emit stack 0x10
	#emit retn
	return 0;
}

// Replace public's address in publics table and return the original address
stock HookPublic(index, address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new publics = amxhdr[AMX_HDR_PUBLICS] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_publics = (amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_PUBLICS]) / defsize;

	if (index < 0 || index >= num_publics) {
		return 0;
	}

	// Table record offset
	new offset = publics + index*defsize;

	new old_address;
	#emit lref.s.pri offset
	#emit stor.s.pri old_address
	#emit load.s.pri address
	#emit sref.s.pri offset

	return old_address;
}


stock GetNativeIndexByAddress(address) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new natives = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_natives = (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / defsize;

	// Linear search
	for (new i = 0; i < num_natives; i++) {
		// Table record offset
		new offset = natives + i*defsize;

		new native_address;
		#emit lref.s.pri offset
		#emit stor.s.pri native_address
		offset += 4;

		if (native_address == address) {
			return i;
		}
	}

	return -1;
}

stock bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new natives = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_natives = (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / defsize;

	if (index < 0 || index >= num_natives) {
		return false;
	}

	// Table record offset
	new offset = natives + index*defsize;

	new address;
	#emit lref.s.pri offset
	#emit stor.s.pri address
	offset += 4;

	new nameofs;
	#emit lref.s.pri offset
	#emit stor.s.pri nameofs

	info[AMX_FUNCSTUBNT_ADDRESS] = address;
	info[AMX_FUNCSTUBNT_NAMEOFS] = nameofs;

	return true;
}

stock GetNativeIndexByName(const name[]) {
	new amxhdr[AMX_HDR];
	GetAmxHeaderOnce(amxhdr);

	new natives = amxhdr[AMX_HDR_NATIVES] - amxhdr[AMX_HDR_DAT];
	new defsize = amxhdr[AMX_HDR_DEFSIZE];
	new num_natives = (amxhdr[AMX_HDR_LIBRARIES] - amxhdr[AMX_HDR_NATIVES]) / defsize;

	// Binary search
	new first = 0;
	new last = num_natives - 1;
	new mid;

	while (first <= last) {
		mid = (first + last) / 2;

		// Table record offset
		new offset = natives + mid*defsize;

		new address;
		#emit lref.s.pri offset
		#emit stor.s.pri address
		offset += 4;

		new nameofs;
		#emit lref.s.pri offset
		#emit stor.s.pri nameofs
		//offset += 4;

		// Copy public's name
		new cur_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			cur_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (cur_name[index] != '\0' && ++index < sizeof(cur_name));

		new cmp = strcmp(name, cur_name);
		if (cmp > 0) {
			last = mid - 1;
		} else if (cmp < 0) {
			first = mid + 1;
		} else {
			return mid;
		}
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

stock GetNativeNameByIndex(index, name[], size = sizeof(name)) {
	new info[AMX_FUNCSTUBNT];
	GetNativeInfo(index, info);

	new nameofs = info[AMX_FUNCSTUBNT_NAMEOFS];

	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat

	new i = 0;
	nameofs -= dat;
	do {
		name[i] = @(nameofs) & 0xFF;
		++nameofs;
	} while (name[i] != '\0' && ++i < size);
	name[size - 1] = '\0'; // terminator

	return 1;
}

stock CallNative(address, {Float,_}:...) {
	if (address <= 0) {
		printf("CallNative(): Invalid native address %x", address);
		return 0;
	}

	new arg_bytes, arg_begin, arg_end;

	// Get number of bytes passed
	#emit load.s.pri 0x8
	#emit const.alt 4
	#emit sub
	#emit stor.s.pri arg_bytes
	// Store in ALT
	#emit move.alt

	// Last argument is at FRM + 0x0C + arg_bytes (which is in ALT)
	#emit lctrl 5
	#emit add.c 0xc
	#emit add
	#emit stor.s.pri arg_end

	// Frist argument is at FRM + 0x10
	#emit lctrl 5
	#emit add.c 0x10
	#emit stor.s.pri arg_begin

	new arg = arg_end;
	new tmp;

	while (arg >= arg_begin) {
		#emit lref.s.pri arg
		#emit load.i // Variable arguments are passed by reference
		#emit push.pri
		arg -= 4;
	}

	// Push number of arguments * 4 (which is params[0])
	#emit push.s arg_bytes

	// Call the function
	// We use sysreq.d for this purpose

	// tmp = cod + cip - dat + <distance to nop #1>
	#emit lctrl 0  // COD
	#emit move.alt
	#emit lctrl 6  // CIP
	#emit add
	#emit move.alt
	#emit lctrl 1 // DAT
	#emit sub.alt
	#emit add.c 0x5c
	#emit stor.s.pri tmp

	// nop #1 = sysreq.d
	#emit const.pri 135
	#emit sref.s.pri tmp

	// tmp += 4
	#emit load.s.pri tmp
	#emit add.c 4
	#emit stor.s.pri tmp

	// nop #2 = address
	#emit load.s.pri address
	#emit sref.s.pri tmp

	#emit nop
	#emit nop

	// Pop native arguments
	#emit lctrl 4 // Get STK
	#emit load.s.alt arg_bytes
	#emit add
	#emit add.c 4 // One extra cell for params[0]
	#emit sctrl 4

	// Pop locals and return
	#emit stack 0x14
	#emit retn
	return 0;
}

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
//       Copies AMX header to plain_amxhdr as is (byte by byte).
//     GetAmxHeader(amxhdr[AMX_HDR])
//       Returns AMX header as a structured array (enum-array?).
//     GetAmxHeaderOnce(amxhdr[AMX_HDR])
//       Same as GetAmxHeader but calls GetPlainAmxHeader only once, on first call.
//     PrintAmxHeader()
//       Prints AMX header to the console in a human readable form.
//   Publics:
//     GetPublicIndexByAddress(address)
//       Returns public function index by address or -1 if no such public found.
//     bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT])
//       Copies public function information from AMX publics table (address + name offset).
//     GetPublicIndexByName(const name[])
//       Gets index of a public function with a given name. Returns is -1 if no such function exists.
//       This function is very simil to the funcidx() native.
//     GetPublicAddressByName(const name[])
//       Gets address of a public function. Returns is 0 if no such function exists.
//     GetPublicAddressByIndex(index);
//       Gets address of a public function by its index in the publics table. Returns is 0 on invalid index.
//     GetPublicNameByIndex(index, name[], size = sizeof(name))
//       Gets name of a public function by its index in the natives table. Returns true on success and false on invalid index.
//     HookPublic(index, address)
//       Replace address of public function stored in publics table with the new one.
//       This will ultimately recirect all calls of the hooked public to the specified address.
//       Note that the address can point out to any location inside the code section, including ordinary (non-public) functions.
//   Natives:
//     GetNativeIndexByAddress(address)
//       Returns native function index by address or -1 if no such native found.
//     bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT])
//       Copies native function information from AMX natives table (address + name offset).
//     GetNativeIndexByName(const name[])
//       Gets index of a native function with a given name. Returns is -1 if no such function exists.
//     GetNativeAddressByName(const name[])
//       Gets address of a native function. Returns is 0 if no such function exists.
//     GetNativeAddressByIndex(index)
//       Gets address of a native function by its index in the natives table. Returns is 0 on invalid index.
//     GetNativeNameByIndex(index, name[], size = sizeof(name))
//       Gets name of a native function by its index in the natives table. Returns true on success and false on invalid index.

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
			first = mid + 1;
		} else if (cmp < 0) {
			last = mid - 1;
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

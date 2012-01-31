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

// Function list:
//   GetPublicIndexByAddress(address)
//   bool:GetPublicInfo(index, info[AMX_FUNCSTUBNT])
//   GetPublicAddressByName(const name[])
//   GetPublicNameByIndex(index, name[], size = sizeof(name))
//   CallPublic(address, {Float,_}:...)

#include <string>
#include "amx_hdr"
#include "memory"

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
		new public_name[32];
		new index = 0;
		nameofs -= amxhdr[AMX_HDR_DAT];
		do {
			public_name[index] = @(nameofs) & 0xFF;
			++nameofs;
		} while (public_name[index] != '\0' && ++index < sizeof(public_name));

		new cmp = strcmp(name, public_name);
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

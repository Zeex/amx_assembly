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
//   GetNativeIndexByAddress(address)
//   bool:GetNativeInfo(index, info[AMX_FUNCSTUBNT])
//   GetNativeAddressByName(const name[])
//   GetNativeNameByIndex(index, name[], size = sizeof(name))

#include "amx_hdr"
#include "memory"

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

stock GetNativeAddressByIndex(index) {
	return info[AMX_FUNCSTUBNT_NAMEOFS];
}

stock GetNativeAddressByName(const name[]) {
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
			return address;
		}
	}

	return 0;
}

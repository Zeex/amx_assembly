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

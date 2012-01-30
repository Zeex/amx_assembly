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

stock GetPlainAMXHeader(plain_amxhdr[AMX_HDR_CELLS]) {
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

stock GetAMXHeader(amxhdr[AMX_HDR]) {
	new plain_amxhdr[AMX_HDR_CELLS];
	GetPlainAMXHeader(plain_amxhdr);

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

stock PrintAMXHeader() {
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

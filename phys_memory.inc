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

// Converts a real address to DAT-relative.
static stock AbsToRel(addr) {
	new dat;
	#emit lctrl 1
	#emit stor.s.pri dat
	return addr - (GetAmxBase() + dat);
}

// Copy num cells from physical memory starting at addr to dest.
stock ReadPhysMemory(addr, dest[], num = sizeof(dest)) {
	new rel_addr = AbsToRel(addr);

	// Current destination cell address.
	new cur_dest;
	#emit load.s.pri dest
	#emit stor.s.pri cur_dest

	// Currently reading address.
	new cur_addr = rel_addr;

	// Read num cells to dest.
	for (new i = 0; i < num; i++, cur_addr += 4, cur_dest += 4) {
		#emit lref.s.pri cur_addr
		#emit sref.s.pri cur_dest
	}

	#emit stack 12
	#emit retn
	return 0;
}

// Copy num cells from src to physical memory starting at addr.
stock WritePhysMemory(addr, src[], num = sizeof(src)) {
	new rel_addr = AbsToRel(addr);

	// Current destination cell address..
	new cur_src;
	#emit load.s.pri src
	#emit stor.s.pri cur_src

	// Currently reading address.
	new cur_addr = rel_addr;

	// Write num cells from src.
	for (new i = 0; i < num; i++, cur_addr += 4, cur_src += 4) {
		#emit lref.s.pri cur_src
		#emit sref.s.pri cur_addr
	}

	#emit stack 12
	#emit retn
	return 0;
}

// Reads a single cell from memory and returns it.
stock ReadPhysMemoryCell(addr) {
	new rel_addr = AbsToRel(addr);
	#emit lref.s.pri rel_addr
	#emit stack 8
	#emit retn
	return 0;
}

// Writes a single cell to memory.
stock WritePhysMemoryCell(addr, what) {
	new rel_addr = AbsToRel(addr);
	#emit load.s.pri what
	#emit sref.s.pri rel_addr
	#emit stack 8
	#emit retn
	return 0;
}

// Returns AMX base address i.e. amx->base.
stock GetAmxBase() {
	static amx_base = 0; // cached

	if (amx_base == 0) {
		new cod, dat;
		#emit lctrl 0
		#emit stor.s.pri cod
		#emit lctrl 1
		#emit stor.s.pri dat

		// Start of code section relative to data.
		new code_start = cod - dat;

		// Get this function address.
		new fn_addr;
		#emit const.pri GetAmxBase
		#emit stor.s.pri fn_addr

		// Get the return address stored from the stack.
		new ret_addr, tmp;
		#emit lctrl 5
		#emit add.c 4
		#emit stor.s.pri tmp
		#emit lref.s.pri tmp
		#emit stor.s.pri ret_addr

		// Get location of relocated function address in code.
		new fn_addr_reloc_ptr = code_start + ret_addr - 4;

		// Read in the relocated address.
		// It is equal to amx->base + amxhdr->cod + fn_addr.
		new fn_addr_reloc;
		#emit lref.s.pri fn_addr_reloc_ptr
		#emit stor.s.pri fn_addr_reloc

		amx_base = fn_addr_reloc - fn_addr - cod;
	}

	return amx_base;
}

// Swaps all bytes in a cell.
stock AlignCell(c) {
	new v[1];
	v[0] = c;
	new tmp;
	tmp = v{3};
	v{3} = v{0};
	v{0} = tmp;
	tmp = v{2};
	v{2} = v{1};
	v{1} = tmp;
	return v[0];
}

// Calls AlignCell against each element of an array.
stock AlignCellArray(a[], size = sizeof(a)) {
	for (new i = 0; i < size; i++) {
		a[i] = AlignCell(a[i]);
	}
}

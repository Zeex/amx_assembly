// Copyright (C) 2012 Zeex
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

#if defined IMPORT_TABLE_INC
	#endinput
#endif
#define IMPORT_TABLE_INC

/**
 * <library name="amx_assembly Windows import_table" summary="AMX Assembly Library: Load PE executable import tables.">
 *   <summary pawndoc="true">
 *     This library uses the enhanced <em>pawndoc.xsl</em> from
 *     <a href="https://github.com/pawn-lang/pawndoc">pawn-lang/pawndoc</a>.
 *     This XSL has features such as library and markdown support, and will not
 *     render this message when used.
 *   </summary>
 *   <remarks>
 *     Helpful resources:
 *     <ul>
 *       <li><a href="http://msdn.microsoft.com/en-us/library/ms809762.aspx">Peering Inside the PE: A Tour of the Win32 Portable Executable File Format</a></li>
 *       <li><a href="http://sandsprite.com/CodeStuff/Understanding_imports.html>Understanding the Import Address Table</a></li>
 *       <li><a href="http://msdn.microsoft.com/en-us/windows/hardware/gg463119.aspx>Microsoft PE and COFF Specification</a></li>
 *     </ul>
 *   </remarks>
 * </library>
 */

/// <p/>

#include <core>
#include "..\phys_memory"

/// <library>amx_assembly Windows import_table</library>
const DefaultImageBase = 0x00400000;

/// <library>amx_assembly Windows import_table</library>
const SizeOfFileHeader = 0x14;

/// <library>amx_assembly Windows import_table</library>
const SizeOfOptionalHeader = 0xE0;

/// <library>amx_assembly Windows import_table</library>
const SizeOfImportDirectory = 0x14;

/// <library>amx_assembly Windows import_table</library>
stock GetImportPointer(const name[]) {
	new DosHeader = DefaultImageBase;
	new NtHeaders = DosHeader + ReadDword(DosHeader, 0x3C);

	new FileHeader = NtHeaders + 0x04;
	new OptionalHeader = FileHeader + SizeOfFileHeader;

	new ImageBase = ReadDword(OptionalHeader, 0x1C);

	new ImportTableRva = ReadDword(OptionalHeader, 0x68);
	new ImportDirectories = ImageBase + ImportTableRva;

	for (new i = 0; ; i++) {
		new ImportDirectory = ImportDirectories + i * SizeOfImportDirectory;

		new Name = ReadDword(ImportDirectory, 0x0C);
		if (Name == 0)
			break;

		new ImportLookupTable = ImageBase + ReadDword(ImportDirectory, 0x00);
		new ImportAddressTable = ImageBase + ReadDword(ImportDirectory, 0x10);

		for (new j = 0 ; ; j++) {
			new NameOrdinal = ReadDword(ImportLookupTable, j * 4);

			new bool:NameOrdinalFlag = (NameOrdinal & 0x80000000) != 0;
			if (NameOrdinalFlag)
				continue;

			new ImportByName = NameOrdinal & ~0x80000000;
			if (ImportByName == 0)
				break;

			new iname[256];
			ReadString(ImageBase, ImportByName + 2, iname);

			if (strcmp(iname, name) == 0) {
				return ImportAddressTable + j * 4;
			}
		}
	}

	return 0;
}

/// <library>amx_assembly Windows import_table</library>
/// <summary>Finds a function in the Import Table and returns its address or 0 if found nothing.</summary>
stock GetImportAddress(const name[]) {
	new ImportPointer = GetImportPointer(name);

	if (ImportPointer != 0) {
		return ReadDword(ImportPointer, 0);
	}

	return 0;
}

/// <library>amx_assembly Windows import_table</library>
static stock ToCharString(s[], size = sizeof(s)) {
	for (new i = 0; i < size; i++) {
		s[i] = swapchars(s[i]);
	}
}

/// <library>amx_assembly Windows import_table</library>
static stock ReadDword(base, offset = 0) {
	return ReadPhysMemoryCell(base + offset);
}

/// <library>amx_assembly Windows import_table</library>
static stock ReadString(base, offset = 0, dest[], size = sizeof(dest)) {
	ReadPhysMemory(base + offset, dest, size);
	ToCharString(dest, size);
	strunpack(dest, dest, size);
}


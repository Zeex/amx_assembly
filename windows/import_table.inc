#include <a_samp>
#include <phys_memory>

static stock const SizeOfFileHeader = 0x14;
static stock const SizeOfOptionalHeader = 0xE0;
static stock const SizeOfImportDirectory = 0x14;

// Finds a function in the Import Table and returns its address or 0 if found nothing.
stock GetImportAddress(const name[], const module[] = "")
{
	new DosHeader = 0x00400000;
	new NtHeaders = DosHeader + ReadDword(DosHeader, 0x3C);

	new FileHeader = NtHeaders + 0x04;
	new OptionalHeader = FileHeader + SizeOfFileHeader;

	new ImageBase = ReadDword(OptionalHeader, 0x1C);

	new ImportTableRva = ReadDword(OptionalHeader, 0x68);
	new ImportDirectories = ImageBase + ImportTableRva;

	for (new i = 0; ; i++) {
		new ImportDirectory = ImportDirectories + i * SizeOfImportDirectory;
		new ModuleName = ReadDword(ImportDirectory, 0x0C);

		if (ModuleName == 0)
			break;

		new cur_module[256];
		ReadString(ImageBase, ModuleName, cur_module);

		if (module[0] != '\0' && strcmp(module, cur_module, true) != 0)
			continue;

		new ImportLookupTable = ImageBase + ReadDword(ImportDirectory, 0x00);
		new ImportAddressTable = ImageBase + ReadDword(ImportDirectory, 0x10);

		for (new j = 0 ; ; j++) {
			new ILTEntry = ReadDword(ImportLookupTable, j * 4);
			new IATEntry = ReadDword(ImportAddressTable, j * 4);

			new bool:OrdinalFlag = (ILTEntry & 0x80000000) != 0;

			if (OrdinalFlag)
				continue; // ??

			new ImportByName = ILTEntry & ~0x80000000;

			if (ImportByName == 0)
				break;

			new iname[256];
			ReadString(ImageBase, ImportByName + 2, iname);

			if (strcmp(iname, name) == 0)
				return IATEntry;
		}
	}

	return 0;
}

static stock ReadDword(base, offset = 0)
{
	return ReadPhysMemoryCell(base + offset);
}

static stock ReadString(base, offset = 0, dest[], size = sizeof(dest))
{
	ReadPhysMemory(base + offset, dest, size);
	ToCharString(dest, size);
	strunpack(dest, dest, size);
}

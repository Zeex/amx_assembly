#include <a_samp>

#include "amx_assembly/phys_memory"

main() {
	new s[24 char];
	new s2[24];
	ReadPhysMemory(0x004AB8CC, s);
	Align(s);
	strunpack(s2, s);
	print(s2); // will print "SA-MP Dedicated Server" on SA-MP 0.3d R2

	CrashServer();
}

stock CrashServer() {
	WritePhysMemoryCell(0, 123); // will give "Access violation reading location 0x00000000"
}


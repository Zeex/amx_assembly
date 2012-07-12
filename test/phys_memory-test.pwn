#include <a_samp>

#include "phys_memory"

main() {
	new s[24 char];
	new s2[24];

	ReadPhysMemory(0x004AB8CC, s);
	AlignCellArray(s);

	strunpack(s2, s);
	print(s2); // prints "SA-MP Dedicated Server" on SA-MP 0.3d R2
}

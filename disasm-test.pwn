#include <a_samp>

#include "disasm"

forward funny_public();

main() {
	Disassemble("disasm.lst");
	funny_public();
}

public funny_public() {
}

public OnGameModeInit() {
	printf("Hello!");
	return 1;
}

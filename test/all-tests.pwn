//#pragma option -a

#define main main_amx
#include "amx-test.pwn"
#undef main
#define main main_asm
#include "asm-test.pwn"
#undef main
#define main main_disasm
#include "disasm-test.pwn"
#undef main
#define main main_dynamic_call
#include "dynamic_call-test.pwn"
#undef main
#define main main_jit
#include "jit-test.pwn"
#undef main
#define main main_phys_memory
#include "phys_memory-test.pwn"
#undef main
#define main main_stack_trace
#include "stack_trace-test.pwn"
#undef main

main() {
	//PrintAmxHeader();
	//printf("0: %d", GetAmxBaseAddress());
	/*main_amx();
	printf("1");*/
	GetAmxAddress();
	//ReadAmxCell(AMX_OFFSET_BASE);
	/*main_asm();
	printf("2");
	main_disasm();
	printf("3");
	main_dynamic_call();
	printf("4");
	main_jit();
	printf("5");
	main_phys_memory();
	printf("6");
	main_stack_trace();
	printf("7");*/
}


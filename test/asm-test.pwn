#include "../asm"
#include "../dynamic_call"

forward HandleAsmError(ctx[AsmContext], AsmError:error);

main() {
	// Must use this native to make GetNativeAddress/IndexFromName go fine.
	print("Doing #emit at runtime...");

	new code[100];
	new ctx[AsmContext];

	AsmInit(ctx, code);
	AsmSetErrorHandler(ctx, GetPublicAddressFromName("HandleEmitError"));

	// Build a function that prints a string and returns:
	//
	// PrintString(const string[]) {
	//     printf(string);
	// }
	//
	// NOTE: "print" must be called somwhere else in order to for this work!

	@emit proc
	@emit push.s   12
	@emit push.c   4
	@emit sysreq.d GetNativeAddressFromName("print")
	@emit stack    8
	@emit retn

	CallFunction(AsmGetCode(ctx), ref("Hello!"));

	// ------------------------------------------------------
	// Same code as above but using some high-level functions:
	AsmInit(ctx, code);

	@emit proc
	@emit push.arg      0
	@emit push.num.args 1
	@emit sysreq        "print"
	@emit pop.args      1
	@emit retn

	CallFunction(AsmGetCode(ctx), ref("Hello again!"));
}

public HandleAsmError(ctx[AsmContext], AsmError:error) {
	printf("EmitError(%x, %d)", ctx, _:error);
}

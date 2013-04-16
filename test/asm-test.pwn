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

	emit proc      1;
	emit push_s    12;
	emit push_c    4;
	emit sysreq_d  GetNativeAddressFromName("print");
	emit stack     8;
	emit retn      ;

	CallFunction(AsmGetCode(ctx), ref("Hello!"));

	// ------------------------------------------------------
	// Same code as above but using some high-level functions:
	AsmInit(ctx, code);

	AsmEmitProc(ctx);
	AsmEmitPushArg(ctx, 0);
	AsmEmitPushNumArgs(ctx, 1);
	AsmEmitCallNative(ctx, "print");
	AsmEmitPopArgs(ctx, 1);
	AsmEmitRetn(ctx);

	CallFunction(AsmGetCode(ctx), ref("Hello again!"));
}

public HandleAsmError(ctx[AsmContext], AsmError:error) {
	printf("EmitError(%x, %d)", ctx, _:error);
}

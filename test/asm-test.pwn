#include "../asm"
#include "../dynamic_call"

forward HandleAsmError(ctx[AsmContext], AsmError:error);

main() {
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

	AsmEmitProc(ctx);
	AsmEmitPushS(ctx, 12);
	AsmEmitPushC(ctx, 4);
	AsmEmitSysreqC(ctx, GetNativeIndexFromName("print"));
	AsmEmitStack(ctx, 8);
	AsmEmitRetn(ctx);

	CallFunction(AsmGetCode(ctx), ref("Hello!"));

	// Same as above but using some helper functions:
	AsmInit(ctx, code);

	AsmEmitProc(ctx);
	AsmEmitPushS(ctx, EmitGetArgOffset(0));
	AsmEmitPushNumArgs(ctx, 1);
	AsmEmitCallNative(ctx, "print");
	AsmEmitPopArgs(ctx, 1);
	AsmEmitRetn(ctx);

	CallFunction(AsmGetCode(ctx), ref("Hello again!"));
}

public HandleAsmError(ctx[AsmContext], AsmError:error) {
	printf("EmitError(%x, %d)", ctx, _:error);
}

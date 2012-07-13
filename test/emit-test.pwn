#include "../emit"
#include "../dynamic_call"

forward HandleEmitError(ctx[EmitContext], EmitError:error);

main() {
	print("Doing #emit at runtime...");

	new code[100];
	new ctx[EmitContext];

	EmitInit(ctx, code);
	EmitSetErrorHandler(ctx, GetPublicAddressFromName("HandleEmitError"));

	// Build a function that prints a string and returns:
	//
	// PrintString(const string[]) {
	//     printf(string);
	// }
	//
	// NOTE: "print" must be called somwhere else in order to for this work!

	EmitProc(ctx);
	EmitPushS(ctx, 12);
	EmitPushC(ctx, 4);
	EmitSysreqC(ctx, GetNativeIndexFromName("print"));
	EmitStack(ctx, 8);
	EmitRetn(ctx);

	CallFunction(EmitGetCode(ctx), ref("Hello!"));

	// Same as above but using some helper functions:
	EmitInit(ctx, code);

	EmitProc(ctx);
	EmitPushS(ctx, EmitGetArgOffset(1));
	EmitPushNumArgs(ctx, 1);
	EmitCallNative(ctx, "print");
	EmitPopArgs(ctx, 1);
	EmitRetn(ctx);

	CallFunction(EmitGetCode(ctx), ref("Hello again!"));
}

public HandleEmitError(ctx[EmitContext], EmitError:error) {
	printf("EmitError(%x, %d)", ctx, _:error);
}

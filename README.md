Quick Overview
--------------

### amx_header ###

Allows you to print or copy AMX header, to explore publics/natives tables of it and more...

### amx_memory ###

A few handy functions/macros for reading from/writing memory within AMX data section. 

	// Example:
	new x = 123;
	new y = ref(x);
	new z = @(y); // z will be set to 123

### asm ###

A library for runtime (dynamic) code generation. For example, to build a function that
prints a string you would do somethin like this this:

	new code[100];
	new ctx[AsmContext];

	AsmInit(ctx, code);

	AsmEmitProc(ctx);
	AsmEmitPushS(ctx, 12);
	AsmEmitPushC(ctx, 4);
	AsmEmitSysreqC(ctx, GetNativeIndexFromName("print"));
	AsmEmitStack(ctx, 8);
	AsmEmitRetn(ctx);

	CallFunction(AsmGetCode(ctx), ref("Hello!"));

### disasm ###

Provides an API for disassembling the calling script, either by pieces or as a whole. For the latter case there
is a function called `DisasmDump(const filename[])` which produces an output similar to that of `pawndisasm`.

### dynamic_call ###

Allows you to call any functions dynamically using a high-level API.

	print("public - method #1");
	CallFunction(GetPublicAddressFromName("test"), 123, ref(x), ref("hell"), ref("yeah"));

	print("public - method #2");
	Push(123);
	Push(ref(x));
	Push(ref("hell"));
	Push(ref("yeah"));
	Call(GetPublicAddressFromName("test"));

	// A test function.
	public test(i, &j, s[], t[]) {
		printf("test: %d %d %s %s", i, j, s, t);
	}


The snippet above calls a public function, but you can do the same with native functions as well
using `SysreqC` or `CallNative`:

	print("native - method #1");
	CallNative(GetNativeIndexFromName("printf"), ref("Hello, %s!"), ref("World"));

	print("native - method #2");
	Push(ref("Hello, %s!"));
	Push(ref("World"));
	SysreqC(GetNativeIndexFromName("printf"));

### profiler ###

A simple profiler that is able to count execution time of all public functions.
It modifies the public functions table of the running AMX in order to redirect 
all public calls to internal helper functions which in turn call the original code.

### phys_memory ###

Allows you to read and write physical (real) memory of the server's process.

### stack_dump ###

Provides a function which dumps the currently active stack area to the server console.
This is Sometimes useful for debugging.

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

Also can be used to pass references to arrays or single variables when working with **dynamic_call**.
Another example of usage is the `EmitContext` structure in **emit**.

### disasm ###

Provides the `Disassemble()` function which disassembles the whole script in a human-readable format
to the specified text file. The output format is similar to that of `pawndisasm`.

Known to work only on Windows.

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

The snippet above calls a public function, but you can do the same with native functions as well
using `SysreqC` or `CallNative`:

	print("native - method #1");
	CallNative(GetNativeIndexFromName("printf"), ref("Hello, %s!"), ref("World"));

	print("native - method #2");
	Push(ref("Hello, %s!"));
	Push(ref("World"));
	SysreqC(GetNativeIndexFromName("printf"));

### emit ###

A library for runtime (dynamic) code generation. For example, to build a function that
prints a string you would do this:

	new code[100];
	new ctx[EmitContext];

	EmitInit(ctx, code);

	EmitProc(ctx);
	EmitPushS(ctx, 12);
	EmitPushC(ctx, 4);
	EmitSysreqC(ctx, GetNativeIndexFromName("print"));
	EmitStack(ctx, 8);
	EmitRetn(ctx);

	CallFunction(EmitGetCode(ctx), ref("Hello!"));

### profiler ###

A simple profiler that is able to count execution time of all public functions.
It modifies the public functions table of the running AMX in order to redirect 
all public calls to internal helper functions which in turn call the original code.

### phys_memory ###

Allows you to read and write physical (real) memory of the server's process.

### stack_dump ###

Provides a function which dumps the currently active stack area to the server console.
This is Sometimes useful for debugging.

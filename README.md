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

### emit ###

A modest library for runtime (dynamic) code generation.

### profiler ###

A simple profiler that is able to count execution time of all public functions.
It modifies the public functions table of the running AMX in order to redirect 
all public calls to internal helper functions which in turn call the original code.

### phys_memory ###

Allows you to read and write physical (real) memory at arbitrary addresses locations.
See phys_memory-test.pwn for examples.

### stack_dump ###

Provides a function which dumps the currently active stack area to the server console.
This is Sometimes useful for debugging.

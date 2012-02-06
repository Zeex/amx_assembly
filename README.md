Quick Overview
--------------

### amx_header ###

Print or copy AMX header, explore public/native tables, and more.

### amx_memory ###

A few handy functions/macros for reading from/writing to AMX data section. 

	// Example:
	new x = 123;
	new y = addressof(x);
	new z = @(y);

Also can be used to pass strings/references when working with dynamic_call.

### disasm ###

Self-disassemble to a text file. Same as running `pawndisasm` against the .amx.

### dynamic_call ###

Call any functions dynamically using a high-level API.

### profiler ###

A simple profiler that is able to count execution time of all public functions.
It modifies the public functions table of the running AMX in order to redirect 
all public calls to internal helper functions which in turn call the original code.

### phys_memory ###

Read and write physical (real) memory at arbitrary locations. See phys_memory-test.pwn for examples.

### stack_dump ###

Dump stack contents to the console, sometimes useful for debugging.

Quick Overview
--------------

### amx_header ###

Allows you to get/print AMX header (prefix) contents, explore public/native tables
and more. Heavily used by other modules.

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

Call public/native functions dynamically using a high-level API.

### profiler ###

A simple profiler that is able to measure execution time of public functions. 
It modifies the public functions table of the running AMX in order to redirect 
all public calls to internal helper functions which in turn call the original code.

### phys_memory ###

Read and write arbitrary memory out of AMX sandbox, i.e. SA-MP server process 
memory. See phys_memory-test.pwn for examples.

### stack_dump ###

Dump stack contents to the console, sometimes useful for debugging.

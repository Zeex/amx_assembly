Quick Overview
--------------

### amx_hdr ###

Allows you to get/print AMX header (prefix) contents. Heavily used by other 
modules.

### disasm ###

Self-disassembling to a text file. Same as running pawndisasm
against the target AMX.

### dynamic_call ###

Call public/native functions dynamically using a high-level API.

### memory ###

A few handy functions/macros for reading from/writing to AMX data section. 
`new x = @(y) // Read x from address stored in y`.
Becomes somehwat more powerful when used in conjuction with dynamic_call.

### phys_memory ###

Read and write arbitrary memory out of AMX sandbox, i.e. SA-MP server process 
memory. See phys_memory-test.pwn for examples.

### stack_dump ###

Dump stack contents to the console. Useful for debugging.

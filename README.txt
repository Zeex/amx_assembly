Quick Overview
===============

amx_hdr.inc - allows you to get/print AMX header (prefix) contents. 
Can be useful for debugging. Used in dynamic_call.

dynamic_call.inc - call public/native functions dynamically using a 
high-level API.

memory.inc  - a few handy functions/macros for reading from/writing to 
AMX memory. For example: new x = @(y) // Read x from address stored in y.

phys_memory.inc - Read and write arbitrary memory out of AMX sandbox,
i.e. SA-MP server process memory. See phys_memory-test.pwn for examples.

stack_dump.inc - the DumpStack() function.

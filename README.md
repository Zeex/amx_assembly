# amx_assembly

Some useful AMX assembly snippets and proof-of-concept scripts.

## Overview

* `amx` - Read/write contents of the AMX strcture (`struct AMX` in C code)
* `amx_base` - Get base address of the AMX in memory (`amx->base`)
* `amx_header` - Read contents of the AMX header (`AMX_HEADER`) and query header tables such as publics, natives, tags, etc.
* `amx_memory` - Utility functions for reading/writing AMX memory.
* `codescan` - Find patterns in bytecode.
* `disasm` - Example of how to disassemble AMX bytecode (i.e. self-disassembly).
* `dynamic_call` - Call any function by address or index. Can be very powerful in combination with `amx_header`.
* `frame_info` - Read information about call frames from the stack.
* `heap_alloc` - Allocate memory on the AMX heap.
* `jit` - Check if running under the [JIT](https://github.com/Zeex/samp-plugin-jit) plugin.
* `opcode` - List of AMX opcodes and utility functions for (un-)relocating opcodes on Linux.
* `os` - Detect operating system (Windows vs Linux).
* `phys_memory` - Read arbitrary memory of the host process.
* `profile` - Simple profiler written purely in Pawn. It can measure execution time of public functions.
* `shellcode` - Execute arbitrary natie code.
* `stack_dump` - Print stack contents to the console.
* `stack_trace` - Print stack trace.
* `windows/import_table` - Read the PE import table of the host process.
* `windows/ShellExecute` - Example of using `shellcode` in combination with `import_table` to call the `ShellExecuteA` function of the Windows API.

## Installation

Simply install to your project:

```bash
sampctl package install amx_assembly
```

Include in your code and begin using the library:

```pawn
#include <amx_assembly\part>
```

## Usage


## Testing

To test, simply run the package:

```bash
sampctl package run
```

And connect to `localhost:7777` to test.

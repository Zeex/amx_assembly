// Copyright (C) 2012 Zeex
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
// of the Software, and to permit persons to whom the Software is furnished to do
// so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "amx_header"
#include "dynamic_call"
#include "phys_memory"

// Calls to machine code stored in the specified buffer. The code should be preceeded with
// at least 15 NOPs (e.g. opcode 0x90) if "align" is true.
stock RunShellcode(code_ptr, bool:align = true) {
	static index = -1;

	if (index < 0) {
		fopen("<>");
		index = GetNativeIndexFromName("fopen");
	}

	if (align) {
		while (code_ptr % 16 != 0) {
			code_ptr++;
		}
	}

	new old = HookNative(index, code_ptr);
	new retval = SysreqC(index);
	HookNative(index, old);

	return retval;
}

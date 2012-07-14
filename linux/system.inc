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

#include "../amx_header"
#include "../dynamic_call"
#include "../phys_memory"

#define asm1(%0)          (0x90909000 | (%0))
#define asm2(%0,%1)       (0x90900000 | ((%1) << 8) | (%0))
#define asm3(%0,%1,%2)    (0x90000000 | ((%2) << 16) | ((%1) << 8) | %0)
#define asm4(%0,%1,%2,%3) (0x00000000 | ((%3) << 24) | ((%2) << 16) | (%1 << 8) | (%0))

#define asm5(%0,%1,%2,%3,%4)          asm4(%0,%1,%2,%3), asm1(%4)
#define asm6(%0,%1,%2,%3,%4,%5)       asm4(%0,%1,%2,%3), asm2(%4,%5)
#define asm7(%0,%1,%2,%3,%4,%5,%6)    asm4(%0,%1,%2,%3), asm3(%4,%5,%6)
#define asm8(%0,%1,%2,%3,%4,%5,%6,%7) asm4(%0,%1,%2,%3), asm4(%4,%5,%6,%7)

// NOTE: commands must be prepared with ToCharString() or similar function.
stock system(const command[]) {
	/*
	.text:00000500                var_18          = dword ptr -18h
	.text:00000500                arg_4           = dword ptr  0Ch
	.text:00000500
	.text:00000500 55                             push    ebp
	.text:00000501 89 E5                          mov     ebp, esp
	.text:00000503 83 EC 18                       sub     esp, 18h        ; string
	.text:00000506 8B 45 0C                       mov     eax, [ebp+arg_4]
	.text:00000509 83 C0 04                       add     eax, 4
	.text:0000050C 8B 00                          mov     eax, [eax]
	.text:0000050E 89 04 24                       mov     [esp+18h+var_18], eax
	.text:00000511 E8 DE 12 00 00                 call    system
	.text:00000516 C9                             leave
	.text:00000517 C3                             retn
	*/

	static const asm[] = {
		asm4(0x90, 0x90, 0x90, 0x90),
		asm4(0x90, 0x90, 0x90, 0x90),
		asm4(0x90, 0x90, 0x90, 0x90),
		asm4(0x90, 0x90, 0x90, 0x90),
		asm1(0x55),
		asm2(0x89, 0xE5),
		asm3(0x83, 0xEC, 0x18),
		asm3(0x8B, 0x45, 0x0C),
		asm3(0x83, 0xC0, 0x04),
		asm2(0x8B, 0x00),
		asm3(0x89, 0x04, 0x24),
		asm6(0xFF, 0x15, 0xE4, 0x5D, 0x19, 0x08), // 0.3e
		asm1(0xC9),
		asm1(0xC3)
	};

	Push(refabs(command));
	return CallNativeCode(asm);
}

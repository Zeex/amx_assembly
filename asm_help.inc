// Copyright (C) 2011-2012 Zeex
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

#if defined ASM_HELP_INC
	#endinput
#endif
#define ASM_HELP_INC

#define asm1(%0)          (0x90909000 | (%0))
#define asm2(%0,%1)       (0x90900000 | ((%1) << 8) | (%0))
#define asm3(%0,%1,%2)    (0x90000000 | ((%2) << 16) | ((%1) << 8) | %0)
#define asm4(%0,%1,%2,%3) (0x00000000 | ((%3) << 24) | ((%2) << 16) | (%1 << 8) | (%0))

#define asm5(%0,%1,%2,%3,%4)          asm4(%0,%1,%2,%3), asm1(%4)
#define asm6(%0,%1,%2,%3,%4,%5)       asm4(%0,%1,%2,%3), asm2(%4,%5)
#define asm7(%0,%1,%2,%3,%4,%5,%6)    asm4(%0,%1,%2,%3), asm3(%4,%5,%6)
#define asm8(%0,%1,%2,%3,%4,%5,%6,%7) asm4(%0,%1,%2,%3), asm4(%4,%5,%6,%7)

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

// Read a cell at a given location
stock read@(address) {
	#emit lref.s.pri address
	#emit retn
	return 0;
}

// Shorthand for read@
#define @ read@

// Get address of a variable
stock addressof(&x) {
	#emit load.s.pri x
	#emit retn
	return 0;
}

// Get address of a string
stock addressofs(const array[]) {
	#emit load.s.pri array
	#emit retn
	return 0;
}

// Write to memory at specified location
stock write@(address, value) {
	#emit load.s.pri value
	#emit sref.s.pri address
	#emit retn
	return 0;
}

#define w@ write@
#define r@ read@

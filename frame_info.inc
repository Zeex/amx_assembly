// Copyright (C) 2012 Y_Less
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

#if defined FRAME_INFO_INC
	#endinput
#endif
#define FRAME_INFO_INC

stock GetCurrentFrame() {
	#emit lctrl 5
	#emit push.pri
	#emit lref.s.pri 0xfffffffc

	#emit stack 4
	#emit retn

	return 0; // make compiler happy
}

stock GetFramePreviousFrame(frm_addr) {
	#emit lref.s.pri frm_addr
	#emit retn

	return 0; // make compiler happy
}

stock GetFrameReturn(frm_addr) {
	#emit load.s.pri frm_addr
	#emit add.c 4

	#emit push.pri
	#emit lref.s.pri 0xfffffffc

	#emit stack 4
	#emit retn

	return 0; // make compiler happy
}

stock SetFrameReturn(frm_addr, addr) {
	#emit load.s.pri frm_addr
	#emit add.c 4

	#emit push.pri
	#emit load.s.alt addr
	#emit sref.s.alt 0xfffffffc

	#emit stack 4
	#emit retn
}

stock GetFrameTotalSize(frm_addr) {
	return GetFrameLocalSize(frm_addr) + GetFrameHeaderSize(frm_addr) + GetFrameParameterSize(frm_addr);
}

stock GetFrameTotalCount(frm_addr) {
	return GetFrameTotalSize(frm_addr) / 4;
}

stock GetFrameLocalSize(frm_addr) {
	// run back through the stack
	new cur_frm = GetCurrentFrame();

	while (cur_frm != 0) {
		new prev_frm = GetFramePreviousFrame(cur_frm);
		if (prev_frm == frm_addr) {
			break;
		}
		cur_frm = prev_frm;
	}

	if (cur_frm == 0) {
		return 0;
	}

	// find the size of local variables in the selected frame.
	new frm_bottom = cur_frm + GetFrameHeaderSize(cur_frm) + GetFrameParameterSize(cur_frm);

	return frm_addr - frm_bottom;
}

stock GetFrameLocalCount(frm_addr) {
	return GetFrameLocalSize(frm_addr) / 4;
}

stock GetFrameHeaderSize(frm_addr) {
	#pragma unused frm_addr
	return 12;
}

stock GetFrameHeaderCount(frm_addr) {
	return GetFrameHeaderSize(frm_addr) / 4;
}

stock GetFrameParameterSize(frm_addr) {
	#emit load.s.pri frm_addr
	#emit add.c 8

	#emit push.pri
	#emit lref.s.pri 0xfffffffc

	#emit stack 4
	#emit retn

	return 0; // make compiler happy
}

stock GetFrameParameterCount(frm_addr) {
	return GetFrameParameterSize(frm_addr) / 4;
}

stock GetFrameParameter(frm_addr, param, idx = -1) {
	if (idx == -1) {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c 12

		#emit push.pri
		#emit lref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	} else {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c 12

		#emit push.pri
		#emit lref.s.alt 0xfffffffc
		
		#emit load.s.pri idx
		#emit lidx

		#emit stack 4
		#emit retn
	}

	return 0; // make compiler happy
}

stock GetFrameLocal(frm_addr, param) {
	if (param < 0) {
		// probably in correct format for negative offsets
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	} else {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit const.alt 0xfffffffc
		#emit sub.alt

		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit lref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	}

	return 0; // make compiler happy
}

stock SetFrameParameter(frm_addr, param, value, idx = -1) {
	if (idx == -1) {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c 12

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	} else {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit load.s.alt frm_addr
		#emit add

		#emit add.c 12

		#emit push.pri
		#emit lref.s.alt 0xfffffffc

		#emit load.s.pri idx
		#emit idxaddr

		#emit load.s.alt value
		#emit xchg
		#emit stor.i

		#emit stack 4
		#emit retn
	}

	return 0; // make compiler happy
}

stock SetFrameLocal(frm_addr, param, value) {
	if (param < 0) {
		// probably in correct format for negative offsets
		#emit load.s.pri param
		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	} else {
		#emit load.s.pri param
		#emit shl.c.pri 2

		#emit const.alt 0xfffffffc
		#emit sub.alt

		#emit load.s.alt frm_addr
		#emit add

		#emit push.pri
		#emit load.s.pri value
		#emit sref.s.pri 0xfffffffc

		#emit stack 4
		#emit retn
	}

	return 0; // make compiler happy
}

static stock GetCallerFrame() {
	#emit lctrl 5

	#emit push.pri
	#emit lref.s.pri 0xfffffffc

	#emit push.pri
	#emit lref.s.pri 0xfffffff8

	#emit stack 8
	#emit retn

	return 0; // make compiler happy
}

stock GetCurrentFramePreviousFrame() {
	return GetFramePreviousFrame(GetCallerFrame());
}

stock GetCurrentFrameReturn() {
	return GetFrameReturn(GetCallerFrame());
}

stock GetCurrentFrameTotalSize() {
	return GetFrameTotalSize(GetCallerFrame());
}

stock GetCurrentFrameTotalCount() {
	return GetFrameTotalCount(GetCallerFrame());
}

stock GetCurrentFrameLocalSize() {
	return GetFrameLocalSize(GetCallerFrame());
}

stock GetCurrentFrameLocalCount() {
	return GetFrameLocalCount(GetCallerFrame());
}

stock GetCurrentFrameHeaderSize() {
	return GetFrameHeaderSize(GetCallerFrame());
}

stock GetCurrentFrameHeaderCount() {
	return GetFrameHeaderCount(GetCallerFrame());
}

stock GetCurrentFrameParameterSize() {
	return GetFrameParameterSize(GetCallerFrame());
}

stock GetCurrentFrameParameter(param, idx = -1) {
	return GetFrameParameter(GetCallerFrame(), param, idx);
}

stock GetCurrentFrameLocal(param) {
	return GetFrameLocal(GetCallerFrame(), param);
}

stock GetCurrentFrameParameterCount() {
	return GetFrameParameterCount(GetCallerFrame());
}

stock SetCurrentFrameReturn(addr) {
	SetFrameReturn(GetCallerFrame(), addr);
}

#include <a_samp>

#include "../amx_header"
#include "../stack_trace"

forward public f2();

main() {
	f1();
}

stock f1() {
	f2();
}

public f2() {
	f3();
}

stock f3() {
	new stack_trace[10];
	new length = GetStackTrace(stack_trace);
	PrintStackTrace(stack_trace, length);
}

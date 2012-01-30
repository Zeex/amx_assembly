#include "amx_hdr"
#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	//PrintAMXHeader();

	new x = 456;

	// Method #1
	CallFunction("test", 123, addressof(x), addressofs("hell"), addressofs("yeah"));

	// Method #2
	Push(123);
	Push(addressof(x));
	Push(addressofs("hell"));
	Push(addressofs("yeah"));
	Call(GetFunctionAddress("test"));

	// Native
	CallNativeFunction("printf", addressofs("Hello, %s!"), addressofs("World"));
}

public test(i, &j, s[], t[]) {
	printf("test: %d %d %s %s", i, j, s, t);
}

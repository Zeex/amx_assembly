#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	new x = 456;

	// Publics -Method #1
	CallFunction("test", 123, addressof(x), addressofs("hell"), addressofs("yeah"));

	// Publics - method #2
	Push(123);
	Push(addressof(x));
	Push(addressofs("hell"));
	Push(addressofs("yeah"));
	Call(GetFunctionAddress("test"));

	// Natives - Method #1
	CallNativeFunction("printf", addressofs("Hello, %s!"), addressofs("World"));

	// Natives - Method #2
	Push(addressofs("Hello, %s!"));
	Push(addressofs("World"));
	CallNative(GetNativeFunctionAddress("printf"));
}

public test(i, &j, s[], t[]) {
	printf("test: %d %d %s %s", i, j, s, t);
}

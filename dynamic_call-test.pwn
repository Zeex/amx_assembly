#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	new x = 456;

	// Publics -Method #1
	CallPublic("test", 123, addressof(x), addressofs("hell"), addressofs("yeah"));

	// Publics - Method #2
	Push(123);
	Push(addressof(x));
	Push(addressofs("hell"));
	Push(addressofs("yeah"));
	Call(GetPublicAddressByName("test"));

	// Natives - Method #1
	CallNative("printf", addressofs("Hello, %s!"), addressofs("World"));

	// Natives - Method #2
	Push(addressofs("Hello, %s!"));
	Push(addressofs("World"));
	Sysreq(GetNativeAddressByName("printf"));
}

public test(i, &j, s[], t[]) {
	printf("test: %d %d %s %s", i, j, s, t);
}

#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	new x = 456;

	print("public - method #1");
	CallPublic(GetPublicAddressByName("test"), 123, addressof(x), addressofs("hell"), addressofs("yeah"));

	print("public - method #2");
	Push(123);
	Push(addressof(x));
	Push(addressofs("hell"));
	Push(addressofs("yeah"));
	Call(GetPublicAddressByName("test"));

	print("native - method #1");
	CallNative(GetNativeAddressByName("printf"), addressofs("Hello, %s!"), addressofs("World"));

	print("native - method #2");
	Push(addressofs("Hello, %s!"));
	Push(addressofs("World"));
	Sysreq(GetNativeAddressByName("printf"));
}

public test(i, &j, s[], t[]) {
	printf("test: %d %d %s %s", i, j, s, t);
}

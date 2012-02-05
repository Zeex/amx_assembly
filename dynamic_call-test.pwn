#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	new x = 456;

	print("public - method #1");
	CallFunction(GetPublicAddressByName("test"), 123, addressof(x), addressof("hell"), addressof("yeah"));

	print("public - method #2");
	Push(123);
	Push(addressof(x));
	Push(addressof("hell"));
	Push(addressof("yeah"));
	Call(GetPublicAddressByName("test"));

	print("native - method #1");
	CallNative(GetNativeAddressByName("printf"), addressof("Hello, %s!"), addressof("World"));

	print("native - method #2");
	Push(addressof("Hello, %s!"));
	Push(addressof("World"));
	Sysreq(GetNativeAddressByName("printf"));
}

public test(i, &j, s[], t[]) {
	printf("test: %d %d %s %s", i, j, s, t);
}

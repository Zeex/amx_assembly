#include "dynamic_call"

forward test(i, s[], t[]);

main() {
	CallFunction("test", "iss", 1, "hell", "yeah");
}

public test(i, s[], t[]) {
	printf("%d %s %s", i, s, t);
}

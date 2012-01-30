#include "dynamic_call"

forward test(i, &j, s[], t[]);

main() {
	new x = 456;
	CallFunction("test", 123, addressof(x), addressofs("hell"), addressofs("yeah"));
}

public test(i, &j, s[], t[]) {
	printf("%d %d %s %s", i, j, s, t);
}

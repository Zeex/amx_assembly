#include <system>

main() {
	new command[] = !"echo Hello from system()";
	ToCharString(command);
	new result = system(command);
	printf("system() returned %d", result);
}

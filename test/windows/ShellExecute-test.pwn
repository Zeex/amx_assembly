#include <ShellExecute>

main() {
	new File[] = !"notepad.exe";
	new Operation[] = !"open";
	new Parameters[] = !"server.cfg";

	ToCharString(File);
	ToCharString(Operation);
	ToCharString(Parameters);

	new result = ShellExecute(Operation, File, Parameters, SW_SHOW);
	printf("ShellExecute() returned %d", result);
}

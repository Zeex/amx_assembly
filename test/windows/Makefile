ifndef PAWNCC
PAWNCC=pawncc
endif

INCLUDE=-i../../ -i../../windows

AMX = ShellExecute-test.amx

all: clean $(AMX)

ShellExecute-test.amx: ShellExecute-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

clean:
	rm -rf $(AMX)

ifndef PAWNCC
PAWNCC=pawncc
endif

INCLUDE=-i../../ -i../../windows

AMX = ShellExecute-test.amx

all: $(AMX)

ShellExecute-test.amx: ShellExecute-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

clean:
	rm -rf $(AMX)

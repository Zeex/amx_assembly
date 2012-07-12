ifndef PAWNCC
PAWNCC=pawncc
endif

INCLUDE=-i../../ -i../../linux

AMX = system-test.amx

all: clean $(AMX)

system-test.amx: system-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

clean:
	rm -rf $(AMX)

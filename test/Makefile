ifndef PAWNCC
PAWNCC = pawncc
endif

INCLUDE = -i../

AMX  = disasm-test.amx
AMX += dynamic_call-test.amx
AMX += asm-test.amx
AMX += phys_memory-test.amx

all: clean $(AMX) windows

disasm-test.amx: disasm-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

dynamic_call-test.amx: dynamic_call-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

asm-test.amx: asm-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

phys_memory-test.amx: phys_memory-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

clean: $(SUBDIRS)
	rm -rf $(AMX)

.PHONY: windows
windows:
	$(MAKE) -C $@


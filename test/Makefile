ifndef PAWNCC
PAWNCC = pawncc
endif

INCLUDE = -i../

AMX  = disasm-test.amx
AMX += dynamic_call-test.amx
AMX += emit-test.amx
AMX += phys_memory-test.amx

SUBDIRS = windows linux

all: clean $(AMX) $(SUBDIRS)

disasm-test.amx: disasm-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

dynamic_call-test.amx: dynamic_call-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

emit-test.amx: emit-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

phys_memory-test.amx: phys_memory-test.pwn
	$(PAWNCC) $(PFLAGS) $(INCLUDE) $^ -o$@

clean: $(SUBDIRS)
	rm -rf $(AMX)

.PHONY: windows
windows:
	$(MAKE) -C $@

.PHONY: linux
linux:
	$(MAKE) -C $@

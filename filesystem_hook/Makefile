# Beats 1 and 2 of the filesystem sequence. Beat 3 (the kernel module) lives in
# kernel_module/ and is built and loaded ONLY inside the throwaway VM.

CFLAGS = -Wall -Wextra -O2

all: hidefile.so rawls

hidefile.so: hidefile.c
	$(CC) -shared -fPIC $(CFLAGS) -o $@ $< -ldl

rawls: rawls.c
	$(CC) $(CFLAGS) -o $@ $<

# Rebuild the demo directory from scratch so the live demo always starts clean.
sandbox:
	rm -rf sandbox
	mkdir sandbox
	touch sandbox/report.txt sandbox/data.csv sandbox/secret_config.yaml

# The two-beat proof, end to end.
demo: all sandbox
	@echo '--- $$ ls sandbox'
	@ls sandbox
	@echo
	@echo '--- $$ HIDE=secret LD_PRELOAD=./hidefile.so ls sandbox   (readdir hooked)'
	@HIDE=secret LD_PRELOAD=./hidefile.so ls sandbox
	@echo
	@echo '--- $$ HIDE=secret LD_PRELOAD=./hidefile.so ./rawls sandbox   (getdents64, hook bypassed)'
	@HIDE=secret LD_PRELOAD=./hidefile.so ./rawls sandbox

clean:
	rm -f hidefile.so rawls
	rm -rf sandbox

.PHONY: all demo clean sandbox

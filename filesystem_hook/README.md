# Filesystem testability hook

Live-demo material for "Being a Test Developer Allows Me to Build in Testability."

The point: a tester can control what a program *sees* the filesystem contain,
without touching the program, and the layer you hook at decides how much you
actually control.

## The three beats

**Beat 1 - user space.** `hidefile.c` overrides glibc's `readdir()` via
`LD_PRELOAD`. Any directory entry matching `$HIDE` disappears from the listing.
The program under test is never recompiled and never knows.

```
make
HIDE=secret LD_PRELOAD=./hidefile.so ls sandbox
```

**Beat 2 - the hook gets walked around.** `rawls.c` asks the kernel directly
with `getdents64()` instead of going through `readdir()`. The hook is still
loaded; the hidden file comes back.

```
HIDE=secret LD_PRELOAD=./hidefile.so ./rawls sandbox
```

Same lesson for testers, not just for demos: a hook that covers one path through
the stack gives false confidence about every other path.

**Beat 3 - the kernel.** The only layer that cannot be bypassed from user space.
Lives in `../kernel_module/` and is built and loaded **only inside a throwaway
VM**, never on a machine you care about. See that directory's README.

## Run the whole thing

```
make demo
```

Rebuilds the sandbox from scratch and runs beats 1 and 2 back to back, which is
also how to reset between rehearsals.

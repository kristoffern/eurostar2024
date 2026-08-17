/*
 * Beat 1: intercept readdir() in user space.
 *
 * The program being tested is not recompiled, not restarted with a special
 * flag, and does not know this exists. We load ahead of glibc and answer the
 * question "what is in this directory?" ourselves.
 *
 *   make
 *   HIDE=secret LD_PRELOAD=./hidefile.so ls sandbox
 *
 * Any entry whose name contains $HIDE is dropped from the listing.
 */

#define _GNU_SOURCE
#include <dirent.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>

struct dirent *readdir(DIR *dirp)
{
	static struct dirent *(*real_readdir)(DIR *) = NULL;

	if (!real_readdir)
		real_readdir = dlsym(RTLD_NEXT, "readdir");

	const char *hide = getenv("HIDE");
	struct dirent *entry;

	/* Keep pulling entries until we find one the test wants visible. */
	while ((entry = real_readdir(dirp))) {
		if (!hide || !strstr(entry->d_name, hide))
			return entry;
	}

	return NULL;
}

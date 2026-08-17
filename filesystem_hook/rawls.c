/*
 * Beat 2: walk around the hook.
 *
 * hidefile.so intercepts glibc's readdir(). This program never calls readdir().
 * It asks the kernel directly with getdents64(), so the interception never
 * happens and the hidden file comes back.
 *
 *   make
 *   HIDE=secret LD_PRELOAD=../hidefile.so ./rawls sandbox
 *
 * This is the argument for going into the kernel. A hook that covers one path
 * through the stack gives false confidence about all the others.
 */

#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

struct linux_dirent64 {
	unsigned long long d_ino;
	long long          d_off;
	unsigned short     d_reclen;
	unsigned char      d_type;
	char               d_name[];
};

int main(int argc, char **argv)
{
	char buf[8192];
	int fd, nread;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <directory>\n", argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY | O_DIRECTORY);
	if (fd < 0) {
		perror("open");
		return 1;
	}

	while ((nread = syscall(SYS_getdents64, fd, buf, sizeof buf)) > 0) {
		for (int off = 0; off < nread; ) {
			struct linux_dirent64 *d = (struct linux_dirent64 *)(buf + off);
			printf("%s\n", d->d_name);
			off += d->d_reclen;
		}
	}

	close(fd);
	return 0;
}

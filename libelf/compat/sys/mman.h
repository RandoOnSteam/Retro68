#ifndef RETRO68_COMPAT_SYS_MMAN_H
#define RETRO68_COMPAT_SYS_MMAN_H

#include <stddef.h>
#include <sys/types.h>

#define PROT_READ 1
#define PROT_WRITE 2
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#define MAP_FAILED ((void *) -1)
#define MS_SYNC 4
#define MS_ASYNC 1

static inline void *mmap(void *address, size_t length, int protection, int flags, int descriptor, off_t offset)
{
	(void) address;
	(void) length;
	(void) protection;
	(void) flags;
	(void) descriptor;
	(void) offset;
	return MAP_FAILED;
}

static inline int munmap(void *address, size_t length)
{
	(void) address;
	(void) length;
	return 0;
}

static inline int msync(void *address, size_t length, int flags)
{
	(void) address;
	(void) length;
	(void) flags;
	return 0;
}

#endif

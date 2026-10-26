#ifndef RETRO68_COMPAT_UNISTD_H
#define RETRO68_COMPAT_UNISTD_H

#include_next <unistd.h>
#include <io.h>

#ifndef _SC_PAGESIZE
#define _SC_PAGESIZE 30
#endif

static inline long sysconf(int name)
{
	if (name == _SC_PAGESIZE)
		return 4096;
	return -1;
}

static inline ssize_t pread(int descriptor, void *buffer, size_t count, off_t offset)
{
	__int64 saved = _lseeki64(descriptor, 0, SEEK_CUR);
	ssize_t result;
	if (saved < 0 || _lseeki64(descriptor, offset, SEEK_SET) < 0)
		return -1;
	result = read(descriptor, buffer, (unsigned int) count);
	_lseeki64(descriptor, saved, SEEK_SET);
	return result;
}

static inline ssize_t pwrite(int descriptor, const void *buffer, size_t count, off_t offset)
{
	__int64 saved = _lseeki64(descriptor, 0, SEEK_CUR);
	ssize_t result;
	if (saved < 0 || _lseeki64(descriptor, offset, SEEK_SET) < 0)
		return -1;
	result = write(descriptor, buffer, (unsigned int) count);
	_lseeki64(descriptor, saved, SEEK_SET);
	return result;
}

#endif

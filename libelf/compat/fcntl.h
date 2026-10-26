#ifndef RETRO68_COMPAT_FCNTL_H
#define RETRO68_COMPAT_FCNTL_H

#include_next <fcntl.h>
#include <errno.h>
#include <io.h>

#ifndef F_GETFD
#define F_GETFD 1
#endif

static inline int fcntl(int descriptor, int command, ...)
{
	if (command == F_GETFD && _get_osfhandle(descriptor) != -1)
		return 0;
	errno = EBADF;
	return -1;
}

static inline int posix_fallocate(int descriptor, off_t offset, off_t length)
{
	__int64 size = _filelengthi64(descriptor);
	if (size < 0)
		return errno;
	if (size >= (__int64) offset + (__int64) length)
		return 0;
	return _chsize_s(descriptor, (__int64) offset + (__int64) length);
}

#endif

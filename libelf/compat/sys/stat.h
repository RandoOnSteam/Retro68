#ifndef RETRO68_COMPAT_SYS_STAT_H
#define RETRO68_COMPAT_SYS_STAT_H

#include_next <sys/stat.h>

#ifndef S_ISUID
#define S_ISUID 0
#endif
#ifndef S_ISGID
#define S_ISGID 0
#endif

static inline int fchmod(int descriptor, mode_t mode)
{
	(void) descriptor;
	(void) mode;
	return 0;
}

#endif

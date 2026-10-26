#ifndef RETRO68_COMPAT_SYS_PARAM_H
#define RETRO68_COMPAT_SYS_PARAM_H

#include_next <sys/param.h>

#ifndef powerof2
#define powerof2(x) ((((x) - 1) & (x)) == 0)
#endif

#endif

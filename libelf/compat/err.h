#ifndef RETRO68_COMPAT_ERR_H
#define RETRO68_COMPAT_ERR_H

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline void retro68_vwarn(int useerrno, const char *format, va_list arguments)
{
	int saved = errno;
	fputs("error: ", stderr);
	if (format)
		vfprintf(stderr, format, arguments);
	if (useerrno)
		fprintf(stderr, ": %s", strerror(saved));
	fputc('\n', stderr);
}

static inline void warn(const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	retro68_vwarn(1, format, arguments);
	va_end(arguments);
}

static inline void warnx(const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	retro68_vwarn(0, format, arguments);
	va_end(arguments);
}

static inline void err(int status, const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	retro68_vwarn(1, format, arguments);
	va_end(arguments);
	exit(status);
}

static inline void errx(int status, const char *format, ...)
{
	va_list arguments;
	va_start(arguments, format);
	retro68_vwarn(0, format, arguments);
	va_end(arguments);
	exit(status);
}

#endif

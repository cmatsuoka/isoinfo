#include <stdio.h>
#include <stdarg.h>
#include "common.h"

void report(char *msg, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	printf("%-28.28s: ", msg);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

void report_s(char *msg, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	printf("%-28.28s: \"", msg);
	vprintf(fmt, ap);
	printf("\"\n");
	va_end(ap);
}

void report_32(char *msg, unsigned char *b)
{
	printf("%-28.28s: %02x %02x %02x %02x (%d)\n",
			msg, b[0], b[1], b[2], b[3], read32l(b));
}

void report_16(char *msg, unsigned char *b)
{
	printf("%-28.28s: %02x %02x (%d)\n", msg, b[0], b[1], read16l(b));
}

void report_offset(unsigned char *b)
{
	printf("\n-----------------------------\n");
	printf("OFFSET %#010lx", (b - buf));
	printf("\n-----------------------------\n");
}

unsigned int read32l(unsigned char *m)
{
	unsigned int a, b, c, d;

	a = m[0];
	b = m[1];
	c = m[2];
	d = m[3];

        return (d << 24) | (c << 16) | (b << 8) | a;
}

unsigned int read16l(unsigned char *m)
{
	unsigned int a, b;

	a = m[0];
	b = m[1];

        return (b << 8) | a;
}


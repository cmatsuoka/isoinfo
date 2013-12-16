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

void report_date(char *msg, unsigned char *b)
{
	char tz = b[16];
	int h, m;

	if (tz < 0) {
		h = -(-tz / 4);
		m = -tz % 4;
	} else {
		h = tz / 4;
		m = tz % 4;
	}

	printf("%-28.28s: %4.4s/%2.2s/%2.2s %2.2s:%2.2s:%2.2s:%2.2s "
				"UTC%+d:%02d\n", msg, b, b + 4, b + 6,
				b + 8, b + 10, b + 12, b + 14, h, m * 15);
}

void report_offset(unsigned char *b)
{
	printf("\n-----------------------------\n");
	printf("OFFSET %#010lx", (b - iso_image));
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


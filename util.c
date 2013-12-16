#include <stdio.h>
#include <stdarg.h>
#include "common.h"

void report(char *msg, char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	printf("%s: ", msg);
	vprintf(fmt, ap);
	printf("\n");
	va_end(ap);
}

void report_offset(unsigned char *b)
{
	printf("OFFSET %#010lx\n", (b - buf));
}

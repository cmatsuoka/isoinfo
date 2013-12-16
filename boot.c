#include "common.h"

int read_boot(unsigned char *b)
{
	report_s("Boot System Identifier", "%-32.32s", b); b += 32;
	report_s("Boot Identifier", "%-32.32s", b); b += 32;

	return 0;
}

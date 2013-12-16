#include <string.h>
#include "common.h"

int read_boot(unsigned char *b)
{
	if (!memcmp(b, "EL TORITO SPECIFICATION\x0\x0\x0\x0\0\x0\x0\x0\x0\x0", 32))
		el_torito = 1;

	report_s("Boot System Identifier", "%-32.32s", b); b += 32;
	report_s("Boot Identifier", "%-32.32s", b); b += 32;

	if (el_torito) {
		boot_catalog = read32l(b) * 2048;
		report_32("Boot Catalog Sector", b); b += 8;
	}

	return 0;
}

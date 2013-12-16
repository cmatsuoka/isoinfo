
#include "common.h"

int read_iso(unsigned char *b)
{
	int type;

	b += 0x8000;

	do {
		type = *b;
		report_offset(b);
		read_volume(b); b += 2048;
	} while (type != 0xff);

	return 0;
}

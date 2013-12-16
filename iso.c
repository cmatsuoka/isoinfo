
#include "common.h"

int read_iso(unsigned char *b)
{
	b += 0x8000;

	report_offset(b);
	read_volume(b); b += 2048;

	report_offset(b);
	read_volume(b); b += 2048;

	return 0;
}

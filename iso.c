#include "common.h"

unsigned char *iso_image;
int el_torito = 0;
int boot_catalog = 0;

int read_iso(unsigned char *b)
{
	int type;

	iso_image = b;
	b += 0x8000;

	do {
		type = *b;
		report_offset(b);
		read_volume(b); b += 2048;
	} while (type != 0xff);

	if (el_torito) {
		b = iso_image + boot_catalog;
		report_offset(b);
		read_catalog(b);
	}

	return 0;
}

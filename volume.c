#include <stdio.h>
#include "common.h"

static const char *descriptor_type[] = {
	"BOOT RECORD DESCRIPTOR",
	"PRIMARY VOLUME DESCRIPTOR",
	"SUPPLEMENTARY VOLUME DESCRIPTOR",
	"VOLUME PARTITION DESCRIPTOR",
	"RESERVED",
	"VOLUME DESCRIPTOR SET TERMINATOR"
};

static const char *get_type_name(int t)
{
	if (t == 255)
		t = 5;
	else if (t > 4)
		t = 4;

	return descriptor_type[t];
}

int read_volume(unsigned char *b)
{
	int type;

	type = *b++;
	printf("%s\n\n", get_type_name(type));
	report("Volume Descriptor Type", "%X", type);
	report_s("Standard Identifier", "%-5.5s", b); b += 5;
	report("Volume Descriptor Version", "%X", *b++);

	switch (type) {
	case 0:
		read_boot(b);
		break;
	case 1:
		read_primary(b);
		break;
	case 2:
		read_supplementary(b);
		break;
	}

	return 0;
}

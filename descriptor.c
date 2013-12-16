#include "common.h"

static const char *descriptor_type[] = {
	"Boot Record Descriptor",
	"Primary Volume Descriptor",
	"Supplementary Volume Descriptor",
	"Volume Partition Descriptor",
	"reserved"
};

static const char *get_type_name(int t)
{
	if (t == 255)
		return "Volume Descriptor Set Terminator";

	if (t > 4)
		t = 4;

	return descriptor_type[t];
}

int read_descriptor(unsigned char *b)
{
	int type;

	type = *b++;
	report("Volume Descriptor Type", "%d (%s)", type, get_type_name(type));
	report("Standard Identifier", "%-5.5s", b); b += 5;
	report("Volume Descriptor Version", "%d", *b++);

	switch (type) {
	case 0:
		break;
	}

	return 0;
}

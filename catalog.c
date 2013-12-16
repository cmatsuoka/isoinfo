#include <stdio.h>
#include "common.h"


static char *get_platform(int n)
{
	switch (n) {
	case 0x00:
		return "80x86";
	case 0x01:
		return "PowerPC";
	case 0x02:
		return "Mac";
	default:
		return "unknown platform";
	}
}

static char *get_boot(int n)
{
	switch (n) {
	case 0x00:
		return "Not Bootable";
	case 0x88:
		return "Bootable";
	default:
		return "unknown";
	}
}

static char *get_media(int n)
{
	switch (n & 7) {
	case 0:
		return "No Emulation";
	case 1:
		return "1.2 MB diskette";
	case 2:
		return "1.44 MB diskette";
	case 3:
		return "2.88 MB diskette";
	case 4:
		return "Hard Disk (drive 80)";
	default:
		return "invalid";
	}
}

static char *get_selection(int n)
{
	switch (n & 7) {
	case 0:
		return "No selection criteria";
	case 1:
		return "Language and Version Information (IBM)";
	default:
		return "unknown";
	}
}

static void validation_entry(unsigned char *b)
{
	printf("\nValidation entry\n");
	report("  Header ID", "%d", *b); b++;
	report("  Platform ID", "%d (%s)", *b, get_platform(*b)); b++;
	b += 2;			/* reserved */
	report_s("  ID string", "%-24.24s", b); b += 24;
	report("  Checksum word", "%02X %02X", b[0], b[1]); b += 2;
	report("  Key byte", "%02X", *b++);
	report("  Key byte", "%02X", *b++);
}

static void default_entry(unsigned char *b)
{
	printf("\nDefault entry\n");
	report("  Boot Indicator", "%02X (%s)", *b, get_boot(*b)); b++;
	report("  Boot Media Type", "%X (%s)", *b, get_media(*b)); b++;
	report("  Load Segment", "%02X %02X", b[0], b[1]); b += 2;
	report("  System Type", "%02X", *b); b++;
	b++;			/* unused */
	report_16("  Sector Count", b); b += 2;
	report_32("  Load RBA", b); b += 2;
	report("  Selection criteria", "%02X (%s)", *b, get_selection(*b)); b++;
}

int read_catalog(unsigned char *b)
{
	printf("EL TORITO BOOT CATALOG\n");

	if (b[0] != 1 || b[30] != 0x55 || b[31] != 0xaa) {
		printf("Invalid boot catalog\n");
		return -1;
	}

	/* Validation entry */
	validation_entry(b); b += 32;
	default_entry(b); b += 32;

	return 0;
}

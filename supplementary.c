#include "common.h"


int read_supplementary(unsigned char *b)
{
	report("Volume Flags", "%02x", *b++);
	report_s("System Identifier", "-%32.32s", b); b += 32;
	report_s("Volume Identifier", "-%32.32s", b); b += 32;
	b += 8;			/* unused */
	report_32("Volume Space Size", b); b += 8;
	b += 32;		/* Escape Sequences */
	report_16("Volume Set Size", b); b += 4;
	report_16("Volume Sequence Number", b); b += 4;
	report_16("Logical Block Size", b); b += 4;
	report_32("Path Table Size", b); b += 8;
	report_16("Location of Type L", b); b += 4;
	report_16("Location of Optional Type L", b); b += 4;
	report_16("Location of Type M", b); b += 4;
	report_16("Location of Optional Type M", b); b += 4;
	b += 34;		/* Directory record */
	report_s("Volume Set Identifier", "%-128.128s", b); b += 128;
	report_s("Publisher Identifier", "%-128.128s", b); b += 128;
	report_s("Data Preparer", "%-128.128s", b); b += 128;
	report_s("Application Identifier", "%-128.128s", b); b += 128;
	report_s("Copyright File Identifier", "%-37.37s", b); b += 37;
	report_s("Abstract File Identifier", "%-37.37s", b); b += 37;
	report_s("Bibliographic File Identifier", "%-37.37s", b); b += 37;
	report_date("Volume Creation Time", b); b += 17;
	report_date("Volume Modification Time", b); b += 17;
	report_date("Volume Expiration Time", b); b += 17;
	report_date("Volume Effective Time", b); b += 17;
	report("File Structure Version", "%d", *b++);

	return 0;
}

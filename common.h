#ifndef ISOINFO_COMMON_H
#define ISOINFO_COMMON_H

extern unsigned char *buf;

int read_iso(unsigned char *);
int read_descriptor(unsigned char *);
void report(char *, char *, ...);
void report_offset(unsigned char *);

#endif

#ifndef ISOINFO_COMMON_H
#define ISOINFO_COMMON_H

extern unsigned char *buf;

int read_iso(unsigned char *);
int read_volume(unsigned char *);
int read_boot(unsigned char *);
int read_primary(unsigned char *);
int read_supplementary(unsigned char *);
unsigned int read32l(unsigned char *);
unsigned int read16l(unsigned char *);
void report(char *, char *, ...);
void report_s(char *, char *, ...);
void report_32(char *, unsigned char *);
void report_16(char *, unsigned char *);
void report_offset(unsigned char *);

#endif

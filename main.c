#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <getopt.h>
#include <errno.h>
#include "common.h"

extern char *optarg;
extern int optind;

static void usage(char *s)
{
	printf("Usage: %s [options] <input>\n", s);
	printf(
"Options:\n"
"    -h        Display a summary of the command line options\n"
"    -v        Display version information and exit\n");
}

static void get_options(int argc, char **argv)
{
	int o;

#define OPTIONS "ho:t:v"
	while ((o = getopt(argc, argv, OPTIONS)) != -1) {
		switch (o) {
		case 'h':
			usage(argv[0]);
			exit(EXIT_SUCCESS);
		case 'v':
			puts(VERSION);
			exit(EXIT_SUCCESS);
		default:
			exit(EXIT_FAILURE);
		}
	}
}

unsigned char *buf;

int main(int argc, char **argv)
{
	char *name;
	struct stat st;
	int fd;

	/* Parse command-line options */
	get_options(argc, argv);

	/* Check for input file */
	if (argc <= optind) {
		usage(argv[0]);
		goto err;
	}
	name = argv[optind];

	if ((fd = open(name, O_RDONLY)) < 0) {
		perror("open");
		goto err;
	}

	if (fstat(fd, &st) < 0) {
		perror("stat");
		goto err2;
	}


	buf = mmap(NULL, st.st_size, PROT_READ, MAP_SHARED, fd, 0);
	if (buf == MAP_FAILED) {
		perror("mmap");
		goto err2;
	}

	read_iso(buf);

	munmap(buf, st.st_size);
	close(fd);

	exit(EXIT_SUCCESS);

    err2:
	close(fd);
    err:
	exit(EXIT_FAILURE);
}

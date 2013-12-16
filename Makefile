VERSION	= 0.1

CC	= gcc
CFLAGS	= -Wall -g -O2 -DVERSION=\"$(VERSION)\"
LD	= gcc
LDFLAGS	=
LIBS	=
OBJS	= main.o iso.o volume.o util.o boot.o primary.o supplementary.o \
	  catalog.o
BIN	= isoinfo


.c.o:
	$(CC) -c $(CFLAGS) -o $*.o $<

all: $(BIN)

$(BIN): $(OBJS)
	$(LD) -o $@ $(LDFLAGS) $(OBJS) $(LIBS)

clean:
	rm -f *~ $(OBJS) depend $(BIN)

depend:
	@echo Building dependencies...
	@$(CC) $(CFLAGS) -MM $(OBJS:.o=.c) > $@

include depend

# Makefile


# ENVIRONMENT 
CC=/usr/bin/gcc
RM=/bin/rm -f

# COMPILE FLAGS
CFLAGS=-Wall -Wextra -Os
INC=-I.

# LINKER FLAGS
LDFLAGS=
LIBS=-lpthread -lrt

# ARCHIVER FLAGS
ARFLAGS=

# TARGETS
binaries=$(patsubst %.c,%.bin,$(wildcard *.c))
objects=$(patsubst %.c,%.o,$(wildcard *.c))
sources = $(wildcard *.c)


all: $(binaries)


# COMPILE
%.o: %.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

# LINK
%.bin: %.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)



.PHONY: clean

clean:
	$(RM) $(objects) $(FOREIGN_TARGETS) $(binaries) $(hexes)

#.SECONDARY: $(objects)
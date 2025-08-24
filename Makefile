CC=cc
CFLAGS=-Wall -Werror

.PHONY: all
all: pubip

pubip: pubip.c
	$(CC) $(CFLAGS) -o pubip pubip.c

install: pubip
	install -m 755 pubip /usr/bin


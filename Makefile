SRC = $(wildcard *.c)
OBJ = $(SRC:c=o)
BIN = histogram
PREFIX ?= /usr/local

CFLAGS = -Wall -Wextra -Werror -std=gnu99 -pedantic

all: $(BIN)

histogram: histogram.o

install: $(BIN)
	cp -f $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: clean install uninstall

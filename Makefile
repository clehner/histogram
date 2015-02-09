SRC = $(wildcard *.c)
OBJ = $(SRC:c=o)
BIN = histogram
PREFIX ?= /usr/local

CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

test: histogram.o test.o
	$(CC) $(CFLAGS) -o $@ $^
	./test

all: $(BIN)

histogram: histogram.o main.o

install: $(BIN)
	cp -f $(BIN) $(PREFIX)/bin/$(BIN)

uninstall:
	rm $(PREFIX)/bin/$(BIN)

clean:
	rm -f $(BIN) $(OBJ)

.PHONY: clean install uninstall

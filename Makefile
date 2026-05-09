CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = x86_64-bf-linux
PREFIX ?= /usr/local
BINDIR = $(PREFIX)/bin
LDFLAGS = 
MANDIR = $(PREFIX)/share/man/man1

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)
DEPS = $(wildcard src/*.h)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< $(LDFLAGS)

.PHONY: clean install
clean:
	rm -f $(OBJS) $(TARGET)

install:
	install -d $(DESTDIR)$(BINDIR)
	install -m 755 x86_64-bf-linux $(DESTDIR)$(BINDIR)/bf

	install -d $(DESTDIR)$(MANDIR)
	install -m 644 bf.1 $(DESTDIR)$(MANDIR)/bf.1

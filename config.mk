# Set C compiler here e.g. tcc, cc, clang, etc
CC      := tcc
CCFLAGS := -g -Wall -pedantic -std=c99

# Set installation paths
PREFIX    ?= $(DESTDIR)/usr/local
BINPREFIX ?= $(PREFIX)/bin
MANPREFIX ?= $(PREFIX)/share/man

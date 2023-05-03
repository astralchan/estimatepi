.POSIX:

include config.mk

all: estimatepi

estimatepi: estimatepi.o
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -lncurses -o $@ estimatepi.o
estimatepi.o: estimatepi.c

clean:
	@rm -f estimatepi estimatepi.o

install:
	@mkdir -p $(DESTDIR)$(PREFIX)/bin
	@cp estimatepi $(DESTDIR)$(PREFIX)
	@chmod 755 $(DESTDIR)$(PREFIX)/bin/estimatepi
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	@cp estimatepi.1 $(DESTDIR)$(PREFIX)/share/man/man1
	@chmod 644 $(DESTDIR)$(PREFIX)/share/man/man1/estimatepi.1 
uninstall:
	@rm -f $(DESTDIR)$(PREFIX)/bin/estimatepi
	@rm -f $(DESTDIR)$(PREFIX)/share/man/man1/estimatepi.1

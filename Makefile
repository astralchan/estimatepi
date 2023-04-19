.POSIX:

all: estimatepi

estimatepi: estimatepi.o
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -lncurses -o $@ estimatepi.o
estimatepi.o: estimatepi.c

clean:
	@rm -f estimatepi estimatepi.o

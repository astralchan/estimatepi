#define _POSIX_C_SOURCE 200809L

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include <math.h>

static double random_number(double lowerBound, double upperBound);
static double distance(double x, double y);

static double
random_number(double lowerBound, double upperBound)
{
	return (upperBound-lowerBound) * rand()/(double)RAND_MAX + lowerBound;
}

/* Specifically, this calculates the distance of (x,y) from (0,0). */
static double
distance(double x, double y)
{
	return sqrt(x*x + y*y);
}

int
main(int argc, char *argv[])
{
	int c;
	int errflg = 0;
	long long interval = 1;
	double radius = 0.5;

	if (argc == 1)
		errflg = 1;

	extern char *optarg;
	extern int optopt, optind;

	while ((c = getopt(argc, argv, "i:r:")) != -1) {
		switch(c) {
		case 'i':
			interval = atoll(optarg);
			break;
		case 'r':
			radius = atof(optarg);
			break;
		case '?':
			fprintf(stderr, "Unrecognized option: -%c\n", optopt);
			errflg = 1;
		}
	}

	if (argc == optind)
		errflg = 1;

	if (errflg == 1) {
		fprintf(stderr, "usage: %s [-i <int>] [-R double] <int>\n", argv[optind-1]);
		return EXIT_FAILURE;
	}

	/* Initialize ncurses */
	initscr();

	/* Random seed from clock */
	srand(time(NULL));

	double coord[2];
	long long pointsInside = 0;
	long long iterations = atoll(argv[optind]);

	for (long long i = 1; i <= iterations; ++i) {
		coord[0] = random_number(-radius, radius);
		coord[1] = random_number(-radius, radius);
		if (distance(coord[0], coord[1]) <= radius)
			++pointsInside;

		if (i%interval == 0) {
			mvprintw(0, 0, "pi(%lld): %.32f", i,
			    4*pointsInside/(double)i);
			refresh();
			sleep(1);
		}
	}

	endwin();

	printf("pi(%lld): %.32f\n", iterations,
	    4*pointsInside/(double)iterations);

	return EXIT_SUCCESS;
}

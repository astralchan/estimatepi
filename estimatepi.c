#define _POSIX_C_SOURCE 200809L

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

static inline double random_number(double lowerBound, double upperBound);
static inline double square_distance(double x, double y);

static inline double
random_number(double lowerBound, double upperBound)
{
	return (upperBound-lowerBound) * rand()/(double)RAND_MAX + lowerBound;
}

/* Specifically, this calculates the square distance of (x,y) from (0,0). */
static inline double
square_distance(double x, double y)
{
	return x*x + y*y;
}

int
main(int argc, char *argv[])
{
	int c;
	int errflg = 0;
	long long interval = 1;
	double radius = 0.5;
	double speed = 1.0;

	if (argc == 1)
		errflg = 1;

	extern char *optarg;
	extern int optopt, optind;

	while ((c = getopt(argc, argv, "i:r:s:")) != -1) {
		switch(c) {
		case 'i':
			interval = atoll(optarg);
			break;
		case 'r':
			radius = atof(optarg);
			break;
		case 's':
			speed = atof(optarg);
			break;
		case '?':
			fprintf(stderr, "Unrecognized option: -%c\n", optopt);
			errflg = 1;
		}
	}

	if (argc == optind)
		errflg = 1;

	if (errflg == 1) {
		fprintf(stderr, "usage: %s [-i <INTERVAL>] [-r <RADIUS>] "
		"[-s <speed>] <ITERATIONS>\n", argv[optind-1]);
		return EXIT_FAILURE;
	}

	/* Initialize ncurses */
	initscr();

	/* Random seed from clock */
	srand(time(NULL));

	double coord[2];
	long long pointsInside = 0;
	long long iterations = atoll(argv[optind]);

	/* Construct timespec */
	time_t seconds = (time_t)(1 / speed);
	long nanoseconds = (long)((1 / speed - seconds) * 1000000000);

	struct timespec ts = {seconds, nanoseconds};

	for (long long i = 1; i <= iterations; ++i) {
		coord[0] = random_number(-radius, radius);
		coord[1] = random_number(-radius, radius);
		if (square_distance(coord[0], coord[1]) < radius*radius)
			++pointsInside;

		if (i%interval == 0) {
			mvprintw(0, 0, "pi(%lld): %.32f", i,
			    4*pointsInside/(double)i);
			refresh();
			nanosleep(&ts, NULL);
		}
	}

	endwin();

	printf("pi(%lld): %.32f\n", iterations,
	    4*pointsInside/(double)iterations);

	return EXIT_SUCCESS;
}

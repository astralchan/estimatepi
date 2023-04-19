#define _POSIX_C_SOURCE 200809L

#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#include <math.h>

static float random_number(float lowerBound, float upperBound);
static float distance(float x, float y);

static float
random_number(float lowerBound, float upperBound)
{
	return (upperBound-lowerBound) * rand()/(float)RAND_MAX + lowerBound;
}

/* Specifically, this calculates the distance of (x,y) from (0,0). */
static float
distance(float x, float y)
{
	return sqrt(x*x + y*y);
}

int
main(int argc, char *argv[])
{
	int c;
	int errflg = 0;
	int interval = 1;
	float radius = 0.5;

	if (argc == 1)
		errflg = 1;

	extern char *optarg;
	extern int optopt, optind;

	while ((c = getopt(argc, argv, "i:r:")) != -1) {
		switch(c) {
		case 'i':
			interval = atoi(optarg);
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
		fprintf(stderr, "usage: %s [-i <int>] [-R float] <int>\n", argv[optind-1]);
		return EXIT_FAILURE;
	}

	/* Initialize ncurses */
	initscr();

	/* Random seed from clock */
	srand(time(NULL));

	float coord[2];
	int pointsInside = 0;
	int iterations = atoi(argv[optind]);

	for (int i = 1, j = 0; i <= iterations; ++i, ++j) {
		coord[0] = random_number(-radius, radius);
		coord[1] = random_number(-radius, radius);
		if (distance(coord[0], coord[1]) <= radius)
			++pointsInside;

		if (j%interval == 0) {
			mvprintw(0, 0, "pi(%d): %f\n", i,
			    4*pointsInside/(float)i);
			refresh();
			sleep(1);
		}
	}

	endwin();

	printf("pi(%d): %f\n", iterations, 4*pointsInside/(float)iterations);

	return EXIT_SUCCESS;
}

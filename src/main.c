/* summary
 * Uses rand() from math.h to generate random coordinates to be used to
 * assign coordinates in a one by one square with an inscribed circle of the
 * same diameter (and consequently radius of one half). The proportion of the
 * number of points inside the circle to the number of iterations should match
 * the proportion of the area of the circle to the area of the square the more
 * iterations are done, which is pi/4. Thus, to estimate pi, the program takes
 * the proportion of the points and multiplies it by 4.
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"

/* definitions */
#define RADIUS 0.5

/* e.g. random_number(-4.5, 80) will generate a random number between -4.5 and
 * 80. */
float
random_number(float lower_bound, float upper_bound)
{
	return ( upper_bound - lower_bound ) * (float)rand()/(float)(RAND_MAX) + lower_bound;
}

/* Specifically, this calculates the distance of (x,y) from (0,0). */
float
distance(float x, float y)
{
	return sqrt( x*x + y*y );
}

int
main(void)
{
	srand(time(NULL)); /* Sets random seed that is based off of the clock of the system. */

	float coord[2];
	int points_inside = 0; /* Count starts with 0 points inside. */
	for (int index = 1; index <= iterations; index++) {
		coord[0] = random_number(-RADIUS, RADIUS);
		coord[1] = random_number(-RADIUS, RADIUS);
		if (distance(coord[0], coord[1]) <= RADIUS)
			points_inside++;
	}
	float result = 4 * ((float)points_inside / (float)iterations);
	printf("%f\n", result);
	return 0;
}

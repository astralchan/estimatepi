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

/* e.g. random_number(-4.5, 80) will generate a random number between -4.5 and
 * 80. */
float
random_number(float lower_bound, float upper_bound)
{
	float random_number = ( upper_bound - lower_bound ) *
		(float)rand()/(float)(RAND_MAX) + lower_bound;
	return random_number;
}

/* Specifically, this calculates the distance of (x,y) from (0,0). */
float
distance(float x, float y)
{
	float distance = sqrt( x*x + y*y );
	return distance;
}

int
main(void)
{
	srand(time(NULL)); /* Sets random seed that is based off of the clock of the
			    * system. */

	float coord[2];
	int points_inside = 0; /* Count starts with 0 points inside. */
	for (int index = 1; index <= iterations; index++) {
		coord[0] = random_number(-0.5,0.5);
		coord[1] = random_number(-0.5,0.5);
		if (distance(coord[0], coord[1]) <= 0.5)
			points_inside++;
	}
	float result = 4 * ((float)points_inside / (float)iterations);
	printf("%f\n", result);

	return 0;
}

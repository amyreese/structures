#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

/**
 * Test populating, searching, and removing integers from a Vector.
 *
 * @param Argument count
 * @param Argument list
 * @return Error level
 */
int main(int argc, char* argv[])
{
	Vector<int> v;

	printf("Vector created: length %d, space %d\n", v.length(), v.space());

	for (int i = 0; i < 300; i++)
	{
		v.unshift(i);
	}

	printf("300 elements unshifted: length %d, space %d\n", v.length(), v.space());

	printf("v[60]: %d\n", v[60]);

	v[60] = 4;
	printf("v[60] = 4: %d\n", v[60]);

	for (int i = 0; i < 300; i++)
	{
		v.push(i);
	}

	printf("300 elements pushed: length %d, space %d\n", v.length(), v.space());

	try {
		v[601] = 1;
	}
	catch (int e)
	{
		printf("v[601] = 1: exception caught\n");
	}

	return 0;
}


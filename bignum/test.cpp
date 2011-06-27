#include <stdio.h>
#include <stdlib.h>

#include "bignum.h"

/**
 * Test populating, searching, and removing integers from a Vector.
 *
 * @param Argument count
 * @param Argument list
 * @return Error level
 */
int main(int argc, char* argv[])
{
	char buffer[1000];
	Bignum n(0);

	n.str(buffer, 1000);
	printf("%u: %s\n", n.length(), buffer);

	n.add(10);
	n.str(buffer, 1000);
	printf("n.add(10): %u, %s\n", n.length(), buffer);

	n.add(1000);
	n.str(buffer, 1000);
	printf("n.add(1000): %u, %s\n", n.length(), buffer);

	n = Bignum(9999);
	n.str(buffer, 1000);
	printf("n = Bignum(9999): %u, %s\n", n.length(), buffer);

	n.add(1);
	n.str(buffer, 1000);
	printf("n.add(1): %u, %s\n", n.length(), buffer);

	n = n + 1;
	n.str(buffer, 1000);
	printf("n = n + 1: %u, %s\n", n.length(), buffer);

	n += 1;
	n.str(buffer, 1000);
	printf("n += 1: %u, %s\n", n.length(), buffer);

	Bignum m(100);
	n.add(m);
	n.str(buffer, 1000);
	printf("n.add(m=100): %u, %s\n", n.length(), buffer);

	n = n + m;
	n.str(buffer, 1000);
	printf("n = n + m: %u, %s\n", n.length(), buffer);

	n += m;
	n.str(buffer, 1000);
	printf("n += m: %u, %s\n", n.length(), buffer);
}


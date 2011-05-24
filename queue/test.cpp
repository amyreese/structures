#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

/**
 * Test populating, searching, and removing integers from a Queue.
 *
 * @param Argument count
 * @param Argument list
 * @return Error level
 */
int main(int argc, char* argv[])
{
	int prios = 4;
	Queue<int> q(prios);

	srand(1337);

	for (int i = 0; i < 100; i++)
	{
		unsigned int prio = rand() % prios;
		q.push(i, prio);

		printf("q.push(%d, %d)\n", i, prio);
	}

	while(q.length())
	{
		int value = q.shift();

		printf("q.shift(): %d\n", value);
	}
}


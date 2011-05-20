#include <stdio.h>
#include <stdlib.h>

#include "list.h"

/**
 * Print a List of integers.
 *
 * @param List to print
 */
void print(List<int>& l)
{
	printf("\nprint()... ");

	ListIter<int> i(l);

	if (i == NULL)
	{
		printf("empty");
	}
	else
	{
		printf("%d", *i);
		++i;
	}

	for (; i != NULL; ++i)
	{
		printf(", %d", *i);
	}

	printf("\n\n");
}

/**
 * Test populating, searching, and removing integers from a List.
 *
 * @param Argument count
 * @param Argument list
 * @return Error level
 */
int main(int argc, char* argv[])
{
	List<int> l;
	printf("List created: length: %d\n", l.length());

	print(l);

	// Test append() and insert()
	l.append(1);
	printf("append(1): length: %d\n", l.length());

	l.append(2);
	printf("append(2): length: %d\n", l.length());

	l.insert(3,1);
	printf("insert(3,1): length: %d\n", l.length());

	l.insert(4,0);
	printf("insert(4,0): length: %d\n", l.length());

	l.append(5);
	printf("append(5): length: %d\n", l.length());

	l.insert(6,7);
	printf("insert(6,7): length: %d\n", l.length());

	print(l);

	// Test find()
	int pos = l.find(4);
	printf("find(4): position: %d\n", pos);

	pos = l.find(5);
	printf("find(5): position: %d\n", pos);

	pos = l.find(6);
	printf("find(6): position: %d\n", pos);

	// Test remove()
	int pop = l.remove(1);
	printf("remove(1): popped %d, length: %d\n", pop, l.length());

	print(l);

	pop = l.remove(3);
	printf("remove(3): popped %d, length: %d\n", pop, l.length());

	print(l);

	pos = l.find(5);
	printf("find(5): position: %d\n", pos);

	pos = l.find(6);
	printf("find(6): position: %d\n", pos);

	return 0;
}


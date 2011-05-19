#include <stdio.h>
#include <stdlib.h>

#include "list.h"

int main(int argc, char* argv[])
{
	printf("Creating list...\n");

	List<void*> l;
	printf("Length: %d\n", l.length());

	return 0;
}


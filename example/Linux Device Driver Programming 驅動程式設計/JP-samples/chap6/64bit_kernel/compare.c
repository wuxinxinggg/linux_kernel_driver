// cc compare.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	unsigned int n = 100;
	long l = -1;

	printf("sizeof(long) %d\n", sizeof(long));

	if (n > l)
		printf("%u > %ld\n", n, l);
	else
		printf("%u <= %ld\n", n, l);

	return 0;
}


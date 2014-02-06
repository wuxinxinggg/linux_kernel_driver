// cc printf.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	long ln = (2L << 31);
	long n = (2 << 31);
	void *ptr = &n;

	printf("ln=%ld n=%ld\n", ln, n);
	printf("%%p=%p\n", ptr);
	printf("%%x=%x\n", ptr);
	printf("%%lx=%lx\n", ptr);

	return 0;
}


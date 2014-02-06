// cc intlimit.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	printf("%lx\n", 1 << 31);
	printf("%lx\n", 1 << 32);
	printf("%lx\n", 1 << 33);

	printf("%lx\n", 1L << 31);
	printf("%lx\n", 1L << 32);
	printf("%lx\n", 1L << 33);

	return 0;
}


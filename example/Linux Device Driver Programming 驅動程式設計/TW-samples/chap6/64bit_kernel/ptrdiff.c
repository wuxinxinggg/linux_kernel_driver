// cc ptrdiff.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int m, n;
	int *pm = &m;
	int *pn = &n;
	unsigned int diff;
	unsigned long ldiff;

	diff = pn - pm;
	printf("%lx = %p - %p\n", diff, pn, pm);
	ldiff = pn - pm;
	printf("%lx = %p - %p\n", ldiff, pn, pm);

	return 0;
}


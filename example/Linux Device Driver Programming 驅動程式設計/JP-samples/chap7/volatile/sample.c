#include <stdio.h>

int main(void)
{
	int val, n;
	int *p;

	val = 2008;
	p = &val;

	n = *p;

	printf("%d\n", val);

	return 0;
}


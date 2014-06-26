// cc minusone.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char buf[30];
	char *p;
	int i;
	unsigned int index = 0;
//	unsigned long index = 0;
	
	printf("index-1 = %lx (sizeof %d)\n", index-1, sizeof(index-1));

	for (i = 'A'; i <= 'Z' ; i++) {
		buf[i - 'A'] = i;
	}
	p = &buf[1];

	printf("%c: buf=%p p=%p p[-1]=%p\n", p[index-1], buf, p, &p[index-1]);

	return 0;
}


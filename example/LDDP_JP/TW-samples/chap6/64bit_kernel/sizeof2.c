// cc sizeof2.c && ./a.out
#include <stdio.h>
#include <stdlib.h>

void sub(void *buf)
{
	int n = 0xdeadbeef;

	memcpy(buf, &n, sizeof(buf));
}

int main(void)
{
	unsigned char buf[8];
	int i;

	memset(buf, 0xff, sizeof(buf));

	sub(buf);

	for (i = 0 ; i < sizeof(buf) ; i++) {
		printf("%02x\n", buf[i]);
	}

	return 0;
}


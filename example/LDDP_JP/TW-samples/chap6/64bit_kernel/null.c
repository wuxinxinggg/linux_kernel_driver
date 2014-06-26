// cc null.c && ./a.out
#include <stdio.h>
#include <stdarg.h>

void sub(char *fmt, ...)
{
	va_list args;
	char *p;
	int i = 0;

	va_start(args, fmt);
	printf("[%d] %s\n", i++, fmt);

	while ( (p = va_arg(args, char *)) ) {
		printf("[%d] %s\n", i, p);
		i++;
	}

	va_end(args);
}

int main(void)
{
	printf("NULL=%d \\0=%d 0=%d 0L=%d\n", 
			sizeof(NULL), sizeof('\0'), sizeof(0), sizeof(0L));

	sub("hello", "world", "hohoho", 0);

	return 0;
}


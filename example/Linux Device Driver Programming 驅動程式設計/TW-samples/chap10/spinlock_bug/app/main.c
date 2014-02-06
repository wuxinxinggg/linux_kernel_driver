/*
 * # cc main.c && ./a.out
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define DEVFILE "/dev/devone0"

int main(void)
{
	int fd;
	int i;
	ssize_t size;
	char buf[32];

	fd = open(DEVFILE, O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	for ( ;; ) {
		size = read(fd, buf, sizeof(buf));
		for (i = 0 ; i < size ; i++) {
			printf("%02x ", buf[i] & 0xff);
		}
		printf("\n");

		sleep(3);
	}

	close(fd);

	return 0;
}


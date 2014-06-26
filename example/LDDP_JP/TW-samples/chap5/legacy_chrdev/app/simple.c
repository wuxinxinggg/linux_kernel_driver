/*
 * # cc simple.c && ./a.out
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define DEVFILE "/dev/devone"

int open_file(void)
{
	int fd;

	fd = open(DEVFILE, O_RDWR);
	if (fd == -1) {
		perror("open");
	}
	return (fd);
}

void close_file(int fd)
{
	if (close(fd) != 0) {
		perror("close");
	}
}

int main(void)
{
	int fd;

	fd = open_file();

	sleep(20);

	close_file(fd);

	return 0;
}


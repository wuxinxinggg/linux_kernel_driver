/*
 * # cc test.c && ./a.out
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

int open_file(char *filename)
{
	int fd;

	fd = open(filename, O_RDWR);
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

void read_file(int fd)
{
	unsigned char buf[8], *p;
	ssize_t ret;

	ret = read(fd, buf, sizeof(buf));
	if (ret > 0) {
		p = buf;
		while (ret--)
			printf("%02x ", *p++);
	} else {
		perror("read");
	}

	printf("\n");
}

void write_file(int fd, unsigned char val)
{
	ssize_t ret;

	ret = write(fd, &val, 1);
	if (ret <= 0) {
		perror("write");
	}
}

int main(void)
{
	int fd;
	int i;

	for (i = 0 ; i < 2 ; i++) {
		printf("No. %d\n", i + 1);

		fd = open_file(DEVFILE);

		read_file(fd);

		write_file(fd, 0x00);
		read_file(fd);

		write_file(fd, 0xC0);
		read_file(fd);

		close_file(fd);
	}

	return 0;
}


/*
 * # cc poll.c && ./a.out
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <poll.h>

#define DEVFILE "/dev/devone0"

int main(void)
{
	int fd;
	struct pollfd fds;
	int retval;
	unsigned char buf[64];
	ssize_t sz;
	int i;

	fd = open(DEVFILE, O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	do {
		fds.fd = fd;
		fds.events = POLLIN;

		printf("poll() ...\n");
		retval = poll(&fds, 1, 5 * 1000);
		if (retval == -1) {
			perror("poll");
			break;
		}

		if (retval) {
			break;
		}
	} while (retval == 0);   /* timeout elapsed */

	if (fds.revents & POLLIN) {
		printf("read() ...\n");
		sz = read(fd, buf, sizeof(buf));
		printf("read() %d\n", sz);
		for (i = 0 ; i < sz ; i++) {
			printf("%02x ", buf[i]);
		}
		printf("\n");
	}

	close(fd);

	return 0;
}


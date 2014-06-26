/*
 * cc -Wall -o app app.c
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "devone_ioctl.h"

#define DEVFILE "/dev/devone0"

void read_buffer(int fd)
{
	unsigned char buf[64];
	int ret;
	int i;

	ret = read(fd, buf, sizeof(buf));
	if (ret == -1) {
		perror("read");
	} 
	for (i = 0 ; i < ret ; i++) {
		printf("%02x ", buf[i]);
	}
	printf("\n");
}

int main(void)
{
	struct ioctl_cmd cmd;
	int ret;
	int fd;

	fd = open(DEVFILE, O_RDWR);
	if (fd == -1) {
		perror("open");
		exit(1);
	}

	memset(&cmd, 0, sizeof(cmd));
	ret = ioctl(fd, IOCTL_VALGET, &cmd);
	if (ret == -1) {
		printf("errno %d\n", errno);
		perror("ioctl");
	}
	printf("val %d\n", cmd.val);

	// read buffer
	read_buffer(fd);

	memset(&cmd, 0, sizeof(cmd));
	cmd.val = 0xCC;
	ret = ioctl(fd, IOCTL_VALSET, &cmd);
	if (ret == -1) {
		printf("errno %d\n", errno);
		perror("ioctl");
	}

	// read buffer
	read_buffer(fd);

	memset(&cmd, 0, sizeof(cmd));
	ret = ioctl(fd, IOCTL_VALGET, &cmd);
	if (ret == -1) {
		printf("errno %d\n", errno);
		perror("ioctl");
	}
	printf("val %d\n", cmd.val);

	close(fd);

	return 0;
}


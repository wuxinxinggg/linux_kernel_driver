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
#include <signal.h>
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

void sigint_handler(int signum)
{
	//printf("%s called\n", __func__);
}

int main(void)
{
	int fd[2];
	int ret;
	struct sigaction sig;

	memset(&sig, 0, sizeof(sig));
	sig.sa_handler = sigint_handler;
	sig.sa_flags = SA_RESTART;

	if (sigaction(SIGINT, &sig, NULL)) {
		perror("sigaction");
		exit(1);
	}

	fd[0] = open_file();
	fd[1] = open_file();

	pause();
	ret = close(fd[0]);
	printf("close0 (ret %d errno %d)\n", ret, errno);

	pause();
	close(fd[1]);
	printf("close1 (ret %d errno %d)\n", ret, errno);

	return 0;
}


#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define DEVFILE1 "/dev/chrdev_minor1"
#define DEVFILE2 "/dev/chrdev_minor2"



int main(void) {
    int fd, fd2;

    fd = open(DEVFILE1, O_RDWR);

    if (fd == -1) {
        perror("open");
    }

    fd2 = open(DEVFILE2, O_RDWR);

    if (fd2 == -1) {
        perror("open");
    }

    sleep(5);

    if (close(fd) != 0) {
        perror("close");
    }

    if (close(fd2) != 0) {
        perror("close");
    }


    return 0;
}

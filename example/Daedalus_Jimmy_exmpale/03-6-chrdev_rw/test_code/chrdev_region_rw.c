#include <stdio.h>
#include <errno.h>
#include <fcntl.h>

#define DEVFILE "/dev/chrdev_rw"



int main(void) {
    int fd;
    unsigned char buf;
    ssize_t ret;

    fd = open(DEVFILE, O_RDWR);

    if (fd == -1) {
        perror("open");
    }

    buf = 0xFF;
    ret = write(fd, &buf, 1);

    if (ret <= 0) {
        perror("write");
    }


    read(fd, &buf, 1);
    printf("Read Char:%x\n", buf);

    buf = 0xCC;
    ret = write(fd, &buf, 1);

    if (ret <= 0) {
        perror("write");
    }


    read(fd, &buf, 1);
    printf("Read Char:%x\n", buf);

    if (close(fd) != 0) {
        perror("close");
    }


    return 0;
}


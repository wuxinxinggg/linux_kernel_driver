//application: syscall-user.c
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../syscall-exam.h"

int main(void)
{
        int fd;
        mydev_info_t mydev_info;
        struct mychrdev_window truncate_window;
        char * mmap_ptr = NULL;
        int i;

        fd = open("/dev/mychrdev", O_RDWR);
        if (fd < 0) {
                perror("open:");
                exit(-1);
        }

        ioctl(fd, MYCHRDEV_IOCTL_GET_INFO, &mydev_info);

        printf("User process: %s(%d)\n", mydev_info.user_name, mydev_info.user_pid);
        printf("Available space: %d bytes\n", mydev_info.available_len);
        printf("Data len: %d bytes\n", mydev_info.len);
        printf("Offset in physical: %lx bytes\n", mydev_info.offset_in_ppage);

        mmap_ptr = mmap(NULL, 65536, PROT_READ, MAP_PRIVATE, fd, 0);

        if ((long) mmap_ptr == -1) {
                perror("mmap:");
                close(fd);
                exit(-1);
        }

        printf("mychrdev content by mmap:\n");
        printf("%s\n", mmap_ptr);
        munmap(mmap_ptr, 65536);

        truncate_window.head = 0;
        truncate_window.tail = 5;
        ioctl(fd, MYCHRDEV_IOCTL_SET_TRUNCATE, &truncate_window);
        close(fd);
}

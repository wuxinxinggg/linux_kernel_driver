#include <termios.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
// #include <jni.h>
#include <assert.h>
#include <errno.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <sys/socket.h>
//#include <utils/Log.h>
#include <stdlib.h>

static int epoll_register(int  epoll_fd, int  fd) {
    struct epoll_event  ev;
    int  ret, flags;

    /* important: make the fd non-blocking */
    flags = fcntl(fd, F_GETFL);
    fcntl(fd, F_SETFL, flags | O_NONBLOCK);
    //fcntl(fd, F_SETOWN, getpid()); //sclu add
    ev.events  = EPOLLIN;
    ev.data.fd = fd;

    do {
        ret = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
    } while (ret < 0 && errno == EINTR);

    return ret;
}

int main(int argc, char** argv) {
    struct termios uart_termios;
    int baudrate = atoi(argv[2]);
    int  epoll_fd = epoll_create(1);
    int ret, err;
    char read_buf[1024];

    int fd = open(argv[1], O_RDWR | O_NOCTTY | O_NDELAY);

    if (fd < 0) {
        LOGE("open %s failure, err = %s\n", argv[1], strerror(errno));
        return fd;
    }

    fcntl(fd, F_SETFL, 0);
    tcflush(fd, TCIOFLUSH);

    if ((err = tcgetattr(fd, &uart_termios)) != 0) {
        LOGE("tcgetattr %s, err = %s\n", argv[1], strerror(errno));
        close(fd);
        return err;
    }

    uart_termios.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
    uart_termios.c_oflag &= ~OPOST;
    uart_termios.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
    uart_termios.c_cflag &= ~(CSIZE | PARENB);
    uart_termios.c_cflag |= CS8;
    // uart_termios.c_cflag &= ~CRTSCTS;//no flow control
    uart_termios.c_cflag &= ~0x0002;
    tcsetattr(fd, TCSANOW, &uart_termios);
    tcflush(fd, TCIOFLUSH);
    tcsetattr(fd, TCSANOW, &uart_termios);
    tcflush(fd, TCIOFLUSH);

    if (cfsetispeed(&uart_termios, baudrate)) {
        LOGE("cfsetispeed, err = %s\n", strerror(errno));
        close(fd);
        return fd;
    }

    if (cfsetospeed(&uart_termios, baudrate)) {
        LOGE("cfsetospeed err = %s\n", strerror(errno));
        close(fd);
        return fd;
    }

    tcsetattr(fd, TCSANOW, &uart_termios);
    epoll_register(epoll_fd, fd);


    ret = write(fd, "$$$$", 4);
    LOGE("ret = %d", ret);

    if ((ret = read(fd, read_buf, sizeof(read_buf))) > 0) {
        int i;

        for (i = 0; i < ret; i++) {
            LOGE("read:%c", read_buf[i]);
        }

        LOGE("\n");
    }

    for (;;) {
        struct epoll_event   events[1];
        int ne, nevents, ret, size;
        LOGE("poll start");
        nevents = epoll_wait(epoll_fd, events, 1, -1);
        LOGE("poll get data");

        if (nevents < 0) {
            if (errno != EINTR) {
                LOGE("epoll_wait() unexpected error: %s", strerror(errno));
            }

            continue;
        }

        for (ne = 0; ne < nevents; ne++) {
            if ((events[ne].events & (EPOLLERR | EPOLLHUP)) != 0) {
                LOGE("EPOLLERR or EPOLLHUP after epoll_wait() !?\n");
                return -1;
            }

            if ((events[ne].events & EPOLLIN) != 0) {
                int  event_fd = events[ne].data.fd;
                int i;

                if (event_fd == fd) {
                    ret = read(fd, read_buf, sizeof(read_buf));

                    if (ret) {
                        LOGE("data:%s", read_buf);
                        char* p = "this is from userspace!";
                        write(fd, p, strlen(p) + 1);
                    }
                }
            }
        }
    }

    return 0;
}

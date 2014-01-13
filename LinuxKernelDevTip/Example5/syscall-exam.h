//header: syscall-exam.h
#ifndef _SYSCALL_EXAM_H
#define _SYSCALL_EXAM_H

#include <linux/ioctl.h>

#undef TASK_COMM_LEN
#define TASK_COMM_LEN 16

typedef struct mychrdev_info {
        pid_t user_pid;
        char user_name[TASK_COMM_LEN];
        unsigned int available_len;
        unsigned int len;
        unsigned long offset_in_ppage;
} mydev_info_t;

struct mychrdev_window {
        unsigned int head;
        unsigned int tail;
};

#define MYCHRDEV_IOCTL_BASE 'm'
#define MYCHRDEV_IOR(nr, size) _IOR(MYCHRDEV_IOCTL_BASE, nr, size)
#define MYCHRDEV_IOW(nr, size) _IOW(MYCHRDEV_IOCTL_BASE, nr, size)

#define MYCHRDEV_IOCTL_GET_INFO MYCHRDEV_IOR(0x01,mydev_info_t)
#define MYCHRDEV_IOCTL_SET_TRUNCATE MYCHRDEV_IOW(0x02,int)
#endif

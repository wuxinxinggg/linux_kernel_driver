//application receiver: netlink-exam-user-recv.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <string.h>
#include <stdlib.h>
#define MAX_MSGSIZE 1024
#define NETLINK_TEST 21

int main(void)
{
        struct sockaddr_nl saddr, daddr;
        struct nlmsghdr *nlhdr = NULL;
        struct msghdr msg;
        struct iovec iov;
        int sd;
        int ret = 1;

        sd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
		if (sd == -1) {
				printf("cannot create netlink\n");
				exit(-1);
		}
        memset(&saddr, 0, sizeof(saddr));
        memset(&daddr, 0, sizeof(daddr));

        saddr.nl_family = AF_NETLINK;      
        saddr.nl_pid = getpid();
        saddr.nl_groups = 11;
		bind(sd, (struct sockaddr*)&saddr, sizeof(saddr));

        nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));

        while (1) {
                memset(nlhdr, 0, NLMSG_SPACE(MAX_MSGSIZE));

                iov.iov_base = (void *)nlhdr;
                iov.iov_len = NLMSG_SPACE(MAX_MSGSIZE);
                msg.msg_name = (void *)&daddr;
                msg.msg_namelen = sizeof(daddr);
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;

                ret = recvmsg(sd, &msg, 0);
                if (ret == 0) {
                        printf("Exit.\n");
                        exit(0);
                }
                else if (ret == -1) {
                        perror("recvmsg:");
                        exit(1);
                }
                printf("%s", (char *)NLMSG_DATA(nlhdr));
        }
 
        close(sd);
}

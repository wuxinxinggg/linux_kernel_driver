//application sender: netlink-exam-user-send.c
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_MSGSIZE 1024
#define NETLINK_TEST 21

int main(int argc, char * argv[])
{
        FILE * fp;
        struct sockaddr_nl saddr, daddr;
        struct nlmsghdr *nlhdr = NULL;
        struct msghdr msg;
        struct iovec iov;
        int sd;
        char text_line[MAX_MSGSIZE];
        int ret = -1;

        if (argc < 2) {
                printf("Usage: %s atextfilename\n", argv[0]);
                exit(1);
        }

        if ((fp = fopen(argv[1], "r")) == NULL) {
                printf("File %s dosen't exist.\n", argv[1]);
                exit(1);
        }

        sd = socket(AF_NETLINK, SOCK_RAW, NETLINK_TEST);
		if (sd == -1) {
				printf("Cannot create netlink\n");
				exit(1);
		}
        memset(&saddr, 0, sizeof(saddr));
        memset(&daddr, 0, sizeof(daddr));

        saddr.nl_family = AF_NETLINK;      
        saddr.nl_pid = getpid();
        saddr.nl_groups = 11;
        bind(sd, (struct sockaddr*)&saddr, sizeof(saddr));

        daddr.nl_family = AF_NETLINK;
        daddr.nl_pid = 0;
        daddr.nl_groups = 1;

        nlhdr = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_MSGSIZE));

        while (fgets(text_line, MAX_MSGSIZE, fp)) {
                memcpy(NLMSG_DATA(nlhdr), text_line, strlen(text_line));
                memset(&msg, 0 ,sizeof(struct msghdr));

                nlhdr->nlmsg_len = NLMSG_LENGTH(strlen(text_line));
                nlhdr->nlmsg_pid = getpid();  /* self pid */
                nlhdr->nlmsg_flags = 0;

                iov.iov_base = (void *)nlhdr;
                iov.iov_len = nlhdr->nlmsg_len;
                msg.msg_name = (void *)&daddr;
                msg.msg_namelen = sizeof(daddr);
                msg.msg_iov = &iov;
                msg.msg_iovlen = 1;
                ret = sendmsg(sd, &msg, 0);
                if (ret == -1) {
                        perror("sendmsg error:");
                }
        }
 
        close(sd);
}

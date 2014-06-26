#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <linux/if.h>
#include <linux/if_ether.h>
#include <netdb.h>

int main(void)
{
	int sock;
	struct ifreq f;
	int ret;

	sock = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	if (sock == -1) {
		perror("Can't create socket\n");
		exit(1);
	}

	strcpy(f.ifr_name, "eth0");
	ret = ioctl(sock, SIOCDEVPRIVATE, &f);
	if (ret == -1) {
		perror("ioctl error\n");
	}

	close(sock);

	return 0;
}


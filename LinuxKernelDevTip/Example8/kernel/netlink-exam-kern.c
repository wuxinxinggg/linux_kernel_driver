//kernel module: netlink-exam-kern.c
#include <linux/module.h>
#include <linux/netlink.h>
#include <linux/sched.h>
#include <net/sock.h>
#include <linux/proc_fs.h>
#include <linux/version.h>

#define BUF_SIZE 16384
static struct sock *netlink_exam_sock;
static unsigned char buffer[BUF_SIZE];
static unsigned int buffer_tail = 0;

#define NETLINK_TEST 21
#if LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 35)
#define sk_sleep(sk) sk->sk_sleep
#endif

#define RCV_SKB_FAIL(err) do { netlink_ack(skb, nlh, (err)); return; } while (0)

static void recv_handler(struct sk_buff *skb)
{
		struct nlmsghdr *nlhdr = (struct nlmsghdr *)skb->data;
		size_t len = 0;
		if (nlhdr->nlmsg_len < sizeof(struct nlmsghdr)) {
			printk("Corrupt netlink message.\n");
		}
		len = nlhdr->nlmsg_len - NLMSG_LENGTH(0);
		if (len + buffer_tail > BUF_SIZE) {
			printk("netlink buffer is full.\n");
		}
		else {
			memcpy(buffer + buffer_tail, NLMSG_DATA(nlhdr), len);
			buffer_tail += len;
		}

}

static int netlink_exam_readproc(char *page, char **start, off_t off,
                          int count, int *eof, void *data)
{
        int len;

        if (off >= buffer_tail) {
                * eof = 1;
                return 0;
        }
        else {
                len = count;
                if (count > PAGE_SIZE) {
                        len = PAGE_SIZE;
                }
                if (len > buffer_tail - off) {
                        len = buffer_tail - off;
                }
                memcpy(page, buffer + off, len);
                *start = page;
                return len;
        }

}

static int __init netlink_exam_init(void)
{
        netlink_exam_sock = netlink_kernel_create(&init_net, NETLINK_TEST, 0, recv_handler, NULL, THIS_MODULE);
        if (!netlink_exam_sock) {
                printk("Fail to create netlink socket.\n");
                return -1;
        }
        create_proc_read_entry("netlink_exam_buffer", 0444, NULL, netlink_exam_readproc, 0);
        return 0;
}

static void __exit netlink_exam_exit(void)
{
        wake_up(sk_sleep(netlink_exam_sock));
        sock_release(netlink_exam_sock->sk_socket);
		remove_proc_entry("netlink_exam_buffer", NULL);
}

module_init(netlink_exam_init);
module_exit(netlink_exam_exit);
MODULE_LICENSE("GPL");

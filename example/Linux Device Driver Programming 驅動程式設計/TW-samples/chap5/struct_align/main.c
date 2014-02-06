/*
 * main.c
 *
 * Update: 2007/12/28 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/unaligned.h>

MODULE_LICENSE("Dual BSD/GPL");

#pragma pack(1)
struct data {
	char num;
    int size;
    void *ptr;
};
#pragma pack()

static int sample_init(void)
{
	struct data s;
	void *p, *ptr;
	unsigned long val;

	printk(KERN_ALERT "sample driver installed.\n");

	printk("sizeof %d\n"
		   "  num %d\n"
		   "  size %d\n"
		   "  ptr %d\n",
		   sizeof(struct data),
		   offsetof(struct data, num),
		   offsetof(struct data, size),
		   offsetof(struct data, ptr));

	memset(&s, 'C', sizeof(s));

	p = &s.ptr;
	printk("%p %p\n", &s.ptr, p);

	ptr = get_unaligned(&s.ptr);
	printk("%p\n", ptr);

	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


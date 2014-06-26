/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

void *memptr;

static int sample_init(void)
{
	void *ptr;

	printk("sample driver installed.\n");

	memptr = ptr = kmalloc(2, GFP_KERNEL);
	printk("ptr %p\n", ptr);

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	kfree(memptr);
	kfree(memptr);   /* double free! */
}

module_init(sample_init);
module_exit(sample_exit);


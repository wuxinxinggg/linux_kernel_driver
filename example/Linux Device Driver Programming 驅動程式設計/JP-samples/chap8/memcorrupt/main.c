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
	char *ptr;
	int i;

	printk("sample driver installed.\n");

	memptr = ptr = kmalloc(32, GFP_KERNEL);
	printk("ptr %p\n", ptr);

	for (i = 0 ; i < 64 ; i++) {
		ptr[i] = i;
	}

	printk("Memory area corrupted!\n");

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	kfree(memptr);
}

module_init(sample_init);
module_exit(sample_exit);


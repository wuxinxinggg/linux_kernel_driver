/*
 * main.c
 *
 * Update: 2007/12/28 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	void *ptr, *palign;
	int order = 1;

	printk(KERN_ALERT "sample driver installed.\n");

	/* allocate two pages */
	ptr = (void *)__get_free_pages(GFP_KERNEL, order);
	printk("__get_free_pages %p\n", ptr);

	palign = (void *)( ((unsigned long)ptr + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1) );
	printk("aligned pointer %p\n", palign);

	free_pages((unsigned long)ptr, order);

	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

void *ptr;
int order = 3;

void *ptr2;
int order2;

static int sample_init(void)
{
	printk("sample driver installed.\n");

	ptr = (void *)__get_free_pages(GFP_KERNEL, order);
	if (ptr) {
		printk("2^%d * %ld bytes allocated\n", order, PAGE_SIZE);
	}

	order2 = get_order(8000);
	ptr2 = (void *)__get_free_pages(GFP_KERNEL, order2);
	if (ptr2) {
		printk("2^%d * %ld bytes allocated\n", order2, PAGE_SIZE);
	}

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	if (ptr)
		free_pages((unsigned long)ptr, order);

	if (ptr2)
		free_pages((unsigned long)ptr2, order2);
}

module_init(sample_init);
module_exit(sample_exit);


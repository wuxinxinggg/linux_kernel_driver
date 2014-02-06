/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	int i;

	printk("sample driver installed\n");

	for (i = 0 ; i < 300 ; i++) {
		if (printk_ratelimit()) 
			printk("I2C access error\n");
	}

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed\n");
}

module_init(sample_init);
module_exit(sample_exit);


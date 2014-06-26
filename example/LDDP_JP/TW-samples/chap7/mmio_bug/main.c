/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	char *reg = (char *)0xFEC00000;

	printk("sample driver installed.\n");

	printk("%x\n", *reg);

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


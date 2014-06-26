/*
 * sub.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

void sample_sub(void)
{
	printk("%s called\n", __func__);

#ifdef DEBUG
	printk("DEBUG macro enabled\n");
#endif
}


#include <linux/module.h>
#include <linux/init.h>

void sub(void)
{
	printk("%s: sub() called\n", __func__);
}


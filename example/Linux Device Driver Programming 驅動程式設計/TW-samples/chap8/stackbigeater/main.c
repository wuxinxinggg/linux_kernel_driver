/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

void sub(int n)
{
	char buf[8192];
	
	printk("%s: n=%d\n", __func__, n);

	if (n >= 10) {
		return;
	}

	memset(buf, 0, sizeof(buf));
	
	//sub(n + 1);
}

static int sample_init(void)
{
	printk("sample driver installed.\n");

	sub(0);

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


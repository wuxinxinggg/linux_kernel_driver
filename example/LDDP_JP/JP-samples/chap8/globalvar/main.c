/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

int g_sample_counter __attribute__ ((unused));
const int g_sample_counter2 __attribute__ ((unused));
static int g_sample_counter3 __attribute__ ((unused));
int g_sample_counter4 __attribute__ ((unused));
EXPORT_SYMBOL(g_sample_counter4);

static int sample_init(void)
{
	printk("sample driver installed.\n");

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


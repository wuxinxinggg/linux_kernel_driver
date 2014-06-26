#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	unsigned long ret;

	printk("driver loaded: %lu\n", jiffies);

	ret = msleep_interruptible(10 * 1000);   /* sleep for 10 seconds. */

	printk("%lu (HZ %d): %s\n", jiffies, HZ, ret ? "Interrupted" : "Timeout");
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


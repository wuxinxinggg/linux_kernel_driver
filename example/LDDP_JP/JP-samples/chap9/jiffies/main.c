#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	printk("driver loaded: %lu\n", jiffies);
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


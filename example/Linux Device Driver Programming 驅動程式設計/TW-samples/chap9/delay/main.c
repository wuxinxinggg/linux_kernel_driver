#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	printk("driver loaded: %lu\n", jiffies);

	mdelay(100);  /* 100 msec */
	udelay(1000); /* 1000 micro second(0.001 msec) */
	ndelay(1000); /* 1000 nano second(0.001 micro second) */

	printk("%lu (HZ %d)\n", jiffies, HZ);
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


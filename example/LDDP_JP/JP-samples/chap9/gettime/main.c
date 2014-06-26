#include <linux/module.h>
#include <linux/init.h>
#include <linux/time.h> 
#include <linux/delay.h> 

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
	struct timeval now;
	suseconds_t diff;
	volatile int i;

	printk(KERN_ALERT "driver loaded: %s\n", __func__);

	do_gettimeofday(&now);
	diff = now.tv_usec;     /* microseconds */

#if 0
	printk("Current UTC: %lu (%lu)\n", now.tv_sec, now.tv_usec);
	for (i = 0 ; i < 9999 ; i++)
		;
#else
	udelay(100);

#endif

	do_gettimeofday(&now);
	diff = now.tv_usec - diff; 

	printk("Elapsed time: %lu\n", diff);
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


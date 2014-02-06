#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static wait_queue_head_t wait;

static int sample_init(void)
{
	printk("driver loaded\n");

	init_waitqueue_head(&wait);
	sleep_on(&wait);
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


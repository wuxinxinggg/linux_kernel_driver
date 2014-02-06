#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

extern wait_queue_head_t yutaka_sample_wait;

static int sample_init(void)
{
	wait_queue_head_t *wq = &yutaka_sample_wait;

	printk("driver loaded\n");

	wake_up(wq);
		
	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


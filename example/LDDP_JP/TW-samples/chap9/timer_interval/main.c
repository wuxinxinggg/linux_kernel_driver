#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

#define TIMEOUT_VALUE (10*HZ)

static struct timer_list tickfn;

static void sample_timeout(unsigned long arg)
{
	struct timer_list *tick = (struct timer_list *)arg;
	int ret;

	ret = mod_timer(tick, jiffies + TIMEOUT_VALUE);
	printk("mod_timer:%d (%lu, %s)\n", ret, jiffies, __func__);
}

static int sample_init(void)
{
	printk("driver loaded: %p\n", &tickfn);

	init_timer(&tickfn);
	tickfn.function = sample_timeout;
	tickfn.data = (unsigned long)&tickfn;
	tickfn.expires = jiffies + TIMEOUT_VALUE;
	add_timer(&tickfn);
		
	return 0;
}

static void sample_exit(void)
{
	int ret;

	ret = del_timer_sync(&tickfn);

	printk(KERN_ALERT "driver unloaded (%d)\n", ret);
}

module_init(sample_init);
module_exit(sample_exit);


/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kthread.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct task_struct *kmain_task = NULL;
static wait_queue_head_t wait;

static int sample_thread(void *num)
{
	printk("%s called\n", __func__);

	for (;;) {
		sleep_on_timeout(&wait, 3 * HZ);

		if (kthread_should_stop())
			break;
	}

	printk("%s leaved\n", __func__);

	return 0;
}

static int sample_init(void)
{
	printk("sample driver installed.\n");

	init_waitqueue_head(&wait);

	kmain_task = kthread_create(sample_thread, NULL, "sample_kthread");
	if (IS_ERR(kmain_task)) {
		return PTR_ERR(kmain_task);
	}
	wake_up_process(kmain_task);

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	kthread_stop(kmain_task);
}

module_init(sample_init);
module_exit(sample_exit);


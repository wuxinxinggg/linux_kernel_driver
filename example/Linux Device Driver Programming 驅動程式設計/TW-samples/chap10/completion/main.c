/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/completion.h>

MODULE_LICENSE("Dual BSD/GPL");

static wait_queue_head_t wait;
static struct completion comp;
static pid_t thr_pid;

static int sample_thread(void *num)
{
	printk("%s called\n", __func__);

	daemonize("sample_thread");
	allow_signal(SIGTERM);

	for (;;) {
		sleep_on_timeout(&wait, 3 * HZ);

		if (signal_pending(current))
			break;
	}

	printk("%s leaved\n", __func__);

	complete_and_exit(&comp, 0);

	return 0;
}

static int sample_init(void)
{
	printk("sample driver installed.\n");

	init_completion(&comp);
	init_waitqueue_head(&wait);

	thr_pid = kernel_thread(sample_thread, NULL, CLONE_FS | CLONE_FILES);
	if (thr_pid < 0) {
		return -EINVAL;
	}
	printk("kernel_thread %d PID\n", thr_pid);

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	kill_proc(thr_pid, SIGTERM, 1);
	wait_for_completion(&comp);
}

module_init(sample_init);
module_exit(sample_exit);


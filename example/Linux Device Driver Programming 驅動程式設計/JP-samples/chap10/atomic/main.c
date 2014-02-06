/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

atomic_t counter = ATOMIC_INIT(0);

static int sample_init(void)
{
	int n;

	atomic_inc(&counter);
	n = atomic_read(&counter);

	printk("n %d\n", n);

	if (atomic_dec_and_test(&counter)) {
		printk("atomic_dec_and_test() TRUE\n");
	} else {
		printk("atomic_dec_and_test() FALSE\n");
	}

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

const int IRQ_NUM = 17;
void *irq_dev_id = (void *)&IRQ_NUM;

irqreturn_t sample_isr(int irq, void *dev_instance)
{
	if (printk_ratelimit()) {
		printk("%s: irq %d dev_instance %p\n", __func__, irq, dev_instance);
	}

	return IRQ_NONE;
}

static int sample_init(void)
{
	int ret;

	printk("sample driver installed.\n");

	ret = request_irq(IRQ_NUM, sample_isr, IRQF_SHARED, "sample", irq_dev_id);
	if (ret) {
		printk("request_irq() failed (%d)\n", ret);
		return (ret);
	}

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");

	free_irq(IRQ_NUM, irq_dev_id);
}

module_init(sample_init);
module_exit(sample_exit);


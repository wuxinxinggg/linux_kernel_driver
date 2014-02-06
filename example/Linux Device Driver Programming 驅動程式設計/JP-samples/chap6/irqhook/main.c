#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

#define IRQ_NUM 17

static irqreturn_t sample_intr(int irq, void *dev_id)
{
	printk("irq %d dev_id %p (%s)\n", irq, dev_id, __func__);

	return IRQ_NONE;
}

static int sample_init(void)
{
	printk("driver loaded \n");

	if (request_irq(IRQ_NUM, 
				sample_intr, 
				IRQF_SHARED, 
				"sample_intr", 
				(void *)sample_intr)) {

	}
		
	return 0;
}

static void sample_exit(void)
{
	free_irq(IRQ_NUM, (void *)sample_intr);

	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


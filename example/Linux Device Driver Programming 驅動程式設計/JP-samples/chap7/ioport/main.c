/*
 * main.c
 *
 * Update: 2008/1/24 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>
#include <asm/io.h>

MODULE_LICENSE("Dual BSD/GPL");

int timeout = 3;
module_param(timeout, int, 0);

struct timer_list timer;

void SetCmd(int value)
{
	unsigned long flag;
	unsigned b;

	local_irq_save(flag);

	do {
		b = inb(0x64);
	} while (b & 0x2);

	outb(value, 0x64);

	local_irq_restore(flag);
}

void SendCmd(int value)
{
	unsigned long flag;
	unsigned b;

	SetCmd(0xAD);

	local_irq_save(flag);

	do {
		b = inb(0x64);
	} while (b & 0x2);

	outb(value, 0x60);

	SetCmd(0xAE);

	local_irq_restore(flag);
}

void sample_timeout(unsigned long arg)
{
	static int toggle = 0;

	printk("%s called\n", __func__);

	SendCmd(0xED);
	if (toggle == 0) {
		SendCmd(0x00);
	} else {
		SendCmd(0x02);
	}
	toggle ^= 1;

	mod_timer(&timer, jiffies + timeout*HZ);
}

static int sample_init(void)
{
	printk("sample driver installed.\n");

	init_timer(&timer);
	timer.function = sample_timeout;
	timer.expires = jiffies + timeout*HZ;
	add_timer(&timer);

	return 0;
}

static void sample_exit(void)
{
	del_timer_sync(&timer);

	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


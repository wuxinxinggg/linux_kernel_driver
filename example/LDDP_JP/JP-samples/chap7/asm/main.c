/*
 * main.c
 *
 * Update: 2008/2/4 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

void do_asm2(void)
{
	u32 cx, dx;
	u32 flag, flag2;

	asm("int $0x1a\n\t"
			"pushfl\n\t"
			"popl %0\n\t"
			"pushfl\n\t"
			"popl %3\n\t"
			: "=r"(flag), "=c" (cx), "=d" (dx), "=r"(flag2)
			: "a" (0x0200)
	   );

	printk("cx %x dx %x flag %x flag2 %x\n", cx, dx, flag, flag2);
}

void do_asm(void)
{
	u16 cx = 0, dx = 0;
	u16 ax = 0x0200;

	asm("int $0x1a"
			: "+a" (ax), "=c" (cx), "=d" (dx)
			: : "ebx", "esi", "edi");

	printk("ax %x cx %x dx %x\n", ax, cx, dx);
}

static int sample_init(void)
{

	printk("sample driver installed.\n");

	do_asm();
	do_asm2();

	return 0;
}

static void sample_exit(void)
{
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


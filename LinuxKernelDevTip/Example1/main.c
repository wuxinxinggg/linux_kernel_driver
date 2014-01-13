#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");

static int __init init_modules(void)
{
	printk("hello world\n");
	return 0;
}

static void __exit exit_modules(void)
{
	printk("goodbye\n");
}

module_init(init_modules);
module_exit(exit_modules);

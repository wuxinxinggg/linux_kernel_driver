#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("HungMing Wu");

MODULE_DESCRIPTION("Enhancement hello world example");
static int debug_enable = 0;	// Addeddefault parameter
module_param(debug_enable, int, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug_enable, "Enable module debug mode.");

static char *dispstr = "world";
module_param(dispstr, charp, S_IRUGO);
MODULE_PARM_DESC(dispstr, "Display string for output");

static int invisible_var = 0;
module_param(invisible_var, int, 0);
MODULE_PARM_DESC(invisible_var, "Can modify via insert module time.");

// Note:
// The meaning of the third paramter of module_param
// 0 -- SysFS cannot see the variable
// S_IRUGO 8sed for a parameter that can be readd but cannot be changed.
// S_IRUGO | S_IWUSR allows root to change the parameter

static int __init init_modules(void)
{
	if (debug_enable) printk("hello %s\n", dispstr);
	return 0;
}

static void __exit exit_modules(void)
{
	if (debug_enable) {
		printk("invisible_var = %d\n", invisible_var);
		printk("goodbye\n");
	}
}

module_init(init_modules);
module_exit(exit_modules);

#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello module");
MODULE_VERSION("1.0");

static int hello_init(void) {
    printk(KERN_ALERT"Hello, world\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

module_init(hello_init);
module_exit(hello_exit);

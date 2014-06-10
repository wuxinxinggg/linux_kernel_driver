#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello file2 module");
MODULE_VERSION("rc1");

static int hello_file2_init(void) {

    printk(KERN_ALERT "Hello, world\n");
    return 0;
}
static void hello_file2_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

void hello_file2_fun(void) {
    printk(KERN_ALERT"This is hello_file2_fun\n");
}
EXPORT_SYMBOL(hello_file2_fun);


module_init(hello_file2_init);
module_exit(hello_file2_exit);

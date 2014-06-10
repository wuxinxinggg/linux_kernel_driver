#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello file1 module");
MODULE_VERSION("rc1");

extern void hello_file2_fun(void);

static int hello_file1_init(void) {

    printk(KERN_ALERT "Hello, world\n");
    /*Call hello_file2_fun*/
    hello_file2_fun();
    return 0;
}
static void hello_file1_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

module_init(hello_file1_init);
module_exit(hello_file1_exit);

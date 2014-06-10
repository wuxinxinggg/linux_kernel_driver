#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h> /*For access task_struct */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello module");
MODULE_VERSION("rc1");

extern void fuck();

static int hello_multfile_init(void) {

    printk(KERN_ALERT "Hello, world\n");
    /*Call fun2 */
    fuck();
    return 0;
}
static void hello_multfile_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

module_init(hello_multfile_init);
module_exit(hello_multfile_exit);


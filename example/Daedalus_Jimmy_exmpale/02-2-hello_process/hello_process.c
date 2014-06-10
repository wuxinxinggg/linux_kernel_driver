#include <linux/init.h>
#include <linux/module.h>
#include <linux/sched.h> /*For access task_struct */

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello_process module");
MODULE_VERSION("rc1");

static int hello_process_init(void) {

    printk(KERN_ALERT "Hello, world\n");
    printk(KERN_ALERT "The Process is %s (PID %i)\n", current->comm, current->pid);
    return 0;
}
static void hello_process_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

module_init(hello_process_init);
module_exit(hello_process_exit);

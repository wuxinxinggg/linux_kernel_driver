/*  This is a simple example of modules.
*
* Compile:
*   Save this file name it helloworld.c
*   # echo "obj-m := helloworld.o" > Makefile
*   # make -Wall -C /lib/modules/`uname -r`/build M=`pwd` modules
* Load the module:
*   #insmod helloworld.ko
*/

#include <linux/init.h>
#include <linux/module.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void) {
    printk(KERN_ALERT "Hello, World\n");
    return 0;
}

static void hello_exit(void) {
    printk(KERN_ALERT "Goodbye ,cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);

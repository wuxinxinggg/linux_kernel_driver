#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is hello parameter module");
MODULE_VERSION("rc1");

static char* name = "Jimmy";
static int count = 1;
static int intArray [] = { 1, 2, 3, 4 };
static int numOftextArrayParam = 4;

module_param(count , int , S_IRUGO) ;
module_param(name , charp , S_IRUGO) ;
module_param_array(intArray , int , &numOftextArrayParam , S_IRUGO) ;

static int __init hellop_init(void) {
    int i;

    for (i = 0; i < count ; i++) {
        printk(KERN_ALERT "(%d) Hello, %s !\n", i, name);
    }

    for (i = 0; i < numOftextArrayParam; i++) {
        printk(KERN_ALERT "intArray[%d] : %d \n" , i , intArray[i]) ;
    }

    return 0;
}

static void __exit hellop_exit(void) {
    printk(KERN_ALERT"Goodbye, Hello world\n");
}

module_init(hellop_init) ;
module_exit(hellop_exit) ;

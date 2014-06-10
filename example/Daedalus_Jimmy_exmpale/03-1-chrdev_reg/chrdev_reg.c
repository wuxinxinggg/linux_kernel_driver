#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is register_chrdev  module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_reg"
static unsigned int chrdev_reg_major = 0;


static int chrdev_reg_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_reg_open\n");
    return 0;
}

static int chrdev_reg_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_reg_close\n");
    return 0;
}

struct file_operations fops = {
    .open = chrdev_reg_open,
    .release = chrdev_reg_close,
};

static int chrdev_reg_init(void) {
    int ret;
    int err = 0;
    /*Static: chrdev_reg_major >0 => ret return 0*/
    /*Dynamic: chrdev_reg_major=0 => ret return >0*/
    ret = register_chrdev(chrdev_reg_major, DRIVER_NAME, &fops);

    if ((chrdev_reg_major == 0 && ret < 0) ||
        (chrdev_reg_major > 0 && ret != 0)) {
        printk("%s Driver registration error\n", DRIVER_NAME);
        err = ret;
        goto error;
    } else {
        chrdev_reg_major = ret;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_reg_major);
error:
    return err;
}

static void chrdev_reg_exit(void) {
    unregister_chrdev(chrdev_reg_major, DRIVER_NAME);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_reg_init) ;
module_exit(chrdev_reg_exit) ;

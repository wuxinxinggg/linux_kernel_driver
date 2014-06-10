#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/device.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is sysfs test  module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_sys"
static unsigned int chrdev_sys_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev  chrdev_sys_cdev;
static struct class* chrdev_sys_class = NULL;

static int chrdev_sys_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_sys_open\n");
    return 0;
}

static int chrdev_sys_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_sys_close\n");
    return 0;
}

struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_sys_open,
    .release = chrdev_sys_close,
};

static int chrdev_sys_init(void) {
    dev_t dev = MKDEV(chrdev_sys_major, 0);
    int alloc_ret = 0;
    int cdev_ret = 0;

    alloc_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);

    if (alloc_ret) {
        goto error;
    }

    chrdev_sys_major = MAJOR(dev);

    cdev_init(&chrdev_sys_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_sys_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    /*Create sys class*/
    chrdev_sys_class = class_create(THIS_MODULE, DRIVER_NAME);

    if (IS_ERR(chrdev_sys_class)) {
        goto error;
    }

    /*Register sysfs*/
    device_create(chrdev_sys_class,
                  NULL,
                  MKDEV(chrdev_sys_major, 0),
                  NULL,
                  DRIVER_NAME);

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_sys_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_sys_cdev);
    }

    if (alloc_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_sys_exit(void) {
    dev_t dev = MKDEV(chrdev_sys_major, 0);

    /* unregister class */
    device_destroy(chrdev_sys_class, dev);
    class_destroy(chrdev_sys_class);

    cdev_del(&chrdev_sys_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_sys_init) ;
module_exit(chrdev_sys_exit) ;

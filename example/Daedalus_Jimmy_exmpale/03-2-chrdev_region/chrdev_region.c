#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is register_chrdev_region  module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_region"
static unsigned int chrdev_region_major = 252;
static unsigned int num_of_dev = 1;
static struct cdev  chrdev_region_cdev;

static int chrdev_region_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_region_open\n");
    return 0;
}

static int chrdev_region_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_region_close\n");
    return 0;
}


struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_region_open,
    .release = chrdev_region_close,
};

static int chrdev_region_init(void) {
    dev_t dev = MKDEV(chrdev_region_major, 0);
    int region_ret = 0;
    int cdev_ret = 0;

    region_ret = register_chrdev_region(dev, num_of_dev, DRIVER_NAME);

    if (region_ret) {
        goto error;
    }

    cdev_init(&chrdev_region_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_region_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_region_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_region_cdev);
    }

    if (region_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_region_exit(void) {
    dev_t dev = MKDEV(chrdev_region_major, 0);

    cdev_del(&chrdev_region_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_region_init) ;
module_exit(chrdev_region_exit) ;

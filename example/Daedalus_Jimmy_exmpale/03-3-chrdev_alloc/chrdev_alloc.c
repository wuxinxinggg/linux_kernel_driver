#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>


MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is alloc_chrdev_region  module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_alloc"
static unsigned int chrdev_alloc_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev  chrdev_alloc_cdev;

static int chrdev_alloc_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_alloc_open\n");
    return 0;
}

static int chrdev_alloc_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_alloc_close\n");
    return 0;
}


struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_alloc_open,
    .release = chrdev_alloc_close,
};

static int chrdev_alloc_init(void) {
    dev_t dev = MKDEV(chrdev_alloc_major, 0);
    int alloc_ret = 0;
    int cdev_ret = 0;

    alloc_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);

    if (alloc_ret) {
        goto error;
    }

    chrdev_alloc_major = MAJOR(dev);

    cdev_init(&chrdev_alloc_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_alloc_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_alloc_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_alloc_cdev);
    }

    if (alloc_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_alloc_exit(void) {
    dev_t dev = MKDEV(chrdev_alloc_major, 0);

    cdev_del(&chrdev_alloc_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_alloc_init) ;
module_exit(chrdev_alloc_exit) ;

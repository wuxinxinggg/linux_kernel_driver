#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is minor and file test module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_minor"
static unsigned int chrdev_minor_major = 0;
static unsigned int num_of_dev = 2;
static struct cdev  chrdev_minor_cdev;

static int one_close(struct inode* inode, struct file* file) {
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );
    return 0;
}

static int one_open(struct inode* inode, struct file* file) {
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );

    return 0;
}

struct file_operations one_fops = {
    .open = one_open,
    .release = one_close,
};
static int zero_close(struct inode* inode, struct file* file) {
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );

    return 0;
}

static int zero_open(struct inode* inode, struct file* file) {
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );

    return 0;
}


struct file_operations zero_fops = {
    .open = zero_open,
    .release = zero_close,
};

static int chrdev_minor_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_minor_open\n");
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );

    switch (iminor(inode)) {
    case 0:
        file->f_op = &zero_fops;
        break;

    case 1:
        file->f_op = &one_fops;
        break;

    default:
        return -ENXIO;
    }

    if (file->f_op && file->f_op->open) {
        return file->f_op->open(inode, file);
    }

    return 0;
}


struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_minor_open,
};

static int chrdev_minor_init(void) {
    dev_t dev = MKDEV(chrdev_minor_major, 0);
    int minor_ret = 0;
    int cdev_ret = 0;

    minor_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);

    if (minor_ret) {
        goto error;
    }

    chrdev_minor_major = MAJOR(dev);

    cdev_init(&chrdev_minor_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_minor_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_minor_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_minor_cdev);
    }

    if (minor_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_minor_exit(void) {
    dev_t dev = MKDEV(chrdev_minor_major, 0);

    cdev_del(&chrdev_minor_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_minor_init) ;
module_exit(chrdev_minor_exit) ;

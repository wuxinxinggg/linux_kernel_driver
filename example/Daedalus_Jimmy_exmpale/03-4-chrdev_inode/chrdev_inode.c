#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is inode and file test module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_inode"
static unsigned int chrdev_inode_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev  chrdev_inode_cdev;

static int chrdev_inode_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_inode_open\n");
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );
    inode->i_private = inode;
    file->private_data = file;
    printk("  i_private=%p private_data=%p\n",
           inode->i_private, file->private_data);

    return 0;
}

static int chrdev_inode_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_inode_close\n");
    printk("%s: major %d minor %d (pid %d)\n", __func__,
           imajor(inode),
           iminor(inode),
           current->pid
          );
    inode->i_private = inode;
    file->private_data = file;
    printk("  i_private=%p private_data=%p\n",
           inode->i_private, file->private_data);
    return 0;
}


struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_inode_open,
    .release = chrdev_inode_close,
};

static int chrdev_inode_init(void) {
    dev_t dev = MKDEV(chrdev_inode_major, 0);
    int inode_ret = 0;
    int cdev_ret = 0;

    inode_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);

    if (inode_ret) {
        goto error;
    }

    chrdev_inode_major = MAJOR(dev);

    cdev_init(&chrdev_inode_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_inode_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_inode_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_inode_cdev);
    }

    if (inode_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_inode_exit(void) {
    dev_t dev = MKDEV(chrdev_inode_major, 0);

    cdev_del(&chrdev_inode_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_inode_init) ;
module_exit(chrdev_inode_exit) ;

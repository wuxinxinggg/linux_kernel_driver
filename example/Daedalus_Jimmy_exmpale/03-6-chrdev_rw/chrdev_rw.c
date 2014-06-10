#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/slab.h>

MODULE_LICENSE("Dual BSD/GPL") ;
MODULE_AUTHOR("Daedalus Jimmy");
MODULE_DESCRIPTION("This is read/write test  module");
MODULE_VERSION("1.0");

#define DRIVER_NAME "chrdev_rw"
static unsigned int chrdev_rw_major = 0;
static unsigned int num_of_dev = 1;
static struct cdev  chrdev_rw_cdev;


ssize_t chrdev_rw_read(struct file* filp, char __user* buf, size_t count, loff_t* f_pos) {
    char* val = (char*)(filp->private_data);
    int retval = 0;
    int i;
    printk(KERN_ALERT "%s\n", __func__);

    for (i = 0 ; i < count ; i++) {
        if (copy_to_user(&buf[i], val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }

    retval = count;

out:
    return (retval);
}


ssize_t chrdev_rw_write(struct file* filp, const char __user* buf, size_t count, loff_t* f_pos) {
    char* val = (char*)(filp->private_data);
    int ret;
    int retval = 0;
    printk(KERN_ALERT "%s\n", __func__);
    ret = copy_from_user(val, &buf[0], count);

    if (ret != 0) {
        retval = -EFAULT;
        goto out;
    } else {
        retval = count;
    }

out:
    return (retval);

}



static int chrdev_rw_open(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_rw_open\n");
    file->private_data = (char*)kmalloc(1, GFP_KERNEL);
    return 0;
}

static int chrdev_rw_close(struct inode* inode, struct file* file) {
    printk(KERN_ALERT "Call chrdev_rw_close\n");
    kfree(file->private_data);
    return 0;
}


struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = chrdev_rw_open,
    .release = chrdev_rw_close,
    .read = chrdev_rw_read,
    .write = chrdev_rw_write,
};

static int chrdev_rw_init(void) {
    dev_t dev = MKDEV(chrdev_rw_major, 0);
    int alloc_ret = 0;
    int cdev_ret = 0;

    alloc_ret = alloc_chrdev_region(&dev, 0, num_of_dev, DRIVER_NAME);

    if (alloc_ret) {
        goto error;
    }

    chrdev_rw_major = MAJOR(dev);

    cdev_init(&chrdev_rw_cdev, &fops);
    cdev_ret = cdev_add(&chrdev_rw_cdev, dev, num_of_dev);

    if (cdev_ret) {
        goto error;
    }

    printk(KERN_ALERT"%s driver(major %d) installed.\n", DRIVER_NAME, chrdev_rw_major);
    return 0;
error:

    if (cdev_ret == 0) {
        cdev_del(&chrdev_rw_cdev);
    }

    if (alloc_ret == 0) {
        unregister_chrdev_region(dev, num_of_dev);
    }

    return -1;
}

static void chrdev_rw_exit(void) {
    dev_t dev = MKDEV(chrdev_rw_major, 0);

    cdev_del(&chrdev_rw_cdev);
    unregister_chrdev_region(dev, num_of_dev);
    printk(KERN_ALERT"%s driver removed\n", DRIVER_NAME);
}

module_init(chrdev_rw_init) ;
module_exit(chrdev_rw_exit) ;

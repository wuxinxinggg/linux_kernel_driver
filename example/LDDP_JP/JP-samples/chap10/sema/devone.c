/*
 * devone.c
 *
 * Update: 2008/03/03 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

static int devone_devs = 1;        /* device count */
static int devone_major = 0;       /* MAJOR: dynamic allocation */
static int devone_minor = 0;       /* MINOR: static allocation */
static struct cdev devone_cdev;  
static struct class *devone_class = NULL;
static dev_t devone_dev;

struct devone_data {
	struct semaphore sem;
};

#define DATA_MAX 64
static unsigned char data[DATA_MAX];


ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	struct devone_data *dev = filp->private_data;
	int len;
	int retval;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if (count > DATA_MAX)
		len = DATA_MAX;
	else
		len = count;

	if (copy_from_user(data, buf, len)) {
		retval = -EFAULT;
		goto out;
	}
	retval = len;

out:
	up(&dev->sem);

	return (retval);
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct devone_data *dev = filp->private_data;
	int len;
	int retval;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if (count > DATA_MAX)
		len = DATA_MAX;
	else
		len = count;

	if (copy_to_user(buf, data, len)) {
		retval = -EFAULT;
		goto out;
	}
	retval = len;

out:
	up(&dev->sem);

	return (retval);
}

int devone_close(struct inode *inode, struct file *filp)
{
	struct devone_data *dev = filp->private_data;

	if (dev) {
		kfree(dev);
	}

	return 0;   /* success */
}

int devone_open(struct inode *inode, struct file *filp)
{
	struct devone_data *dev;

	dev = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
	if (dev == NULL) {
		return -ENOMEM;
	}

	/* initialize members */
	init_MUTEX(&dev->sem);

	filp->private_data = dev;

	return 0;   /* success */
}

struct file_operations devone_fops = {
	.owner = THIS_MODULE,
	.open = devone_open,
	.release = devone_close,
	.read = devone_read,
	.write = devone_write,
};

static int devone_init(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	int alloc_ret = 0;
	int major;
	int cdev_err = 0;
	struct class_device *class_dev = NULL;

	alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
	if (alloc_ret)
		goto error;
	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_fops);
	devone_cdev.owner = THIS_MODULE;
	devone_cdev.ops = &devone_fops;
	cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, devone_minor), 1);
	if (cdev_err) 
		goto error;

	/* register class */
	devone_class = class_create(THIS_MODULE, "devone");
	if (IS_ERR(devone_class)) {
		goto error;
	}
	devone_dev = MKDEV(devone_major, devone_minor);
	class_dev = class_device_create(
					devone_class, 
					NULL, 
					devone_dev,
					NULL, 
					"devone%d",
					devone_minor);

	printk(KERN_ALERT "devone driver(major %d) installed.\n", major);

	return 0;

error:
	if (cdev_err == 0)
		cdev_del(&devone_cdev);

	if (alloc_ret == 0)
		unregister_chrdev_region(dev, devone_devs);

	return -1;
}

static void devone_exit(void)
{
	dev_t dev = MKDEV(devone_major, 0);

	/* unregister class */
	class_device_destroy(devone_class, devone_dev);
	class_destroy(devone_class);

	cdev_del(&devone_cdev);
	unregister_chrdev_region(dev, devone_devs);

	printk(KERN_ALERT "devone driver removed.\n");

}

module_init(devone_init);
module_exit(devone_exit);


/*
 * devone.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/sched.h>
#include <asm/current.h>
#include <asm/uaccess.h>
#include <linux/delay.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "new_devone"

static int devone_devs = 2;        /* device count */
static int devone_major = 0;       /* dynamic allocation */
module_param(devone_major, uint, 0);
static struct cdev devone_cdev;  

static ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	ssize_t ret = count;

	printk("%s: entered (pid %d)\n", __func__, current->pid);

	if (clear_user(buf, count)) {
		ret = -EFAULT;
	}

	printk("%s: leaved (pid %d)\n", __func__, current->pid);

	return ret;
}

static ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	printk("%s: entered (pid %d)\n", __func__, current->pid);

	msleep_interruptible(30 * 1000);

	printk("%s: leaved (pid %d)\n", __func__, current->pid);

	return count;
}

static int devone_open(struct inode *inode, struct file *file)
{
	printk("%s: major %d minor %d (pid %d)\n", __func__,
			imajor(inode),
			iminor(inode),
			current->pid
		  );

	return 0;
}

static int devone_close(struct inode *inode, struct file *file)
{
	printk("%s: major %d minor %d (pid %d)\n", __func__,
			imajor(inode),
			iminor(inode),
			current->pid
		  );

	return 0;
}

struct file_operations devone_fops = {
	.open = devone_open,
	.release = devone_close,
	.write = devone_write,
	.read = devone_read,
};


static int devone_init(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	int alloc_ret = 0;
	int major;
	int cdev_err = 0;

	alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, DRIVER_NAME);
	if (alloc_ret)
		goto error;
	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_fops);
	devone_cdev.owner = THIS_MODULE;

	cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), devone_devs);
	if (cdev_err) 
		goto error;

	printk(KERN_ALERT "%s driver(major %d) installed.\n", DRIVER_NAME, major);

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

	cdev_del(&devone_cdev);
	unregister_chrdev_region(dev, devone_devs);

	printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);


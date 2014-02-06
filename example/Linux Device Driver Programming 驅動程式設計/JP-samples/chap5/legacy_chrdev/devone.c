/*
 * devone.c - static registration major number with legacy interface
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

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static unsigned int devone_major = 0;
module_param(devone_major, uint, 0);

static int devone_open(struct inode *inode, struct file *file)
{
	printk("%s: major %d minor %d (pid %d)\n", __func__,
			imajor(inode),
			iminor(inode),
			current->pid
		  );

	inode->i_private = inode;
	file->private_data = file;

	printk("  i_private=%p private_data=%p\n", 
			inode->i_private, file->private_data);

	return 0;     /* success */
}

static int devone_close(struct inode *inode, struct file *file)
{
	printk("%s: major %d minor %d (pid %d)\n", __func__,
			imajor(inode),
			iminor(inode),
			current->pid
		  );
	printk("  i_private=%p private_data=%p\n", 
			inode->i_private, file->private_data);

	return 0;     /* success */
}

struct file_operations devone_fops = {
	.open = devone_open,
	.release = devone_close,
};

static int devone_init(void)
{
	int major;
	int ret = 0;

	major = register_chrdev(devone_major, DRIVER_NAME, &devone_fops);
	if ((devone_major > 0 && major != 0) ||        /* static allocation */
			(devone_major == 0 && major < 0) ||    /* dynamic allocation */
			major < 0) {                           /* else */
		printk("%s driver registration error\n", DRIVER_NAME);
		ret = major;
		goto error;
	}
	if (devone_major == 0) {   /* dynamic allocation */
		devone_major = major;
	}

	printk("%s driver(major %d) installed.\n", DRIVER_NAME, devone_major);

error:
	return (ret);
}

static void devone_exit(void)
{
	unregister_chrdev(devone_major, DRIVER_NAME);

	printk("%s driver removed.\n", DRIVER_NAME);

}

module_init(devone_init);
module_exit(devone_exit);


/* 
 * Linux kernel book sample driver
 *
 * Race condition between Pseudo ISR handler and timeout function.
 *
 * Update: Yutaka Hirata (2007/12/5)
 *
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int timeout_value = 10;   
static unsigned int irq_value = 3;

/* driver parameter */
module_param(timeout_value, uint, 0);
module_param(irq_value, uint, 0);

static int devone_devs = 1;
static int devone_major = 0;   /* 0=dynamic allocation */
static struct cdev devone_cdev;  

struct devone_data {
	struct timer_list timeout;
	struct timer_list irq;
	spinlock_t lock;
	wait_queue_head_t wait;
	int dma_done;
	int timeout_done;
};


static void devone_timeout(unsigned long arg)
{
	struct devone_data *dev = (struct devone_data *)arg;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	printk("%s called\n", __func__);
	dev->timeout_done = 1;
	wake_up(&dev->wait);
	spin_unlock_irqrestore(&dev->lock, flags);
}

static void devone_irq(unsigned long arg)
{
	struct devone_data *dev = (struct devone_data *)arg;
	unsigned long flags;

	spin_lock_irqsave(&dev->lock, flags);
	printk("%s called\n", __func__);
	dev->dma_done = 1;
	wake_up(&dev->wait);
	spin_unlock_irqrestore(&dev->lock, flags);
}

static void devone_dma_transfer(struct devone_data *dev)
{
	dev->dma_done = 0;
	mod_timer(&dev->irq, jiffies + irq_value*HZ);
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct devone_data *dev = filp->private_data;
	int i;
	unsigned char val = 0xff;
	int retval;

	/* start timer */
	dev->timeout_done = 0;
	mod_timer(&dev->timeout, jiffies + timeout_value*HZ);

	/* kick DMA */
	devone_dma_transfer(dev);

	/* sleep process with condition */
	wait_event(dev->wait, (dev->dma_done == 1) || (dev->timeout_done == 1));

	/* cancel timer */
	del_timer_sync(&dev->timeout);

	if (dev->timeout_done == 1)   /* timeout occurred */
		return -EIO;

	/* store read data */
	for (i = 0 ; i < count ; i++) {
		if (copy_to_user(&buf[i], &val, 1)) {
			retval = -EFAULT;
			goto out;
		}
	}

	retval = count;
out:
	return (retval);
}

int devone_close(struct inode *inode, struct file *filp)
{
	struct devone_data *dev = filp->private_data;

	if (dev) {
		del_timer_sync(&dev->timeout);
		del_timer_sync(&dev->irq);
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
	spin_lock_init(&dev->lock);

	init_waitqueue_head(&dev->wait);

	dev->dma_done = 0;
	dev->timeout_done = 0;

	init_timer(&dev->timeout);
	dev->timeout.function = devone_timeout;
	dev->timeout.data = (unsigned long)dev;

	init_timer(&dev->irq);
	dev->irq.function = devone_irq;
	dev->irq.data = (unsigned long)dev;

	filp->private_data = dev;

	return 0;   /* success */
}

struct file_operations devone_fops = {
	.open = devone_open,
	.release = devone_close,
	.read = devone_read,
};

static int devone_init(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	int ret;
	int major;
	int err;

	ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
	if (ret < 0)
		return ret;
	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_fops);
	devone_cdev.owner = THIS_MODULE;
	devone_cdev.ops = &devone_fops;
	err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), 1);
	if (err) 
		return err;

	printk(KERN_ALERT "devone driver(major %d) installed.\n", major);
	printk(KERN_ALERT "timeout %u irq %u timer (%s)\n", timeout_value, irq_value, __func__);

	return 0;
}

static void devone_exit(void)
{
	dev_t dev = MKDEV(devone_major, 0);

	printk(KERN_ALERT "devone driver removed.\n");

	cdev_del(&devone_cdev);

	unregister_chrdev_region(dev, devone_devs);

}

module_init(devone_init);
module_exit(devone_exit);


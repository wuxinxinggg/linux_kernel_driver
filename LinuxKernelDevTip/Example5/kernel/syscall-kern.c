//kernel module: syscall-kern.c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/version.h>
#include <linux/miscdevice.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <linux/sched.h>
#include <linux/cred.h>
#include <linux/mm.h>
#include "../syscall-exam.h"

#define MYCHRDEV_CAPACITY 65536

struct mychrdev_data {
        char buffer[MYCHRDEV_CAPACITY];
        long headptr;
        long tailptr;
};

struct mychrdev_data *mydata;
static atomic_t mychrdev_use_stats;

struct mychrdev_private {
        pid_t user_pid;
        char user_name[TASK_COMM_LEN];
};

ssize_t mychrdev_read(struct file * file, char __user * buf, size_t count, loff_t * ppos)
{
        long len;

        len = mydata->tailptr - mydata->headptr;
        if (*ppos >= len) {
                return 0;
        }

        if (*ppos + count > len) {
                count = len - *ppos;
        }

        if (copy_to_user(buf, mydata->buffer + mydata->headptr + *ppos, count)) {
                return -EFAULT;
        }
        *ppos += count;

        return count;
}

ssize_t mychrdev_write(struct file * file, const char __user * buf, size_t count, loff_t * ppos)
{
        long leftlen = (MYCHRDEV_CAPACITY - mydata->tailptr);

        if (* ppos >= MYCHRDEV_CAPACITY) {
                return -ENOBUFS;
        }

        if (*ppos + count > leftlen) {
                count = leftlen - *ppos;
        }

        if (copy_from_user(mydata->buffer + mydata->headptr + *ppos, buf, count)) {
                return -EFAULT;
        }
        *ppos += count;
        mydata->tailptr += count;
        return count;;
}

long mychrdev_unlocked_ioctl(struct file * file, unsigned int cmd, unsigned long argp)
{
        struct mychrdev_private * myprivate = (struct mychrdev_private *)file->private_data;
        mydev_info_t a;
        struct mychrdev_window window;

        switch(cmd) {
                case MYCHRDEV_IOCTL_GET_INFO:
                        a.user_pid = myprivate->user_pid;
                        memcpy(a.user_name, myprivate->user_name, strlen(myprivate->user_name));
                        a.available_len = MYCHRDEV_CAPACITY - mydata->tailptr;
                        a.len = mydata->tailptr - mydata->headptr;
                        a.offset_in_ppage = __pa(myprivate) & 0x00000fff;
                        if (copy_to_user((void *)argp, (void *)&a, sizeof(a))) {
                                return -EFAULT;
                        }
                        break;
                case MYCHRDEV_IOCTL_SET_TRUNCATE:
                        if (copy_from_user(&window, (void *)argp, sizeof(window))) {
                                return -EFAULT;
                        }

                        if (window.head < mydata->headptr) {
                                return -EINVAL;
                        }

                        if (window.tail > mydata->tailptr) {
                                return -EINVAL;
                        }

                        mydata->headptr = window.head;
                        mydata->tailptr = window.tail;
                        break;
                default:
                        return -EINVAL;
        }

        return 0;

}

int mychrdev_open(struct inode * inode, struct file * file)
{
        struct mychrdev_private * myprivate = NULL;

        if (current_euid() != 0) {
                return -EPERM;
        }

        if (atomic_read(&mychrdev_use_stats)) {
                return -EBUSY;
        }
        else {
                atomic_inc(&mychrdev_use_stats);
        }

        myprivate = (struct mychrdev_private *)kmalloc(sizeof(struct mychrdev_private), GFP_KERNEL);
        if (myprivate == NULL) {
                return -ENOMEM;
        }

        myprivate->user_pid = current->pid;
        sprintf(myprivate->user_name, "%s", current->comm);
        file->private_data = (void *)myprivate;
        return 0;
}

int mychrdev_mmap(struct file * file, struct vm_area_struct * vma)
{
        unsigned long pfn;

        /* Turn a kernel-virtual address into a physical page frame */
        pfn = __pa(mydata->buffer) >> PAGE_SHIFT;

        if (!pfn_valid(pfn)) {
		printk("pfn_is not valid\n");
                return -EIO;
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
        vma->vm_flags |= VM_RESERVED; /* Don't swap */
#else
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP; /* Don't swap */
#endif /* LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0) */

        vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

        /* Remap-pfn-range will mark the range VM_IO and VM_RESERVED */
        if (remap_pfn_range(vma,
                            vma->vm_start,
                            pfn,
                            vma->vm_end - vma->vm_start,
                            vma->vm_page_prot))
                return -EAGAIN;

        return 0;
}

int mychrdev_release(struct inode * inode, struct file * file)
{
        atomic_dec(&mychrdev_use_stats);
        kfree(file->private_data);
        return 0;
}

loff_t mychrdev_llseek(struct file * file, loff_t offset, int seek_flags)
{
        int len = mydata->tailptr - mydata->headptr;

        switch (seek_flags) {
                case 0:
                        if ((offset > len)
                                || (offset < 0)) {
                                return -EINVAL;
                        }
                case 1:
                        if ((offset + file->f_pos < 0)
                                || (offset + file->f_pos > len)) {
                                return -EINVAL;
                        }
                        offset += file->f_pos;
                case 2:
                        if ((offset > 0)
                                || (-offset > len)) {
                                return -EINVAL;
                        }
                        offset += len;
                        break;
                default:
                        return -EINVAL;
        }

        if ((offset >= 0) && (offset <= len)) {
                file->f_pos = offset;
                file->f_version = 0;
                return offset;
        }
        else {
                return -EINVAL;
        }
}

static struct file_operations mychrdev_fops = {
        .owner = THIS_MODULE,
        .read = mychrdev_read,
        .write = mychrdev_write,
        .unlocked_ioctl = mychrdev_unlocked_ioctl,
        .open = mychrdev_open,
        .llseek = mychrdev_llseek,
        .release = mychrdev_release,
        .mmap = mychrdev_mmap,
};

static struct miscdevice my_miscdev = {
	.name       = "mychrdev",
	.fops       = &mychrdev_fops,
};
static int __init mychardev_init(void)
{
        int ret;
	mydata = kmalloc(sizeof(struct mychrdev_data), GFP_KERNEL);
	if (mydata == NULL) {
		printk("cannot allocate memory\n");
		return -1;
	}
	memset(mydata, 0, sizeof(struct mychrdev_data));
	ret = misc_register(&my_miscdev);
	if (ret != 0) {
		printk("cannot register miscdev on minor=11 (err=%d)\n", ret);
		return ret;
	}
        printk("misc device mychrdev is registered.\n");

	return 0;
}

static void __exit mychardev_remove(void)
{
	printk("misc  device mychrdev is unregistered.\n");
	misc_deregister(&my_miscdev);
	kfree(mydata);
}

module_init(mychardev_init);
module_exit(mychardev_remove);
MODULE_LICENSE("GPL");

#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "driver/sample"

static int sample_flag = 0;

int sample_proc_read(char *page, char **start, off_t off,
        int count, int *eof, void *data)
{
	int len;

	printk(KERN_INFO "%s called\n", __func__);

	if (off > 0) {
		len = 0;
	} else {
		len = sprintf(page, "%d\n", sample_flag);
	}

	return (len);
}

int sample_proc_write(struct file *file, const char *buffer, unsigned long count,
		void *data)
{
	char buf[16];
	unsigned long len = count;
	int n;

	printk(KERN_INFO "%d (%s)\n", (int)len, __func__);

	if (len >= sizeof(buf))
		len = sizeof(buf) - 1;

	if (copy_from_user(buf, buffer, len)) 
		return -EFAULT;
	buf[len] = '\0';

	n = simple_strtol(buf, NULL, 10);
	if (n == 0) 
		sample_flag = 0;
	else
		sample_flag = 1;

	return (len);
}

static int sample_init(void)
{
	struct proc_dir_entry *entry;

	/* add /proc */
	entry = create_proc_entry(PROCNAME, 0666, NULL);
	if (entry == NULL) {
		printk(KERN_WARNING "sample: unable to create /proc entry\n");
		return -ENOMEM;
	}

	entry->read_proc = sample_proc_read;
	entry->write_proc = sample_proc_write;
	entry->owner = THIS_MODULE;

	printk("driver loaded\n");
		
	return 0;
}

static void sample_exit(void)
{
	remove_proc_entry(PROCNAME, NULL);

	printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);


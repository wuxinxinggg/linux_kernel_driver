#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "sample"

static char *data_message[] = {
	"Fedora",
	"Red Hat Enterprise Server",
	"Debian",
	"Vine",
	"Ubuntu",
	0
};

static void *as_start(struct seq_file *m, loff_t *pos)
{
	loff_t n = *pos;
	char **p;
	int i;

	printk("%lld (%s)\n", n, __func__);

	if (n == 0) {
		seq_printf(m, "=== seq_file header ===\n");
	}

	p = data_message;
	for (i = 0 ; p[i] ; i++) {
		n--;
		if (n < 0)
			return (void *)(i + 1);
	}

	return 0;
}

static void *as_next(struct seq_file *m, void *p, loff_t *pos)
{
	int n = (int)p;
	char **ptr;

	printk("%u (%s)\n", n, __func__);

	(*pos)++;

	ptr = data_message;
	if (ptr[n]) {   /* exist next data */
		return (void *)(n + 1);   /* next index */
	}

	return 0;
}

static void as_stop(struct seq_file *m, void *p)
{
	int n = (int)p;

	printk("%u (%s)\n", n, __func__);
}

static int as_show(struct seq_file *m, void *p)
{
	int n = (int)p - 1;

	printk("%u (%s)\n", (int)p, __func__);

	seq_printf(m, "[%d] %s\n", n, data_message[n]);

	return 0;
}

/* seq_file handler */
static struct seq_operations sample_seq_op = {
	.start	= as_start,
 	.next	= as_next,
	.stop	= as_stop,
	.show	= as_show,
};

static int sample_proc_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &sample_seq_op);
}

/* procfs handler */
static struct file_operations sample_operations = {
	.open = sample_proc_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = seq_release,
};

static int sample_init(void)
{
	struct proc_dir_entry *entry;

	/* add /proc */
	entry = create_proc_entry(PROCNAME, S_IRUGO | S_IWUGO, NULL);
	if (entry)
		entry->proc_fops = &sample_operations;

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


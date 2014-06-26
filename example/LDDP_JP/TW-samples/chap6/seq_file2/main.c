#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <linux/version.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "sample2"

static void *as_start(struct seq_file *m, loff_t *pos)
{
	loff_t n = *pos;
	struct task_struct *p = NULL;

	printk("%lld (%s)\n", n, __func__);

	if (n == 0) {
		seq_printf(m, "=== seq_file header ===\n");
	} 

	/* Acquire a read-only spinlock */
#if ( LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,18) )
	read_lock(&tasklist_lock);
#else
	rcu_read_lock();
#endif

	if (n == 0)
		return (&init_task);   /* swapper process */

	for_each_process(p) {  /* init later process */
		n--;
		if (n <= 0)
			return (p);
	}
	return 0;
}

static void *as_next(struct seq_file *m, void *p, loff_t *pos)
{
	struct task_struct *tp = (struct task_struct *)p;

	printk("%lld (%s)\n", *pos, __func__);

	(*pos)++;

	tp = next_task(tp);
	if (tp == &init_task)
		return NULL;

	return (tp);
}

static void as_stop(struct seq_file *m, void *p)
{
	printk("%p (%s)\n", p, __func__);

	/* Release a read-only spinlock */
#if ( LINUX_VERSION_CODE <= KERNEL_VERSION(2,6,18) )
	read_unlock(&tasklist_lock);
#else
	rcu_read_unlock();
#endif
}

static int as_show(struct seq_file *m, void *p)
{
	struct task_struct *tp = (struct task_struct *)p;

	printk("%p (%s)\n", tp, __func__);

	seq_printf(m, "[%s] pid=%d\n", tp->comm, tp->pid);
	seq_printf(m, "     tgid=%d\n", tp->tgid);
	seq_printf(m, "     state=%ld\n", tp->state);
	seq_printf(m, "     mm=0x%p\n", tp->mm);
	seq_printf(m, "     utime=%lu\n", tp->utime);
	seq_printf(m, "     stime=%lu\n", tp->stime);
	seq_printf(m, "     oomkilladj=%d\n", tp->oomkilladj);
	seq_puts(m, "\n");

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


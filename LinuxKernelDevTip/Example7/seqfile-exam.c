#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");

#define MAX_LINE        1000
static uint32_t *lines;

/**
 * seq_start() takes a position as an argument and returns an iterator which
 * will start reading at that position.
 */
static void* seq_start(struct seq_file *s, loff_t *pos)
{
    uint32_t *lines;

    if (*pos >= MAX_LINE) {
        return NULL; // no more data to read
    }

    lines = kzalloc(sizeof(uint32_t), GFP_KERNEL);
    if (!lines) {
        return NULL;
    }

    *lines = *pos + 1;

    return lines;
}

/**
 * move the iterator forward to the next position in the sequence
 */
static void* seq_next(struct seq_file *s, void *v, loff_t *pos)
{
    uint32_t *lines = v;
    *pos = ++(*lines);
    if (*pos >= MAX_LINE) {
        return NULL; // no more data to read
    }
    return lines;
}

/**
 * stop() is called when iteration is complete (clean up)
 */
static void seq_stop(struct seq_file *s, void *v)
{
    kfree(v);
}

/**
 * success return 0, otherwise return error code
 */
static int seq_show(struct seq_file *s, void *v)
{
    seq_printf(s, "Line #%d: This is Brook's demo\n", *((uint32_t*)v));
    return 0;
}

static struct seq_operations seq_ops = {
    .start = seq_start,
    .next  = seq_next,
    .stop  = seq_stop,
    .show  = seq_show
};

static int proc_open(struct inode *inode, struct file *file)
{
    return seq_open(file, &seq_ops);
}

static struct file_operations proc_ops = {
    .owner   = THIS_MODULE, // system
    .open    = proc_open,
    .read    = seq_read,    // system
    .llseek  = seq_lseek,   // system
    .release = seq_release  // system
};

static int __init init_modules(void)
{
    struct proc_dir_entry *ent;

    ent = create_proc_entry("brook", 0, NULL);
    if (ent) {
        ent->proc_fops = &proc_ops;
    }
    return 0;
}

static void __exit exit_modules(void)
{
    if (lines) {
        kfree(lines);
    }
    remove_proc_entry("brook", NULL);
}

module_init(init_modules);
module_exit(exit_modules);



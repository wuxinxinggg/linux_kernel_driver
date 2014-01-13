//kernel module: procfs-exam.c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/types.h>
#include <asm/uaccess.h>

#define STR_MAX_SIZE 255
static int int_var;
static char string_var[256];
static char big_buffer[65536];
static int big_buffer_len = 0;
static struct proc_dir_entry * myprocroot;
static int first_write_flag = 1;

int int_read_proc(char *page, char **start, off_t off,
                          int count, int *eof, void *data)
{
        count = sprintf(page, "%d", *(int *)data);
        return count;
}

int int_write_proc(struct file *file, const char __user *buffer,
                           unsigned long count, void *data)
{
        unsigned int c = 0, len = 0, val, sum = 0;
        int * temp = (int *)data;

        while (count) {
                if (get_user(c, buffer))
                        return -EFAULT;

                len++;
                buffer++;
                count--;

                if (c == 10 || c == 0)
                        break;
                val = c - '0';
                if (val > 9)
                        return -EINVAL;
                sum *= 10;
                sum += val;
        }
        * temp = sum;
        return len;
}

int string_read_proc(char *page, char **start, off_t off,
                          int count, int *eof, void *data)
{
        count = sprintf(page, "%s", (char *)data);
        return count;
}

int string_write_proc(struct file *file, const char __user *buffer,
                           unsigned long count, void *data)
{
        if (count > STR_MAX_SIZE) {
                count = 255;
        }
        copy_from_user(data, buffer, count);
        return count;
}

int bigfile_read_proc(char *page, char **start, off_t off,
                          int count, int *eof, void *data)
{
        if (off > big_buffer_len) {
                * eof = 1;
                return 0;
        }

        if (count > PAGE_SIZE) {
                count = PAGE_SIZE;
        }

        if (big_buffer_len - off < count) {
                count = big_buffer_len - off;
        }

        memcpy(page, data, count);
        *start = page;
        return count;

}

int bigfile_write_proc(struct file *file, const char __user *buffer,
                           unsigned long count, void *data)
{
        char * p = (char *)data;

        if (first_write_flag) {
                big_buffer_len = 0;
                first_write_flag = 0;
        }

        if (65536 - big_buffer_len < count) {
                count = 65536 - big_buffer_len;
                first_write_flag = 1;
        }

        copy_from_user(p + big_buffer_len, buffer, count);
        big_buffer_len += count;
        return count;
}
static int __init procfs_exam_init(void)
{
        struct proc_dir_entry * entry;
        myprocroot = proc_mkdir("myproctest", NULL);
        entry = create_proc_entry("aint", 0644, myprocroot);
        if (entry) {
                entry->data = &int_var;
                entry->read_proc = &int_read_proc;
                entry->write_proc = &int_write_proc; 
        }


        entry = create_proc_entry("astring", 0644, myprocroot);
        if (entry) {
                entry->data = &string_var;
                entry->read_proc = &string_read_proc;
                entry->write_proc = &string_write_proc; 
        }

        entry = create_proc_entry("bigprocfile", 0644, myprocroot);
        if (entry) {
                entry->data = &big_buffer;
                entry->read_proc = &bigfile_read_proc;
                entry->write_proc = &bigfile_write_proc; 
        }

        return 0;
}

static void __exit procfs_exam_exit(void)
{
        remove_proc_entry("aint", myprocroot);
        remove_proc_entry("astring", myprocroot);
        remove_proc_entry("bigprocfile", myprocroot);
        remove_proc_entry("myproctest", NULL);
}

module_init(procfs_exam_init);
module_exit(procfs_exam_exit);
MODULE_LICENSE("GPL");

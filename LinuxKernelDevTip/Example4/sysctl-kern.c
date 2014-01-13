//kernel module: sysctl-kern.c
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sysctl.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("HungMing Wu");

#define MY_MAX_SIZE 256
static char mystring[MY_MAX_SIZE];
static int myint;

static int sysctl_kernusr_data = 1024;
static int kernusr_callback(ctl_table *table, int write,
        void __user *buffer, size_t *lenp, loff_t *ppos)
{
    int rc;
    int *data = table->data;

    printk(KERN_INFO "original value = %d\n", *data);

    rc = proc_dointvec(table, write, buffer, lenp, ppos);
    if (write)
        printk(KERN_INFO "this is write operation, current value = %d\n", *
data);

    return rc;

}
static struct ctl_table my_sysctl_example[] = {
        {
                .procname       = "myint",
                .data           = &myint,
                .maxlen         = sizeof(int),
                .mode           = 0666,
                .proc_handler   = &proc_dointvec,
        },
        {
                .procname       = "mystring",
                .data           = mystring,
                .maxlen         = MY_MAX_SIZE,
                .mode           = 0666,
                .proc_handler   = &proc_dostring,
        },
	    {
			     .procname		= "kernusr",
				 .data          = &sysctl_kernusr_data,
			     .maxlen        = sizeof(int),
		         .mode          = 0666,
		         .proc_handler  = kernusr_callback,
	    },
        {
			/* sentinel */
        }
};

static struct ctl_table my_root = {
        .procname       = "sysctl_example",
        .mode           = 0555,
        .child          = my_sysctl_example,
};

static struct ctl_table_header *my_ctl_header;

static int __init sysctl_exam_init(void)
{
        my_ctl_header = register_sysctl_table(&my_root);

	    if (my_ctl_header == NULL) {
	        printk(KERN_INFO "ERR: register_sysctl_table!");
	        return -1;
		}

        return 0;
}

static void __exit sysctl_exam_exit(void)
{
        unregister_sysctl_table(my_ctl_header);
}

module_init(sysctl_exam_init);
module_exit(sysctl_exam_exit);

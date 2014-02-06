/*
 * main.c
 *
 * Update: 2008/1/7 Yutaka Hirata
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

struct sample_data {
	spinlock_t lock;
	struct file *file;
	struct list_head list;
	wait_queue_head_t wait;
	int no;
};

struct sample_data head;

void free_struct(void)
{
	struct list_head *listptr;
	struct sample_data *entry;

	list_for_each(listptr, &head.list) {
		entry = list_entry(listptr, struct sample_data, list);
		printk("Free: no=%d (list %p, next %p, prev %p)\n", 
				entry->no, &entry->list, entry->list.next,  entry->list.prev);

		kfree(entry);
	}
}

void show_struct(void)
{
	struct list_head *listptr;
	struct sample_data *entry;

	printk("===================================\n");
	printk("no=%d (list %p, next %p, prev %p)\n", 
			head.no, &head.list, head.list.next,  head.list.prev);

	list_for_each(listptr, &head.list) {
		entry = list_entry(listptr, struct sample_data, list);
		printk("no=%d (list %p, next %p, prev %p)\n", 
				entry->no, &entry->list, entry->list.next,  entry->list.prev);
	}
}


void remove_struct(struct sample_data *entry)
{
	printk("Free: no=%d (list %p, next %p, prev %p)\n", 
			entry->no, &entry->list, entry->list.next,  entry->list.prev);

	list_del(&entry->list);       /* Delete entry */
	kfree(entry);               /* free! */
}

struct sample_data *add_struct(int no)
{
	struct sample_data *ptr;

	ptr = kmalloc(sizeof(struct sample_data), GFP_KERNEL);
	if (ptr) {
		ptr->no = no;
		list_add_tail(&ptr->list, &head.list);  /* change list_add to list_add_tail */
	}

	return (ptr);
}

static int sample_init(void)
{
	struct sample_data *p;

	memset(&head, 0, sizeof(head));
	INIT_LIST_HEAD(&head.list);       /* Initialize linked-list */
	show_struct();

	add_struct(1);
	show_struct();

	p = add_struct(2);
	show_struct();

	add_struct(3);
	show_struct();

	if (p) {
		remove_struct(p);
		show_struct();
	}

	free_struct();

	printk(KERN_ALERT "sample driver installed.\n");

	return 0;
}

static void sample_exit(void)
{
	printk(KERN_ALERT "sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);


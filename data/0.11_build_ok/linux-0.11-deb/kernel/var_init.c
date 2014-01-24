/*
 * Many global-scoped variables/data-structures are incorrectly
 * initialized due to some bug I cannot figure out. So this function
 * aims at fixing all of them (I wish it would).
 * Note that there're also some static variables/data-structures with
 * file scope which are also incorrectly initialized, and they are fixed
 * in the file where they are defined.
 */
#include <string.h>
#include <linux/fs.h>
#include <linux/sched.h>
extern long last_pid;

void var_fix_init(void)
{
	int i;

	/* the inode_table[] is also incorrectly initialized */
	memset(inode_table, 0, sizeof(inode_table));

	/* these are some variable defined in sched.c */
	last_task_used_math = NULL;
	startup_time = 0;
	jiffies = 0;

	/* fork.c */
	last_pid = 0;
}

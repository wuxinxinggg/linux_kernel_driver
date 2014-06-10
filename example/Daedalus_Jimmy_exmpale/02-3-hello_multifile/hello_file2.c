#include <linux/module.h>

void fuck() {
    printk(KERN_ALERT "File2 is here\n");
}
EXPORT_SYMBOL(fuck);

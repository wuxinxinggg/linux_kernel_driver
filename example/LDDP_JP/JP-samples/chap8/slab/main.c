/*
 * main.c
 *
 */
#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

#define CACHESIZE (128*1024)

void *ptr[10];
struct kmem_cache *cache;

static int sample_init(void)
{
	int i;
	int ret = 0;

	printk("sample driver installed.\n");

	memset(ptr, 0, sizeof(ptr));

	cache = kmem_cache_create("sample_yutaka", CACHESIZE, 0, 0, NULL);
	if (cache == NULL) {
		ret = -ENOMEM;
		goto error;
	}

	for (i = 0 ; i < 10 ; i++) {
		ptr[i] = kmem_cache_alloc(cache, GFP_KERNEL);
		if (ptr[i] == NULL) {
			ret = -ENOMEM;
			goto error;
		}
		memset(ptr[i], 0, CACHESIZE);
		printk("ptr[%d]=%p\n", i, ptr[i]);
	}
	return 0;

error:
	for (i = 0 ; i < 10 ; i++) {
		if (ptr[i]) 
			kmem_cache_free(cache, ptr[i]);
	}

	if (cache)
		kmem_cache_destroy(cache);

	return (ret);
}

static void sample_exit(void)
{
	int i;

	printk("sample driver removed.\n");

	for (i = 0 ; i < 10 ; i++) {
		if (ptr[i]) 
			kmem_cache_free(cache, ptr[i]);
	}

	if (cache)
		kmem_cache_destroy(cache);
}

module_init(sample_init);
module_exit(sample_exit);


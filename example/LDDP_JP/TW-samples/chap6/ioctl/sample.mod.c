#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x3b69997a, "module_layout" },
	{ 0x6fcb3e03, "cdev_del" },
	{ 0x62eb2c87, "kmalloc_caches" },
	{ 0x681c3ac3, "cdev_init" },
	{ 0x4c4fef19, "kernel_stack" },
	{ 0xc01cf848, "_raw_read_lock" },
	{ 0x4e6693ef, "device_destroy" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0x27e1a049, "printk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb4390f9a, "mcount" },
	{ 0x7f658e80, "_raw_write_lock" },
	{ 0xfafe0694, "device_create" },
	{ 0x5bbcf139, "cdev_add" },
	{ 0xc6cbbc89, "capable" },
	{ 0x399c29ef, "kmem_cache_alloc_trace" },
	{ 0x37a0cba, "kfree" },
	{ 0x480b818b, "class_destroy" },
	{ 0x4f6b400b, "_copy_from_user" },
	{ 0xd7a6b38a, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D3CD69A3FFE265D61D53734");

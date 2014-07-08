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
	{ 0xc8b57c27, "autoremove_wake_function" },
	{ 0xf22449ae, "down_interruptible" },
	{ 0x4e6693ef, "device_destroy" },
	{ 0xfb0e29f, "init_timer_key" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x7d11c268, "jiffies" },
	{ 0x6395be94, "__init_waitqueue_head" },
	{ 0x4f8b5ddb, "_copy_to_user" },
	{ 0xd5f2172f, "del_timer_sync" },
	{ 0x8f64aa4, "_raw_spin_unlock_irqrestore" },
	{ 0x9db7a936, "current_task" },
	{ 0x27e1a049, "printk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb4390f9a, "mcount" },
	{ 0x68aca4ad, "down" },
	{ 0xfafe0694, "device_create" },
	{ 0x8834396c, "mod_timer" },
	{ 0x5bbcf139, "cdev_add" },
	{ 0xd62c833f, "schedule_timeout" },
	{ 0x399c29ef, "kmem_cache_alloc_trace" },
	{ 0x9327f5ce, "_raw_spin_lock_irqsave" },
	{ 0xcf21d241, "__wake_up" },
	{ 0x37a0cba, "kfree" },
	{ 0x5c8b5ce8, "prepare_to_wait" },
	{ 0x71e3cecb, "up" },
	{ 0x480b818b, "class_destroy" },
	{ 0xfa66f77c, "finish_wait" },
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0xd7a6b38a, "__class_create" },
	{ 0x29537c9e, "alloc_chrdev_region" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "EF848570BAEC24E316C868C");

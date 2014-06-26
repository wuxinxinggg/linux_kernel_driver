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
	{ 0xc3fe87c8, "param_ops_uint" },
	{ 0x7485e15e, "unregister_chrdev_region" },
	{ 0x5bbcf139, "cdev_add" },
	{ 0x681c3ac3, "cdev_init" },
	{ 0x6fcb3e03, "cdev_del" },
	{ 0x29537c9e, "alloc_chrdev_region" },
	{ 0x7aec9089, "clear_user" },
	{ 0xcc5005fe, "msleep_interruptible" },
	{ 0x27e1a049, "printk" },
	{ 0x9db7a936, "current_task" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "A96C76E0671EEC9DF398473");

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
    { 0x8495e121, "module_layout" },
    { 0x7485e15e, "unregister_chrdev_region" },
    { 0x149a0346, "cdev_add" },
    { 0xb02fdc3a, "cdev_init" },
    { 0xe49685e5, "cdev_del" },
    { 0x29537c9e, "alloc_chrdev_region" },
    { 0x4f8b5ddb, "_copy_to_user" },
    { 0x4f6b400b, "_copy_from_user" },
    { 0xa1c76e0a, "_cond_resched" },
    { 0x24f41ee7, "kmem_cache_alloc_trace" },
    { 0xc6d08280, "kmalloc_caches" },
    { 0x37a0cba, "kfree" },
    { 0x27e1a049, "printk" },
    { 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
    "depends=";


MODULE_INFO(srcversion, "AFA31D36B7CA4C2AD87A200");

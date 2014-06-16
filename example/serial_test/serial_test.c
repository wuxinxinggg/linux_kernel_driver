/*
 * drivers/tty/serial/sw_uart.c
 * (C) Copyright 2007-2011
 * Reuuimlla Technology Co., Ltd. <www.reuuimllatech.com>
 * Aaron.Maoye <leafy.myeh@reuuimllatech.com>
 *
 * description for this code
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/clk.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/ctype.h>
#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/platform_device.h>

#include <linux/console.h>
#include <linux/tty.h>
#include <linux/tty_flip.h>
#include <linux/serial_core.h>
#include <linux/workqueue.h>
#include <linux/serial.h>
#include <linux/module.h>
#include <linux/ioport.h>
#include <linux/init.h>
#include <linux/console.h>
#include <linux/sysrq.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/tty.h>
#include <linux/ratelimit.h>
#include <linux/tty_flip.h>
#include <linux/serial_reg.h>
#include <linux/serial_core.h>
#include <linux/serial.h>
#include <linux/nmi.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/clk.h>
#include <linux/timer.h>
#include <linux/workqueue.h>
#include <linux/dma-mapping.h>

#include <asm/io.h>
#include <asm/irq.h>

#define SW_UART_NR  8
static struct timer_list* timer;
struct platform_device* pdev;
struct work_struct q_work;
struct workqueue_struct* workqueue;
volatile static int force_enable_work;


//当有硬件数据到来时，要手动调用该函数接收数据并上报
static void sw_uart_handle_rx(unsigned long data) {
#if 1
    struct uart_port* port;
    struct tty_struct* tty;
    unsigned char ch = 0;
    int i;
    int flag;
    char* send_buff = "i am sclu, this is from serial rx";

    flag = TTY_NORMAL;
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    port = (struct uart_port*)data;

    if (!port) {
        return;
    }

    if (!port->state) {
        return;
    }

    tty = port->state->port.tty;

    //tty->flags |= TTY_HW_COOK_IN;
    //tty = port->info->tty;
    if (!tty) {
        return;
    }

    //  for (i = 0; i < strlen(send_buff) + 1; i++) {
    //用tty_insert_flip_char函数也可以
    //    ch = send_buff[i];
    //  uart_insert_char(port, 0, 0, ch, flag);
    // }
    tty_insert_flip_string(tty, send_buff, strlen(send_buff) + 1);
    //    uart_insert_char(port, 0, 0, '\n', flag);
    //  uart_insert_char(port, 0, 0, '\t', 0);
    tty_flip_buffer_push(tty);
#endif
    timer->expires = jiffies + 3 * HZ;
    add_timer(timer);
}

static void sw_uart_stop_tx(struct uart_port* port) {
    //del_timer(timer);
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

//上层用户空间写的数据最终调用该函数完成发送
static void sw_uart_start_tx(struct uart_port* port) {
    struct circ_buf* xmit = &port->state->xmit;

    // printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    //开始发送数据
    if (!force_enable_work || uart_circ_empty(xmit) || uart_tx_stopped(port)) {
        queue_work(workqueue, &q_work);
    }
}



static unsigned int sw_uart_tx_empty(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    //当硬件fifo中的数据发送完成后，要返回TIOCSER_TEMI，否则上层一直写等待，如echo数据一直没有返回
    return TIOCSER_TEMT;
}

static void sw_uart_set_mctrl(struct uart_port* port, unsigned int mctrl) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static unsigned int sw_uart_get_mctrl(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

static void sw_uart_stop_rx(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static void sw_uart_enable_ms(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static void sw_uart_break_ctl(struct uart_port* port, int break_state) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);

}

static int sw_uart_startup(struct uart_port* port) {
    /* this is the first time this port is opened */
    /* do any hardware initialization needed here */

    /* create our timer and submit it */
    force_enable_work = 0;

    if (!timer) {
        timer = kmalloc(sizeof(*timer), GFP_KERNEL);

        if (!timer) {
            return -ENOMEM;
        }
    }

    setup_timer(timer, sw_uart_handle_rx, (unsigned long)port);
    timer->expires = jiffies + HZ * 3;
#if 0
    timer->data = (unsigned long)port;
    timer->expires = jiffies + DELAY_TIME;
    timer->function = tiny_timer;
#endif
    add_timer(timer);

    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

static void sw_uart_shutdown(struct uart_port* port) {
    /* The port is being closed by the last user. */
    /* Do any hardware specific stuff here */

    /* shut down our timer */
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    force_enable_work = 1;
    cancel_work_sync(&q_work);

}

static void sw_uart_set_termios(struct uart_port* port, struct ktermios* termios,
                                struct ktermios* old) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static const char* sw_uart_type(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    return "SW";
}

static void sw_uart_release_port(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static int sw_uart_request_port(struct uart_port* port) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

static void sw_uart_config_port(struct uart_port* port, int flags) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
}

static int sw_uart_verify_port(struct uart_port* port, struct serial_struct* ser) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    return 0;
}

static void sw_uart_pm(struct uart_port* port, unsigned int state,
                       unsigned int oldstate) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);

}

static struct uart_driver sw_uart_driver;

static struct uart_ops sw_uart_ops = {
#if 1
    .tx_empty = sw_uart_tx_empty,
    .set_mctrl = sw_uart_set_mctrl,
    .get_mctrl = sw_uart_get_mctrl,
    .stop_tx = sw_uart_stop_tx,
    .enable_ms = sw_uart_enable_ms,
    .break_ctl = sw_uart_break_ctl,
    .set_termios = sw_uart_set_termios,
    .type = sw_uart_type,
    .release_port = sw_uart_release_port,
    .request_port = sw_uart_request_port,
    .config_port = sw_uart_config_port,
    .verify_port = sw_uart_verify_port,
    .pm = sw_uart_pm,
#endif
    .startup = sw_uart_startup,
    .start_tx = sw_uart_start_tx,
    .stop_rx = sw_uart_stop_rx,
    .shutdown = sw_uart_shutdown,
};

static struct uart_port tiny_port = {
    .ops = &sw_uart_ops,
    .type = PORT_8250,
    .fifosize = 64,
    .flags = UPF_SKIP_TEST | UPF_BOOT_AUTOCONF,
};

#ifdef CONFIG_CONSOLE_POLL
static void sw_console_write(struct console* co, const char* s,
                             unsigned int count) {
}

static int __init sw_console_setup(struct console* co, char* options) {
    struct uart_port* port;
    int baud = 115200;
    int bits = 8;
    int parity = 'n';
    int flow = 'n';

    port = &tiny_port;

    if (options) {
        uart_parse_options(options, &baud, &parity, &bits, &flow);
    }

    return uart_set_options(port, co, baud, parity, bits, flow);


}
#endif
static void tx_work(struct work_struct* work) {
#if 1
    struct uart_port* port = &tiny_port;
    struct circ_buf* xmit = &port->state->xmit;
    int count;

    // printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    if (port->x_char) {
        printk("x_char %2x", port->x_char);
        port->icount.tx++;
        port->x_char = 0;
        return;
    }


    if (uart_circ_empty(xmit) || uart_tx_stopped(port)) {
        return;
    }

    count = port->fifosize / 2;
    // printk("sclu %s, count = %d\n", __func__, count);
    //发送数据
    //  serial_out(&sw_uport->port, xmit->buf[xmit->tail], SW_UART_THR);
    printk("get data:\n");

    do {
        printk("%c", xmit->buf[xmit->tail]);

        xmit->tail = (xmit->tail + 1) & (UART_XMIT_SIZE - 1);
        port->icount.tx++;

        if (uart_circ_empty(xmit)) {
            break;
        }
    } while (--count > 0);

    printk("\n");

    if (uart_circ_chars_pending(xmit) < WAKEUP_CHARS) {
        // spin_unlock(&port->lock);
        uart_write_wakeup(port);
        // spin_lock(&port->lock);
    }

    if (uart_circ_empty(xmit)) {
        sw_uart_stop_tx(port);
    }

#endif

}

#ifdef CONFIG_CONSOLE_POLL
static struct console sw_console = {
    .name = "ttyVirtual",
    .write = sw_console_write,
    .device = uart_console_device,
    .setup = sw_console_setup,
    .flags = CON_PRINTBUFFER | CON_ANYTIME,
    .index = -1,
    .data = &sw_uart_driver,
};
#define SERIAL_CONSOLE  &sw_console
#else
#define SERIAL_CONSOLE  NULL
#endif

static struct uart_driver sw_uart_driver = {
    .owner = THIS_MODULE,
    .driver_name = "Virtual_serial",
    .dev_name = "ttyVirtual",
    .nr = SW_UART_NR,
    .cons = SERIAL_CONSOLE
};

static int sw_uart_probe(struct platform_device* pdev) {
    printk("%s, %d, %s\n", __FILE__, __LINE__, __func__);
    workqueue = create_singlethread_workqueue("ttyVirtual_work");
    INIT_WORK(&q_work, tx_work);
    return uart_add_one_port(&sw_uart_driver, &tiny_port);
}

static int sw_uart_remove(struct platform_device* pdev) {
    return 0;
}

#define SERIAL_SW_PM_OPS    NULL

static struct platform_driver sw_uport_platform_driver = {
    .probe = sw_uart_probe,
    .remove = (sw_uart_remove),
    .driver.name = "ttyVirtual",
    .driver.pm = SERIAL_SW_PM_OPS,
    .driver.owner = THIS_MODULE,
};


static int __init sw_uart_init(void) {
    int ret;

    printk("serial driver initializied\n");

    ret = uart_register_driver(&sw_uart_driver);

    if (unlikely(ret)) {
        printk("serial driver initializied err\n");
        return ret;
    }

    pdev = platform_device_register_simple("ttyVirtual", 0, NULL, 0);

    return platform_driver_register(&sw_uport_platform_driver);
}

static void __exit sw_uart_exit(void) {
    if (timer) {
        del_timer(timer);
        timer = NULL;
    }

    if (workqueue) {
        flush_workqueue(workqueue);
        destroy_workqueue(workqueue);
        workqueue = NULL;
    }

    printk("driver exit\n");
    uart_remove_one_port(&sw_uart_driver, &tiny_port);
    platform_driver_unregister(&sw_uport_platform_driver);

    if (pdev) {
        platform_device_unregister(pdev);
    }

    uart_unregister_driver(&sw_uart_driver);
}

module_init(sw_uart_init);
module_exit(sw_uart_exit);

MODULE_AUTHOR("Aaron<leafy.myeh@allwinnertech.com>");
MODULE_DESCRIPTION("Driver for SW serial device");
MODULE_LICENSE("GPL");

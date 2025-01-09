#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/ioport.h>
#include <linux/platform_device.h>
// #include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>

/*
* 描述: platform设备
*/


/* 寄存器物理地址 */
// #define CCM_CCGR1_BASE              (0X020C406C)
// #define SW_MUX_GPIO1_IO03_BASE      (0X020E0068)
// #define SW_PAD_GPIO1_IO03_BASE      (0X020E02F4)
// #define GPIO1_DR_BASE               (0X0209C000)
// #define GPIO1_GDIR_BASE             (0X0209C004)
// #define REGISTER_LENGTH             4

#define SYS_GRF             0xFDC60000
#define GRF_GPIO3B_IOMUX_H  (SYS_GRF + 0x004C)
#define GIPO3_BASE          0xFE760000
#define GIPO3_SWPORT_DR_L   (GIPO3_BASE + 0x0000)
#define GIPO3_SWPORT_DDR_L  (GIPO3_BASE + 0x0008)
#define REGISTER_LENGTH             4


/*
* @description  : 释放platform设备模块的时候，此函数会执行
* @param - dev  : 要释放的设备
* @return       : 无
*/
static void led_release(struct device *dev)
{
    printk("led device released!\r\n");
}

/*
* 设备资源信息，也就是LED0所使用的所有寄存器
*/
static struct resource led_resources[] = {
    [0] = {
        .start = GRF_GPIO3B_IOMUX_H,
        .end = (GRF_GPIO3B_IOMUX_H + REGISTER_LENGTH -1),
        .flags = IORESOURCE_MEM,
    },
    [1] = {
        .start = GIPO3_SWPORT_DDR_L,
        .end = (GIPO3_SWPORT_DDR_L + REGISTER_LENGTH -1),
        .flags = IORESOURCE_MEM,
    },
    [2] = {
        .start = GIPO3_SWPORT_DR_L,
        .end = (GIPO3_SWPORT_DR_L + REGISTER_LENGTH -1),
        .flags = IORESOURCE_MEM,
    },
};

/*
* platform 设备结构体
*/
static struct platform_device leddevice = {
    .name = "tspi-led",
    .id = -1,
    .dev = {
        .release = &led_release,
    },
    .num_resources = ARRAY_SIZE(led_resources),
    .resource = led_resources,
};

/*
* @description  : 设备模块加载
* @param        : 无
* @return       : 无
*/
static int __init leddevice_init(void)
{
    return platform_device_register(&leddevice);
}

/*
* @description  : 设备模块注销
* @param        : 无
* @return       : 无
*/
static void __exit leddevice_exit(void)
{
    platform_device_unregister(&leddevice);
}

module_init(leddevice_init);
module_exit(leddevice_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jack");

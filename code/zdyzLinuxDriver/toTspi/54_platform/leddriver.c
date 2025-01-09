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
// #include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/platform_device.h>


/*
* 描述: platform驱动
*/

#define LEDDEV_CNT      1           /* 设备号长度 */
#define LEDDEV_NAME     "platled"   /* 设备名称 */
#define LEDOFF          0
#define LEDON           1

/* 映射后的寄存器虚拟地址指针 */
unsigned int *virt_gpio3b_iomux;
unsigned int *virt_gpio3_ddr;
unsigned int *virt_gpio3_dr;

/* leddev 设备结构体 */
struct leddev_dev{
    dev_t devid;            /* 设备号 */
    struct cdev cdev;       /* cdev */
    struct class *class;    /* 类 */
    struct device *device;  /* 设备 */
    int major;              /* 主设备号 */
};

struct leddev_dev leddev;     /* led 设备 */

/*
* @description  : LED 打开/关闭
* @param - sta  : LEDN(0) 打开LED, LEDOFF(1) 关闭LED
* @return       : 无
*/
void led_switch(u8 sta)
{
    // u32 val = 0;
    if(sta == LEDON) {
        // GPIO_SWPORT_DR_L：设置GPIO3B4为输出高电平(LED亮). 
        // 12位写1（设置输出高电平）;28位写1(写使能)
        *virt_gpio3_dr |= ((0x1 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));
    } else if(sta == LEDOFF) {
        // GPIO_SWPORT_DR_L：设置GPIO3B4为输出低电平(LED灭). 
        // 12位写0（设置输出低电平）;28位写1(写使能)
        *virt_gpio3_dr = ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));
    }
}

/*
* @description   : 打开设备
* @param - inode : 传递给驱动的 inode
* @param - filp  : 设备文件, file结构体有个private_data的成员变量,
                   一般在open的时候将private_data指向设备结构体
* @return        : 0 成功; 其他 失败
*/
static int led_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &leddev;    /* 设置私有数据 */
    return 0;
}


/*
* @description  : 从设备读取数据
* @param - filp : 要打开的设备文件（文件描述符）
* @param - buf  : 返回给用户空间的数据缓冲区
* @param - cnt  : 要读取的数据长度
* @param - offt : 相对于文件首地址的偏移
* @return       : 读取的字节数，如果为负值，表示读取失败
*/
static ssize_t led_read(struct file *filp, char __user *buf, 
                        size_t cnt, loff_t *offt)
{
    return 0;
}

/*
* @description  : 向设备写数据
* @param - filp : 设备文件，表示打开的文件描述符
* @param - buf  : 要给设备写入的数据
* @param - cnt  : 要写入的数据长度
* @param - offt : 相对于文件首地址的偏移
* @return       : 写入的字节数，如果为负值，表示写入失败
*/
ssize_t led_write(struct file *filp, const char __user *buf,
                         size_t cnt, loff_t *offt)
{
    int retvalue;
    unsigned char databuf[1];
    unsigned char ledstat;

    retvalue = copy_from_user(databuf, buf, cnt);
    if(retvalue < 0) {
        printk("kernel write failed!\r\n");
        return -EFAULT;
    }

    ledstat = databuf[0];   /* 获取状态值 */

    if(ledstat == LEDON) {
        led_switch(LEDON);  /* 打开LED灯 */
    } else if(ledstat == LEDOFF ) {
        led_switch(LEDOFF); /* 关闭LED灯 */
    }
    return 0;
}


/*
* @description   : 关闭/释放设备
* @param - inode : 传递给驱动的 inode
* @param - filp  : 要关闭的设备文件（文件描述符）
* @return        : 0 成功; 其他 失败
*/
static int led_release(struct inode *node, struct file *filp)
{
    return 0;
}

/* 设备操作函数 */
static struct file_operations led_fops = {
    .owner  = THIS_MODULE,
    .open   = led_open,
    .read   = led_read,
    .write  = led_write,
    .release = led_release
};

/*
* @description   : platform 驱动的 probe 函数，
                   当驱动与设备匹配以后此函数会执行
* @param - dev   : platform 设备
* @return        : 0 成功; 其他负值 失败
*/
static int led_probe(struct platform_device *dev)
{
    int i = 0;
    int ressize[5];
    // u32 val = 0;
    struct resource *ledsource[5];

    printk("led driver and device has matched!\r\n");

    /* 1. 获取资源 */
    for(i = 0; i < 3; i++) {
        ledsource[i] = platform_get_resource(dev, IORESOURCE_MEM, i);
        if(!ledsource[i]) {
            dev_err(&dev->dev, "No MEM resource for always on\r\n");
            return -ENXIO;
        }
        ressize[i] = resource_size(ledsource[i]);
    }

    /* 2. 初始化LED */
    /* 寄存器地址映射 */
    virt_gpio3b_iomux = ioremap(ledsource[0]->start, ressize[0]);
    if(virt_gpio3b_iomux == NULL) {
        printk("ioremap iomux register error!\r\n");
        return -ENOMEM;
    }
    virt_gpio3_ddr = ioremap(ledsource[1]->start, ressize[1]);
    if(virt_gpio3_ddr == NULL) {
        printk("ioremap ddr register error!\r\n");
        return -ENOMEM;
    }
    virt_gpio3_dr = ioremap(ledsource[2]->start, ressize[1]);
    if(virt_gpio3_dr == NULL) {
        printk("ioremap dr register error!\r\n");
        return -ENOMEM;
    }

    /* 使能GPIO1时钟 */
    // val = readl(IMX6U_CCM_CCGR1);
    // val &= ~(3 << 26); /* 清除以前的设置 */
    // val |= (3 << 26);  /* 设置新值 */
    // writel(val, IMX6U_CCM_CCGR1);

    /* 设置GPIO1_IO03 的复用功能,
    * 将其复用为 GPIO1_IO03,最后设置IO属性 
    */
    // GRF_GPIO3B_IOMUX_H: 2~0位 写0(gpio功能); 16~18 写1(写使能)  
    *virt_gpio3b_iomux |= ((0x7 << (16+0)) + (0x0 << 0));

    /* 设置 GPIO1_IO03 为输出功能 */
    // GPIO_SWPORT_DRR_L：设置GPIO3B4为输出. 
    // 12位写1(设置为输出);28位写1(写使能)
    *virt_gpio3_ddr |= ((0x1 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4))); 

    /* 默认关闭 LED */
    // GPIO_SWPORT_DR_L：设置GPIO3B4为输出低电平(LED灭). 
    // 12位写0（设置输出低电平）;28位写1(写使能)
    *virt_gpio3_dr |= ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));

    /* 注册字符设备驱动 */
    if(leddev.major) { // 定义了设备号
        leddev.devid = MKDEV(leddev.major, 0);
        register_chrdev_region(leddev.devid, LEDDEV_CNT, 
                               LEDDEV_NAME);
    } else { // 没有定义设备号
        alloc_chrdev_region(&leddev.devid, 0, LEDDEV_CNT,
                            LEDDEV_NAME); // 申请设备号
        leddev.major = MAJOR(leddev.devid);   //获取主设备号
    }
    printk("leddev major=%d\r\n", leddev.major);

    /* 2. 初始化cdev */
    leddev.cdev.owner = THIS_MODULE,
    cdev_init(&leddev.cdev, &led_fops);

    /* 3. 添加一个cdev */
    cdev_add(&leddev.cdev, leddev.devid, LEDDEV_CNT);

    /* 4. 创建类 */
    leddev.class = class_create(THIS_MODULE, LEDDEV_NAME);
    if(IS_ERR(leddev.class)) {
        return PTR_ERR(leddev.class);
    }

    /* 5. 创建设备 */
    leddev.device = device_create(leddev.class, NULL, 
                        leddev.devid, NULL, LEDDEV_NAME);
    if(IS_ERR(leddev.device)) {
        return PTR_ERR(leddev.device);
    }
    return 0;
}

/*
* @description   : 移除platform驱动的时候会执行此函数
* @param - dev   : platform 设备
* @return        : 0 成功; 其他负值 失败
*/
static int led_remove(struct platform_device *dev)
{
    /* 取消映射 */
    // GPIO_SWPORT_DR_L：设置GPIO3B4为输出低电平(LED灭). 
    // 12位写0（设置输出低电平）;28位写1(写使能)
    *virt_gpio3_dr = ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));
    iounmap(virt_gpio3b_iomux);
    iounmap(virt_gpio3_ddr);
    iounmap(virt_gpio3_dr);


    /* 注销字符设备 */
    cdev_del(&leddev.cdev);  //删除cdev
    unregister_chrdev_region(leddev.devid, LEDDEV_CNT);

    device_destroy(leddev.class, leddev.devid);
    class_destroy(leddev.class);
    return 0;
}

/* platform 驱动结构体*/
static struct platform_driver led_driver = {
    .driver = {
        .name = "tspi-led",   /* 驱动名字，用于和设备匹配 */
    },
    .probe = led_probe,
    .remove = led_remove,
};

/*
* @description  : 驱动模块加载函数
* @param        : 无
* @return        : 0 成功; 其他 失败
*/
static int __init leddriver_init(void)
{
    return platform_driver_register(&led_driver);
}

/*
* @description  : 驱动模块卸载函数
* @param        : 无
* @return       : 无
*/
static void __exit leddriver_exit(void)
{
    platform_driver_unregister(&led_driver);
}

module_init(leddriver_init);
module_exit(leddriver_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jack");

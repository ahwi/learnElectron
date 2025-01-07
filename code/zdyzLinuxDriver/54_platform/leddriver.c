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
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>


/*
* 描述: platform驱动
*/

#define LEDDEV_CNT      1           /* 设备号长度 */
#define LEDDEV_NAME     "platled"   /* 设备名称 */
#define LEDOFF          0
#define LEDON           1

/* 映射后的寄存器虚拟地址指针 */
static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;

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
    u32 val = 0;
    if(sta == LEDON) {
        val = readl(GPIO1_DR);
        val &= ~(1 << 3);
        writel(val, GPIO1_DR);
    } else if(sta == LEDOFF) {
        val = readl(GPIO1_DR);
        val |= (1 << 3);
        writel(val, GPIO1_DR);
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
    file->private_data = &newchrled;    /* 设置私有数据 */
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
static ssize_t led_write(struct file *filp, const char __user buf,
                         size_t cnt, loff_t *offt)
{
    int retvalue;
    unsinged char databuf[1];
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
    .relase = led_release
};

/*
* @description   : platform 驱动的 probe 函数，
                   当驱动与设备匹配以后此函数会执行
* @param - dev   : platform 设备
* @return        : 0 成功; 其他负值 失败
*/
static int led_probe(void)
{
    int i = 0;
    int ressize[5];
    u32 val = 0;
    struct resource *ledsource[5];

    printk("led driver and device has matched!\r\n");

    /* 1. 获取资源 */
    for(i = 0; i < 5; i++) {
        ledsource[i] = platform_get_resource(dev, IORESOURCE_MEM, i);
        if(!ledsource[i]) {
            dev_err(&dev->dev, "No MEM resource for always on\r\n");
            return -ENXIO;
        }
        ressize[i] = resource_size(ledsource[i]);
    }

    /* 2. 初始化LED */
    /* 寄存器地址映射 */
    IMX6U_CCM_CCGR1     = ioremap(ledsource[0]->start, ressize[0]);
    SW_MUX_GPIO1_IO03   = ioremap(ledsource[1]->start, ressize[1]);
    SW_PAD_GPIO1_IO03   = ioremap(ledsource[2]->start, ressize[2]);
    GPIO1_DR            = ioremap(ledsource[3]->start, ressize[3]);
    GPIO1_GDIR          = ioremap(ledsource[4]->start, ressize[4]);

    /* 使能GPIO1时钟 */
    val = readl(IMX6U_CCM_CCGR1);
    val &= ~(3 << 26); /* 清除以前的设置 */
    val |= (3 << 26);  /* 设置新值 */
    writel(val, IMX6U_CCM_CCGR1);

    /* 设置GPIO1_IO03 的复用功能,
    * 将其复用为 GPIO1_IO03,最后设置IO属性 
    */
   writel(5, SW_MUX_GPIO1_IO03);

   /* 寄存器 SW_PAD_GPIO1_IO03 设置IO属性 */
   writel(0x10B0, SW_PAD_GPIO1_IO03);

   /* 设置 GPIO1_IO03 为输出功能 */
    val = readl(GPIO1_GDIR);
    val &= ~(1 << 3); /* 清除以前的设置 */
    val |= (1 << 3);  /* 设置新值 */
    writel(val, GPIO1_GDIR);

    /* 默认关闭 LED */
    val = readl(GPIO1_DR);
    val |= (1 << 3);
    writel(val, GRIO1_DR);

    /* 注册字符设备驱动 */
    if(newchrled.major) { // 定义了设备号
        newchrled.devid = MKDEV(newchrled.major, 0);
        register_chrdev_region(newchrled.devid, LEDDEV_CNT, 
                               LEDDEV_NAME);
    } else { // 没有定义设备号
        alloc_chrdev_region(&newchrled.devid, 0, LEDDEV_CNT,
                            LEDDEV_NAME); // 申请设备号
        newchrled.major = MAJOR(newchrled.devid);   //获取主设备号
        newchrled.minor = MINOR(newchrled.devid);   //获取次设备号
    }
    printk("newcheled major=%d,minor=%d\r\n", newchrled.major, 
                newchrled.minor);

    /* 2. 初始化cdev */
    newchrled.cdev.owner = THIS_MODULE,
    cdev_init(&newchrled.cdev, &led_fops);

    /* 3. 添加一个cdev */
    cdev_add(&newchrled.cdev, newchrled.devid, LEDDEV_CNT);

    /* 4. 创建类 */
    newchrled.class = class_create(THIS_MODULE, LEDDEV_NAME);
    if(IS_ERR(newchrled.class)) {
        return PTR_ERR(newchrled.class);
    }

    /* 5. 创建设备 */
    newchrled.device = device_create(newchrled.class, NULL, 
                        newchrled.devid, NULL, LEDDEV_NAME);
    if(IS_ERR(newchrled.device)) {
        return PTR_ERR(newchrled.device);
    }
    return 0;
}

/*
* @description   : 移除platform驱动的时候会执行此函数
* @param - dev   : platform 设备
* @return        : 0 成功; 其他负值 失败
*/
static void led_remove(void)
{
    /* 取消映射 */
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    /* 注销字符设备 */
    cdev_del(&newchrled.cdev);  //删除cdev
    unregister_chrdev_region(newchrled.devid, LEDDEV_CNT);

    device_destroy(leddev.class, leddev.devid);
    class_destory(leddev.class);
    return 0;
}

/* platform 驱动结构体*/
static struct platform_driver led_driver = {
    .driver = {
        .name = "imx6ul-led",   /* 驱动名字，用于和设备匹配 */
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
static int __exit leddriver_exit(void)
{
    platform_driver_unregister(&led_driver);
}

module_init(leddriver_init);
module_exit(leddriver_exit);
MOUDLE_LICENSE("GPL");
MOUDLE_AUTHOR("jack");

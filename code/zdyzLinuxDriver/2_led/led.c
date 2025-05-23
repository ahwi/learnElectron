#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define LED_MAJOR   200     /* 主设备号 */
#define LED_NAME    "led"   /* 设备名字 */

#define LEDOFF      0   /* 关灯 */
#define LEDON       1   /* 开灯 */

/* 寄存器物理地址 */
#define CCM_CCGR1_BASE              (0X020C406C)
#define SW_MUX_GPIO1_IO03_BASE      (0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE      (0X020E02F4)
#define GPIO1_DR_BASE               (0X0209C000)
#define GPIO1_GDIR_BASE             (0X0209C004)

/* 映射后的寄存器虚拟地址指针 */
static void __iomem *IMX6U_CCM_CCGR1
static void __iomem *SW_MUX_GPIO1_IO03
static void __iomem *SW_PAD_GPIO1_IO03
static void __iomem *GPIO1_DR
static void __iomem *GPIO1_GDIR

/*
* @description  : LED 打开/关闭
* @param -sta   : LEDON(0) 打开LED，LEDOFF(1) 关闭LED
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
* @description      : 打开设备
* @param - inode    : 传递给驱动的inode
* @param - filp     : 设备文件，file结构体有个叫做private_data的成员变量
                      一般在open的时候将 private_data 指向设备结构体
* @return       : 无
*/
static int led_open(struct inode *inode, struct file *filp)
{
    return 0;
}


/*
* @description      : 从设备读取数据
* @param - filp     : 要打开的设备文件（文件描述符）
* @param - buf      : 返回给用户空间的数据缓冲区
* @param - offt     : 相对于文件首地址的偏移
* @return           : 读取的字节数，如果为负值，表示读取失败 
*/
static ssize_t led_read(struct file *filp, char __user *buf,
                         size_t cnt, loff_t *offt)
{
    return 0;
}


/*
* @description      : 向设备写数据
* @param - filp     : 要打开的设备文件（文件描述符）
* @param - buf      : 要给设备写入的数据
* @param - cnt      : 要写入的数据长度
* @param - offt     : 相对于文件首地址的偏移
* @return           : 写入的字节数，如果为负值，表示写入失败
*/
static ssize_t led_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *offt)
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
    } else if(ledstat == LEDOFF) {
        led_switch(LEDOFF); /* 关闭LED灯 */
    }

    return 0;
}

/*
* @description      : 关闭/释放设备
* @param - filp     : 要关闭的设备（文件描述符）
* @return           : 0 成功; 其他 失败
*/
static int led_release(struct inode *inode, struct file *filp)
{
    return 0;
}

/* 设备操作函数 */
static struct file_operations led_fops = {
    .owner      = THIS_MODULE,
    .open       = led_open,
    .read       = led_read,
    .write      = led_write,
    .release    = led_release
}

/*
* @description      : 驱动入口函数
* @param            : 无
* @return           : 无
*/
static int __init led_init(void)
{
    int retvalue = 0;
    u32 val = 0;

    /* 初始化LED */
    /* 1. 寄存器地址映射 */
    IMX6U_CCM_CCGR1     = ioremap(CCM_CCGR1_BASE, 4);
    SW_MUX_GPIO1_IO03   = ioremap(SW_MUX_GPIO1_IO03_BASE, 4);
    SW_PAD_GPIO1_IO03   = ioremap(SW_PAD_GPIO1_IO03_BASE, 4);
    GPIO1_DR            = ioremap(GPIO1_DR_BASE, 4);
    GPIO1_GDIR          = ioremap(GPIO1_GDIR_BASE, 4);

    /* 2. 使能GPIO1时钟 */
    val = readl(IMX6U_CCM_CCGR1);
    val &= ~(3 << 26);  /* 清除以前的设置 */
    val |= (3 << 26);   /* 设置新值 */
    writel(val, IMX6I_CCM_CCGR1);

    /* 3. 设置GPIO1_IO03的复用时钟,将其复用为 
    *     GPIO1_IO03,最后设置IO属性
    */
    writel(5, SW_MUX_GPIO1_IO03);

    /* 寄存器 SW_MUX_GPIO1_IO03 设置IO属性 */
    writel(0x10B0, SW_PAD_GPIO1_IO03);

    /* 4. 设置 GPIO1_IO03 为输出功能*/
    val = readl(GPIO1_GDIR);
    val &= ~(1 << 3);  /* 清除以前的设置 */
    val |= (1 << 3);   /* 设置为输出 */
    writel(val, GPIO1_GDIR);

    /* 5. 默认关闭LED */
    val = readl(GPIO1_DR);
    val |= (1 << 3);
    writel(val, GPIO1_DR);

    /* 6. 注册字符设备驱动 */
    retvalue = register_chrdev(LED_MAJOR, LED_NAME, &led_fops);
    if(retvalue < 0) {
        printk("register chrdev failed!\r\n");
        return -EIO;
    }
    return 0;
}


/*
* @description      : 驱动出口函数
* @param            : 无
* @return           : 无
*/
static void __exit led_exit(void)
{
    /* 取消映射 */
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    /* 注销字符设备驱动 */
    unregister_chrdev(LED_MAJOR, LED_NAME);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jack");

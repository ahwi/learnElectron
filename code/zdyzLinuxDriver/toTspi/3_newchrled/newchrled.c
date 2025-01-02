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
//#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <linux/fs.h>

/*
* 描述： 使用GPIO3_B4 引脚来点亮LED
* SYS_GRF 0xFDC60000
* GRF_GPIO3B_IOMUX_H AddressBase(0xFDC6000) + offset (0x004C)
* GPIO_SWPORT_DR_L  数据寄存器
* GPIO_SWPORT_DDR_L 方向控制寄存器
*/

#define NEWCHRLED_CNT       1               /* 设备号个数 */
#define NEWCHRLED_NAME      "newchrled"     /* 名字 */
#define LEDOFF              0               /* 关灯 */ 
#define LEDON               1               /* 开灯 */ 

/* 寄存器物理地址 */
#define SYS_GRF             0xFDC60000
#define GRF_GPIO3B_IOMUX_H  (SYS_GRF + 0x004C)
#define GIPO3_BASE          0xFE760000
#define GIPO3_SWPORT_DR_L   (GIPO3_BASE + 0x0000)
#define GIPO3_SWPORT_DDR_L  (GIPO3_BASE + 0x0008)

/* 映射后的寄存器虚拟地址指针 */
unsigned int *virt_gpio3b_iomux;
unsigned int *virt_gpio3_ddr;
unsigned int *virt_gpio3_dr;

/* newcharled 设备结构体 */
struct newchrled_dev{
    dev_t devid;            /* 设备号 */
    struct cdev cdev;       /* cdev */
    struct class *class;    /* 类 */
    struct device *device;  /* 设备 */
    int major;              /* 主设备号 */
    int minor;              /* 次设备号 */
};

struct newchrled_dev newchrled;     /* led 设备 */

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
        *virt_gpio3_dr |= ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));
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
    filp->private_data = &newchrled;    /* 设置私有数据 */
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
ssize_t led_read(struct file *filp, char __user *buf, 
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
static struct file_operations newchrled_fops = {
    //.owner  = THIS_MODULE,
    .open   = led_open,
    .read   = led_read,
    .write  = led_write,
    .release = led_release
};


/*
* @description   : 驱动入口函数
* @param         : 无
* @return        : 0 成功; 其他 失败
*/
static int __init led_init(void)
{
    //u32 val = 0;

    /* 初始化LED */
    /* 1. 寄存器地址映射 */
    virt_gpio3b_iomux = ioremap(GRF_GPIO3B_IOMUX_H, 4);
    if(virt_gpio3b_iomux == NULL) {
        printk("ioremap iomux register error!\r\n");
        return -ENOMEM;
    }

    virt_gpio3_ddr = ioremap(GIPO3_SWPORT_DDR_L, 4);
    if(virt_gpio3_ddr == NULL) {
        printk("ioremap ddr register error!\r\n");
        return -ENOMEM;
    }

    virt_gpio3_dr = ioremap(GIPO3_SWPORT_DR_L, 4);
    if(virt_gpio3_dr == NULL) {
        printk("ioremap dr register error!\r\n");
        return -ENOMEM;
    }

    /* 2. 使能GPIO1时钟 */
    // val = readl(IMX6U_CCM_CCGR1);
    // val &= ~(3 << 26); /* 清除以前的设置 */
    // val |= (3 << 26);  /* 设置新值 */
    // writel(val, IMX6U_CCM_CCGR1);

    /* 3. 设置GPIO1_IO03 的复用功能,
    * 将其复用为 GPIO1_IO03,最后设置IO属性 
    */
    // GRF_GPIO3B_IOMUX_H: 2~0位 写0(gpio功能); 16~18 写1(写使能)  
    *virt_gpio3b_iomux |= ((0x7 << (16+0)) + (0x0 << 0));

    /* 4. 设置 GPIO1_IO03 为输出功能 */
    // GPIO_SWPORT_DRR_L：设置GPIO3B4为输出. 
    // 12位写1(设置为输出);28位写1(写使能)
    *virt_gpio3_ddr |= ((0x1 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4))); 

    /* 5. 默认关闭 LED */
    // GPIO_SWPORT_DR_L：设置GPIO3B4为输出低电平(LED灭). 
    // 12位写0（设置输出低电平）;28位写1(写使能)
    *virt_gpio3_dr |= ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));

    /* 注册字符设备驱动 */
    if(newchrled.major) { // 定义了设备号
        newchrled.devid = MKDEV(newchrled.major, 0);
        register_chrdev_region(newchrled.devid, NEWCHRLED_CNT, 
                               NEWCHRLED_NAME);
    } else { // 没有定义设备号
        alloc_chrdev_region(&newchrled.devid, 0, NEWCHRLED_CNT,
                            NEWCHRLED_NAME); // 申请设备号
        newchrled.major = MAJOR(newchrled.devid);   //获取主设备号
        newchrled.minor = MINOR(newchrled.devid);   //获取次设备号
    }
    printk("newcheled major=%d,minor=%d\r\n", newchrled.major, 
                newchrled.minor);

    /* 2. 初始化cdev */
    newchrled.cdev.owner = THIS_MODULE,
    cdev_init(&newchrled.cdev, &newchrled_fops);

    /* 3. 添加一个cdev */
    cdev_add(&newchrled.cdev, newchrled.devid, NEWCHRLED_CNT);

    /* 4. 创建类 */
    newchrled.class = class_create(THIS_MODULE, NEWCHRLED_NAME);
    if(IS_ERR(newchrled.class)) {
        return PTR_ERR(newchrled.class);
    }

    /* 5. 创建设备 */
    newchrled.device = device_create(newchrled.class, NULL, 
                        newchrled.devid, NULL, NEWCHRLED_NAME);
    if(IS_ERR(newchrled.device)) {
        return PTR_ERR(newchrled.device);
    }
    return 0;
}

/*
* @description   : 驱动出口函数
* @param         : 无
* @return        : 无
*/
static void __exit led_exit(void)
{
    /* 取消映射 */
    // GPIO_SWPORT_DR_L：设置GPIO3B4为输出低电平(LED灭). 
    // 12位写0（设置输出低电平）;28位写1(写使能)
    *virt_gpio3_dr |= ((0x0 << (8*1 + 4)) + (0x1 << (16 + 8*1 +4)));
    iounmap(virt_gpio3b_iomux);
    iounmap(virt_gpio3_ddr);
    iounmap(virt_gpio3_dr);

    /* 注销字符设备 */
    cdev_del(&newchrled.cdev);  //删除cdev
    unregister_chrdev_region(newchrled.devid, NEWCHRLED_CNT);

    device_destroy(newchrled.class, newchrled.devid);
    class_destroy(newchrled.class);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jack");
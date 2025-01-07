/*
* LED灯控制 
* 引脚为 GPIO3_B4
* 该版本 使用内核提供的api来控制GPIO，如: 
* gpio_request/gpio_direction_output/gpio_set_value
*/

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
#include <linux/of_address.h>
#include <linux/of_gpio.h>


#define LED_NODE_PATH  "/myled"         /* 设备树路径 */
#define LED_NODE_PROPERTY_GPIO "gpios"   /* gpio属性 */

#define DTSLED_CNT      1           /* 设备号个数 */
#define DTSLED_NAME     "dtsled"    /* 名字 */
#define LEDOFF          0           /* 关灯 */
#define LEDON           1           /* 开灯 */

int gpionum = -1;

/* dtsled 设备结构体 */
struct dtsled_dev {
    dev_t devid;            /* 设备号 */
    struct cdev cdev;        /* cdev */
    struct class *class;     /* 类 */
    struct device *device;   /* 设备 */
    int major;              /* 主设备号 */
    int minor;              /* 次设备号 */
    struct device_node *nd; /* 设备节点 */
};

struct dtsled_dev dtsled;   /* led设备 */

static int led_open(struct inode *inode, struct file *filp);
ssize_t led_read(struct file *filp, char __user *buf, 
                        size_t cnt, loff_t *offt);
ssize_t led_write(struct file *filp, const char __user *buf,
                         size_t cnt, loff_t *offt);
static int led_release(struct inode *node, struct file *filp);

static struct file_operations dtsled_fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .read = led_read,
    .write = led_write,
    .release = led_release
};

/*
* @description  : LED 打开/关闭
* @param - sta  : LEDN(0) 打开LED, LEDOFF(1) 关闭LED
* @return       : 无
*/
void led_switch(u8 sta)
{
    // u32 val = 0;
    if(sta == LEDON) {
        gpio_set_value(gpionum, 1); //设置高电平
    } else if(sta == LEDOFF) {
        gpio_set_value(gpionum, 0); //设置低电平
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
    filp->private_data = &dtsled;    /* 设置私有数据 */
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


/*
* @description  : 驱动入口函数
* @param        : 无
* @return       : 0 成功; 其他 失败
*/
static int __init led_init(void)
{
    int ret;
    // u32 regdata[14];
    const char *str;
    struct property *proper;

    /* 获取设备上中的属性数据 */
    /* 1. 获取设备节点 */
    dtsled.nd = of_find_node_by_path(LED_NODE_PATH);
    if(dtsled.nd == NULL) {
        printk("node can not found!\r\n");
        return -EINVAL;
    } else {
        printk("node has been found!\r\n");
    }

    /* 2. 获取compatible 属性内容 */
    proper = of_find_property(dtsled.nd, "compatible", NULL);
    if(proper == NULL) {
        printk("compatible property find failed\r\n");
    } else {
        printk("compatible = %s\r\n", (char*)proper->value);
    }

    /* 3. 获取status属性内容 */
    ret = of_property_read_string(dtsled.nd, "status", &str);
    if(ret < 0) {
        printk("status read failed!\r\n");
    } else {
	    printk("status = %s\r\n", str);
    }

    /* 获取gpio编号 */
    gpionum = of_get_named_gpio(dtsled.nd, LED_NODE_PROPERTY_GPIO, 0);
    if(gpionum < 0) {
        printk("get property %s failed!\r\n", LED_NODE_PROPERTY_GPIO);
        return -EINVAL;
    }
    printk("gpionum:%d\r\n", gpionum);

    /* 初始化LED */
    /* 申请GPIO */
    if(gpio_request(gpionum, NULL)) {
        printk("request gpio failed!\r\n");
        return -EINVAL;
    }

    /* 设置GPIO为输出: 默认为低电平 led灯灭 */
    if(gpio_direction_output(gpionum, 0)) {
        printk("set gpio direction failed!\r\n");
        return -EINVAL;
    }

    /* 注册字符设备驱动 */
    if(dtsled.major) {   //定义了设备号
        dtsled.devid = MKDEV(dtsled.major, 0);
        register_chrdev_region(dtsled.devid, DTSLED_CNT, DTSLED_NAME);
    } else {
        // 没有定义设备号
        alloc_chrdev_region(&dtsled.devid, 0, DTSLED_CNT, DTSLED_NAME); //申请设备号
        dtsled.major = MAJOR(dtsled.devid); //获取主设备号
        dtsled.minor = MAJOR(dtsled.devid); //获取次设备号
    }
    printk("dtsled major=%d,minor=%d\r\n", dtsled.major, dtsled.minor);

    /* 2. 初始化cdev */
    dtsled.cdev.owner = THIS_MODULE;
    cdev_init(&dtsled.cdev, &dtsled_fops);

    /* 3. 添加一个cdev*/
    cdev_add(&dtsled.cdev, dtsled.devid, DTSLED_CNT);

    /* 4. 创建类 */
    dtsled.class = class_create(THIS_MODULE, DTSLED_NAME);
    if(IS_ERR(dtsled.class)) {
        return PTR_ERR(dtsled.class);
    }

    /* 5. 创建设备 */
    dtsled.device = device_create(dtsled.class, NULL, 
                    dtsled.devid, NULL, DTSLED_NAME);
    if(IS_ERR(dtsled.class)) {
        return PTR_ERR(dtsled.class);
    }
    return 0;
}

/*
* @description  : 驱动出口函数
* @param        : 无
* @return       : 无
*/
static void __exit led_exit(void)
{
    /* 关闭led灯 */
    gpio_set_value(gpionum, 0);
    /* 释放gpio资源 */
    gpio_free(gpionum);

    /* 注销字符设备 */
    cdev_del(&dtsled.cdev); //删除cdev
    unregister_chrdev_region(dtsled.devid, DTSLED_CNT);

    device_destroy(dtsled.class, dtsled.devid);
    class_destroy(dtsled.class);
}

module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("jack");

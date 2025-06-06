#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define CHRDEVBASE_MAJOR    200             //主设备号
#define CHRDEVBASE_NAME     "chrdevbase"    //名字

static char readbuf[100]; /* 读缓冲区 */
static char writebuf[100]; /* 写缓冲区 */
static char kerneldata[] = {"kernel data!"};

static int chrdevbase_open(struct inode *inode, struct file *filp)
{
    // printk("chrdevbase_open\r\n");
    return 0;
}

static int chrdevbase_release(struct inode *inode, struct file *filp)
{
    // printk("chrdevbase_release\r\n");
    return 0;
}

static ssize_t chrievbase_read(struct file *filp, __user char *buf, size_t count, size_t loff_t *ppos)
{
    int ret = 0;
    // printk("chrdevbase_read\r\n");
    memcpy(readbuf, kerneldata, sizeof(kerneldata));
    ret = copy_to_user(buf, readbuf, count);
    if(ret == 0) {

    } else {

    }
    return 0;
}

static ssize_t chrievbase_write(struct file *filp, __user char *buf, size_t count, size_t loff_t *ppos)
{
    // printk("chrdevbase_write\r\n");
    ret = copy_from_user(writebuf, buf, count);
    if(ret == 0) {
        printk("kernel receive data:%s\r\n", writebuf);
    } else {

    }
    return 0;
}

static struct file_operations chrdevbase_fops = {
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .release = chrdevbase_release,
    .read = chrievbase_read,
    .write = chrievbase_write,
};

static int __init chrdevbase_init(void)
{
    int ret = 0;
    printk("chrdevbase_init\r\n");

    /* 注册字符设备 */
    ret = register_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME, &chrdevbase_fops);
    if(ret < 0) {
        printk("chrdevbase init failed!\r\n");
    }
    return 0;
}

static void __exit chrdevbase_exit(void)
{
    printk("chrdevbase_exit\r\n");

    /* 注销字符设备 */
    unregister_chrdev(CHRDEVBASE_MAJOR, CHRDEVBASE_NAME);
}

/*
模块入口与出口
*/
module_init(chrdevbase_init);  /* 入口 */
module_exit(chrdevbase_exit);  /* 出口 */
# 正点原子-Linux驱动学习

学习资料：

* `i.MX6ULL Linux阿尔法开发板 `：http://www.openedv.com/docs/boards/arm-linux/zdyz-i.mx6ull.html

* 网盘资料：
  - 配套 `Linux之Ubuntu入门篇 `视频链接： [https://pan.baidu.com/s/1uTu9-Fy2gVWSUxhoUsqZCQ ](https://pan.baidu.com/s/1uTu9-Fy2gVWSUxhoUsqZCQ)提取码：jmoz
  - 配套 `Linux之ARM裸机篇 `视频链接： [https://pan.baidu.com/s/1TjaQSuRZK0OiUCqc6S0SiQ ](https://pan.baidu.com/s/1TjaQSuRZK0OiUCqc6S0SiQ)提取码：r27n
  - 配套 `Linux之系统移植和文件系统构建篇 `视频链接： [https://pan.baidu.com/s/1vdUOu0uF8VXoLN51boJyHw ](https://pan.baidu.com/s/1vdUOu0uF8VXoLN51boJyHw)提取码：d2rz
  - 配套 `Linux之驱动开发篇 `视频链接： [https://pan.baidu.com/s/1JU95JHG-v7MKvkvXsMNhdw ](https://pan.baidu.com/s/1JU95JHG-v7MKvkvXsMNhdw)提取码：n3ju
  - 配套 `Linux之网络环境搭建篇 `视频链接： [https://pan.baidu.com/s/1K_cwr2Trq2lvWlXju8bq8Q ](https://pan.baidu.com/s/1K_cwr2Trq2lvWlXju8bq8Q)提取码：5sfw
  - 配套 `Linux之Qt5（C++）篇 `视频链接： [https://pan.baidu.com/s/1Z_AlP2M1H8R_TjIWN-Pk0g ](https://pan.baidu.com/s/1Z_AlP2M1H8R_TjIWN-Pk0g)提取码：2df1
  - 配套 `Linux之C应用开发篇 `视频链接： [https://pan.baidu.com/s/19fOMRvPaPbCokOj5vkYsxA ](https://pan.baidu.com/s/19fOMRvPaPbCokOj5vkYsxA)提取码：j5dj

## 第1讲 Linux驱动开发与裸机开发区别

## 第2讲 字符设备驱动开发基础实验

略

## 第3讲 字符设备驱动框架

### 1. 字符设备驱动框架

字符设备驱动的编写主要就是驱动对应的open、close、read等函数，其实就是file_operations结构体的成员变量的实现。

### 2. 驱动模块的加载与卸载

Linux驱动程序可以编译到kernel里面，也就是zImage，也可以编译为模块`.ko`。

编写驱动的基本流程：

* 编译驱动的时候需要用到Linux内核源码，因此需要解压缩Linux内核源码，编译Linux内核源码，得到zImage和`.dtb`。需要使用编译后得到的zImage和dtb启动系统。

* 从SD卡启动，SD卡烧写了uboot。uboot通过tftp从ubuntu里面获取zimage和dtb，rootfs也是通过nfs挂载。

* 设置bootcmd和bootargs

  ```txt
  bootargs=console=ttymxc0,115200rw root=/dev/nfs nfsroot=192.168.1.66:/home/zzk/linux/nfs/rootfs ip=192.168.1.50:192.168.1.66:192.168.1.1:255.255.255.0::eth0:off
  
  bootcmd=tftp 80800000 zImage;tftp 83000000 imx6ull-alientek emmc.dtb;bootz 80800000 - 83000000;
  ```

* 将编译出来的`.ko`文件放到根文件系统里面。加载驱动会用到加载命令；insmod、modprobe

  > 对于新的模块，使用modprobe加载的时候需要先调用一下depmo命令。

* 驱动模块加载成功后，可以使用lsmod查看一下
* 卸载模块使用rmmod命令

### 3. 字符设备的注册与注销

1. 我们需要向系统注册一个字符设备，使用函数`register_chrdev`
2. 卸载驱动的时候需要注销掉前面注册的字符设备，使用函数`unregister_chrdeb`

### 4. 设备号

1. Linux内核使用`dev_t`表示设备号

   ```c
   typedef __kernel_dev_t dev_t;
   typedef __u32 __kernel_dev_t;
   typedef unsigned int __u32;
   ```

2. Linux内核将设备号分为两部分：主设备号（前12位）和次设备号（后20位）。

3. 设备号的相关操作：

   * 获取主设备号：`MAJOR(dev_t)`
   * 获取次设备号：`MAJOR(dev_t)`
   * 构造设备号：`MKDEV(major,minor)`

### 5. `file_operations`的具体实现

`file_operations`结构体

### 6. 字符设备驱动框架搭建

### 7. 应用程序编写

Linux下一切皆文件，使用open、read、write文件操作驱动设备文件

### 8. 测试

1. 把新的驱动拷贝的开发板并加载驱动

   `modprobe chrdevbase.ko`

2. 进入/dev查看设备文件`/dev/chrdevbase`。需要先创建设备节点`mkmod /dev/chrdevbase c 200 0`

3. 测试

   `./chrdevbaseAPP /dev/chrdevbase`

### 9. chrdevbase 设备驱动的完善

添加对驱动设备的读写操作，从驱动里面读取字符串，向驱动里面写数据。

* 驱动给应用传递数据：`copy_to_user`函数
* 应用给驱动传递数据：`copy_from_user`函数

### 3. 实验

#### 实验1：第一个字符设备驱动

* 创建工程目录：

    ```txt
    cd ~/linux/IMX6ULL/Linux_Drivers
    mkdir 1_chrdevbase
    cd 1_chrdevbase
    ```

* 创建`chrdevbase.c`文件

  ​	参考代码：`linux/linux-imx-rel_imx_4.1.15_2.1.0_ga_alientek`

  ​	`TODO:4:05`

* 设置vscode的头文件路径：`TODO:19:28`

    ```txt
    {内核位置}/include
    {内核位置}/arch/arm/include
    {内核位置}/arch/arm/include/generated
    ```

	> 内核源码的位置：`第3期 系统移植和根文件系统\第3期 程序源码.rar`

* 编译：
  * `make`
  * 确认是否有生成`chrdevbase.ko`
* 测试：使用`modprobe`加载驱动

#### 实验2：添加设备号和file_operation操作

* 查看未使用的主设备号：

  ```base
  # 查看已使用的主设备号
  cat /proc/devices
  Character devices底下
  # 使用一个未在这边出现的号码
  ```

* 完善`chrdevbase.c`代码

  * 填写设备号
  * 添加`file_operations`代码
  * 添加设备的注册与注销函数

* 添加调用代码`chrdevbaseAPP.c`

  编译：

  ```base
  arm-linux-gnueabihf-gcc chrdevbaseAPP.c -o chrdevbaseAPP
  ```

#### 实验3：用户对驱动的读写

## 第4讲 嵌入式Linux LED驱动开发实验

### 1. 地址映射

1. 裸机LED灯实验就是操作6ULL的寄存器
2. Linux驱动开发也是操作寄存器，Linux不能直接对寄存器物理地址进行读写操作，因为Linux会使用MMU内存管理单元，需要获得物理地址对应的虚拟地址，然后再进行操作。
   * ioremap函数：将物理地址映射到虚拟地址。
   * iounmap函数：释放掉ioremap函数所作的映射。

### 2. 驱动程序编写

创建`2_led/led.c`文件：

1. 初始化时钟、GPIO等
2. 注册字符设备驱动
3. 注销字符设备驱动等

> 如果你烧写的是正点原子提供的linux内核，这个时候LED默认被配置为心跳灯，必须关闭心跳灯才能测试该程序。具体参考书籍：P1093

### 3. 应用程序编写

编写测试驱动的程序：`ledApp.c`

### 4. 测试

1. 加载驱动

   ```shell
   depmod	//第一次加载驱动的时候需要运行此命令
   modprobe led.ko	//加载驱动
   ```

2. 创建设备节点：

   ```shell
   mknod /dev/led c 200 0
   ```

3. 运行测试程序：

   ```shell
   ./ledApp /dev/led 1	//打开LED灯
   ./ledApp /dev/led 0	//关闭LED灯
   ```

4. 卸载命令：

   ```shell
   rmmod led.ko
   ```

## 第5讲 新字符设备驱动实验

### 1. 新的字符设备注册方法

#### 1.1 新的设备号申请和释放函数

register_chrdev 和 unregister_chrdev 这两个函数是老版本驱动使用的函数
register_chrdev 两个问题：
    a. 需要我们事先确定好哪些主设备号没有使用。
    b. 会将一个主设备号下的所有次设备号都使用掉

新的申请和释放设备号函数：

* 申请设备号：

  * 如果没有指定设备号的话就使用如下函数来申请设备号：

    ```c
    int alloc_chrdev_region(dev_t *dev, unsigned baseminor, unsigned count, const char *name)
    ```

  * 如果给定了设备的主设备号和次设备号就使用如下所示函数来注册设备号即可：

    ```c
    int register_chrdev_region(dev_t from, unsigned count, const char *name)
    ```

  * 释放设备号

    ```c
    void unregister_chrdev_region(dev_t from, unsigned count)
    ```

使用示例：

```c
/* 申请设备号 */
int major; /* 主设备号 */
int minor; /* 次设备号 */
dev_t devid; /* 设备号 */

if (major) { /* 定义了主设备号 */
    devid = MKDEV(major, 0); /* 大部分驱动次设备号都选择 0*/
    register_chrdev_region(devid, 1, "test");
} else { /* 没有定义设备号 */
    alloc_chrdev_region(&devid, 0, 1, "test"); /* 申请设备号 */
    major = MAJOR(devid); /* 获取分配号的主设备号 */
    minor = MINOR(devid); /* 获取分配号的次设备号 */
}

/*************************************************/
/* 注销设备号 */
unregister_chrdev_region(devid, 1); /* 注销设备号 */
```

#### 1.2 新的字符设备注册方法

<font color=blue>1. 字符设备结构</font>

在 Linux 中使用 cdev 结构体表示一个字符设备，cdev 结构体在 include/linux/cdev.h 文件中：

```c
struct cdev {
    struct kobject kobj;
    struct module *owner;
    const struct file_operations *ops;
    struct list_head list;
    dev_t dev;
    unsigned int count;
};
```

两个重要的成员变量：

* ops：字符设备文件操作集合函数
* dev：设备号

<font color=blue>cdev_init 函数 </font>

定义好 cdev 变量以后就要使用 cdev_init 函数对其进行初始化，cdev_init 函数原型如下：

```c
void cdev_init(struct cdev *cdev, const struct file_operations *fops)
```

<font color=blue>cdev_add 函数 </font>

cdev_add 函数用于向 Linux 系统添加字符设备(cdev 结构体变量)，首先使用 cdev_init 函数完成对 cdev 结构体变量的初始化，然后使用 cdev_add 函数向 Linux 系统添加这个字符设备。

cdev_add 函数原型如下：

```c
int cdev_add(struct cdev *p, dev_t dev, unsigned count)
```

* p：指向要添加的字符设备（cdev结构体变量）
* dev：设备所使用的设备号
* count：要添加的设备数量 

示例代码：

```c
struct cdev testcdev;

/* 设备操作函数 */
static struct file_operations test_fops = {
    .owner = THIS_MODULE,
    /* 其他具体的初始项 */
};

testcdev.owner = THIS_MODULE;
cdev_init(&testcdev, &test_fops); /* 初始化 cdev 结构体变量 */
cdev_add(&testcdev, devid, 1); /* 添加字符设备 */
```

上面就是新的注册字符设备代码段，Linux 内核中大量的字符设备驱动都是采用这种方法向 Linux 内核添加字符设备。如果在刚才分配设备号的程序，那么就它们一起实现的就是函数 register_chrdev 的功能。

<font color=blue>cdev_del 函数 </font>

卸载驱动的时候一定要使用 cdev_del 函数从 Linux 内核中删除相应的字符设备，cdev_del 函数原型如下：

```c
void cdev_del(struct cdev *p)
```

cdev_del 和 unregister_chrdev_region 这两个函数合起来的功能相当于 unregister_chrdev 函数。

### 2. 自动创建设备节点

前面的实验中，modprobe加载驱动后还需要使用命令mkmod手动创建设备节点，本节讲解驱动中实现自动创建设备节点的功能，在modprobe加载驱动时自动创建设备节点（即在/dev目录下自动创建对应的设备文件）

#### 2.1 **mdev** 机制

udev 是一个用户程序，在 Linux 下通过 udev 来实现设备文件的创建与删除，udev 可以检测系统中硬件设备状态，可以根据系统中硬件设备状态来创建或者删除设备文件。比如使用modprobe 命令成功加载驱动模块以后就自动在/dev 目录下创建对应的设备节点文件,使用rmmod 命令卸载驱动模块以后就删除掉/dev 目录下的设备节点文件。

使用 busybox 构建根文件系统的时候，busybox 会创建一个 udev 的简化版本—mdev，所以在嵌入式 Linux 中我们使用 mdev 来实现设备节点文件的自动创建与删除，Linux 系统中的热插拔事件也由 mdev 管理，在/etc/init.d/rcS 文件中如下语句：

```shell
echo /sbin/mdev > /proc/sys/kernel/hotplug
```

#### 2.2 创建和删除类

自动创建设备节点的工作是在驱动程序的入口函数中完成的，一般在 cdev_add 函数后面添加自动创建设备节点相关代码。

创建class结构体对象

```c
struct class *class_create (struct module *owner, const char *name)
```

* owner：一般为`THIS_MODULE`
* name：类的名字
* 返回值：指向结构体 class 的指针，也就是创建的类

卸载驱动程序的时候需要删除掉类，类删除函数为 class_destroy：

```c
void class_destroy(struct class *cls);
```

#### 2.3 创建设备

创建类后还需要在类下创建一个设备，device_create函数就是在类下面创建设备：

```c
struct device *device_create(struct class *class, 
						     struct device *parent,
						     dev_t devt, 
						     void *drvdata, 
						     const char *fmt, ...)
```

* class：设备要创建在哪个类下面
* parent：父设备，一般为NULL
* devt：设备号
* drvdata：设备可能会使用的一些数据，一般为NULL
* fmt：设备名字，如果设置 fmt=xxx 的话，就会生成/dev/xxx这个设备文件。
* 返回值：创建好的设备。

卸载驱动的时候需要删除掉创建的设备，设备删除函数为 device_destroy：

```c
void device_destroy(struct class *class, dev_t devt)
```

#### 2.4 示例代码

`创建/删除类和创建设备`

```c
struct class *class; /* 类 */ 
struct device *device; /* 设备 */
dev_t devid; /* 设备号 */ 

/* 驱动入口函数 */
static int __init led_init(void)
{
    /* 创建类 */
    class = class_create(THIS_MODULE, "xxx");
    /* 创建设备 */
    device = device_create(class, NULL, devid, NULL, "xxx");
    return 0;
}

/* 驱动出口函数 */
static void __exit led_exit(void)
{
    /* 删除设备 */
    device_destroy(newchrled.class, newchrled.devid);
    /* 删除类 */
    class_destroy(newchrled.class);
}

module_init(led_init);
module_exit(led_exit);
```

### 3. 设置文件私有数据

每个硬件设备都有一些属性，比如主设备号(dev_t)，类(class)、设备(device)、开关状态(state)等等，在编写驱动的时候你可以将这些属性全部写成变量的形式，如下所示：

```c
dev_t devid; /* 设备号 */
struct cdev cdev; /* cdev */
struct class *class; /* 类 */
struct device *device; /* 设备 */
int major; /* 主设备号 */
int minor; /* 次设备号 */
```

这样比较杂乱，最好写成结构体更整洁，并且编写驱动 open 函数的时候将设备结构体作为私有数据添加到设备文件中。

在 open 函数里面设置好私有数据以后，在 write、read、close 等函数中直接读取 private_data即可得到设备结构体。

示例代码：`设备结构体作为私有数据`

```c
struct test_dev{
    dev_t devid; /* 设备号 */
    struct cdev cdev; /* cdev */
    struct class *class; /* 类 */
    struct device *device; /* 设备 */
    int major; /* 主设备号 */
    int minor; /* 次设备号 */
};

struct test_dev testdev;

/* open 函数 */
static int test_open(struct inode *inode, struct file *filp)
{
    filp->private_data = &testdev; /* 设置私有数据 */
    return 0;
}
```

### 4. 实验：使用新的字符设备驱动

参考示例代码：`3_newchrled`

三个文件：

* `newchrled.c`
* `ledApp.c`
* `Makefile`

测试：

把编译出来的`newchrled.ko`和`ledApp`拷贝到开发板

加载驱动模块：

```shell
depmod	//第一次加载驱动的时候需要运行此命令
modprobe newchrled.ko //加载驱动
```

驱动加载成功以后会输出申请到的主设备号和次设备号

驱动加载成功以后会自动在/dev 目录下创建设备节点文件/dev/newchrdev

测试开关灯：

```shell
./ledApp /dev/newchrled 1 //打开 LED 灯
./ledApp /dev/newchrled 0 //关闭 LED 灯
```

卸载驱动：

```shell
rmmod newchrled.ko
```


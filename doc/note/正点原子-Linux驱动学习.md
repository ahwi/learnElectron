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




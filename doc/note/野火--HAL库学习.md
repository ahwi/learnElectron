

学习资料：

* 野火资料汇总：https://doc.embedfire.com/products/link/zh/latest/mcu/stm32/ebf_stm32f407_batianhu_v1_v2/download/stm32f407_batianhu_v1_v2.html
* STM32 HAL库开发实战指南--基于野火F4系列开发板：https://doc.embedfire.com/mcu/stm32/f4/hal_general/zh/latest/
* 视频：`https://www.bilibili.com/video/BV18X4y1M763`

## 第9讲 使用STM32CubeMX 新建工程

1. 设置固件包的安装位置

<img src="野火--HAL库学习.assets/image-20240426085417142.png" alt="image-20240426085417142" style="zoom:50%;" />

<img src="野火--HAL库学习.assets/image-20240426085518100.png" alt="image-20240426085518100" style="zoom:50%;" />

2. 有三种方式新建工程，我们这边选择第一种：

   <img src="野火--HAL库学习.assets/image-20240426085746333.png" alt="image-20240426085746333" style="zoom:80%;" />

3. 在弹出的框中输入芯片型号，并双击芯片型号：

   ![image-20240426090259293](野火--HAL库学习.assets/image-20240426090259293.png)

   <img src="野火--HAL库学习.assets/image-20240426090554998.png" alt="image-20240426090554998" style="zoom:50%;" />

4. 初始化LED灯引脚：PB0、PB1、PB5：

   <img src="野火--HAL库学习.assets/image-20240426091046215.png" alt="image-20240426091046215" style="zoom:80%;" />

   点击引脚：选择输出模式：

   <img src="野火--HAL库学习.assets/image-20240426091218500.png" alt="image-20240426091218500" style="zoom:80%;" />

   PB1和PB5也配置成输出模式，芯片左侧栏中会显示相应的引脚配置：

   ![image-20240426091451737](野火--HAL库学习.assets/image-20240426091451737.png)

   配置具体GPIO具体配置：

   <img src="野火--HAL库学习.assets/image-20240426091802274.png" alt="image-20240426091802274" style="zoom:80%;" />

5. 配置`SYS`的`Debug`选项为`Serial Wire`

   <img src="野火--HAL库学习.assets/image-20240426092003164.png" alt="image-20240426092003164" style="zoom:80%;" />

6. 其他窗口介绍（这边不需要配置）：

   a. 可选中间件：

   <img src="野火--HAL库学习.assets/image-20240426092303563.png" alt="image-20240426092303563" style="zoom:80%;" />

   b. 也可导入丰富的组件：

   ![image-20240426092411600](野火--HAL库学习.assets/image-20240426092411600.png)

   <img src="野火--HAL库学习.assets/image-20240426092448916.png" alt="image-20240426092448916" style="zoom: 50%;" />

7. 时钟配置：这边先使用默认即可：

   <img src="野火--HAL库学习.assets/image-20240426093101420.png" alt="image-20240426093101420" style="zoom:50%;" />



8. 工程配置：

   ![image-20240426093757338](野火--HAL库学习.assets/image-20240426093757338.png)

   ![image-20240426094017345](野火--HAL库学习.assets/image-20240426094017345.png)

   下载固件库包：`Help --> Manage embedded software packages`

   ![image-20240426094121274](野火--HAL库学习.assets/image-20240426094121274.png)

   选择相应的固件库包下载即可：

   <img src="野火--HAL库学习.assets/image-20240426094325460.png" alt="image-20240426094325460" style="zoom:50%;" />

9. 配置代码的生成规则：

   ![image-20240426095212405](野火--HAL库学习.assets/image-20240426095212405.png)

   <img src="野火--HAL库学习.assets/image-20240426095918123.png" alt="image-20240426095918123" style="zoom:80%;" />



10. 点击生成代码：

    ![image-20240426100158221](野火--HAL库学习.assets/image-20240426100158221.png)

11. 打开工程：

    ![image-20240426100304114](野火--HAL库学习.assets/image-20240426100304114.png)

<img src="野火--HAL库学习.assets/image-20240426100436611.png" alt="image-20240426100436611" style="zoom:50%;" />

12. 编译工程：

    可能会报编译器不可用

    ![image-20240426100633878](野火--HAL库学习.assets/image-20240426100633878.png)

    选择相应的编译器版本即可：

    <img src="野火--HAL库学习.assets/image-20240426100749513.png" alt="image-20240426100749513" style="zoom:80%;" />





**用户手册**

https://www.st.com/zh/development-tools/stm32cubemx.html#documentation

stm官方提供了软件操作的用户手册（在软件下载页面里）

![image-20240426092948690](野火--HAL库学习.assets/image-20240426092948690.png)
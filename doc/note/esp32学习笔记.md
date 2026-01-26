## esp32学习

参考资料：https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/get-started/index.html

## ESP-IDF V5.1

### 快速入门

#### 1. 目标

帮助用户：

- 安装 ESP-IDF 开发环境
- 编译并烧录第一个 Hello World 或 Blink 示例到 ESP32 开发板

#### 2. 所需硬件

* 一款 ESP32 开发板
* USB 数据线 (A 转 Micro-B)
* 电脑（Windows、Linux 或 macOS）

#### 3. 软件

在 ESP32 上使用 ESP-IDF，需安装以下软件：

* 设置 **工具链**，用于编译 ESP32 代码；
* **编译构建工具** —— CMake 和 Ninja 编译构建工具，用于编译 ESP32 **应用程序**；
* 获取 **ESP-IDF** 软件开发框架。该框架已经基本包含 ESP32 使用的 API（软件库和源代码）和运行 **工具链** 的脚本；

![image-20260112101200385](esp32学习笔记.assets/image-20260112101200385.png)

#### 4. 安装方式

- IDE 插件安装：
  - [Eclipse Plugin](https://github.com/espressif/idf-eclipse-plugin/blob/master/README.md)
  - [VSCode Extension](https://github.com/espressif/vscode-esp-idf-extension/blob/master/docs/tutorial/install.md)

* 手动安装：
  - [Windows Installer](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/get-started/windows-setup.html)
  - [Linux and macOS](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/get-started/linux-macos-setup.html)

> 这边选择手动安装windows installer，然后再安装vscode的esp-idf插件，然后选择本地的已安装esp-idf环境

#### 5. 编译第一个工程

> 备注：
>
> 1. 这边使用命令行编译的方式
>
> 2. ESP-IDF 编译系统不支持 ESP-IDF 路径或其工程路径中带有空格。

1. 创建工程：

   将 [get-started/hello_world](https://github.com/espressif/esp-idf/tree/1e54adca6f9/examples/get-started/hello_world) 工程复制至您本地的 `~/esp` 目录下

   ```cmd
   cd %userprofile%\esp
   xcopy /e /i %IDF_PATH%\examples\get-started\hello_world hello_world
   ```

2. 连接设备：

   * 将 ESP32 开发板连接到 PC，并查看开发板使用的串口。

3. 配置工程：

   * 进入 `hello_world` 目录，设置 ESP32 为目标芯片，然后运行工程配置工具 `menuconfig`。

       ```cmd
       cd %userprofile%\esp\hello_world
       idf.py set-target esp32
       idf.py menuconfig
       ```

   * 正确操作上述步骤后，系统将显示以下菜单

     ![image-20260112103044847](esp32学习笔记.assets/image-20260112103044847.png)

     可以通过此菜单设置项目的具体变量，包括 Wi-Fi 网络名称、密码和处理器速度等。

4. 编译工程：

   * 使用以下命令，编译烧录工程：

       ```cmd
idf.py build
       ```
   
   * 运行以上命令可以编译应用程序和所有 ESP-IDF 组件，接着生成引导加载程序、分区表和应用程序二进制文件。
   
       ```cmd
       $ idf.py build
       Running cmake in directory /path/to/hello_world/build
       Executing "cmake -G Ninja --warn-uninitialized /path/to/hello_world"...
       Warn about uninitialized values.
       -- Found Git: /usr/bin/git (found version "2.17.0")
       -- Building empty aws_iot component due to configuration
       -- Component names: ...
       -- Component paths: ...
       
       ... (more lines of build system output)
       
       [527/527] Generating hello_world.bin
       esptool.py v2.3.1
       
       Project build complete. To flash, run this command:
       ../../../components/esptool_py/esptool/esptool.py -p (PORT) -b 921600 write_flash --flash_mode dio --flash_size detect --flash_freq 40m 0x10000 build/hello_world.bin  build 0x1000 build/bootloader/bootloader.bin 0x8000 build/partition_table/partition-table.bin
       or run 'idf.py -p PORT flash'
       ```
   
   * 如果一切正常，编译完成后将生成 .bin 文件
   
5. 烧录到设备

   * 使用如下命令：

     ```cmd
     idf.py -p PORT flash
     ```

     将 PORT 替换为 ESP32 开发板的串口名称

6. 监视输出

   ```cmd
   idf.py -p PORT monitor
   ```

7. 退出IDF监视器

   ```cmd
   Ctrl + ]
   ```

#### 6. 卸载ESP-IDF

略，参考链接：https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/api-guides/tools/idf-tools.html



### 时钟树

#### 1. 概述

ESP32的时钟子系统用于从一系列根时钟中提取并分配系统/模块时钟。时钟树驱动程序负责维护系统时钟的基本功能，并管理模块时钟间的复杂关系。

#### 2. 根时钟

ESP32支持的根时钟包括：

* 内部8MHz RC振荡器 (RC_FAST)
  * 产生约8.5 MHz时钟信号输出，标识为`RC_FAST_CLK`
  * 传入分频器，生成`RC_FAST_D256_CLK`（默认分频256倍）

* 外部2～40MHz晶振 (XTAL)

* 内部150kHz RC振荡器 (RC_SLOW)
  * 产生约150 kHz时钟信号，标识为`RC_SLOW_CLK`

* 外部32kHz晶振 - 可选 (XTAL32K)

  `XTAL32K_CLK`的时钟源可以来自：

  * 连接到`32K_XP`和`32K_XN`管脚的32 KHz晶振。

  * 外部电路生成的32kHz时钟信号。

    > 如果使用外部电路生成的时钟信号，该信号必须连接到`32K_XN`管脚，并且在`32K_XP`管脚和地之间连接一个1nF的电容。此时，`32K_XP`管脚不能用作GPIO管脚。

与晶振产生的信号相比，从RC振荡器电路产生的信号通常精度较低，且容易受环境影响。

ESP32为`RTC_SLOW_CLK`提供了几种时钟源选项，可以根据对系统时间精度和对功耗的要求选择。更多详情，参阅 [RTC 定时器时钟源](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/api-reference/system/system_time.html#rtc-clock-source-choice)。

#### 3. 模块时钟

ESP32 的可用模块时钟在 [`soc_module_clk_t`](https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/api-reference/peripherals/clk_tree.html#_CPPv416soc_module_clk_t) 中列出，ESP32支持的模块时钟包括：

- `SOC_MOD_CLK_CPU`：CPU时钟源（可从XTAL、PLL、RC_FAST或APLL获取）
- `SOC_MOD_CLK_RTC_FAST`：RTC快速时钟
- `SOC_MOD_CLK_RTC_SLOW`：RTC慢速时钟
- `SOC_MOD_CLK_APB`：APB总线时钟
- `SOC_MOD_CLK_PLL_D2`：PLL分频2倍的时钟
- `SOC_MOD_CLK_PLL_F160M`：固定160MHz的PLL时钟
- 其他外设专用时钟（如ADC、DAC、UART等）

































### LED PWM 控制器

文档：https://docs.espressif.com/projects/esp-idf/zh_CN/release-v5.1/esp32/api-reference/peripherals/ledc.html

文档介绍了 ESP32 LED PWM 控制器 (LEDC) 的核心概念、配置流程及 API 参考，旨在帮助开发者快速掌握如何利用该外设控制 LED 亮度或生成 PWM 信号。

#### 1. 概述与核心功能：

- 基本定义：LED 控制器 (LEDC) 专为控制 LED 设计，也可用于生成通用 PWM 信号。
- 通道架构：
  - 共有 8 路通道（0-7），可产生独立波形（如驱动 RGB LED）。
  - 分为 **高速模式**（硬件实现，自动无干扰改变占空比）和 **低速模式**（软件驱动改变占空比）。
- 核心优势：支持硬件渐变（Fade），可在无需 CPU 干预的情况下自动改变占空比，实现平滑的亮度或颜色过渡。

#### 2. 功能概览

设置LEDC通道在高速模式或低速模式下运行，需要进行如下配置：

* 定时器配置：指定PWM信号的频率或占空比分辨率
* 通道配置：绑定定时器和输出PWM信号的GPIO
* 改变PWM信号：输出PWM信号来驱动LED。可通过软件控制或使用硬件渐变功能来改变LED的亮度。

另一个可选步骤：在渐变终端设置一个中断。

![image-20260116134720299](esp32学习笔记.assets/image-20260116134720299.png)

##### 2.1 定时器配置（ledc_timer_config_t）

负责设定 PWM 信号的基础时钟属性：

- 速度模式 (`ledc_mode_t`)：选择高速或低速模式。
- 定时器索引 (`ledc_timer_t`)：选择定时器 0-3。
- 频率 (`freq_hz`)：设定 PWM 信号频率。
- 占空比分辨率(duty_resolution)：设定分辨率（位数）。
- 时钟源 (clk_cfg)：
  - `APB_CLK` (80 MHz)：高速/低速通用。
  - `REF_TICK` (1 MHz)：支持动态调频。
  - `RC_FAST_CLK` (～8 MHz)：仅低速，支持 Light-sleep 模式。

> 频率和占空比的互斥关系：频率越高，支持的分辨率越低；反之亦然。

##### 2.2 通道配置（ledc_channel_config_t）

负责将定时器信号绑定到具体的 GPIO 引脚：

- GPIO 编号 (`gpio_num`)：指定输出引脚。
- 通道选择 (`channel`)：选择通道 0-7。
- 绑定定时器 (`timer_sel`)：关联上述配置的定时器。
- 中断类型(`intr_type`)：可选渐变结束中断。

停止输出：`ledc_stop()` 可禁用PWM输出并设置空闲电平。

##### 2.3 改变PWM信号

通道开始运行、生成具有恒定占空比和频率的 PWM 信号之后，有如下几种方式可以改变占空比：

* 软件改变占空比
* 硬件改变占空比
* 通过改变PWM频率也可以改变占空比

###### 2.3.1 使用软件改变PWM占空比

- 普通的设置占空比方式：
  - `ledc_set_duty()`：设置新的占空比数值。
  - `ledc_update_duty()`：必须调用此函数使新占空比生效（在下一个 PWM 周期生效）。
  - `ledc_get_duty()`：读取当前占空比。
- 配置通道时也可以设置占空比：
  * `ledc_channel_config()`

<font color=blue>占空比分辨率(duty_resolution)</font>

传递给函数的占空比数值范围取决于选定的`duty_resolution(占空比分辨率)`，应为`0~(2**duty_resolution)`，例如：如选定的占空比分辨率为 10，则占空比的数值范围为 0 至 1024。此时分辨率为` ~ 0.1%`。

> 在 ESP32 上，当通道绑定的定时器配置了其最大 PWM 占空比分辨率（ `MAX_DUTY_RES` ），通道的占空比不能被设置到 `(2 ** MAX_DUTY_RES)` 。否则，硬件内部占空比计数器会溢出，并导致占空比计算错误。

###### 2.3.2 使用硬件改变PWM占空比

LED PWM 控制器硬件可逐渐改变占空比的数值。

- 初始化：需先调用 `ledc_fade_func_install()` 安装渐变服务。
- 配置渐变，使用下面3个函数之一：
  - `ledc_set_fade_with_time()`：指定目标占空比和持续时间。
  - `ledc_set_fade_with_step()`：指定步长和周期数。
  - `ledc_set_fade()`
- 启动渐变：`ledc_fade_start()`，支持阻塞 (`LEDC_FADE_WAIT_DONE`) 或非阻塞模式。
- 回调机制：可通过 `ledc_cb_register()` 注册渐变结束回调函数。

* 关闭渐变：

  如不需要渐变和渐变中断，可用函数 `ledc_fade_func_uninstall()` 关闭

###### 2.3.3 改变PWM频率

有多种改变LED PWM频率的方式：

* 通过调用函数`ledc_set_freq()`设置频率。可用函数`ledc_get_freq()`查看当前频率。
* 通过调用函数`ledc_bind_channel_timer()`将其他定时器绑定到该通道来改变频率和占空比分辨率。
* 通过调用函数`ledc_channel_config()`改变通道的定时器。

###### 2.3.4 控制PWM的更多方式

有一些较独立的定时器特定函数可用于更改 PWM 输出：

* `ledc_timer_set()`
* `ledc_timer_rst()`
* `ledc_timer_pause()`
* `ledc_timer_resume()`

##### 2.4 使用中断

* 配置 LED PWM 控制器通道时，设置 `ledc_channel_config_t` 中的参数 `ledc_intr_type_t`，在渐变完成时触发中断。
* `ledc_isr_register()`用来注册中断函数。

#### 3. LED PWM控制器高速与低速模式

暂时略过

#### 4. 频率与占空比分辨率支持范围

暂时略过 

#### 5. 应用实例

* 使用 LEDC 基本实例请参照 [peripherals/ledc/ledc_basic](https://github.com/espressif/esp-idf/tree/b0f5707906b/examples/peripherals/ledc/ledc_basic)。

* 使用 LEDC 改变占空比和渐变控制的实例请参照 [peripherals/ledc/ledc_fade](https://github.com/espressif/esp-idf/tree/b0f5707906b/examples/peripherals/ledc/ledc_fade)。
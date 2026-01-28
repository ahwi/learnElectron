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



### I2S

#### 1. I2S 基础概述

1. 核心定义I2S（Inter-IC Sound）是同步串行通信协议，用于数字音频设备间的音频数据传输，ESP32 内置 2 个 I2S 外设，支持输入和输出采样数据。

2. 总线线路
   * **标准 / TDM 模式**：
     * MCLK（可选主时钟）
     * BCLK（位时钟）
     * WS（声道选择线）
     * DIN/DOUT（数据输入/输出，同 GPIO 可内部回环）。
   * **PDM 模式**：
     * CLK（PDM 时钟）
     * DIN/DOUT（数据输入 / 输出）。

3. 核心功能
   * 支持主机 / 从机、发射器 / 接收器角色。
   * DMA 流数据采样，无需 CPU 逐帧复制。
   * 支持RX/TX单工通信；全双工需 RX/TX 的配置一致（共用时钟）。

#### 2. I2S文件结构

![i2s_file_structure](esp32学习笔记.assets/i2s_file_structure.png)

* 需要包含在I2S应用中的公共头文件：

  * `i2s.h`：提供原有 I2S API（用于使用原有驱动的应用）。
  * `i2s_std.h`：提供标准通信模式的 API（用于使用标准模式的新驱动程序的应用）。
  * `i2s_pdm.h`：提供 PDM 通信模式的 API（用于使用 PDM 模式的新驱动程序的应用）。
  * `i2s_tdm.h`：提供 TDM 通信模式的 API（用于使用 TDM 模式的新驱动的应用）。

  > 原有驱动与新驱动无法共存。包含 `i2s.h` 以使用原有驱动，或包含其他三个头文件以使用新驱动。原有驱动未来可能会被删除。

* 已包含在上述头文件中的公共头文件：
  * `i2s_types_legacy.h`：提供只在原有驱动中使用的原有公共类型。
  * `i2s_types.h`：提供公共类型。
  * `i2s_common.h`：提供所有通信模式通用的 API。

#### 3. I2S时钟

##### 3.1 时钟源

* `i2s_clock_src_t::I2S_CLK_SRC_DEFAULT`：默认 PLL 时钟。
* `i2s_clock_src_t::I2S_CLK_SRC_PLL_160M`：160 MHz PLL 时钟。
* `i2s_clock_src_t::I2S_CLK_SRC_APLL`：音频 PLL 时钟，高采样率更精准，可配置频率；若被占用则会尝试原有APLL频率，如果原有 APLL 频率无法满足 I2S 的需求，时钟配置将失败。

##### 3.2 时钟术语

* **采样率**：单声道每秒采样数据数量。
* **SCLK**：源时钟频率，即时钟源的频率。
* **MCLK**：主时钟频率，BCLK 由其产生。MCLK 信号通常作为参考时钟，用于同步 I2S 主机和从机之间的 BCLK 和 WS。
  * 默认设为 `I2S_MCLK_MULTIPLE_256`。
  * 若声道位宽为 24 位，需设为能被 3 整除的倍数（如 `I2S_MCLK_MULTIPLE_384`），否则 WS 不精准。

* **BCLK**：位时钟频率，一个 BCLK 时钟周期代表数据管脚上的一个数据位。通过 `i2s_std_slot_config_t::slot_bit_width` 配置的通道位宽即为一个声道中的 BCLK 时钟周期数量，因此一个声道中可以有 8/16/24/32 个 BCLK 时钟周期。

* **LRCK** / **WS**：左/右时钟或字选择时钟。在非 PDM 模式下，其频率等于采样率。

#### 4. I2S通信模式

#### 4.1 模式预览

![image-20260128141144401](esp32学习笔记.assets/image-20260128141144401.png)

| 模式       | 功能说明                         | 芯片支持                           |
| ---------- | -------------------------------- | ---------------------------------- |
| 标准模式   | Philips/MSB/PCM 格式，左右双声道 | 所有芯片（ESP32-S2 仅 I2S0）       |
| PDM TX     | PCM→PDM 转换（16位固定）         | ESP32/ESP32-C3/C6/S3/H2（仅 I2S0） |
| PDM RX     | PDM→PCM 转换（16位固定）         | ESP32/ESP32-S3（仅 I2S0）          |
| TDM        | 多声道时分复用                   | ESP32-C3/C6/S3                     |
| LCD/摄像头 | 并行总线模式（非音频）           | ESP32/ESP32-S2/S3（仅 I2S0）       |
| ADC/DAC    | 内部模数/数模转换直连            | 仅 ESP32（I2S0）                   |

>  **注意**：PDM 模式不支持全双工；ESP32 单工模式下 TX/RX 不能共存于同一 I2S 端口

##### 4.1.1 标准模式

标准模式中有且仅有左右两个声道，驱动中将声道称为 slot。这些声道可以支持 8/16/24/32 位宽的采样数据。

声道的通信格式主要包括以下几种：

* **Philips 格式**：数据信号与 WS 信号相比有一个位的位移。WS 信号的占空比为 50%

  ![image-20260128141834991](esp32学习笔记.assets/image-20260128141834991.png)

* **MSB 格式**：与 Philips 格式基本相同，但其数据没有位移。

  ![image-20260128141903048](esp32学习笔记.assets/image-20260128141903048.png)

* **PCM 帧同步**：数据有一个位的位移，同时 WS 信号变成脉冲，持续一个 BCLK 周期。

  ![image-20260128141932258](esp32学习笔记.assets/image-20260128141932258.png)

##### 4.1.2 PDM模式（TX）

PDM（Pulse-density Modulation，脉冲密度调制） TX 模式：

* TX 通道可以将 PCM 数据转换为 PDM 格式，该格式始终有左右两个声道。
* 只在 I2S0 中受支持，且只支持 16 位宽的采样数据。
* 至少需要一个 CLK 管脚用于时钟信号，一个 DOUT 管脚用于数据信号（即下图中的 WS 和 SD 信号。BCK 信号为内部位采样时钟，在 PDM 设备之间不需要）。

* 允许用户配置上采样参数 `i2s_pdm_tx_clk_config_t::up_sample_fp` 和 `i2s_pdm_tx_clk_config_t::up_sample_fs`
  * 采样率计算公式：`up_sample_rate = fp / fs`

* 在 PDM TX 中有以下两种上采样模式：

  * 固定时钟频率模式：在这种模式下，上采样率将根据采样率的变化而变化。设置 `fp = 960`、 `fs = sample_rate / 100`，则 CLK 管脚上的时钟频率 (Fpdm) 将固定为 `128 * 48 KHz = 6.144 MHz`。注意此频率不等于采样率 (Fpcm)。
  * 固定上采样率模式：在这种模式下，上采样率固定为 2。设置 `fp = 960`、 `fs = 480`，则 CLK 管脚上的时钟频率 (Fpdm) 将为 `128 * sample_rate`。

  > 注：这边两个模式的采样率计算没看懂，先忽略

![image-20260128142728736](esp32学习笔记.assets/image-20260128142728736.png)

##### 4.1.3 PDM模式（RX）

PDM（Pulse-density Modulation，脉冲密度调制）RX 模式：

* RX 通道可以接收 PDM 格式的数据并将数据转换成 PCM 格式。
* 只在 I2S0 中受支持，且只支持 16 位宽的采样数据。
* 至少需要一个 CLK 管脚用于时钟信号，一个 DIN 管脚用于数据信号。
* 此模式允许用户配置下采样参数 `i2s_pdm_rx_clk_config_t::dn_sample_mode`
* 在 PDM RX 中有以下两种下采样模式：
  * `i2s_pdm_dsr_t::I2S_PDM_DSR_8S`：在这种模式下，WS 管脚的时钟频率 (Fpdm) 将为 `sample_rate (Fpcm) * 64`。
  * `i2s_pdm_dsr_t::I2S_PDM_DSR_16S`：在这种模式下，WS 管脚的时钟频率 (Fpdm) 将为 `sample_rate (Fpcm) * 128`。

##### 4.1.4 LCD/摄像头模式

略

##### 4.1.5 ADC/DAC模式

略































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
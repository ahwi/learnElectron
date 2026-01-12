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






















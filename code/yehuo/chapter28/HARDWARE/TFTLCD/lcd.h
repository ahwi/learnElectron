#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "stm32f4xx.h"

/********************************************************
2^26 = 0x0400 0000 = 64M,每个 BANK 有4*64MB = 256MB
(26为26根地址线)
64MB: FSMC_Bank1_NORSRAM1:0x6000 0000 ~ 0x63FF FFFF 
64MB: FSMC_Bank1_NORSRAM2:0x6400 0000 ~ 0x67FF FFFF 
64MB: FSMC_Bank1_NORSRAM3:0x6800 0000 ~ 0x6BFF FFFF 
64MB: FSMC_Bank1_NORSRAM4:0x6c00 0000 ~ 0x6FFF FFFF 
 
 选择BANK1-NORSRAM3 连接 TFT，地址范围为0x6800 0000 ~ 0x6BFF FFFF
 FSMC_A0 接LCD的DC(寄存器/数据选择)脚
 寄存器基地址 = 0x6800 0000
**********************************************************/

/************************** ILI9806g 显示屏的 FSMC 参数定义*******************************/
// FSMC_Bank1_NORSRAM 用于LCD命令操作的地址

#define FSMC_Addr_ILI9806G_CMD ((unit32) 0x68000000)

// FSMC_Bank1_NORSRAM 用于LCD命令操作的地址
#define FSMC_Addr_ILI9806G_DATA ((unit32) 0x68000002)

// 由片选引脚决定的NOR/SRAM块
#define FSMC_Bank1_NORSRAM  FSMC_Bank1_NORSRAM3

/**************************** ILI98-6g 显示屏8080通讯引脚定义 ******************************/
/*********控制信号线***********/
#define FSMC_AF                     GPIO_AF_FSMC
//片选，选择NOR/SRAM块
#define ILI9806G_CS_CLK             RCC_AHB1Periph_GPIOG
#define ILI9806G_CS_PORT            GPIOG
#define ILI9806G_CS_PIN             GPIO_Pin_10
#define ILI9806G_CS_PinSource       GPIO_PinSource10

//DC引脚，使用FSMC的地址信号控制，本引脚决定了访问LCD时使用的地址
//PF0为FSMC_A0
#define ILI9806G_DC_CLK             RCC_AHB1Periph_GPIOF
#define ILI9806G_DC_PORT            GPIOF
#define ILI9806G_DC_PIN             GPIO_Pin_0
#define ILI9806G_DC_PinSource       GPIO_PinSource0

//写使能
#define ILI9806G_WR_CLK             RCC_AHB1Periph_GPIOD
#define ILI9806G_WR_PORT            GPIOD
#define ILI9806G_WR_PIN             GPIO_Pin_5
#define ILI9806G_WR_PinSource       GPIO_PinSource5

//读使能
#define ILI9806G_RD_CLK             RCC_AHB1Periph_GPIOD
#define ILI9806G_RD_PORT            GPIOD
#define ILI9806G_RD_PIN             GPIO_Pin_4
#define ILI9806G_RD_PinSource       GPIO_PinSource4

//复位引脚
#define ILI9806G_RST_CLK            RCC_AHB1Periph_GPIOF
#define ILI9806G_RST_PORT           GPIOF
#define ILI9806G_RST_PIN            GPIO_Pin_11

//背光引脚
#define ILI9806G_BK_CLK            RCC_AHB1Periph_GPIOF
#define ILI9806G_BK_PORT           GPIOF
#define ILI9806G_BK_PIN            GPIO_Pin_9

/********数据信号线***************/
#define      ILI9806G_D0_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D0_PORT               GPIOD
#define      ILI9806G_D0_PIN                GPIO_Pin_14
#define      ILI9806G_D0_PinSource          GPIO_PinSource14

#define      ILI9806G_D1_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D1_PORT               GPIOD
#define      ILI9806G_D1_PIN                GPIO_Pin_15
#define      ILI9806G_D1_PinSource          GPIO_PinSource15

#define      ILI9806G_D2_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D2_PORT               GPIOD
#define      ILI9806G_D2_PIN                GPIO_Pin_0
#define      ILI9806G_D2_PinSource          GPIO_PinSource0

#define      ILI9806G_D3_CLK                RCC_AHB1Periph_GPIOD  
#define      ILI9806G_D3_PORT               GPIOD
#define      ILI9806G_D3_PIN                GPIO_Pin_1
#define      ILI9806G_D3_PinSource          GPIO_PinSource1

#define      ILI9806G_D4_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D4_PORT               GPIOE
#define      ILI9806G_D4_PIN                GPIO_Pin_7
#define      ILI9806G_D4_PinSource          GPIO_PinSource7

#define      ILI9806G_D5_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D5_PORT               GPIOE
#define      ILI9806G_D5_PIN                GPIO_Pin_8
#define      ILI9806G_D5_PinSource          GPIO_PinSource8

#define      ILI9806G_D6_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D6_PORT               GPIOE
#define      ILI9806G_D6_PIN                GPIO_Pin_9
#define      ILI9806G_D6_PinSource          GPIO_PinSource9

#define      ILI9806G_D7_CLK                RCC_AHB1Periph_GPIOE  
#define      ILI9806G_D7_PORT               GPIOE
#define      ILI9806G_D7_PIN                GPIO_Pin_10
#define      ILI9806G_D7_PinSource          GPIO_PinSource10

#define      ILI9806G_D8_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D8_PORT               GPIOE
#define      ILI9806G_D8_PIN                GPIO_Pin_11
#define      ILI9806G_D8_PinSource          GPIO_PinSource11

#define      ILI9806G_D9_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D9_PORT               GPIOE
#define      ILI9806G_D9_PIN                GPIO_Pin_12
#define      ILI9806G_D9_PinSource          GPIO_PinSource12

#define      ILI9806G_D10_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D10_PORT               GPIOE
#define      ILI9806G_D10_PIN                GPIO_Pin_13
#define      ILI9806G_D10_PinSource          GPIO_PinSource13

#define      ILI9806G_D11_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D11_PORT               GPIOE
#define      ILI9806G_D11_PIN                GPIO_Pin_14
#define      ILI9806G_D11_PinSource          GPIO_PinSource14

#define      ILI9806G_D12_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D12_PORT               GPIOE
#define      ILI9806G_D12_PIN                GPIO_Pin_15
#define      ILI9806G_D12_PinSource          GPIO_PinSource15

#define      ILI9806G_D13_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D13_PORT               GPIOD
#define      ILI9806G_D13_PIN                GPIO_Pin_8
#define      ILI9806G_D13_PinSource          GPIO_PinSource8

#define      ILI9806G_D14_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D14_PORT               GPIOD
#define      ILI9806G_D14_PIN                GPIO_Pin_9
#define      ILI9806G_D14_PinSource          GPIO_PinSource9

#define      ILI9806G_D15_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D15_PORT               GPIOD
#define      ILI9806G_D15_PIN                GPIO_Pin_10
#define      ILI9806G_D15_PinSource          GPIO_PinSource10

/************************ 调试预用 ***************************************/
#define DEBUG_DELAY()   Delay(0x5000)

/************************ ILI9806 显示区域的起始坐标和总行列数 ***************************************/
#define ILI9806G_DispWindow_X_Start 0   //起始点的x坐标 
#define ILI9806G_DispWindow_Y_Start 0   //起始点的y坐标 

#define ILI9806G_LESS_PIXEL 480 //液晶屏较短方向的像素宽度
#define ILI9806G_MORE_PIXEL 854 //液晶屏较长方向的像素宽度

//根据液晶扫描方向而变化的XY像素宽度
//调用ILI9806G_GramScan函数设置方向时会自动更改
extern uint16_t LCD_XLENGTH, LCD_Y_LENGTH;

//液晶屏扫描模式
//参数可选值为0-7
extern uint8_t  LCD_SCAN_MODE;

/************************* 定义ILI9806显示屏常用颜色 ***************/
#define BACKGROUND  BLACK   //默认背景颜色

#define      WHITE                         0x0000  //白色
#define      GREY                          0xF7DE	   //灰色 
#define      BLUE                          0x001F	   //蓝色 
#define      BLUE2                         0x051F	   //浅蓝色 
#define      RED                           0xF800	   //红色 
#define      MAGENTA                       0xF81F	   //红紫色，洋红色 
#define      GREEN                         0x07E0	   //绿色 
#define      CYAN                          0x7FFF	   //蓝绿色，青色 
#define      YELLOW                        0xFFE0	   //黄色 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF

/************************* 定义ILI9806常用命令 *******************/
#define CMD_SetCoordinateX  0x2A    //设置X坐标
#define CMD_SetCoordinateY  0x2B    //设置Y坐标
#define CMD_SetPixel        0x2c    //填充像素

/************************* 声明ILI9806函数 *******************/
void ILI9806G_Init(void);
void ILI9806G_Rst(void);
void ILI9806G_GramScan(uint8_t ucOtion);
void ILI9806G_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWindth, uint16_t usHeight);
void ILI9806G_SetPointPixel(uint16_t usX, uint16_t usY);
uint16_t ILI9806G_GetPointPixel(uint16_t usX , uint16_t usY);
void ILI9806G_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2);


#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "stm32f4xx.h"
// #include "stm32f4xx_fsmc.h"

extern uint16_t lcd_id;

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

/************************** NT35510 显示屏的 FSMC 参数定义*******************************/
// FSMC_Bank1_NORSRAM 用于LCD命令操作的地址

#define FSMC_Addr_NT35510_CMD ((uint32_t) 0x6C000000)

// FSMC_Bank1_NORSRAM 用于LCD命令操作的地址
#define FSMC_Addr_NT35510_DATA ((uint32_t) 0x6C000080)

// 由片选引脚决定的NOR/SRAM块
#define FSMC_Bank1_NORSRAMx  FSMC_Bank1_NORSRAM4

/**************************** NT35510(ID5510) 显示屏8080通讯引脚定义 ******************************/
/*
正点原子探索者开发板
屏幕4.3寸 控制器 NT35510(ID5510)
分辨率为 800*480

控制信号线
LCD_CS 	FSMC_NE		FG12	片选，悬着NOR/SRAM块
RS 		FSMC_A6 	PF12 	地址信号控制线
WR/CLK	FSMC_NWE	PD5		写使能
RD		FSMC_NOE	PD4		读使能
RST		RESET		直连系统复位	复位引脚	
BL		LCD_BL		PB15	背光引脚 	

数据信号线
D0		FSMC_D0		PD14
D1		FSMC_D1		PD15
D2		FSMC_D2		PD0
D3		FSMC_D3		PD1
D4		FSMC_D4		PE7
D5		FSMC_D5		PE8
D6		FSMC_D6		PE9
D7		FSMC_D7		PE10
D8		FSMC_D8		PE11
D9		FSMC_D9		PE12
D10		FSMC_D10	PE13
D11		FSMC_D11	PE14
D12		FSMC_D12	PE15
D13		FSMC_D13	PD8
D14		FSMC_D14	PD9
D15		FSMC_D15	PD10
*/

/*********控制信号线***********/
#define FSMC_AF                     GPIO_AF_FSMC
//片选，选择NOR/SRAM块
#define NT35510_CS_CLK             RCC_AHB1Periph_GPIOG
#define NT35510_CS_PORT            GPIOG
#define NT35510_CS_PIN             GPIO_Pin_12
#define NT35510_CS_PinSource       GPIO_PinSource12

//DC引脚，使用FSMC的地址信号控制，本引脚决定了访问LCD时使用的地址
//PF0为FSMC_A0
#define NT35510_DC_CLK             RCC_AHB1Periph_GPIOF
#define NT35510_DC_PORT            GPIOF
#define NT35510_DC_PIN             GPIO_Pin_12
#define NT35510_DC_PinSource       GPIO_PinSource12

//写使能
#define NT35510_WR_CLK             RCC_AHB1Periph_GPIOD
#define NT35510_WR_PORT            GPIOD
#define NT35510_WR_PIN             GPIO_Pin_5
#define NT35510_WR_PinSource       GPIO_PinSource5

//读使能
#define NT35510_RD_CLK             RCC_AHB1Periph_GPIOD
#define NT35510_RD_PORT            GPIOD
#define NT35510_RD_PIN             GPIO_Pin_4
#define NT35510_RD_PinSource       GPIO_PinSource4

// //复位引脚  //正点原子的复位引脚和系统的复位引脚连接在一起
// #define NT35510_RST_CLK            RCC_AHB1Periph_GPIOx
// #define NT35510_RST_PORT           GPIOx
// #define NT35510_RST_PIN            GPIO_Pin_x

//背光引脚
#define NT35510_BK_CLK            RCC_AHB1Periph_GPIOB
#define NT35510_BK_PORT           GPIOB
#define NT35510_BK_PIN            GPIO_Pin_15

/********数据信号线***************/
#define      NT35510_D0_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D0_PORT               GPIOD
#define      NT35510_D0_PIN                GPIO_Pin_14
#define      NT35510_D0_PinSource          GPIO_PinSource14

#define      NT35510_D1_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D1_PORT               GPIOD
#define      NT35510_D1_PIN                GPIO_Pin_15
#define      NT35510_D1_PinSource          GPIO_PinSource15

#define      NT35510_D2_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D2_PORT               GPIOD
#define      NT35510_D2_PIN                GPIO_Pin_0
#define      NT35510_D2_PinSource          GPIO_PinSource0

#define      NT35510_D3_CLK                RCC_AHB1Periph_GPIOD  
#define      NT35510_D3_PORT               GPIOD
#define      NT35510_D3_PIN                GPIO_Pin_1
#define      NT35510_D3_PinSource          GPIO_PinSource1

#define      NT35510_D4_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D4_PORT               GPIOE
#define      NT35510_D4_PIN                GPIO_Pin_7
#define      NT35510_D4_PinSource          GPIO_PinSource7

#define      NT35510_D5_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D5_PORT               GPIOE
#define      NT35510_D5_PIN                GPIO_Pin_8
#define      NT35510_D5_PinSource          GPIO_PinSource8

#define      NT35510_D6_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D6_PORT               GPIOE
#define      NT35510_D6_PIN                GPIO_Pin_9
#define      NT35510_D6_PinSource          GPIO_PinSource9

#define      NT35510_D7_CLK                RCC_AHB1Periph_GPIOE  
#define      NT35510_D7_PORT               GPIOE
#define      NT35510_D7_PIN                GPIO_Pin_10
#define      NT35510_D7_PinSource          GPIO_PinSource10

#define      NT35510_D8_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D8_PORT               GPIOE
#define      NT35510_D8_PIN                GPIO_Pin_11
#define      NT35510_D8_PinSource          GPIO_PinSource11

#define      NT35510_D9_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D9_PORT               GPIOE
#define      NT35510_D9_PIN                GPIO_Pin_12
#define      NT35510_D9_PinSource          GPIO_PinSource12

#define      NT35510_D10_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D10_PORT               GPIOE
#define      NT35510_D10_PIN                GPIO_Pin_13
#define      NT35510_D10_PinSource          GPIO_PinSource13

#define      NT35510_D11_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D11_PORT               GPIOE
#define      NT35510_D11_PIN                GPIO_Pin_14
#define      NT35510_D11_PinSource          GPIO_PinSource14

#define      NT35510_D12_CLK                RCC_AHB1Periph_GPIOE   
#define      NT35510_D12_PORT               GPIOE
#define      NT35510_D12_PIN                GPIO_Pin_15
#define      NT35510_D12_PinSource          GPIO_PinSource15

#define      NT35510_D13_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D13_PORT               GPIOD
#define      NT35510_D13_PIN                GPIO_Pin_8
#define      NT35510_D13_PinSource          GPIO_PinSource8

#define      NT35510_D14_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D14_PORT               GPIOD
#define      NT35510_D14_PIN                GPIO_Pin_9
#define      NT35510_D14_PinSource          GPIO_PinSource9

#define      NT35510_D15_CLK                RCC_AHB1Periph_GPIOD   
#define      NT35510_D15_PORT               GPIOD
#define      NT35510_D15_PIN                GPIO_Pin_10
#define      NT35510_D15_PinSource          GPIO_PinSource10

/************************ NT35510 显示区域的起始坐标和总行列数 ***************************************/
#define NT35510_DispWindow_X_Start 0   //起始点的x坐标 
#define NT35510_DispWindow_Y_Start 0   //起始点的y坐标 

#define NT35510_LESS_PIXEL 480 //液晶屏较短方向的像素宽度
#define NT35510_MORE_PIXEL 800 //液晶屏较长方向的像素宽度

//根据液晶扫描方向而变化的XY像素宽度
//调用LCD_Display_Dir函数设置方向时会自动更改
extern uint16_t LCD_X_LENGTH, LCD_Y_LENGTH;

//液晶屏扫描模式
//参数可选值为0-7
extern uint8_t  LCD_SCAN_MODE;

/************************* 定义 NT35510 显示屏常用颜色 ***************/
#define BACKGROUND  BLACK   //默认背景颜色

#define      WHITE                         0xFFFF  //白色
#define      BLACK                         0x0000	   //黑色 
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

/************************* 定义 NT35510 常用命令 *******************/
// #define CMD_SetCoordinateX  0x2A    //设置X坐标
// #define CMD_SetCoordinateY  0x2B    //设置Y坐标
// #define CMD_SetPixel        0x2c    //填充像素

#define CMD_SetCoordinateX  0x2A00    //设置X坐标
#define CMD_SetCoordinateY  0x2B00    //设置Y坐标
#define CMD_SetPixel        0x2C00    //填充像素

/************************* 声明 NT35510 函数 *******************/
void NT35510_Init(void);
// void NT35510_Rst(void);
// void NT35510_GramScan(uint8_t ucOtion);
// void NT35510_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWindth, uint16_t usHeight);
// void NT35510_SetPointPixel(uint16_t usX, uint16_t usY);
// uint16_t NT35510_GetPointPixel(uint16_t usX , uint16_t usY);
// void NT35510_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2);

// void NT35510_Clear(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight);
// void LCD_SetColors(uint16_t TextColor, uint16_t BackColor);
// void LCD_GetColors(uint16_t *TextColor, uint16_t *BackColor);
// void LCD_SetTextColor(uint16_t Color);
void LCD_Draw_Rect(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color);



/***************** 正点原子 **********************/
// LCD重要参数封装成一个结构体
typedef struct
{
    u16 width;  //LCD 宽度
    u16 height; //LCD 高度
    u16 id;     //LCD ID
    u8 dir;     //横屏还是竖屏：0，竖屏；1，横屏
    u16 wramcmd;    //开始写gram指令
    u16 setxcmd;    //设置x坐标指令
    u16 setycmd;    //设置y坐标指令
}_lcd_dev;


//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数


typedef struct 
{
    /* data */
    vu16 LCD_REG;
    vu16 LCD_RAM;
} LCD_TypeDef;


//扫描方向定义
#define L2R_U2D  0 //从左到右,从上到下
#define L2R_D2U  1 //从左到右,从下到上
#define R2L_U2D  2 //从右到左,从上到下
#define R2L_D2U  3 //从右到左,从下到上

#define U2D_L2R  4 //从上到下,从左到右
#define U2D_R2L  5 //从上到下,从右到左
#define D2U_L2R  6 //从下到上,从左到右
#define D2U_R2L  7 //从下到上,从右到左	 

#define LCD_BASE ((u32)(0x6C000000 | 0X0000007E))
#define LCD ((LCD_TypeDef *) LCD_BASE)
#define	LCD_LED PBout(15) 

#endif


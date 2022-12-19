#ifndef __LCD_H
#define __LCD_H

#include "sys.h"

//LCD重要参数集
typedef struct{
    u16 width;  //LCD宽度
    u16 height; //LCD高度
    u16 id;     //LCD ID
    u8  dir;    //横屏还是竖屏控制：0，竖屏；1，横屏
    u16 wramcmd;    //开始写gram指令
    u16 setxcmd;    //设置x坐标指令
    u16 setycmd;    //设置y坐标指令
} _lcd_dev;

//LCD参数
extern _lcd_dev lcddev; //管理LCD重要参数

typedef struct
{
	vu16 LCD_REG;
	vu16 LCD_RAM;
} LCD_TypeDef;

//使用NOR/SRAM的Bank1.sector4，地址位HADDR[27,26]=11 A6作为数据/命令区分线
// 使用16位数据总线时，STM32内部会右移一位对齐
#define LCD_BASE ((U32)(0x6c000000|0x0000007E))
#define LCD ((LCD_TypeDef *)LCD_BASE)


#endif

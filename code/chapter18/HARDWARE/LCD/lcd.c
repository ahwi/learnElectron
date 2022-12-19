#include "lcd.h"


//写寄存器函数
//regval:寄存器值
void LCD_WR_REG(vu16 regval)
{
    regval = regval;    //使用-O2优化的时候，必须插入的延时
    LCD->LCD_REG = regval;  //写入要写的寄存器序号
}

//写LCD数据
//data:要写入的值
void LCD_WR_DATA(vu16 data)
{
    data = data;    //使用-O2优化的时候，必须插入的延时
    LCD->LCD_RAM = data;
}

//读LCD数据
//返回值:读到的值
u16 LCD_RD_DATA(void)
{
    vu16 ram;   //vu16 防止被优化
    ram = LCD->LCD_RAM;
    return ram;
}

//写寄存器
//LCD_Reg:寄存器地址
//LCD_RegValue:要写入的数据
void LCD_WriteReg(vu16 LCD_Reg, vu16 LCD_RegValue)
{
    LCD->LCD_REG = LCD_Reg; //写入要写的寄存器序号
    LCD->LCD_RAM = LCD_RegValue;    //写入数据
}

//读寄存器
//LCD_Reg:寄存器地址
//返回值:读到的数据
u16 LCD_ReadReg(vu16 LCD_Reg)
{
    LCD_WR_REG(LCD_Reg);    //写入要读的寄存器序号
    delay_us(5);
    return LCD_RD_DATA();   //返回读到的值
}

//开始写GRAM
void LCD_WriteRAM_Prepare(void)
{
    LCD->LCD_REG = lcddev.wramcmd;
}

//LCD写GRAM
//RGB_Code:颜色值
void LCD_WriteRAM(u16 RGB_Code)
{
    LCD->LCD_RAM = RGB_Code;    //写十六位GRAM
}

//设置光标位置
//Xpos:横坐标
//Ypos:纵坐标
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
    if(lcddev.id==0X9341 || lcddev.id==0x5310)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos>>8);
        LCD_WR_DATA(Xpos&0xFF);
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Ypos>>8);
        LCD_WR_DATA(Ypos&0xFF);
    } else if(lcddev.id==0x6804)
    {
        if(lcddev.dir==1) Xpos = lcddev.width-1-Xpos;   //横屏时处理
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos>>8);
        LCD_WR_DATA(Xpos&0xFF);
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Ypos>>8);
        LCD_WR_DATA(Ypos&0xFF);
    } else if(lcddev.id==0x5510)
    {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos>>8);
        LCD_WR_REG(lcddev.setxcmd+1);
        LCD_WR_DATA(Xpos&0xFF);
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Ypos>>8);
        LCD_WR_REG(lcddev.setxcmd+1);
        LCD_WR_DATA(Ypos&0xFF);
    } else 
    {
        if(lcddev.dir==1) Xpos = lcddev.width-1-Xpos;   //横屏其实就是调转x,y坐标
        LCD_WriteReg(lcddev.setxcmd, Xpos);
        LCD_WriteReg(lcddev.setxcmd, Ypos);
    }

}
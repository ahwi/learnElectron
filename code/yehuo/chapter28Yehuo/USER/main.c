/*
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tpad.h"


extern u8 TIM5CH1_CAPTURE_STA;	//输入状态捕获
extern u32 TIM5CH1_CAPTURE_VAL;	//输入捕获值（TIM2/TIM5是32位）

int main(void)
{
	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置系统中断优先级分组2
	delay_init(168);	//初始化延时函数
	uart_init(115200);	//初始化串口波特率115200
	LED_Init();
	
	TPAD_Init(8);
	while(1)
	{
		if(TPAD_Scan(0))	//成功捕获到一次上升沿
		{
			LED1 = !LED1;	//LED取反	
		}
		t++;
		if(t==15)
		{
			t = 0;
			LED0 = !LED0;	//LED0取反，提示程序正在运行
		}
		delay_ms(10);
	}
}
*/


#include "sys.h"
#include "delay.h"
#include "led.h"
#include "lcd.h"

static void LCD_Test(void);
static void Delay(__IO uint32_t nCount);

int main(void)
{
	LED_Init();
	ILI9806G_Init();	//lcd初始化

	//设置显示屏的方向位模式6
	ILI9806G_GramScan(6);

	while(1)
	{
		LCD_Test();
	}
}

//用于测试各种液晶的函数
void LCD_Test(void)
{
	LCD_SetColors(RED, BLACK);
	ILI9806G_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH); // 清屏，显示全黑

	// 画直线
	LCD_SetTextColor(BLUE);
	ILI9806G_DrawLine(50, 270, 420, 275);
}

/**
 * @brief 简单延时函数
 * @param nCount: 延时计数值
 * @retval 无
 */
static void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount --);
}

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"

// static void LCD_Test(void);

int main(void)
{
	delay_init(168);	//初始化延时函数
	uart_init(115200);	//初始化串口波特率115200
	LED_Init();
	NT35510_Init();	//lcd初始化

	LCD_Draw_Rect(10,10, 100, 100, RED); //画一个矩形

	while(1)
	{
		delay_ms(1000);
		printf("lcd_id %d\r\n", lcd_id);
		// LCD_Test();
	}
}

// //用于测试各种液晶的函数
// void LCD_Test(void)
// {
// 	// LCD_SetColors(RED, BLACK);
// 	// NT35510_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH); // 清屏，显示全黑

// 	// // 画直线
// 	// LCD_SetTextColor(BLUE);
// 	// NT35510_DrawLine(50, 270, 420, 275);
// }

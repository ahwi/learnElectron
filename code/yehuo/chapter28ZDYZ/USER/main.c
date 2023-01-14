#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"

// static void LCD_Test(void);

int main(void)
{
	delay_init(168);	//��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����115200
	LED_Init();
	NT35510_Init();	//lcd��ʼ��

	LCD_Draw_Rect(10,10, 100, 100, RED); //��һ������

	while(1)
	{
		delay_ms(1000);
		printf("lcd_id %d\r\n", lcd_id);
		// LCD_Test();
	}
}

// //���ڲ��Ը���Һ���ĺ���
// void LCD_Test(void)
// {
// 	// LCD_SetColors(RED, BLACK);
// 	// NT35510_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH); // ��������ʾȫ��

// 	// // ��ֱ��
// 	// LCD_SetTextColor(BLUE);
// 	// NT35510_DrawLine(50, 270, 420, 275);
// }

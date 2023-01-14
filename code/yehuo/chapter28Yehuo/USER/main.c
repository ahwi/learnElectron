/*
#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tpad.h"


extern u8 TIM5CH1_CAPTURE_STA;	//����״̬����
extern u32 TIM5CH1_CAPTURE_VAL;	//���벶��ֵ��TIM2/TIM5��32λ��

int main(void)
{
	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����ϵͳ�ж����ȼ�����2
	delay_init(168);	//��ʼ����ʱ����
	uart_init(115200);	//��ʼ�����ڲ�����115200
	LED_Init();
	
	TPAD_Init(8);
	while(1)
	{
		if(TPAD_Scan(0))	//�ɹ�����һ��������
		{
			LED1 = !LED1;	//LEDȡ��	
		}
		t++;
		if(t==15)
		{
			t = 0;
			LED0 = !LED0;	//LED0ȡ������ʾ������������
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
	ILI9806G_Init();	//lcd��ʼ��

	//������ʾ���ķ���λģʽ6
	ILI9806G_GramScan(6);

	while(1)
	{
		LCD_Test();
	}
}

//���ڲ��Ը���Һ���ĺ���
void LCD_Test(void)
{
	LCD_SetColors(RED, BLACK);
	ILI9806G_Clear(0, 0, LCD_X_LENGTH, LCD_Y_LENGTH); // ��������ʾȫ��

	// ��ֱ��
	LCD_SetTextColor(BLUE);
	ILI9806G_DrawLine(50, 270, 420, 275);
}

/**
 * @brief ����ʱ����
 * @param nCount: ��ʱ����ֵ
 * @retval ��
 */
static void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount --);
}

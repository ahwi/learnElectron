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

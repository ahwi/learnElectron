#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "timer.h"

int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����ϵͳ�ж����ȼ�����2
	delay_init(168);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�˿�
	TIM3_Int_Init(5000-1, 8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����5000��Ϊ500ms
	
	while(1)
	{
		LED0 = !LED0;
		delay_ms(200);	//��ʱ200ms
	}
}

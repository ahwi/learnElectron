#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"


int main(void)
{
	delay_init(168);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�˿�
	BEEP_Init();	//��ʼ��������

	while(1){
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9���� ����
		GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//GPIOF.8���� ����������
		delay_ms(300);	//��ʱ300ms
		GPIO_SetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9���� ����
		GPIO_SetBits(GPIOF, GPIO_Pin_8);	//GPIOF.10���� ��������
		delay_ms(300);	//��ʱ300ms
	}

}


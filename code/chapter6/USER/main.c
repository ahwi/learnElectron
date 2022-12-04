#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


int main(void)
{
	delay_init(168);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�˿�

	/*ͨ�������⺯���ķ�ʽʵ��IO����*/
	while(1){
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9���� ����
		GPIO_SetBits(GPIOF, GPIO_Pin_10);	//GPIOF.10���� ����
		delay_ms(500);	//��ʱ500ms
		GPIO_SetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9���� ����
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);	//GPIOF.10���� ����
		delay_ms(500);	//��ʱ500ms
	}

}

/*

int main(void)
{
	delay_init(168);	//��ʼ����ʱ����
	LED_init();	//��ʼ��LED�˿�

	// ͨ��λ�������ķ�ʽʵ��IO����
	while(1){
		LED0 = 0;	//LED0��
		LED1 = 1;	//LED1��
		delay_ms(500);
		LED0 = 1;	//LED0��
		LED1 = 0;	//LED1��
		delay_ms(500);
	}
}

int main(void)
{
	delay_init(168);	//��ʼ����ʱ����
	LED_init();	//��ʼ��LED�˿�

	// ͨ��λֱ�Ӳ����Ĵ����ķ�ʽʵ��IO����
	while(1){
		GPIOF->BSRRH = GPIO_Pin_9;	//LED0��
		GPIOF->BSRRL = GPIO_Pin_10;	//LED1��
		delay_ms(500);
		GPIOF->BSRRL = GPIO_Pin_9;	//LED1��
		GPIOF->BSRRH = GPIO_Pin_10;	//LED0��
		delay_ms(500);
	}
}

*/

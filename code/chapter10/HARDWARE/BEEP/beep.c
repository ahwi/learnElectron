#include "beep.h"


//��ʼ��PE8Ϊ�����
//BEEP IO��ʼ��
void BEEP_Init(void)
{
	GPIO_InitTypeDef gpio_init;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //ʹ��GPIOFʱ��
	
	gpio_init.GPIO_Pin = GPIO_Pin_8;
	gpio_init.GPIO_Mode	= GPIO_Mode_OUT;	//��ͨ���ģʽ
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;	//2MHz
	gpio_init.GPIO_OType = GPIO_OType_PP;	//�������
	gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;	//����
	GPIO_Init(GPIOF, &gpio_init);	//��ʼ��GPIO
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//��������Ӧ����GPIOF8���ͣ�����������
}

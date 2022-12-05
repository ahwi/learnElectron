#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef gpio_init_e;
	GPIO_InitTypeDef gpio_init_a;
	
	// ��ʼ��GPIOE��GPIOA��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA, ENABLE);
	
	gpio_init_e.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	gpio_init_e.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_e.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_init_e.GPIO_OType = GPIO_OType_PP;
	gpio_init_e.GPIO_PuPd = GPIO_PuPd_UP;	//��ʼΪ����
	GPIO_Init(GPIOE, &gpio_init_e);
	
	gpio_init_a.GPIO_Pin = GPIO_Pin_0;
	gpio_init_a.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_a.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_init_a.GPIO_OType = GPIO_OType_PP;
	gpio_init_a.GPIO_PuPd = GPIO_PuPd_DOWN;	//��ʼ��Ϊ����
	GPIO_Init(GPIOA, &gpio_init_a);
}


//����������
//���ذ���ֵ
//mode 0 ��֧��������; 1 ֧��������
// 0û�а������� KEY0 KEY0_PRES; KEY1 KEY1_PRES; KEY2 KEY2_PRES; KEY_WKUP WKUP_PRES
// ע�⣺�˺�������Ӧ���ȼ���KEY0>KEY1>KEY2>KEY_WKUP
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;	//�����ɿ���־;0 ���� 1�ɿ�
	if(mode) key_up = 1;
	
	if(key_up && (KEY0==0 || KEY1==0 || KEY2==0 || WK_UP==1)){
		delay_ms(10);	//ȥ����
		key_up = 0;
		if(KEY0 == 0) return KEY0_PRES;
		else if(KEY1 == 0) return KEY1_PRES;
		else if(KEY2 == 0) return KEY2_PRES;
		else if(WK_UP == 1) return WKUP_PRES;
	
	}
	else if(KEY0==1 && KEY1==1 && KEY2==1 && WK_UP==0){
		key_up = 1;
	}
	return 0;//û�а�������
}

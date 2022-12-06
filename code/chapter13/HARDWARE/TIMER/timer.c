#include "timer.h"
#include "led.h"



//ͨ�ö�ʱ��3�жϳ�ʼ��
//arr: �Զ���װֵ
//psc: ʱ��Ԥ��Ƶ��
//��ʱ�����ʱ����㷽����Tout=((arr+1)*(psc+1))/Ft us.
//Ft=��ʱ������Ƶ�ʣ���λ��Mhz
//����ʹ�õ��Ƕ�ʱ��3
void TIM3_Int_Init(u16 arr,u16 psc)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//1. ʹ��TIM3ʱ��
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;	//��ʱ����Ƶ 
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = arr;	//�Զ���װ��ֵ
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);	//2. ��ʼ����ʱ��TIM3
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);	//3. ����ʱ��3�����ж�
	
	NVIC_InitStruct.NVIC_IRQChannel = TIM3_IRQn;	//��ʱ��3�ж�
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x03;	//�����ȼ�3
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);	//4.��ʼ��NVIC
	
	TIM_Cmd(TIM3, ENABLE);	//5.ʹ�ܶ�ʱ��3
}

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)	//����ж�
	{
		LED1 = !LED1;
	}
	
	TIM_ClearITPendingBit(TIM3, TIM_IT_Update);	//����жϱ�־λ
}
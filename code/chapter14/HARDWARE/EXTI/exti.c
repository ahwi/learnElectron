#include "exti.h"
#include "key.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "delay.h"
#include "beep.h"
#include "led.h"


//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//����
	if(WK_UP ==1){
		BEEP = !BEEP;	//��������ת
	}
	EXTI_ClearITPendingBit(EXTI_Line0);	//���LINE0�ϵ��жϱ�־
}

//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY2 ==1){
		LED0 = !LED0;	
	}
	EXTI_ClearITPendingBit(EXTI_Line2);	//���LINE2�ϵ��жϱ�־
}

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY1 ==1){
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);	//���LINE3�ϵ��жϱ�־
}

//�ⲿ�ж�4�������
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//����
	if(KEY0 ==1){
		LED0 = !LED0;
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);	//���LINE4�ϵ��жϱ�־
}
	

//�ⲿ�жϳ�ʼ������
//��ʼ��PE2~4��PA0Ϊ�ж�����
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	KEY_Init();	//������Ӧ��IO�ڳ�ʼ��
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//ʹ��SYSCFGʱ��

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);	//PE2���ӵ��ж���2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);	//PE3���ӵ��ж���3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);	//PE4���ӵ��ж���4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);	//PA0���ӵ��ж���0
	
	/* ����EXTI_Line2,3,4 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line2|EXTI_Line3|EXTI_Line4;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//�ж��¼�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; //�½��ش���
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStruct);	//����
	
	/* ����EXTI_Line1 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//�ж��¼�
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//�����ش���
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	//�ж���ʹ��
	EXTI_Init(&EXTI_InitStruct);	//����
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;	//�ⲿ�ж�2
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;	//��ռ���ȼ�3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//�����ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;	//�ⲿ�ж�3
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//�����ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;	//�ⲿ�ж�4
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;	//��ռ���ȼ�1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//�����ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	//�ⲿ�ж�0
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	//��ռ���ȼ�0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//�����ȼ�2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStruct);
	
}

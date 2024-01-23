#include "basic_tim.h"
#include "misc.h"
#include "led.h"

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	// �жϷ���
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	// �ж����ȼ�
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void TIM_Config(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	// ʹ�ܶ�ʱ��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	// ��ʼ����ʱ��6
	// APB1 48MHz 
	TIM_TimeBaseInitStruct.TIM_Prescaler = 4800 - 1;
	TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	// �����ʱ���жϱ�־
	TIM_ClearFlag(TIM6, TIM_FLAG_Trigger);
	
	// ������ʱ���ж�
	TIM_Cmd(TIM6, ENABLE);
}

void TIM_Init(void)
{
	NVIC_Config();
	TIM_Config();
}


void TIM6_DAC_IRQHandler(void)
{
	static int i = 0;
	if(TIM_GetITStatus(TIM6, TIM_IT_Trigger) == SET){
		TIM_ClearFlag(TIM6, TIM_FLAG_Trigger);
		// LED0_TOGGLE;
		LED0 = i;
		i = ~i;
	}
	
}

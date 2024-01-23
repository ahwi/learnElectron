#include "basic_tim.h"
#include "misc.h"
#include "led.h"

void NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStruct;
	// 中断分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
	
	// 中断优先级
	NVIC_InitStruct.NVIC_IRQChannel = TIM6_DAC_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void TIM_Config(void)
{
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	
	// 使能定时器时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);
	
	// 初始化定时器6
	// APB1 48MHz 
	TIM_TimeBaseInitStruct.TIM_Prescaler = 4800 - 1;
	TIM_TimeBaseInitStruct.TIM_Period = 5000 - 1;
	TIM_TimeBaseInit(TIM6, &TIM_TimeBaseInitStruct);
	
	// 清除定时器中断标志
	TIM_ClearFlag(TIM6, TIM_FLAG_Trigger);
	
	// 开启定时器中断
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

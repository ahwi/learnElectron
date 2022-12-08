#include "pwm.h"


//TIM14 PWM部分初始化
//PWM输出初始化
//arr:自动重装载值 psc:时钟预分频数
void TIM14_PWM_Init(u32 arr, u32 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, ENABLE);	//TIM14时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //GPIO.F时钟使能

	GPIO_PinAFConfig(GPIOF, GPIO_PinSource9, GPIO_AF_TIM14);	//GPIO.F9复用位定时器14
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//复用功能
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;	//100Mhz
	GPIO_InitStruct.GPIO_OType	= GPIO_OType_PP;	//推挽输出
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;	//上拉电阻
	GPIO_Init(GPIOF, &GPIO_InitStruct);	//初始化PF9
	
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc; //定时器分频
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up; //向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = arr; //自动重装载值
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM14, &TIM_TimeBaseInitStruct);	//初始化定时器14
	
	//初始化TIM14 Channel1 PWM模式
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;	//PWM调试模式1
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;	//比较输出使能
	//TIM_OCInitStruct.TIM_OutputNState
	//TIM_OCInitStruct.TIM_Pulse
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_Low;	//输出极性低
	//TIM_OCInitStruct.TIM_OCNPolarity
	//TIM_OCInitStruct.TIM_OCIdleState
	//TIM_OCInitStruct.TIM_OCNIdleState
	TIM_OC1Init(TIM14, &TIM_OCInitStruct);	//ARPE使能

	TIM_OC1PreloadConfig(TIM14, TIM_OCPreload_Enable);	//使能TIM14在CCR1上的预装载寄存器
	TIM_ARRPreloadConfig(TIM14, ENABLE);	//ARPE使能
	TIM_Cmd(TIM14, ENABLE);	//使能TIM14
	
}


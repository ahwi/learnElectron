#include "exti.h"
#include "key.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"
#include "delay.h"
#include "beep.h"
#include "led.h"


//外部中断0服务程序
void EXTI0_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(WK_UP ==1){
		BEEP = !BEEP;	//蜂鸣器反转
	}
	EXTI_ClearITPendingBit(EXTI_Line0);	//清除LINE0上的中断标志
}

//外部中断2服务程序
void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY2 ==1){
		LED0 = !LED0;	
	}
	EXTI_ClearITPendingBit(EXTI_Line2);	//清除LINE2上的中断标志
}

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY1 ==1){
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line3);	//清除LINE3上的中断标志
}

//外部中断4服务程序
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if(KEY0 ==1){
		LED0 = !LED0;
		LED1 = !LED1;
	}
	EXTI_ClearITPendingBit(EXTI_Line4);	//清除LINE4上的中断标志
}
	

//外部中断初始化程序
//初始化PE2~4，PA0为中断输入
void EXTIX_Init(void)
{
	EXTI_InitTypeDef EXTI_InitStruct;
	NVIC_InitTypeDef NVIC_InitStruct;
	
	KEY_Init();	//按键对应的IO口初始化
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);	//使能SYSCFG时钟

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource2);	//PE2连接到中断线2
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);	//PE3连接到中断线3
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);	//PE4连接到中断线4
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);	//PA0连接到中断线0
	
	/* 配置EXTI_Line2,3,4 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line2|EXTI_Line3|EXTI_Line4;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//中断事件
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿触发
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	//中断线使能
	EXTI_Init(&EXTI_InitStruct);	//配置
	
	/* 配置EXTI_Line1 */
	EXTI_InitStruct.EXTI_Line = EXTI_Line0;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;	//中断事件
	EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;	//上升沿触发
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;	//中断线使能
	EXTI_Init(&EXTI_InitStruct);	//配置
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI2_IRQn;	//外部中断2
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x03;	//抢占优先级3
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//子优先级2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI3_IRQn;	//外部中断3
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//子优先级2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI4_IRQn;	//外部中断4
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x01;	//抢占优先级1
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//子优先级2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);
	
	NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;	//外部中断0
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0x00;	//抢占优先级0
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = 0x02;	//子优先级2
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;	//使能外部中断通道
	NVIC_Init(&NVIC_InitStruct);
	
}

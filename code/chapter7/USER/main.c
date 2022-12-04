#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"


int main(void)
{
	delay_init(168);	//初始化延时函数
	LED_Init();	//初始化LED端口
	BEEP_Init();	//初始化蜂鸣器

	while(1){
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9拉低 灯亮
		GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//GPIOF.8拉低 蜂鸣器不响
		delay_ms(300);	//延时300ms
		GPIO_SetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9拉高 灯灭
		GPIO_SetBits(GPIOF, GPIO_Pin_8);	//GPIOF.10拉高 蜂鸣器响
		delay_ms(300);	//延时300ms
	}

}


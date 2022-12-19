#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "tpad.h"


extern u8 TIM5CH1_CAPTURE_STA;	//输入状态捕获
extern u32 TIM5CH1_CAPTURE_VAL;	//输入捕获值（TIM2/TIM5是32位）

int main(void)
{
	u8 t=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置系统中断优先级分组2
	delay_init(168);	//初始化延时函数
	uart_init(115200);	//初始化串口波特率115200
	LED_Init();
	
	TPAD_Init(8);
	while(1)
	{
		if(TPAD_Scan(0))	//成功捕获到一次上升沿
		{
			LED1 = !LED1;	//LED取反	
		}
		t++;
		if(t==15)
		{
			t = 0;
			LED0 = !LED0;	//LED0取反，提示程序正在运行
		}
		delay_ms(10);
	}
}

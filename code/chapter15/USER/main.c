#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"


extern u8 TIM5CH1_CAPTURE_STA;	//输入状态捕获
extern u32 TIM5CH1_CAPTURE_VAL;	//输入捕获值（TIM2/TIM5是32位）

int main(void)
{
	long long temp = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//设置系统中断优先级分组2
	delay_init(168);	//初始化延时函数
	uart_init(115200);	//初始化延时函数
	TIM14_PWM_Init(500-1, 84-1); //84M/84=1Mhz的计数频率，重装载值500，所以PWM频率为1M/500=2Hhz
	TIM5_CH1_Cap_Init(0xFFFFFFFF, 84-1);	//以1Mhz的频率计数
	
	while(1)
	{
		delay_ms(10);
		TIM_SetCompare1(TIM14, TIM_GetCapture1(TIM14)+1);
		if(TIM_GetCapture1(TIM14)==300) TIM_SetCompare1(TIM14, 0);
		
		if(TIM5CH1_CAPTURE_STA & 0x80)	//成功捕获到了一次高电平
		{
			temp = TIM5CH1_CAPTURE_STA & 0x3f;
			temp *= 0xFFFFFFFF;	//溢出时间总和
			temp += TIM5CH1_CAPTURE_VAL;	//得到总的高电平时间
			printf("HIGH:%lld us\r\n", temp);	//打印总的高电平时间
			TIM5CH1_CAPTURE_STA = 0;	//开启下一次捕获
		}
		//printf("running...\r\n");
	}
}

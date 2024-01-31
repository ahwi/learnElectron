#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "basic_tim.h"


static void Delay(__IO uint32_t nCount);

int main(void)
{
	LED_Init();

	TIM_Init();

	while(1)
	{
	}
}

static void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount --);
}

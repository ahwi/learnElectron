#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "basic_tim.h"


// static void LCD_Test(void);

static void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount --);
}

int main(void)
{
	int i = 0;
	LED_Init();

	//TIM_Init();
	// LED0 = 0;

	
	while(1)
	{
		LED0 = 0;
		Delay(0xffff);
		LED0 = 1;
		Delay(0xffff);
		i = ~i;
		//delay_ms(1000);
		// LCD_Test();
		//LED0 = 1;
		//delay_ms(1000);
		// LED0_TOGGLE;
	}
}



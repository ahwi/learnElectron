#include "beep.h"


//初始化PE8为输出口
//BEEP IO初始化
void BEEP_Init(void)
{
	GPIO_InitTypeDef gpio_init;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE); //使能GPIOF时钟
	
	gpio_init.GPIO_Pin = GPIO_Pin_8;
	gpio_init.GPIO_Mode	= GPIO_Mode_OUT;	//普通输出模式
	gpio_init.GPIO_Speed = GPIO_Speed_2MHz;	//2MHz
	gpio_init.GPIO_OType = GPIO_OType_PP;	//推挽输出
	gpio_init.GPIO_PuPd = GPIO_PuPd_DOWN;	//下拉
	GPIO_Init(GPIOF, &gpio_init);	//初始化GPIO
	
	GPIO_ResetBits(GPIOF, GPIO_Pin_8);	//蜂鸣器对应引脚GPIOF8拉低，蜂鸣器不响
}

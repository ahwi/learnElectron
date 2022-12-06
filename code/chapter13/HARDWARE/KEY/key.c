#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
	GPIO_InitTypeDef gpio_init_e;
	GPIO_InitTypeDef gpio_init_a;
	
	// 初始化GPIOE和GPIOA的时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA, ENABLE);
	
	gpio_init_e.GPIO_Pin = GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4;
	gpio_init_e.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_e.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_init_e.GPIO_OType = GPIO_OType_PP;
	gpio_init_e.GPIO_PuPd = GPIO_PuPd_UP;	//初始为上拉
	GPIO_Init(GPIOE, &gpio_init_e);
	
	gpio_init_a.GPIO_Pin = GPIO_Pin_0;
	gpio_init_a.GPIO_Mode = GPIO_Mode_IN;
	gpio_init_a.GPIO_Speed = GPIO_Speed_100MHz;
	gpio_init_a.GPIO_OType = GPIO_OType_PP;
	gpio_init_a.GPIO_PuPd = GPIO_PuPd_DOWN;	//初始化为下拉
	GPIO_Init(GPIOA, &gpio_init_a);
}


//按键处理函数
//返回按键值
//mode 0 不支持连续按; 1 支持连续按
// 0没有按键按下 KEY0 KEY0_PRES; KEY1 KEY1_PRES; KEY2 KEY2_PRES; KEY_WKUP WKUP_PRES
// 注意：此函数有响应优先级，KEY0>KEY1>KEY2>KEY_WKUP
u8 KEY_Scan(u8 mode)
{
	static u8 key_up = 1;	//按照松开标志;0 按下 1松开
	if(mode) key_up = 1;
	
	if(key_up && (KEY0==0 || KEY1==0 || KEY2==0 || WK_UP==1)){
		delay_ms(10);	//去抖动
		key_up = 0;
		if(KEY0 == 0) return KEY0_PRES;
		else if(KEY1 == 0) return KEY1_PRES;
		else if(KEY2 == 0) return KEY2_PRES;
		else if(WK_UP == 1) return WKUP_PRES;
	
	}
	else if(KEY0==1 && KEY1==1 && KEY2==1 && WK_UP==0){
		key_up = 1;
	}
	return 0;//没有按键按下
}

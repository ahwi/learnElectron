#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"


int main(void)
{
	delay_init(168);	//初始化延时函数
	LED_Init();	//初始化LED端口

	/*通过操作库函数的方式实现IO控制*/
	while(1){
		GPIO_ResetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9拉低 灯亮
		GPIO_SetBits(GPIOF, GPIO_Pin_10);	//GPIOF.10拉高 灯灭
		delay_ms(500);	//延时500ms
		GPIO_SetBits(GPIOF, GPIO_Pin_9);	//GPIOF.9拉高 灯灭
		GPIO_ResetBits(GPIOF, GPIO_Pin_10);	//GPIOF.10拉低 灯亮
		delay_ms(500);	//延时500ms
	}

}

/*

int main(void)
{
	delay_init(168);	//初始化延时函数
	LED_init();	//初始化LED端口

	// 通过位带操作的方式实现IO控制
	while(1){
		LED0 = 0;	//LED0亮
		LED1 = 1;	//LED1灭
		delay_ms(500);
		LED0 = 1;	//LED0灭
		LED1 = 0;	//LED1亮
		delay_ms(500);
	}
}

int main(void)
{
	delay_init(168);	//初始化延时函数
	LED_init();	//初始化LED端口

	// 通过位直接操作寄存器的方式实现IO控制
	while(1){
		GPIOF->BSRRH = GPIO_Pin_9;	//LED0亮
		GPIOF->BSRRL = GPIO_Pin_10;	//LED1灭
		delay_ms(500);
		GPIOF->BSRRL = GPIO_Pin_9;	//LED1亮
		GPIOF->BSRRH = GPIO_Pin_10;	//LED0灭
		delay_ms(500);
	}
}

*/

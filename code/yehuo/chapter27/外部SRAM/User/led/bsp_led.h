#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"


// 引脚定义
#define LED0_PIN            GPIO_Pin_9
#define LED0_GPIO_PORT      GPIOF
#define LED0_GPIO_CLK       RCC_AHB1Periph_GPIOF

#define LED1_PIN            GPIO_Pin_10
#define LED1_GPIO_PORT      GPIOF
#define LED1_GPIO_CLK       RCC_AHB1Periph_GPIOF


/**
 * 控制LED灯亮灭的宏
 * LED低电平亮，设置ON=0,OFF=1
 * 若LED高电平，把宏设置成ON=1，OFF=0即可
 */
#define ON      0
#define OFF     1

/* 带参宏，可以像内联函数一样使用 */
#define LED0(a) if (a) \
    GPIO_SetBits(LED0_GPIO_PORT, LED0_PIN);\
    else    \
    GPIO_ResetBits(LED0_GPIO_PORT, LED0_PIN);\

#define LED1(a) if (a) \
    GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN);\
    else    \
    GPIO_ResetBits(LED1_GPIO_PORT, LED1_PIN);\


/* 直接操作寄存器的方法控制IO */
#define digitalHi(p, i)     {p->BSRRL=i;}   //设置为高电平
#define digitalLo(p, i)     {p->BSRRH=i;}   //输出低电平
#define digitalToggle(p, i) {p->ODR ^=i;}   //输出反转状态

/* 定义控制IO的宏 */
#define LED0_TOGGLE     digitalToggle(LED0_GPIO_PORT, LED0_PIN)
#define LED0_OFF        digitalHi(LED0_GPIO_PORT, LED0_PIN)
#define LED0_ON         digitalLo(LED0_GPIO_PORT, LED0_PIN)

#define LED1_TOGGLE     digitalToggle(LED1_GPIO_PORT, LED1_PIN)
#define LED1_OFF        digitalHi(LED1_GPIO_PORT, LED1_PIN)
#define LED1_ON         digitalLo(LED1_GPIO_PORT, LED1_PIN)



void LED_GPIO_Config(void);

#endif

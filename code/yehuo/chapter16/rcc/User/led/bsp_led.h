#ifndef __BSP_LED_H
#define __BSP_LED_H

#include "stm32f4xx.h"


// ���Ŷ���
#define LED0_PIN            GPIO_Pin_9
#define LED0_GPIO_PORT      GPIOF
#define LED0_GPIO_CLK       RCC_AHB1Periph_GPIOF

#define LED1_PIN            GPIO_Pin_10
#define LED1_GPIO_PORT      GPIOF
#define LED1_GPIO_CLK       RCC_AHB1Periph_GPIOF


/**
 * ����LED������ĺ�
 * LED�͵�ƽ��������ON=0,OFF=1
 * ��LED�ߵ�ƽ���Ѻ����ó�ON=1��OFF=0����
 */
#define ON      0
#define OFF     1

/* ���κ꣬��������������һ��ʹ�� */
#define LED0(a) if (a) \
    GPIO_SetBits(LED0_GPIO_PORT, LED0_PIN);\
    else    \
    GPIO_ResetBits(LED0_GPIO_PORT, LED0_PIN);\

#define LED1(a) if (a) \
    GPIO_SetBits(LED1_GPIO_PORT, LED1_PIN);\
    else    \
    GPIO_ResetBits(LED1_GPIO_PORT, LED1_PIN);\


/* ֱ�Ӳ����Ĵ����ķ�������IO */
#define digitalHi(p, i)     {p->BSRRL=i;}   //����Ϊ�ߵ�ƽ
#define digitalLo(p, i)     {p->BSRRH=i;}   //����͵�ƽ
#define digitalToggle(p, i) {p->ODR ^=i;}   //�����ת״̬

/* �������IO�ĺ� */
#define LED0_TOGGLE     digitalToggle(LED0_GPIO_PORT, LED0_PIN)
#define LED0_OFF        digitalHi(LED0_GPIO_PORT, LED0_PIN)
#define LED0_ON         digitalLo(LED0_GPIO_PORT, LED0_PIN)

#define LED1_TOGGLE     digitalToggle(LED1_GPIO_PORT, LED1_PIN)
#define LED1_OFF        digitalHi(LED1_GPIO_PORT, LED1_PIN)
#define LED1_ON         digitalLo(LED1_GPIO_PORT, LED1_PIN)



void LED_GPIO_Config(void);

#endif

#ifndef __LED_H
#define __LED_H

#include "sys.h"

//LED�˿ڶ���
#define LED0 PFout(9) //DS0
#define LED1 PFout(10)	//DS1

#define digitalToggle(p, i) {p->ODR ^= i;} //�������״̬

// �������IO�ĺ�
#define LED0_TOGGLE digitalToggle(GPIOF, GPIO_Pin_9)
#define LED1_TOGGLE digitalToggle(GPIOF, GPIO_Pin_10)

void LED_Init(void);	//LED��ʼ��

#endif

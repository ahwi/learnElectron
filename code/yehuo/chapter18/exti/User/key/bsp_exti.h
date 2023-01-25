#ifndef __BSP_EXTI_H
#define __BSP_EXTI_H

#include "stm32f4xx.h"


/*
KEY0 --> PE4
KEY1 --> PE3
*/
void NVIC_Configuration(void);
void EXTI_Key_Config(void);

#endif

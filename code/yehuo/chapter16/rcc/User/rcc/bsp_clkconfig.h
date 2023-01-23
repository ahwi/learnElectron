#ifndef __BSP_CLKCONFIG_H
#define __BSP_CLKCONFIG_H

#include "stm32f4xx_rcc.h"
 

void user_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q);
void HSE_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q);
void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q);
void MCO1_GPIO_Config(void);
void MCO2_GPIO_Config(void);


#endif

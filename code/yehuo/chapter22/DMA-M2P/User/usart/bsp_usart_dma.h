#ifndef __BSP_USART_DMA_H
#define __BSP_USART_DMA_H

#include "stm32f4xx.h"
#include <stdio.h>


#define SENDBUFF_SIZE           5000    //发送的数据量
#define DEBUG_USART_BAUDRATE    115200

void Debug_USART_Config(void);
void USART_DMA_Config(void);


#endif

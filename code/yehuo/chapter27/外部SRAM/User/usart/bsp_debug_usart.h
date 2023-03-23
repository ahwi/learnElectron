#ifndef __BSP_DEBUG_USART_H
#define __BSP_DEBUG_USART_H

#include "stm32f4xx.h"
#include "stdio.h"

void Debug_USART_Config(void);
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch);
void Usart_SendString(USART_TypeDef *pUSARTx, char *str);

void uart_init(u32 bound);
#endif

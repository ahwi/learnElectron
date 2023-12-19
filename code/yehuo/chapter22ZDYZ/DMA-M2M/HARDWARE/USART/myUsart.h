#ifndef __MY_USART_H
#define __MY_USART_H

#include "stm32f4xx.h"

void NVIC_Configuration(void);
void USART_Configuration(void);
void Usart_SendByte(USART_TypeDef* USARTx, uint8_t c);
void Usart_SendString(USART_TypeDef* USARTx, char *s);

#endif

#ifndef __USART_DMA_H
#define __USART_DMA_H

#include "stm32f4xx.h"

#define SENDBUFF_SIZE 	5000 //���͵�������
#define USART_BAUDRATE 	115200 //���ڲ�����


void usart_configuraion(void);
void usart_dma_configuration(void);
#endif

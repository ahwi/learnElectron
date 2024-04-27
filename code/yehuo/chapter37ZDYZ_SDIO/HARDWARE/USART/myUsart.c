#include "myUsart.h"

#include "misc.h"

// 嵌套向量中断控制器 NVIC
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef nvic_initStruct;
	
	// 中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	// 配置串口中断优先级
	nvic_initStruct.NVIC_IRQChannel = USART1_IRQn;
	nvic_initStruct.NVIC_IRQChannelCmd = ENABLE;
	nvic_initStruct.NVIC_IRQChannelPreemptionPriority = 0x01;
	nvic_initStruct.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_Init(&nvic_initStruct);
}

void USART_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// 初始化GPIOA、串口时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// 初始化GPIO复用：USART1_RX PA10 / USART1_TX PA9 
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_High_Speed;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

	// 初始化嵌套向量中断控制器 NVIC
	NVIC_Configuration();
	
	// 初始化串口
	USART_InitStruct.USART_BaudRate = 115200;
	USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruct.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStruct.USART_Parity = USART_Parity_No;
	USART_InitStruct.USART_StopBits = USART_StopBits_1;
	USART_InitStruct.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1, &USART_InitStruct);
	
	// 使能串口接收中断
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	// 使能串口
	USART_Cmd(USART1, ENABLE);
}

// 发送单个字节
void Usart_SendByte(USART_TypeDef* USARTx, uint8_t c)
{
	USART_SendData(USARTx, c);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

// 发送字符串
void Usart_SendString(USART_TypeDef* USARTx, char *s)
{
	unsigned int pos = 0;
	while(*(s+pos) != '\0'){
		Usart_SendByte(USARTx, *(s+pos));
		
		pos ++;
	}
	
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
}

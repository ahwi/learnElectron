#include "usart_dma.h"


uint8_t dataArray[10];


/**
* @brief ���ô���
*/
void usart_configuraion(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	USART_InitTypeDef USART_InitStruct;
	
	// ��ʼ������
	// USART1_TX PA9; USART1_RX PA10
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	// GPIO����Ϊ����
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	// ��ʼ��GPIO/����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	

	USART_InitStruct.USART_BaudRate = USART_BAUDRATE;
  USART_InitStruct.USART_WordLength = USART_WordLength_8b;
  USART_InitStruct.USART_StopBits = USART_StopBits_1;
  USART_InitStruct.USART_Parity = USART_Parity_No;
  USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	// ��ʼ������
	USART_Init(USART1, &USART_InitStruct);
	
	// ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);
}


/**
* @brief ���ô��ڵ�dma����
*/
void usart_dma_configuration(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	
	//��ʼ��DMAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	// ��λ��ʼ��DMA������
	DMA_DeInit(DMA1_Stream7);
	
	// ȷ����λ���
	while(DMA_GetCmdStatus(DMA1_Stream7) != DISABLE);
	
	DMA_InitStruct.DMA_Channel = DMA_Channel_4;
	DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)(USART1_BASE + 0x04);
	DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)dataArray;
	DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStruct.DMA_BufferSize = SENDBUFF_SIZE;
	DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStruct.DMA_MemoryInc = DMA_PeripheralInc_Enable;
	DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte; 
	DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
	DMA_InitStruct.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStruct.DMA_Priority = DMA_Priority_High;
	// ����FIFOģʽ
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream7, &DMA_InitStruct);
	
	// ʹ��DMA����������ʼDMA���ݴ���
	DMA_Cmd(DMA1_Stream7, ENABLE);
	
	// ���DMA�������Ƿ���Ч
	while(DMA_GetCmdStatus(DMA1_Stream7) != ENABLE);
}

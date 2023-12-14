#include "usart_dma.h"


uint8_t dataArray[10];


/**
* @brief ���ô��ڵ�dma����
*/
void usart_configuraion()
{

}


/**
* @brief ���ô��ڵ�dma����
*/
void usart_dma_configuration()
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

#include "usart_dma.h"


uint8_t dataArray[10];


/**
* @brief 配置串口的dma功能
*/
void usart_configuraion()
{

}


/**
* @brief 配置串口的dma功能
*/
void usart_dma_configuration()
{
	DMA_InitTypeDef DMA_InitStruct;
	
	//初始化DMA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	// 复位初始化DMA数据流
	DMA_DeInit(DMA1_Stream7);
	
	// 确保复位完成
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
	// 禁用FIFO模式
	DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
	DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
	DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream7, &DMA_InitStruct);
	
	// 使能DMA数据流，开始DMA数据传输
	DMA_Cmd(DMA1_Stream7, ENABLE);
	
	// 检测DMA数据流是否有效
	while(DMA_GetCmdStatus(DMA1_Stream7) != ENABLE);
}

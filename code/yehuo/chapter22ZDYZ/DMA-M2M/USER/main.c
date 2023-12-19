#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
//#include "usart_dma.h"


#define BUFFER_SIZE 32
#define TIMEOUT_MAX 1000 // Maximum timeout value

// const �ؼ��ֻ�������������Ϊ�������ͣ�const ��������洢��flash��
const uint32_t src_const_buffer[BUFFER_SIZE] = {
	0x00000001, 0x00000002, 0x00000003, 0x00000004,
	0x00000005, 0x00000006, 0x00000007, 0x00000008,
	0x00000009, 0x0000000a, 0x0000000b, 0x0000000c,
	0x0000000d, 0x0000000e, 0x0000000f, 0x00000010,
	0x01000001, 0x02000002, 0x03000003, 0x04000004,
	0x05000005, 0x06000006, 0x07000007, 0x08000008,
	0x09000009, 0x0a00000a, 0x0b00000b, 0x0c00000c,
	0x0d00000d, 0x0e00000e, 0x0f00000f, 0x10000010,
	};

// ����DMA��Ŀ��洢��
uint32_t dst_buff[BUFFER_SIZE];

void delay(__IO u32 nCount);
void dma_configure(void);
uint8_t bufferCmp(const uint32_t *src, uint32_t *dst, uint16_t len);

int main(void)
{
	uint8_t status;
	
	// ��ʼ��LED
	LED_Init();
	
	delay(0xFFFFF);
	
	// DMA ��������
	dma_configure();
	
	// �ȴ�DMA�������
	while(DMA_GetFlagStatus(DMA2_Stream1, DMA_FLAG_TCIF1) != SET);
	
	// �ж������Ƿ����
	status = bufferCmp(src_const_buffer, dst_buff, BUFFER_SIZE);
	if(status == 0) //�����
	{
		LED0 = 1;
		LED1 = 0;
	}
	else{	//���
		LED0 = 0;
		LED1 = 1;
	}
	
	while(1){
	}

}


void delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount --);
}



void dma_configure(void)
{
	DMA_InitTypeDef DMA_InitStruct;
	__IO uint32_t timeout = TIMEOUT_MAX;
	
	// ��ʼ��ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	
	// ��λDMA
	DMA_DeInit(DMA2_Stream1);
	
	while(DMA_GetCmdStatus(DMA2_Stream1) != DISABLE);
	
	// ��ʼ��DMA
	DMA_InitStruct.DMA_Channel = DMA_Channel_0;
  DMA_InitStruct.DMA_PeripheralBaseAddr = (uint32_t)src_const_buffer;
  DMA_InitStruct.DMA_Memory0BaseAddr = (uint32_t)dst_buff;
  DMA_InitStruct.DMA_DIR = DMA_DIR_MemoryToMemory;
  DMA_InitStruct.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
  DMA_InitStruct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  DMA_InitStruct.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStruct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  DMA_InitStruct.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  DMA_InitStruct.DMA_Mode = DMA_Mode_Normal;
  DMA_InitStruct.DMA_Priority = DMA_Priority_High;
  DMA_InitStruct.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStruct.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  DMA_InitStruct.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  DMA_InitStruct.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	DMA_Init(DMA2_Stream1, &DMA_InitStruct);
	
	// ʹ��DMA
	DMA_Cmd(DMA2_Stream1, ENABLE);
	
	// �ȴ�DMA����
	while((DMA_GetCmdStatus(DMA2_Stream1) != ENABLE) && (timeout-- > 0));
	
	// �ж��Ƿ�ʱ����ʱ���ó���ѭ�������
	while(1) {
		LED0 = 1;
		LED1 = 1;
		delay(0xFFFFFF);
		LED0 = 0;
		LED1 = 0;
		delay(0xFFFFFF);
	}
}

// �Ƚ�����
// �����ȫ��ȷ���1 ����ȷ���0
uint8_t bufferCmp(const uint32_t *src, uint32_t *dst, uint16_t len)
{
	while(len --){
		if(*src != *dst){
			return 0;
		}
		src ++;
		dst ++;
	}
	return 1;
}



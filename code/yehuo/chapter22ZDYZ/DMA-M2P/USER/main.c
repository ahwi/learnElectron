#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usart_dma.h"

void delay(__IO u32 nCount);

int main(void)
{
	// 初始化LED
	LED_Init();
	
	// 初始化串口
	usart_configuraion();

	// 串口dma配置
	usart_dma_configuration();
	
	// USART1向DMA发出DMA请求
  USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);
	
	
	while(1){
		LED0 = 1;
		LED1 = 1;
		delay(0x9ffffff);
		LED0 = 0;
		LED1 = 0;
	  delay(0x9ffffff);
	}

}


void delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount --);
}

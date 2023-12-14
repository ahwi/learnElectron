#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "myUsart.h"

void delay(__IO u32 nCount);

int main(void)
{
	// ��ʼ��LED
	LED_Init();
	
	// ��������
	USART_Configuration();

    // Usart_SendString(USART1, "hello\r\n");
	while(1){
		Usart_SendString(USART1, "hello\r\n");
		
		delay(0x9ffffff);
	}

}


void delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount --);
}

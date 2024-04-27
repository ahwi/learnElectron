#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "myUsart.h"
#include "sdio_test.h"

void delay(__IO u32 nCount);

int main(void)
{
	// ≥ı ºªØLED
	LED_Init();
	
	// ¥Æø⁄≈‰÷√
	USART_Configuration();

  // Usart_SendString(USART1, "hello\r\n");
	
	
	while(1){
	}

}


void delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount --);
}

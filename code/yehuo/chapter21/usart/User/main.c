/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用1.8.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"

void Delay(__IO u32 nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

  // u8 USART_RX_BUF[5] = {'h', 'e', 'l', 'l', 'o'};
  // int t = 0;
  // int len = 5;
  	// u16 times=0; 
    /* 初始化USART 配置模式为 115200 8-N-1, 中断接收 */
    // Debug_USART_Config();
    uart_init(115200);

    /* 发送一个字符串 */
    // Usart_SendString(USART1, "\r\n这是一个串口中断接收回显实验\r\n");
    // Usart_SendString(USART1, "\r\nThis is a usart test.\r\n");
    // Usart_SendByte(USART1, 'a');
    // printf("这是一个串口中断接收回显实验\n");

    /* LED IO口初始化 */
    // LED_GPIO_Config();

    // for(t=0;t<len;t++)
    // {
    //   USART_SendData(USART1, USART_RX_BUF[t]);         //?ò????1·???????
    //   while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//????·????á??
    // }    

    while(1)
    {
        // LED0(ON); 
        // LED1(ON);
        // Delay(0xFFFFFF);
        // Usart_SendByte(USART1, 'a');
        // Usart_SendString(USART1, "这是一个串口中断接收回显实验\n");
        // LED0(OFF);
        // LED1(OFF); 
        // Delay(0xFFFFFF);
        // printf("请输入数据\r\n");
      //   			times++;
			// if(times%50000==0)
			// {
      //   printf("请输入数据\r\n");
			// }

			// delay_ms(10);   
        printf("\r\n请输入数据\r\n");
        Delay(0xFFFFFF);
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


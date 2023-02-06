/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.8.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"

void Delay(__IO u32 nCount);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{

  // u8 USART_RX_BUF[5] = {'h', 'e', 'l', 'l', 'o'};
  // int t = 0;
  // int len = 5;
  	// u16 times=0; 
    /* ��ʼ��USART ����ģʽΪ 115200 8-N-1, �жϽ��� */
    // Debug_USART_Config();
    uart_init(115200);

    /* ����һ���ַ��� */
    // Usart_SendString(USART1, "\r\n����һ�������жϽ��ջ���ʵ��\r\n");
    // Usart_SendString(USART1, "\r\nThis is a usart test.\r\n");
    // Usart_SendByte(USART1, 'a');
    // printf("����һ�������жϽ��ջ���ʵ��\n");

    /* LED IO�ڳ�ʼ�� */
    // LED_GPIO_Config();

    // for(t=0;t<len;t++)
    // {
    //   USART_SendData(USART1, USART_RX_BUF[t]);         //?��????1��???????
    //   while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//????��????��??
    // }    

    while(1)
    {
        // LED0(ON); 
        // LED1(ON);
        // Delay(0xFFFFFF);
        // Usart_SendByte(USART1, 'a');
        // Usart_SendString(USART1, "����һ�������жϽ��ջ���ʵ��\n");
        // LED0(OFF);
        // LED1(OFF); 
        // Delay(0xFFFFFF);
        // printf("����������\r\n");
      //   			times++;
			// if(times%50000==0)
			// {
      //   printf("����������\r\n");
			// }

			// delay_ms(10);   
        printf("\r\n����������\r\n");
        Delay(0xFFFFFF);
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


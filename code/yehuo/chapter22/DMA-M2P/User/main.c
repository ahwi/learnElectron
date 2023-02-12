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
// #include "bsp_debug_usart.h"
#include "bsp_usart_dma.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
void Delay(__IO u32 nCount);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    uint16_t i;
    /* ��ʼ��USART */
    Debug_USART_Config();

    /* ����ʹ��DMAģʽ */
    USART_DMA_Config();

    /* LED IO�ڳ�ʼ�� */
    LED_GPIO_Config();

    /* ��佫Ҫ���͵����� */
    for(i=0; i < SENDBUFF_SIZE; i ++)
    {
        SendBuff[i] = 'A';
    }

    /* USART1��DMA����TX���� */
    USART_DMACmd(USART1, USART_DMAReq_Tx, ENABLE);

    while(1)
    {
        LED0(ON); 
        LED1(ON);
        Delay(0xFFFFFF);
        LED0(OFF);
        LED1(OFF); 
        Delay(0xFFFFFF);
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


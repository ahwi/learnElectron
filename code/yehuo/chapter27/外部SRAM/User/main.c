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
    /* ��ʼ������ */
    uart_init(115200);

    /* ����һ���ַ��� */
    printf("����һ��EEPROM��дʵ��\r\n");

    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


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
#include "bsp_sram.h"

void Delay(__IO u32 nCount);

// #define sram_addr (unsinged int32_t)0x68000000
#define SRAM_BASE_ADDR 0x68000000


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    // *sram_addr = 'aa';
    volatile uint8_t *p = (uint8_t *) SRAM_BASE_ADDR;

    /* ��ʼ������ */
    uart_init(115200);

    /* ��ʼ�� FSMC */
    FSMC_Init();

    // д�����
    *p = 0xAA;
    // ��ȡ����
    printf("\np:0x%x", *p);


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


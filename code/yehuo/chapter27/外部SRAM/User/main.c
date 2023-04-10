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
// #define SRAM_BASE_ADDR 0x68000000


/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
  uint32_t temp;
    // *sram_addr = 'aa';
    // volatile uint8_t *p = (uint8_t *) SRAM_BASE_ADDR;

    /* ��ʼ������ */
    uart_init(115200);

    /* ��ʼ�� FSMC */
    FSMC_Init();

    /* ����һ���ַ��� */
    printf("����һ��EEPROM��дʵ��\r\n");

    // ��SRAMд��8λ����
    *(uint8_t*) Bank1_SRAM3_ADDR = (uint8_t)0xAA;
    printf("\r\nָ�����SRAM��д������0xAA \r\n");

    // ��SRAM��ȡ����
    temp = *(uint8_t *)(Bank1_SRAM3_ADDR);
    printf("\n��ȡ����:0x%x\r\n", temp);

    // д/�� 16 λ����
    *(uint16_t*) (Bank1_SRAM3_ADDR + 10) = (uint16_t)0xBBBB;
    printf("\r\nָ�����SRAM��д������0xBBBB \r\n");

    temp = *(uint16_t *)(Bank1_SRAM3_ADDR+10);
    printf("\n��ȡ����:0x%x\r\n", temp);

    // д/�� 32 λ����
    *(uint32_t*) (Bank1_SRAM3_ADDR + 20) = (uint32_t)0xCCCCCCCC;
    printf("\r\n11ָ�����SRAM��д������0xCCCCCCCC \r\n");

    temp = *(uint32_t *)(Bank1_SRAM3_ADDR + 20);
    printf("\n��ȡ����:0x%x\r\n", temp);



    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


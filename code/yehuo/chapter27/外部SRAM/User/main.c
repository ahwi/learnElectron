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
#include "bsp_sram.h"

void Delay(__IO u32 nCount);

// #define sram_addr (unsinged int32_t)0x68000000
// #define SRAM_BASE_ADDR 0x68000000


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
  uint32_t temp;
    // *sram_addr = 'aa';
    // volatile uint8_t *p = (uint8_t *) SRAM_BASE_ADDR;

    /* 初始化串口 */
    uart_init(115200);

    /* 初始化 FSMC */
    FSMC_Init();

    /* 发送一个字符串 */
    printf("这是一个EEPROM读写实验\r\n");

    // 向SRAM写入8位数据
    *(uint8_t*) Bank1_SRAM3_ADDR = (uint8_t)0xAA;
    printf("\r\n指针访问SRAM，写入数据0xAA \r\n");

    // 从SRAM读取数据
    temp = *(uint8_t *)(Bank1_SRAM3_ADDR);
    printf("\n读取数据:0x%x\r\n", temp);

    // 写/读 16 位数据
    *(uint16_t*) (Bank1_SRAM3_ADDR + 10) = (uint16_t)0xBBBB;
    printf("\r\n指针访问SRAM，写入数据0xBBBB \r\n");

    temp = *(uint16_t *)(Bank1_SRAM3_ADDR+10);
    printf("\n读取数据:0x%x\r\n", temp);

    // 写/读 32 位数据
    *(uint32_t*) (Bank1_SRAM3_ADDR + 20) = (uint32_t)0xCCCCCCCC;
    printf("\r\n11指针访问SRAM，写入数据0xCCCCCCCC \r\n");

    temp = *(uint32_t *)(Bank1_SRAM3_ADDR + 20);
    printf("\n读取数据:0x%x\r\n", temp);



    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


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
#define SRAM_BASE_ADDR 0x68000000


/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    // *sram_addr = 'aa';
    volatile uint8_t *p = (uint8_t *) SRAM_BASE_ADDR;

    /* 初始化串口 */
    uart_init(115200);

    /* 初始化 FSMC */
    FSMC_Init();

    // 写入操作
    *p = 0xAA;
    // 读取操作
    printf("\np:0x%x", *p);


    /* 发送一个字符串 */
    printf("这是一个EEPROM读写实验\r\n");

    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


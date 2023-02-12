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
// #include "bsp_debug_usart.h"
#include "bsp_usart_dma.h"

extern uint8_t SendBuff[SENDBUFF_SIZE];
void Delay(__IO u32 nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    uint16_t i;
    /* 初始化USART */
    Debug_USART_Config();

    /* 配置使用DMA模式 */
    USART_DMA_Config();

    /* LED IO口初始化 */
    LED_GPIO_Config();

    /* 填充将要发送的数据 */
    for(i=0; i < SENDBUFF_SIZE; i ++)
    {
        SendBuff[i] = 'A';
    }

    /* USART1向DMA发出TX请求 */
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

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


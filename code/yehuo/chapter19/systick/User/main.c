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
#include "bsp_SysTick.h"

void Delay(__IO u32 nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    /* LED IO口初始化 */
    LED_GPIO_Config();

    /* 配置 SysTick 为1ms中断一次，时间到后触发定时中断，
     * 进入 stm32fxx_it.c 文件的SysTick_Handler处理
     */
    SysTick_Init();

    while(1)
    {
        LED0(ON); 
        // Delay_ms(1000);
        SysTick_Delay_ms(1000);
        LED0(OFF);
        // Delay_ms(1000);
        SysTick_Delay_ms(1000);
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


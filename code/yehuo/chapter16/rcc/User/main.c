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
#include "bsp_clkconfig.h"

void Delay(__IO u32 nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    // MCO GPIO 初始化
    MCO1_GPIO_Config(); 
    MCO2_GPIO_Config();

    // MCO1 输出PLLCLK
    RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);
    // MCO2 输出PLLCLK
    RCC_MCO2Config(RCC_MCO2Source_PLLCLK, RCC_MCO2Div_1);

    // 使用HSE,配置系统时钟为168M
    // 野火晶振为25M，正点原子为8M
    HSE_SetSysClock(8, 336, 2, 7);

    // // 超频到216M, 最高是216M
    // HSE_SetSysClock(8, 432, 2, 9);

    // // 使用HSI,配置系统时钟为168M
    // HSI_SetSysClock(25, 336, 2, 7);

    /* LED IO口初始化 */
    LED_GPIO_Config();
    while(1)
    {
        LED0(ON); 
        Delay(0xFFFFFF);
        LED0(OFF);
        Delay(0xFFFFFF);
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


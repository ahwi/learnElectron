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

void Delay(__IO u32 nCount);

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
		/* 程序来到main函数之前，启动文件：statup_stm32f4xx.s已经调用
		* SystemInit()函数把系统时钟初始化成168MHZ
		* SystemInit()在system_stm32f4xx.c中定义
		* 如果用户想修改系统时钟，可自行编写程序修改
		*/
		  /* add your code here ^_^. */

    /* LED IO口初始化 */
    LED_GPIO_Config();
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


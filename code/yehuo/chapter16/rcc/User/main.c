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
#include "bsp_clkconfig.h"

void Delay(__IO u32 nCount);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    // MCO GPIO ��ʼ��
    MCO1_GPIO_Config(); 
    MCO2_GPIO_Config();

    // MCO1 ���PLLCLK
    RCC_MCO1Config(RCC_MCO1Source_PLLCLK, RCC_MCO1Div_1);
    // MCO2 ���PLLCLK
    RCC_MCO2Config(RCC_MCO2Source_PLLCLK, RCC_MCO2Div_1);

    // ʹ��HSE,����ϵͳʱ��Ϊ168M
    // Ұ����Ϊ25M������ԭ��Ϊ8M
    HSE_SetSysClock(8, 336, 2, 7);

    // // ��Ƶ��216M, �����216M
    // HSE_SetSysClock(8, 432, 2, 9);

    // // ʹ��HSI,����ϵͳʱ��Ϊ168M
    // HSI_SetSysClock(25, 336, 2, 7);

    /* LED IO�ڳ�ʼ�� */
    LED_GPIO_Config();
    while(1)
    {
        LED0(ON); 
        Delay(0xFFFFFF);
        LED0(OFF);
        Delay(0xFFFFFF);
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


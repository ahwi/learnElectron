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
#include "bsp_SysTick.h"

void Delay(__IO u32 nCount);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* LED IO�ڳ�ʼ�� */
    LED_GPIO_Config();

    /* ���� SysTick Ϊ1ms�ж�һ�Σ�ʱ�䵽�󴥷���ʱ�жϣ�
     * ���� stm32fxx_it.c �ļ���SysTick_Handler����
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

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


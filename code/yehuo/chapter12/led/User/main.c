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

void Delay(__IO u32 nCount);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
		/* ��������main����֮ǰ�������ļ���statup_stm32f4xx.s�Ѿ�����
		* SystemInit()������ϵͳʱ�ӳ�ʼ����168MHZ
		* SystemInit()��system_stm32f4xx.c�ж���
		* ����û����޸�ϵͳʱ�ӣ������б�д�����޸�
		*/
		  /* add your code here ^_^. */

    /* LED IO�ڳ�ʼ�� */
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

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


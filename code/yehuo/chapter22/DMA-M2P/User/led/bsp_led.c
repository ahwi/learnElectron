#include "bsp_led.h"


void LED_GPIO_Config(void)
{
    /* ����һ�� GPIO_InitTypeDef ���͵Ľṹ�� */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* ����LED��ص�GPIO����ʱ�� */
    RCC_AHB1PeriphClockCmd( LED0_GPIO_CLK | 
                            LED1_GPIO_CLK,
                            ENABLE);

    /* ѡ��Ҫ���Ƶ� GPIO ����*/
    GPIO_InitStructure.GPIO_Pin     = LED0_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;        // ���ģʽ
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;        // �������
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;         // ����ģʽ
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_2MHz;      // �������� 2MHz

    /* ��ʼ��GPIO */
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = LED1_PIN;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

    /*�ر�LED*/
    LED0(OFF);
    LED1(OFF);

}


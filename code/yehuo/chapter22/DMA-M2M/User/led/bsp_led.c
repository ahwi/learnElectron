#include "bsp_led.h"


void LED_GPIO_Config(void)
{
    /* 定义一个 GPIO_InitTypeDef 类型的结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启LED相关的GPIO外设时钟 */
    RCC_AHB1PeriphClockCmd( LED0_GPIO_CLK | 
                            LED1_GPIO_CLK,
                            ENABLE);

    /* 选择要控制的 GPIO 引脚*/
    GPIO_InitStructure.GPIO_Pin     = LED0_PIN;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;        // 输出模式
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;        // 推挽输出
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;         // 上拉模式
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_2MHz;      // 引脚速率 2MHz

    /* 初始化GPIO */
    GPIO_Init(LED0_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin     = LED1_PIN;
    GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);

    /*关闭LED*/
    LED0(OFF);
    LED1(OFF);

}


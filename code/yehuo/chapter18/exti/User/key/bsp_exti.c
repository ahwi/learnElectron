#include "bsp_exti.h"

/**
 * @brief 配置嵌套向量中断控制器NVIC
 * @param 无
 * @retval 无
*/
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 配置NVIC为优先级分组1 */
    /* 提示 NVIC_PriorityGroupConfig() 在整个工程中只需要调用一次来配置优先级分组 */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    /* 配置中断源：按键KEY0(PE4) */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
    /* 配置抢占优先级: 1*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    /* 配置子优先级: 1*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    /* 使能中断通道 */
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* 配置中断源：按键KEY3(PE3) */
    NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
    NVIC_Init(&NVIC_InitStructure);

}


/**
 * @brief 配置 KEY0(PE4) KEY1(PE3) 按键中断，并设置中断优先级
 * @param 无
 * @retval 无
*/
void EXTI_Key_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    EXTI_InitTypeDef EXTI_InitStructure;

    /* 开启按键GPIO口的时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    /* 使能SYSCFG时钟，使用GPIO外部中断时必须使能SYSCFG时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

    /* 配置 NVIC */
    NVIC_Configuration();

    /* 选择KEY0的引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
    /* 设置引脚为输入模式 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    /* 设置为100M */
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    /* 设置引脚不上拉也不下拉 */
    // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    /* 使用上面的结构体初始化按键 */
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* 连接 EXTI 中断源到 KEY0 引脚*/
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource4);

    /* 选择 EXTI 中断源 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line4;
    /* 中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    /* 下降沿触发 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    /* 使能中断/事件线 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    /* 选择KEY1引脚 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    /* 其他配置与上面相同 */
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    /* 连接 EXTI 中断源到 KEY1 引脚*/
    SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource3);

    /* 选择 EXTI 中断源 */
    EXTI_InitStructure.EXTI_Line = EXTI_Line3;
    /* 中断模式 */
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    /* 下降沿触发 */
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    /* 使能中断/事件线 */
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

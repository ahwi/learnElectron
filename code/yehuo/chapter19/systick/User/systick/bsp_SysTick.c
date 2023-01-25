#include "bsp_SysTick.h"

static __IO u32 TimingDelay;

/**
 * @brief   启动系统滴答定时器 SysTick
 * @param   无
 * @retval  无
*/
void SysTick_Init(void)
{
    /* SystemFrequency / 1000       1ms中断一次
     * SystemFrequency / 100000     10us中断一次
     * SystemFrequency / 1000000    1us中断一次
     */
    if(SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */
        while(1);
    }
}


/**
 * @brief us延时程序，1ms为一个单位
 * @param
 * @arg mTime: Delay_ms(1) 则实现延时1ms
 * @retval 无
*/
void Delay_ms(__IO u32 mTime)
{
    TimingDelay = mTime;

    while(TimingDelay != 0);
}

void SysTick_Delay_ms(__IO u32 mTime)
{
    uint32_t i;
    /* SystemFrequency / 1000       1ms  定时器到期一次(CRTL位 16 置 1)
     * SystemFrequency / 100000     10us 定时器到期一次(CRTL位 16 置 1)
     * SystemFrequency / 1000000    1us  定时器到期一次(CRTL位 16 置 1)
     */
    SysTick_Config(SystemCoreClock/1000);

    for(i=0; i<mTime; i++)
    {
        // 当计数器的值减小到0的时候，CRTL寄存器的位 16 会置 1
        while(!((SysTick->CTRL)&(1<<16)));
    }

    // 关闭 SysTick定时器
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
 * @brief 递减节拍程序
 * @param 无
 * @param 无
 * @attention 在 SysTick 中断函数 SysTick_Handler() 调用
*/
void TimingDelay_Decrement(void)
{
    if(TimingDelay != 0x00)
        TimingDelay --;
}

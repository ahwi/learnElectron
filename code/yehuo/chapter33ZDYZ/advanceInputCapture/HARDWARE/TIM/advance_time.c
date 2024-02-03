#include "advance_time.h"
#include "usart.h"

__IO uint32_t IC1Value;
__IO uint32_t IC2Value;
__IO float DutyCycle = 0;
__IO float Frequency = 0;

// 计数器和周期的计算
/**
 * 秒的换算：1s = 1000 ms  = 1000 000 um = 1000 000 000 nm = 1000 000 000 000 pm
 * 定时器2的时钟源为TIMxCLK = HCLK/2 = 84MHz 84000000Hz
 * 设置分频器值为 840 - 1，则数一次的频率为：100 000hz = 10 um
 * 数1000 次的时间 = 10 ms = 100Hz
*/
uint16_t TIM2_Prescaler = 840 - 1;
uint16_t TIM2_ReloadValue = 1000 - 1;

// 配置脉宽，也就是占空比
uint32_t TIM2_Pulse = 300;

// 配置高级定时器8的计数器和周期
uint16_t TIM8_Prescaler = 1680 - 1;
// uint16_t TIM8_ReloadValue = 1000 - 1;

/**
 * GPIO 配置
 * */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // 配置GPIO
    // PWM输出 PA5; PWM输入捕获 PC6

    // 使能GPIO时钟
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC, ENABLE);

    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(GPIOA, &GPIO_InitStruct);   


    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOC, &GPIO_InitStruct);   

    GPIO_PinAFConfig(GPIOA,  GPIO_PinSource5, GPIO_AF_TIM2);
    GPIO_PinAFConfig(GPIOC,  GPIO_PinSource6, GPIO_AF_TIM8);
}


 /**
  * @brief  高级控制定时器 TIMx,x[1,8]中断优先级配置
  * @param  无
  * @retval 无
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // 设置中断组为0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// 设置中断来源
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn; 	
		// 设置抢占优先级
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // 设置子优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 *  定时器2 配置为PWM输出
 * 
*/
void Tim2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // 使能时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 配置时基
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM2_Prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = TIM2_ReloadValue;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);


    // 配置比较输出
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = TIM2_Pulse;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    // 不需要设置 TIM2没用到
    // TIM_OCInitStruct.TIM_OutputNState;
    // TIM_OCInitStruct.TIM_OCNPolarity;
    // TIM_OCInitStruct.TIM_OCIdleState;
    // TIM_OCInitStruct.TIM_OCNIdleState;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    // 使用重载载的影子寄存器
    TIM_CCPreloadControl(TIM2, ENABLE);

    // 使能定时器2
    TIM_Cmd(TIM2, ENABLE);
}


/**
 * 高级定时器8 的配置
*/
void AdvaceTim8_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_ICInitTypeDef TIM_ICInitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // // 输入引脚配置 PC6
    // // 使能GPIO时钟 
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // GPIO_Init(GPIOA, &GPIO_InitStruct);   


    // 使能时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

    // 配置时基
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM8_Prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF-1;
    // TIM_TimeBaseInitStruct.TIM_ClockDivision;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;    
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

    // 配置输入捕获
    // IC1捕获：上升沿触发 TI1F1
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0;
    // TIM_ICInit(TIM8, &TIM_ICInitStruct);
    TIM_PWMIConfig(TIM8, &TIM_ICInitStruct);

    // 选择输入捕获的触发信号
    TIM_SelectInputTrigger(TIM8, TIM_TS_TI1FP1);

    // 选择从模式：复位模式
    // PWM 输入复位时，从模式控制器必须工作在复位模式，当捕获开始时，计数器CNT会被复位
    TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);

    // 使能捕获中断，这个中断针对的是主捕获通道（测量周期那个）
    TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);
    TIM_ClearITPendingBit(TIM8, TIM_FLAG_CC1);

    // 使能定时器8
    TIM_Cmd(TIM8, ENABLE);

}

void TIMx_Configuration(void)
{
    // GPIO 配置
    GPIO_Configuration();

    // 中断配置
    TIMx_NVIC_Configuration();

    // 初始化定时器2：输出PWM波
    Tim2_Configuration();

    // 初始化高级定时器8：输入PWM捕获
    AdvaceTim8_Configuration();

}

/**
 * 定时器8中断
 * 
*/
void TIM8_CC_IRQHandler(void)
{
    
    //清除定时器捕获/比较1中断
    TIM_ClearITPendingBit(TIM8, TIM_FLAG_CC1);

    // 获取输入比较
    IC1Value = TIM_GetCapture1(TIM8);
    IC2Value = TIM_GetCapture2(TIM8);
    printf("IC1Value = %d IC2Value = %d\r\n", IC1Value, IC2Value);

    if(IC1Value != 0){
        // 占空比计算
        DutyCycle = (float)(IC2Value * 100) / IC1Value;

        // 频率计算
        Frequency = 168000000/1680/(float)(IC1Value+1);

        printf("占空比: %0.2f%% 频率: %0.2fHZ\r\n", DutyCycle, Frequency);
    }
    else {
        DutyCycle = 0;
        Frequency = 0;
    }

}

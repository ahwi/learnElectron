#include "advance_time.h"
#include "usart.h"

__IO uint32_t IC1Value;
__IO uint32_t IC2Value;
__IO float DutyCycle = 0;
__IO float Frequency = 0;

// �����������ڵļ���
/**
 * ��Ļ��㣺1s = 1000 ms  = 1000 000 um = 1000 000 000 nm = 1000 000 000 000 pm
 * ��ʱ��2��ʱ��ԴΪTIMxCLK = HCLK/2 = 84MHz 84000000Hz
 * ���÷�Ƶ��ֵΪ 840 - 1������һ�ε�Ƶ��Ϊ��100 000hz = 10 um
 * ��1000 �ε�ʱ�� = 10 ms = 100Hz
*/
uint16_t TIM2_Prescaler = 840 - 1;
uint16_t TIM2_ReloadValue = 1000 - 1;

// ��������Ҳ����ռ�ձ�
uint32_t TIM2_Pulse = 300;

// ���ø߼���ʱ��8�ļ�����������
uint16_t TIM8_Prescaler = 1680 - 1;
// uint16_t TIM8_ReloadValue = 1000 - 1;

/**
 * GPIO ����
 * */
void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    // ����GPIO
    // PWM��� PA5; PWM���벶�� PC6

    // ʹ��GPIOʱ��
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
  * @brief  �߼����ƶ�ʱ�� TIMx,x[1,8]�ж����ȼ�����
  * @param  ��
  * @retval ��
  */
static void TIMx_NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure; 
    // �����ж���Ϊ0
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);		
		// �����ж���Դ
    NVIC_InitStructure.NVIC_IRQChannel = TIM8_CC_IRQn; 	
		// ������ռ���ȼ�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;	 
	  // ���������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;	
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 *  ��ʱ��2 ����ΪPWM���
 * 
*/
void Tim2_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_OCInitTypeDef TIM_OCInitStruct;

    // ʹ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // ����ʱ��
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM2_Prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = TIM2_ReloadValue;
    TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;    
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);


    // ���ñȽ����
    TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStruct.TIM_Pulse = TIM2_Pulse;
    TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High;
    // ����Ҫ���� TIM2û�õ�
    // TIM_OCInitStruct.TIM_OutputNState;
    // TIM_OCInitStruct.TIM_OCNPolarity;
    // TIM_OCInitStruct.TIM_OCIdleState;
    // TIM_OCInitStruct.TIM_OCNIdleState;
    TIM_OC1Init(TIM2, &TIM_OCInitStruct);

    // ʹ�������ص�Ӱ�ӼĴ���
    TIM_CCPreloadControl(TIM2, ENABLE);

    // ʹ�ܶ�ʱ��2
    TIM_Cmd(TIM2, ENABLE);
}


/**
 * �߼���ʱ��8 ������
*/
void AdvaceTim8_Configuration(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
    TIM_ICInitTypeDef TIM_ICInitStruct;
    GPIO_InitTypeDef GPIO_InitStruct;

    // // ������������ PC6
    // // ʹ��GPIOʱ�� 
    // RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6;
    // GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    // GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
    // GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
    // GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    // GPIO_Init(GPIOA, &GPIO_InitStruct);   


    // ʹ��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

    // ����ʱ��
    TIM_TimeBaseInitStruct.TIM_Prescaler = TIM8_Prescaler;
    TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStruct.TIM_Period = 0xFFFF-1;
    // TIM_TimeBaseInitStruct.TIM_ClockDivision;
    TIM_TimeBaseInitStruct.TIM_RepetitionCounter = 0;    
    TIM_TimeBaseInit(TIM8, &TIM_TimeBaseInitStruct);

    // �������벶��
    // IC1���������ش��� TI1F1
    TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;
    TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
    TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICInitStruct.TIM_ICFilter = 0;
    // TIM_ICInit(TIM8, &TIM_ICInitStruct);
    TIM_PWMIConfig(TIM8, &TIM_ICInitStruct);

    // ѡ�����벶��Ĵ����ź�
    TIM_SelectInputTrigger(TIM8, TIM_TS_TI1FP1);

    // ѡ���ģʽ����λģʽ
    // PWM ���븴λʱ����ģʽ���������빤���ڸ�λģʽ��������ʼʱ��������CNT�ᱻ��λ
    TIM_SelectSlaveMode(TIM8, TIM_SlaveMode_Reset);
    TIM_SelectMasterSlaveMode(TIM8, TIM_MasterSlaveMode_Enable);

    // ʹ�ܲ����жϣ�����ж���Ե���������ͨ�������������Ǹ���
    TIM_ITConfig(TIM8, TIM_IT_CC1, ENABLE);
    TIM_ClearITPendingBit(TIM8, TIM_FLAG_CC1);

    // ʹ�ܶ�ʱ��8
    TIM_Cmd(TIM8, ENABLE);

}

void TIMx_Configuration(void)
{
    // GPIO ����
    GPIO_Configuration();

    // �ж�����
    TIMx_NVIC_Configuration();

    // ��ʼ����ʱ��2�����PWM��
    Tim2_Configuration();

    // ��ʼ���߼���ʱ��8������PWM����
    AdvaceTim8_Configuration();

}

/**
 * ��ʱ��8�ж�
 * 
*/
void TIM8_CC_IRQHandler(void)
{
    
    //�����ʱ������/�Ƚ�1�ж�
    TIM_ClearITPendingBit(TIM8, TIM_FLAG_CC1);

    // ��ȡ����Ƚ�
    IC1Value = TIM_GetCapture1(TIM8);
    IC2Value = TIM_GetCapture2(TIM8);
    printf("IC1Value = %d IC2Value = %d\r\n", IC1Value, IC2Value);

    if(IC1Value != 0){
        // ռ�ձȼ���
        DutyCycle = (float)(IC2Value * 100) / IC1Value;

        // Ƶ�ʼ���
        Frequency = 168000000/1680/(float)(IC1Value+1);

        printf("ռ�ձ�: %0.2f%% Ƶ��: %0.2fHZ\r\n", DutyCycle, Frequency);
    }
    else {
        DutyCycle = 0;
        Frequency = 0;
    }

}

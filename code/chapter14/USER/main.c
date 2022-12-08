#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"
#include "usart.h"
#include "exti.h"
#include "pwm.h"

int main(void)
{
	u16 pwmval = 0;
	u8 dir = 1;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����ϵͳ�ж����ȼ�����2
	delay_init(168);	//��ʼ����ʱ����
	TIM14_PWM_Init(500-1, 84-1); //84M/84=1Mhz�ļ���Ƶ�ʣ���װ��ֵ500������PWMƵ��Ϊ1M/500=2Hhz
	
	while(1)
	{
		delay_ms(10);
		if(dir)
			pwmval ++;
		else
			pwmval --;
		
		if(pwmval > 300)
			dir = 0;
		else if(pwmval == 0)
			dir = 1;
		
		TIM_SetCompare1(TIM14, pwmval);	//�޸ıȽ�ֵ���޸�ռ�ձ�
	}
}

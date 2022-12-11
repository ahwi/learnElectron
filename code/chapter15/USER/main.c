#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "timer.h"


extern u8 TIM5CH1_CAPTURE_STA;	//����״̬����
extern u32 TIM5CH1_CAPTURE_VAL;	//���벶��ֵ��TIM2/TIM5��32λ��

int main(void)
{
	long long temp = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	//����ϵͳ�ж����ȼ�����2
	delay_init(168);	//��ʼ����ʱ����
	uart_init(115200);	//��ʼ����ʱ����
	TIM14_PWM_Init(500-1, 84-1); //84M/84=1Mhz�ļ���Ƶ�ʣ���װ��ֵ500������PWMƵ��Ϊ1M/500=2Hhz
	TIM5_CH1_Cap_Init(0xFFFFFFFF, 84-1);	//��1Mhz��Ƶ�ʼ���
	
	while(1)
	{
		delay_ms(10);
		TIM_SetCompare1(TIM14, TIM_GetCapture1(TIM14)+1);
		if(TIM_GetCapture1(TIM14)==300) TIM_SetCompare1(TIM14, 0);
		
		if(TIM5CH1_CAPTURE_STA & 0x80)	//�ɹ�������һ�θߵ�ƽ
		{
			temp = TIM5CH1_CAPTURE_STA & 0x3f;
			temp *= 0xFFFFFFFF;	//���ʱ���ܺ�
			temp += TIM5CH1_CAPTURE_VAL;	//�õ��ܵĸߵ�ƽʱ��
			printf("HIGH:%lld us\r\n", temp);	//��ӡ�ܵĸߵ�ƽʱ��
			TIM5CH1_CAPTURE_STA = 0;	//������һ�β���
		}
		//printf("running...\r\n");
	}
}

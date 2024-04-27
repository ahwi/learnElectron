#include "tpad.h"
#include "delay.h"
#include "usart.h"

#define TPAD_ARR_MAX_VAL 0xFFFFFFFF
//����ARRֵ��TIM2��32λ��ʱ����
vu16 tpad_default_val = 0;

//���ص�ʱ��û���ְ��£�����������Ҫ��ʱ��
//��ʼ����������
//��ÿ��ص�ʱ����������ȡֵ
//psc:��Ƶϵ����ԽС��������Խ��
//����ֵ��0,��ʼ���ɹ���1����ʼ��ʧ��
u8 TPAD_Init(u8 psc)
{
	u16 buf[10];
	u16 temp;
	u8 j, i;
	TIM2_CH1_Cap_Init(TPAD_ARR_MAX_VAL, psc-1);	//���÷�Ƶϵ��
	for(i=0; i<10; i++)	//������ȡ10��
	{
		buf[i] = TPAD_Get_Val();
		delay_ms(10);
	}
	
	for(i=0; i<9; i++)	//����
	{
		for(j=i+1; i<10; i++)
		{
			if(buf[i]>buf[j])	//��������
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	temp=0;
	for(i=2; i<8; i++)
		temp += buf[i];	//ȡ�м��6��������ƽ��
	tpad_default_val = temp/6;
	printf("tpad_default_val:%d\r\n", tpad_default_val);
	if(tpad_default_val > TPAD_ARR_MAX_VAL/2) 
		return 1;
	
	return 0;	//��ʼ����������TPAD_ARR_MAX_VAL/2����ֵ��������
}

//��λ1��
//�ͷŵ��ݵ������������ʱ���ļ���ֵ
void TPAD_Reset(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//��ʼ��PA5����Ϊ�������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;	//����
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA5�������0��ʹ���ݽ��зŵ�
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	
	delay_ms(5);
	//����жϱ�־
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update|TIM_IT_CC1);
	//���ü�����Ϊ0
	TIM_SetCounter(TIM2, 0);
	
	//��ʼ��PA5Ϊ����ģʽ������������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//����ģʽ
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//����������
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//�õ���ʱ������ֵ
//�����ʱ����ֱ�ӷ��ض�ʱ���ļ���ֵ
//����ֵ������ֵ/����ֵ����ʱ������·��أ�
u16 TPAD_Get_Val(void)
{
	//�ȸ�λ
	TPAD_Reset();
	
	//ѭ���ȴ�������
	while(TIM_GetFlagStatus(TIM2, TIM_IT_CC1) == RESET) //�ȴ�����������
	{
		if(TIM_GetCounter(TIM2) > TPAD_ARR_MAX_VAL - 500)
			return TIM_GetCounter(TIM2);	//��ʱ�ˣ�ֱ�ӷ���CNT��ֵ
	
	}
	
	//����ֵ
	return TIM_GetCapture1(TIM2);
}

//��ȡn�Σ�ȡ���ֵ
//n��������ȡ�Ĵ���
//����ֵ��n�ζ������������������ֵ
u16 TPAD_Get_MaxVal(u8 n)
{
	u16 temp=0;
	u16 res=0;
	while(n--)
	{
		temp = TPAD_Get_Val();	//�õ�һ��ֵ
		if(temp > res)
			res = temp;
	}
	return res;
}

//ɨ�败������
//mode:0,��֧����������������һ�α����ɿ����ܰ���һ�Σ�;1,֧����������������һֱ����ȥ��
//����ֵ��0��û�а��£�1���а���
#define TPAD_GATE_VAL 100	//����������ֵ��Ҳ���Ǳ������tpad_default_val+TPAD_GAT_VAL������Ϊ����Ч����

u8 TPAD_Scan(u8 mode)
{
	static u8 keyen = 0;	//0�����Կ�ʼ��⣻> 0:�����ܿ�ʼ���
	u8 res=0;
	u8 sample=3;	//Ĭ�ϲ�������Ϊ3��
	u16 rval;
	if(mode)
	{
		sample=6;	//֧��������ʱ�����ò�������Ϊ6��
		keyen=0;	//֧������
	}
	
	rval = TPAD_Get_MaxVal(sample);
	if(rval>(tpad_default_val+TPAD_GATE_VAL)&&rval<(10*tpad_default_val))	//rvalֵ��Ч
	{
		//if((keyen==0)&&(rval>(tpad_default_val+TPAD_GAT_VAL)))
		if(keyen==0)	//�˴ΰ�����Ч
		{
			res=1;
		}
		
		keyen = 3;	//����ʱ������Ҫ����3��֮����ܰ�����Ч
	}
	if(keyen) 
		keyen--;
	
	return res;
}

//��ʱ��2ͨ��2���벶������
//arr:�Զ���װֵ
//psc:ʱ��Ԥ��Ƶ��
void TIM2_CH1_Cap_Init(u32 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	//ʹ��TIM2ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//ʹ��GPIOAʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//GPIOA5����Ϊ��ʱ��2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	
	//��ʼ��PA5�����ù��ܣ�����������
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//��ʼ��TIM2
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc; //�������Զ���װֵ
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//���ϼ���ģʽ
	TIM_TimeBaseInitStruct.TIM_Period = arr;	//Ԥ��Ƶ��
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//�趨ʱ�ӷָ���TDTS = Tck_tim
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//��ʼ��TIM2 IC1
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;	//CC1S=01 ѡ������� IC1ӳ�䵽TIM2��
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	//�����ز���
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//�������벻��Ƶ
	TIM_ICInitStruct.TIM_ICFilter = 0x00;;	//IC2F=000 ���������˲������˲�
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM2, ENABLE);	//ʹ�ܶ�ʱ��2
}

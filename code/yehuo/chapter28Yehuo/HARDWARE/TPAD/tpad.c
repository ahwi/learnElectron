#include "tpad.h"
#include "delay.h"
#include "usart.h"

#define TPAD_ARR_MAX_VAL 0xFFFFFFFF
//最大的ARR值（TIM2是32位定时器）
vu16 tpad_default_val = 0;

//空载的时候（没有手按下），计数器需要的时间
//初始化触摸按键
//获得空载的时候触摸按键的取值
//psc:分频系数，越小，灵敏度越高
//返回值：0,初始化成功；1，初始化失败
u8 TPAD_Init(u8 psc)
{
	u16 buf[10];
	u16 temp;
	u8 j, i;
	TIM2_CH1_Cap_Init(TPAD_ARR_MAX_VAL, psc-1);	//设置分频系数
	for(i=0; i<10; i++)	//连续读取10次
	{
		buf[i] = TPAD_Get_Val();
		delay_ms(10);
	}
	
	for(i=0; i<9; i++)	//排序
	{
		for(j=i+1; i<10; i++)
		{
			if(buf[i]>buf[j])	//升序排序
			{
				temp = buf[i];
				buf[i] = buf[j];
				buf[j] = temp;
			}
		}
	}
	temp=0;
	for(i=2; i<8; i++)
		temp += buf[i];	//取中间的6个数进行平均
	tpad_default_val = temp/6;
	printf("tpad_default_val:%d\r\n", tpad_default_val);
	if(tpad_default_val > TPAD_ARR_MAX_VAL/2) 
		return 1;
	
	return 0;	//初始化遇到超过TPAD_ARR_MAX_VAL/2的数值，不正常
}

//复位1次
//释放电容电量，并清除定时器的计数值
void TPAD_Reset(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//初始化PA5引脚为推挽输出
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_DOWN;	//下拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//PA5引脚输出0，使电容进行放电
	GPIO_ResetBits(GPIOA, GPIO_Pin_5);
	
	delay_ms(5);
	//清除中断标志
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update|TIM_IT_CC1);
	//设置计数器为0
	TIM_SetCounter(TIM2, 0);
	
	//初始化PA5为复用模式，不带上下拉
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;	//复用模式
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;	//不带上下拉
	GPIO_Init(GPIOA, &GPIO_InitStruct);
}

//得到定时器捕获值
//如果超时，则直接返回定时器的计数值
//返回值：捕获值/计数值（超时的情况下返回）
u16 TPAD_Get_Val(void)
{
	//先复位
	TPAD_Reset();
	
	//循环等待上升沿
	while(TIM_GetFlagStatus(TIM2, TIM_IT_CC1) == RESET) //等待捕获上升沿
	{
		if(TIM_GetCounter(TIM2) > TPAD_ARR_MAX_VAL - 500)
			return TIM_GetCounter(TIM2);	//超时了，直接返回CNT的值
	
	}
	
	//返回值
	return TIM_GetCapture1(TIM2);
}

//读取n次，取最大值
//n：连续获取的次数
//返回值：n次读数里面读到的最大读数值
u16 TPAD_Get_MaxVal(u8 n)
{
	u16 temp=0;
	u16 res=0;
	while(n--)
	{
		temp = TPAD_Get_Val();	//得到一次值
		if(temp > res)
			res = temp;
	}
	return res;
}

//扫描触摸按键
//mode:0,不支持连续触发（按下一次必须松开才能按下一次）;1,支持连续触发（可以一直按下去）
//返回值：0，没有按下；1，有按下
#define TPAD_GATE_VAL 100	//触摸的门限值，也就是必须大于tpad_default_val+TPAD_GAT_VAL，才认为是有效触摸

u8 TPAD_Scan(u8 mode)
{
	static u8 keyen = 0;	//0：可以开始检测；> 0:还不能开始检测
	u8 res=0;
	u8 sample=3;	//默认采样次数为3次
	u16 rval;
	if(mode)
	{
		sample=6;	//支持连按的时候，设置采样次数为6次
		keyen=0;	//支持连按
	}
	
	rval = TPAD_Get_MaxVal(sample);
	if(rval>(tpad_default_val+TPAD_GATE_VAL)&&rval<(10*tpad_default_val))	//rval值有效
	{
		//if((keyen==0)&&(rval>(tpad_default_val+TPAD_GAT_VAL)))
		if(keyen==0)	//此次按下有效
		{
			res=1;
		}
		
		keyen = 3;	//连按时，至少要经过3次之后才能按键有效
	}
	if(keyen) 
		keyen--;
	
	return res;
}

//定时器2通道2输入捕获配置
//arr:自动重装值
//psc:时钟预分频数
void TIM2_CH1_Cap_Init(u32 arr, u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	//使能TIM2时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	//使能GPIOA时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//GPIOA5复用为定时器2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_TIM2);
	
	//初始化PA5，复用功能，不带上下拉
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	
	//初始化TIM2
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc; //计数器自动重装值
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数模式
	TIM_TimeBaseInitStruct.TIM_Period = arr;	//预分频器
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;	//设定时钟分隔：TDTS = Tck_tim
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStruct);
	
	//初始化TIM2 IC1
	TIM_ICInitStruct.TIM_Channel = TIM_Channel_1;	//CC1S=01 选择输入端 IC1映射到TIM2上
	TIM_ICInitStruct.TIM_ICPolarity = TIM_ICPolarity_Rising;	//上升沿捕获
	TIM_ICInitStruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;	//配置输入不分频
	TIM_ICInitStruct.TIM_ICFilter = 0x00;;	//IC2F=000 配置输入滤波器不滤波
	TIM_ICInit(TIM2, &TIM_ICInitStruct);
	
	//使能定时器
	TIM_Cmd(TIM2, ENABLE);	//使能定时器2
}

#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "advance_time.h"



static void Delay(__IO uint32_t nCount);

int main(void)
{
	uart_init(115200);	//��ʼ�����ڲ�����115200

	// ��ʱ����ʼ��
	TIMx_Configuration();

	while(1)
	{

	}

}

static void Delay(__IO uint32_t nCount)
{
	for (; nCount != 0; nCount --);
}

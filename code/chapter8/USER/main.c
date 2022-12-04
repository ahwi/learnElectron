#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


int main(void)
{
	u8 key;	//�����ֵ
	delay_init(168);	//��ʼ����ʱ����
	LED_Init();	//��ʼ��LED�˿�
	BEEP_Init();	//��ʼ��������
	KEY_Init();	//��ʼ������

	LED0 = 0; //�ȵ������
	while(1){
		key = KEY_Scan(0);
		if(key){
			switch(key){
				case WKUP_PRES: 	//���Ʒ�����
					BEEP =! BEEP;
					break;
				case KEY0_PRES:		//����LED0��ת
					LED0 =! LED0;
					break;
				case KEY1_PRES:		//����LED1��ת
					LED1 =! LED1;
					break;
				case KEY2_PRES:		//����LED0 LED1��ת
					LED0 =! LED0;
					LED1 =! LED1;
					break;		
			}
		}else{
			delay_ms(10);
		}
	}

}

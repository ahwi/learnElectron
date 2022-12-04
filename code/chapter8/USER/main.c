#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "key.h"


int main(void)
{
	u8 key;	//保存键值
	delay_init(168);	//初始化延时函数
	LED_Init();	//初始化LED端口
	BEEP_Init();	//初始化蜂鸣器
	KEY_Init();	//初始化按键

	LED0 = 0; //先点亮红灯
	while(1){
		key = KEY_Scan(0);
		if(key){
			switch(key){
				case WKUP_PRES: 	//控制蜂鸣器
					BEEP =! BEEP;
					break;
				case KEY0_PRES:		//控制LED0翻转
					LED0 =! LED0;
					break;
				case KEY1_PRES:		//控制LED1翻转
					LED1 =! LED1;
					break;
				case KEY2_PRES:		//控制LED0 LED1翻转
					LED0 =! LED0;
					LED1 =! LED1;
					break;		
			}
		}else{
			delay_ms(10);
		}
	}

}

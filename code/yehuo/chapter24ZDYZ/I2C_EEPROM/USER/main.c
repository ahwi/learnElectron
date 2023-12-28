#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "i2c_ee.h"

#if 0
int main(void)
{
	uint8_t i;
	uint8_t data;
	uint8_t buff[8];
	uint8_t readBuff[8];
	
	// 串口初始化
	uart_init(115200);

	printf("这是一个EEPROM读写实验\r\n");
	
	// 单个字节写入测试
	EEPROM_Byte_Write(0x00, 0x13);
	printf("写入成功\r\n");
	EEPROM_Random_Read(0x00, &data);
	printf("读取到的数据 0x%x \r\n", data);
	
	// 页写入测试
	for(i=0; i<8; ++i){
		buff[i] = i;
	}
	
	EEPROM_Page_Write(0x00, buff, 8);
	EEPROM_Buffer_Read(0x00, readBuff, 8);
	printf("页写入测试，读取到的数据:\r\n");
	for(i=0; i < 8; i++){
		printf("0x%02x ", readBuff[i]);
	}
	
	while(1){
	}
}
#endif

#define TEST_SIZE 123

int main(void)
{
	uint8_t i;
	uint8_t buff[TEST_SIZE];
	uint8_t readBuff[TEST_SIZE];
	
	
	// 串口初始化
	uart_init(115200);

	printf("这是一个EEPROM读写实验\r\n");

	
	// 页写入测试
	for(i=0; i < TEST_SIZE; ++i){
		buff[i] = i;
	}
	
	printf("开始写入\r\n");
	EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
	printf("开始读取r\n");
	EEPROM_Buffer_Read(0x00, readBuff, TEST_SIZE);
	printf("页写入测试，读取到的数据:\r\n");
	for(i=0; i < TEST_SIZE; i++){
		printf("0x%02x ", readBuff[i]);
	}
	
	while(1){
	}
}

void delay(__IO u32 nCount)
{
	for(; nCount != 0; nCount --);
}





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
	
	// ���ڳ�ʼ��
	uart_init(115200);

	printf("����һ��EEPROM��дʵ��\r\n");
	
	// �����ֽ�д�����
	EEPROM_Byte_Write(0x00, 0x13);
	printf("д��ɹ�\r\n");
	EEPROM_Random_Read(0x00, &data);
	printf("��ȡ�������� 0x%x \r\n", data);
	
	// ҳд�����
	for(i=0; i<8; ++i){
		buff[i] = i;
	}
	
	EEPROM_Page_Write(0x00, buff, 8);
	EEPROM_Buffer_Read(0x00, readBuff, 8);
	printf("ҳд����ԣ���ȡ��������:\r\n");
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
	
	
	// ���ڳ�ʼ��
	uart_init(115200);

	printf("����һ��EEPROM��дʵ��\r\n");

	
	// ҳд�����
	for(i=0; i < TEST_SIZE; ++i){
		buff[i] = i;
	}
	
	printf("��ʼд��\r\n");
	EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
	printf("��ʼ��ȡr\n");
	EEPROM_Buffer_Read(0x00, readBuff, TEST_SIZE);
	printf("ҳд����ԣ���ȡ��������:\r\n");
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





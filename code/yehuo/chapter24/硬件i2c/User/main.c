/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   ��1.8.0�汾�⽨�Ĺ���ģ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F407 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_i2c_ee.h"

void Delay(__IO u32 nCount);


#if 0 // ����ҳд��
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    uint8_t data;
    uint8_t i;
    uint8_t buff[8];
    uint8_t readBuff[8];

    /* ��ʼ������ */
    uart_init(115200);

    /* ����һ���ַ��� */
    printf("����һ��EEPROM��дʵ��\r\n");

    /* ��ʼ��I2C */
    I2C_EE_Init();

    // ===========���ֽ�д�����========
    // EEPROM_Byte_Write(0x00, 0x13);
    // printf("д����Գɹ�\r\n");
    // EEPROM_Random_Read(0x00, &data);
    // printf("��д����Խ���, data=0x%x\r\n", data);

    // ===========ҳд�����============
    // ��buff��ֵ
    for(i=0; i < 8; i++){
      buff[i] = i;
    }
    EEPROM_Page_Write(0x00, buff, 8);
    // EEPROM_Random_Read(0x07, &data);
    EEPROM_Buffer_Read(0x00, readBuff, 8);
    printf("ҳ��д����Խ���, ��ȡ��������Ϊ:\r\n");
    for(i=0;i<8;i++){
        printf("0x%02x ", readBuff[i]);
    }

    while(1)
    {
    }

}
#endif

#define TEST_SIZE 256
/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    uint16_t i;
    uint8_t buff[TEST_SIZE];
    uint8_t readBuff[TEST_SIZE];

    /* ��ʼ������ */
    uart_init(115200);

    /* ����һ���ַ��� */
    printf("����һ��EEPROM��дʵ��\r\n");

    /* ��ʼ��I2C */
    I2C_EE_Init();

    // ===========���ֽ�д�����========
    // EEPROM_Byte_Write(0x00, 0x13);
    // printf("д����Գɹ�\r\n");
    // EEPROM_Random_Read(0x00, &data);
    // printf("��д����Խ���, data=0x%x\r\n", data);

    // ===========ҳд�����============
    // ��buff��ֵ
    printf("��ʼ��buff\r\n");
    for(i=0; i < TEST_SIZE; i++){
      buff[i] = i;
    }
    printf("��ʼд��\r\n");
    EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
    printf("��ʼ��ȡ\r\n");
    EEPROM_Buffer_Read(0x00, readBuff, TEST_SIZE);
    printf("ҳ��д����Խ���, ��ȡ��������Ϊ:\r\n");
    for(i=0;i<TEST_SIZE;i++){
        printf("0x%02x ", readBuff[i]);
    }
    printf("\r\n");
    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


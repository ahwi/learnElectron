/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2015-xx-xx
  * @brief   用1.8.0版本库建的工程模板
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F407 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
  
#include "stm32f4xx.h"
#include "bsp_led.h"
#include "bsp_debug_usart.h"
#include "bsp_i2c_ee.h"

void Delay(__IO u32 nCount);


#if 0 // 测试页写入
/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    uint8_t data;
    uint8_t i;
    uint8_t buff[8];
    uint8_t readBuff[8];

    /* 初始化串口 */
    uart_init(115200);

    /* 发送一个字符串 */
    printf("这是一个EEPROM读写实验\r\n");

    /* 初始化I2C */
    I2C_EE_Init();

    // ===========单字节写入测试========
    // EEPROM_Byte_Write(0x00, 0x13);
    // printf("写入测试成功\r\n");
    // EEPROM_Random_Read(0x00, &data);
    // printf("读写入测试结束, data=0x%x\r\n", data);

    // ===========页写入测试============
    // 给buff赋值
    for(i=0; i < 8; i++){
      buff[i] = i;
    }
    EEPROM_Page_Write(0x00, buff, 8);
    // EEPROM_Random_Read(0x07, &data);
    EEPROM_Buffer_Read(0x00, readBuff, 8);
    printf("页读写入测试结束, 读取到的数据为:\r\n");
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
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{
    uint16_t i;
    uint8_t buff[TEST_SIZE];
    uint8_t readBuff[TEST_SIZE];

    /* 初始化串口 */
    uart_init(115200);

    /* 发送一个字符串 */
    printf("这是一个EEPROM读写实验\r\n");

    /* 初始化I2C */
    I2C_EE_Init();

    // ===========单字节写入测试========
    // EEPROM_Byte_Write(0x00, 0x13);
    // printf("写入测试成功\r\n");
    // EEPROM_Random_Read(0x00, &data);
    // printf("读写入测试结束, data=0x%x\r\n", data);

    // ===========页写入测试============
    // 给buff赋值
    printf("初始化buff\r\n");
    for(i=0; i < TEST_SIZE; i++){
      buff[i] = i;
    }
    printf("开始写入\r\n");
    EEPROM_Buffer_Write(0x00, buff, TEST_SIZE);
    printf("开始读取\r\n");
    EEPROM_Buffer_Read(0x00, readBuff, TEST_SIZE);
    printf("页读写入测试结束, 读取到的数据为:\r\n");
    for(i=0;i<TEST_SIZE;i++){
        printf("0x%02x ", readBuff[i]);
    }
    printf("\r\n");
    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


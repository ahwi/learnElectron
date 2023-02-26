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
#include "bsp_spi_flash.h"

void Delay(__IO u32 nCount);



uint8_t read_buf[4096] = {0};
uint8_t write_buf[4096] = {0};

/**
  * @brief  主函数
  * @param  无
  * @retval 无
  */
int main(void)
{

    uint8_t flash_id = 0;
    uint32_t i = 0;

    /* 初始化串口 */
    uart_init(115200);

    /* 发送一个字符串 */
    printf("这是一个 FLASH 读写实验\r\n");

    SPI_FLASH_Init();

    flash_id = SPI_FLASH_Read_ID();
    printf("flash id = 0x%x\r\n", flash_id);

    // 擦除测试 
    printf("擦除开始\r\n");
    SPI_FLASH_Erase_Sector(4096*0);
    SPI_FLASH_Erase_Sector(4096*1);
    printf("擦除完成\r\n");

    SPI_FLASH_Read_Buff(0, read_buf, 4096);
    for(i=0;i<4096;i++){
      // 若不等于0xFF,说明擦除不成功
      if(read_buf[i] != 0xFF){
        printf("擦除校验失败\r\n");
      }
    }
    printf("擦除校验完成\r\n");

    printf("开始写入\r\n");
    // 初始化要写入的数据
    for(i=0;i<4096;i++){
      write_buf[i] = 0x77;
    }
    SPI_FLASH_Page_Write(10, write_buf, 4096);
    printf("写入完成\r\n");

    SPI_FLASH_Read_Buff(10, read_buf, 4096);
    printf("读取到的数据:\r\n");
    for(i=0;i<4096;i++){
      printf("0x%02x ", read_buf[i]);
    }
    printf("读取完成\r\n");


    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // 简单延时函数
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


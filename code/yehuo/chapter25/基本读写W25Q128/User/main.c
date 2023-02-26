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
#include "bsp_spi_flash.h"

void Delay(__IO u32 nCount);



uint8_t read_buf[4096] = {0};
uint8_t write_buf[4096] = {0};

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{

    uint8_t flash_id = 0;
    uint32_t i = 0;

    /* ��ʼ������ */
    uart_init(115200);

    /* ����һ���ַ��� */
    printf("����һ�� FLASH ��дʵ��\r\n");

    SPI_FLASH_Init();

    flash_id = SPI_FLASH_Read_ID();
    printf("flash id = 0x%x\r\n", flash_id);

    // �������� 
    printf("������ʼ\r\n");
    SPI_FLASH_Erase_Sector(4096*0);
    SPI_FLASH_Erase_Sector(4096*1);
    printf("�������\r\n");

    SPI_FLASH_Read_Buff(0, read_buf, 4096);
    for(i=0;i<4096;i++){
      // ��������0xFF,˵���������ɹ�
      if(read_buf[i] != 0xFF){
        printf("����У��ʧ��\r\n");
      }
    }
    printf("����У�����\r\n");

    printf("��ʼд��\r\n");
    // ��ʼ��Ҫд�������
    for(i=0;i<4096;i++){
      write_buf[i] = 0x77;
    }
    SPI_FLASH_Page_Write(10, write_buf, 4096);
    printf("д�����\r\n");

    SPI_FLASH_Read_Buff(10, read_buf, 4096);
    printf("��ȡ��������:\r\n");
    for(i=0;i<4096;i++){
      printf("0x%02x ", read_buf[i]);
    }
    printf("��ȡ���\r\n");


    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/*********************************************END OF FILE**********************/


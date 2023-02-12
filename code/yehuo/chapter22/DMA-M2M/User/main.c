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

#define BUFFER_SIZE   32
#define TIMEOUT_MAX   10000 // Maximum timeout value


/* ����aSRC_Const_Buffer������ΪDMA��������Դ
  const�ؼ��ֽ�aSRC_Const_Buffer�����������Ϊ��������
  const ��������洢��flash��
   */
const uint32_t aSRC_Const_Buffer[BUFFER_SIZE]= {
                                    0x01020304,0x05060708,0x090A0B0C,0x0D0E0F10,
                                    0x11121314,0x15161718,0x191A1B1C,0x1D1E1F20,
                                    0x21222324,0x25262728,0x292A2B2C,0x2D2E2F30,
                                    0x31323334,0x35363738,0x393A3B3C,0x3D3E3F40,
                                    0x41424344,0x45464748,0x494A4B4C,0x4D4E4F50,
                                    0x51525354,0x55565758,0x595A5B5C,0x5D5E5F60,
                                    0x61626364,0x65666768,0x696A6B6C,0x6D6E6F70,
                                    0x71727374,0x75767778,0x797A7B7C,0x7D7E7F80};
/* ����DMA����Ŀ��洢�� */
uint32_t aDST_Buffer[BUFFER_SIZE];


void Delay(__IO u32 nCount);
static void DMA_Config(void);
uint8_t Buffercmp(const uint32_t *pBuffer1, uint32_t* pBuffer2, uint16_t BufferLength);

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{
    /* �����űȽϽ������ */
    uint8_t TransferStatus;

    /* LED IO�ڳ�ʼ�� */
    LED_GPIO_Config();

    /* ����ʱ���� */
    Delay(0xFFFFFF);

    /* DMA�������� */
    DMA_Config();
    

    /* �ȴ�DMA������� */
    while(DMA_GetFlagStatus(DMA2_Stream0, DMA_FLAG_TCIF0) == DISABLE)
    {}

    /* �Ƚ�Դ�����봫������� */
    TransferStatus = Buffercmp(aSRC_Const_Buffer, aDST_Buffer, BUFFER_SIZE);

    /* �ж�Դ�����봫������ݱȽϽ�� */
    if(TransferStatus == 0) // �����
    {
        LED0(ON); 
        LED1(OFF);

    } else { // ���
        LED0(OFF); 
        LED1(ON);
    }

    while(1)
    {
    }

}

void Delay(__IO u32 nCount) // ����ʱ����
{
  for(; nCount != 0; nCount --);
}

/**
 * @brief DMA��������
*/
static void DMA_Config(void)
{
  DMA_InitTypeDef DMA_InitStructure;
  __IO uint32_t Timeout = TIMEOUT_MAX;

  /* ʹ��DMAʱ�� */
  /* �洢�����洢���������ʹ��DMA2 */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

  /* ��λ��ʼ��DMA������ */
  DMA_DeInit(DMA2_Stream0);

  /* ȷ��DMA��������λ��� */
  while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE)
  {
  }
  /* DMA������ͨ��ѡ�� */
  DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  /* Դ���ݵ�ַ */
  DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)aSRC_Const_Buffer;   
  /* Ŀ���ַ */
  DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)aDST_Buffer;
  /* �洢�����洢��ģʽ */
  DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToMemory;
  /* ������Ŀ */
  DMA_InitStructure.DMA_BufferSize = (uint32_t)BUFFER_SIZE;
  /* ʹ���Զ���ַ���� */
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
  /* ʹ���Զ���ַ���� */
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  /* Դ�������ִ�С(32λ) */
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Word;
  /* Ŀ���������ִ�С(32λ) */
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Word;
  /* һ�δ���ģʽ���洢�����洢��ģʽ����ʹ��ѭ������ */
  DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;
  /* DMA���������ȼ�Ϊ�� */
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  /* ����FIFOģʽ */
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
  /* ����ģʽ */
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
  /* ����ģʽ */
  DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
  /* ���DMA�������������� */
  DMA_Init(DMA2_Stream0, &DMA_InitStructure);

  /* ���DMA������������ɱ�־λ */
  DMA_ClearFlag(DMA2_Stream0, DMA_FLAG_TCIF0);

  /* ʹ��DMA����������ʼDMA���ݴ��� */
  DMA_Cmd(DMA2_Stream0, ENABLE);

  /* ���DMA�������Ƿ���Ч�����г�ʱ��⹦�� */
  while((DMA_GetCmdStatus(DMA2_Stream0) != ENABLE) && (Timeout -- > 0))
  {
  }

  /* �ж��Ƿ�ʱ */
  if( Timeout == 0)
  {
    /* ��ʱ���ó�����������ѭ��������� */
    while(1){
        LED0(ON); 
        LED1(ON);
        Delay(0xFFFFFF);
        LED0(OFF);
        LED1(OFF); 
        Delay(0xFFFFFF);
    }
  }
}


/**
 * @brief �Ƚ����� 
 *  �ж�ָ�����ȵ���������Դ�Ƿ���ȫ���
 *  �����ȫ��ȷ���1��ֻҪ����һ�����ݲ���ȷ���0
*/
uint8_t Buffercmp(const uint32_t *pBuffer1,
                  uint32_t* pBuffer2, uint16_t BufferLength)
{
  /* ���ݳ��ȵݼ� */
  while(BufferLength--){
    /* �ж���������Դ�Ƿ��Ӧ��� */
    if(*pBuffer1 != *pBuffer2){
      /* ��Ӧ����Դ����������˳�����������0 */
      return 0;
    }
    /* ������������Դ�ĵ�ַָ�� */
    pBuffer1 ++;
    pBuffer2 ++;
  }
  /* ����жϲ��Ҷ�Ӧ������� */
  return 1;

}


/*********************************************END OF FILE**********************/


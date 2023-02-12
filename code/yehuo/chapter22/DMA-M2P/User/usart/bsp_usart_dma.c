#include "bsp_usart_dma.h"


uint8_t SendBuff[SENDBUFF_SIZE];


/**
 * @brief USART GPIO ���ã�����ģʽ���á�115200 8-N-1
*/
void Debug_USART_Config(void)
{

   //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //ʹ��GPIOAʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//ʹ��USART1ʱ��
 
	//����1��Ӧ���Ÿ���ӳ��
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9����ΪUSART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10����ΪUSART1
	
	//USART1�˿�����
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9��GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//�ٶ�50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //����
	GPIO_Init(GPIOA,&GPIO_InitStructure); //��ʼ��PA9��PA10

   //USART1 ��ʼ������
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;//����������
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
    USART_Init(USART1, &USART_InitStructure); //��ʼ������1
    USART_Cmd(USART1, ENABLE);  //ʹ�ܴ���1 
}

/**
 * @brief ����һ���ַ�
*/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* ����һ���ֽ����ݵ�USART */
    USART_SendData(pUSARTx, ch);

    /* �ȴ��������ݼĴ���Ϊ�� */
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
    // while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) != SET);
}

/**
 * @brief �����ַ���
*/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k=0;
    do {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');

    /* �ȴ�������� */
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

//�ض���fputc���� 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
	USART1->DR = (u8) ch;      
	return ch;
}


/**
 * @brief USART1 TX DMA ���ã��ڴ浽���裨USART1->DR��
 * @param ��
 * @retval ��
*/
void USART_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* ʹ��DMAʱ�� */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* ��λ��ʼ��DMA������ */
    DMA_DeInit(DMA2_Stream7);

    /* ȷ��DMA��������λ��� */
    while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)
    {
    }
    /* usart1 tx��Ӧdma2, ͨ��4, ������7 */
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    /* ����DMAԴ���������ݼĴ�����ַ */
    DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)(USART1_BASE + 0x04);   
    /* �ڴ��ַ��Ҫ����ı�����ָ�룩 */
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)SendBuff;
    /* ���򣺴��ڴ浽���� */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    /* �����С DMA_BufferSize=SENDBUFF_SIZE */
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /* �����ַ���� */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /* �ڴ��ַ���� */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /* �������ݵ�λ 8bit */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /* �ڴ����ݵ�λ 8bit */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /* DMAģʽ������ѭ�� */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    /* ���ȼ����� */
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    /* ����FIFOģʽ */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    /* �洢��ͻ������ 1������ */
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    /* ����ͻ������ 1������ */
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    /* ����DMA2��������7 */
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);

    // /* ���DMA������������ɱ�־λ */
    // DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF0);

    /* ʹ��DMA����������ʼDMA���ݴ��� */
    DMA_Cmd(DMA2_Stream7, ENABLE);

    /* ���DMA�������Ƿ���Ч�����г�ʱ��⹦�� */
    while(DMA_GetCmdStatus(DMA2_Stream7) != ENABLE)
    {
    }
}

#include "bsp_usart_dma.h"


uint8_t SendBuff[SENDBUFF_SIZE];


/**
 * @brief USART GPIO 配置，工作模式配置。115200 8-N-1
*/
void Debug_USART_Config(void)
{

   //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE); //使能GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);//使能USART1时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1); //GPIOA10复用为USART1
	
	//USART1端口配置
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOA,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = DEBUG_USART_BAUDRATE;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
    USART_Init(USART1, &USART_InitStructure); //初始化串口1
    USART_Cmd(USART1, ENABLE);  //使能串口1 
}

/**
 * @brief 发送一个字符
*/
void Usart_SendByte(USART_TypeDef *pUSARTx, uint8_t ch)
{
    /* 发送一个字节数据到USART */
    USART_SendData(pUSARTx, ch);

    /* 等待发送数据寄存器为空 */
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
    // while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) != SET);
}

/**
 * @brief 发送字符串
*/
void Usart_SendString(USART_TypeDef *pUSARTx, char *str)
{
    unsigned int k=0;
    do {
        Usart_SendByte(pUSARTx, *(str + k));
        k++;
    } while (*(str + k) != '\0');

    /* 等待发送完成 */
    while(USART_GetFlagStatus(pUSARTx, USART_FLAG_TC) == RESET);
}

//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      
	return ch;
}


/**
 * @brief USART1 TX DMA 配置，内存到外设（USART1->DR）
 * @param 无
 * @retval 无
*/
void USART_DMA_Config(void)
{
    DMA_InitTypeDef DMA_InitStructure;

    /* 使能DMA时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);

    /* 复位初始化DMA数据流 */
    DMA_DeInit(DMA2_Stream7);

    /* 确保DMA数据流复位完成 */
    while(DMA_GetCmdStatus(DMA2_Stream7) != DISABLE)
    {
    }
    /* usart1 tx对应dma2, 通道4, 数据流7 */
    DMA_InitStructure.DMA_Channel = DMA_Channel_4;
    /* 设置DMA源：串口数据寄存器地址 */
    DMA_InitStructure.DMA_PeripheralBaseAddr =  (uint32_t)(USART1_BASE + 0x04);   
    /* 内存地址（要传输的变量的指针） */
    DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)SendBuff;
    /* 方向：从内存到外设 */
    DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    /* 传输大小 DMA_BufferSize=SENDBUFF_SIZE */
    DMA_InitStructure.DMA_BufferSize = SENDBUFF_SIZE;
    /* 外设地址不增 */
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    /* 内存地址自增 */
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    /* 外设数据单位 8bit */
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    /* 内存数据单位 8bit */
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    /* DMA模式：不断循环 */
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    /* 优先级：中 */
    DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
    /* 禁用FIFO模式 */
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_Full;
    /* 存储器突发传输 1个节拍 */
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    /* 外设突发传输 1个节拍 */
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    /* 配置DMA2的数据流7 */
    DMA_Init(DMA2_Stream7, &DMA_InitStructure);

    // /* 清除DMA数据流传输完成标志位 */
    // DMA_ClearFlag(DMA2_Stream7, DMA_FLAG_TCIF0);

    /* 使能DMA数据流，开始DMA数据传输 */
    DMA_Cmd(DMA2_Stream7, ENABLE);

    /* 检测DMA数据流是否有效并带有超时检测功能 */
    while(DMA_GetCmdStatus(DMA2_Stream7) != ENABLE)
    {
    }
}

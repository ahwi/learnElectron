#include "bsp_spi_flash.h"

/**
*  1. ��ʼ��������ż�SPI����ģʽ
*  2. ��д�����Ķ�д�����ֽڵ����̺���
*  3. ����2�ĺ�������ɸ�������
*  4. ���������дFLASH��У������
*/

static __IO uint32_t SPITimeout = SPI_LONG_TIMEOUT;

static void SPI_GPIO_Init(void);
static void SPI_Mode_Config(void);
static uint32_t SPI_TIMETOUT_UserCallback(uint8_t errorCode);


static void SPI_GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ��ʼ��ʱ��
    FLASH_SPI_INIT(FLASH_SPI_CLK, ENABLE);
    RCC_AHB1PeriphClockCmd(FLASH_SPI_SCK_GPIO_CLK|FLASH_SPI_MOSI_GPIO_CLK|
                           FLASH_SPI_MISO_GPIO_CLK|FLASH_SPI_CS_GPIO_CLK, ENABLE);
    
    // ��������
    GPIO_PinAFConfig(FLASH_SPI_SCK_GPIO_PORT, FLASH_SPI_SCK_SOURCE, FLASH_SPI_SCK_AF);
    GPIO_PinAFConfig(FLASH_SPI_MOSI_GPIO_PORT, FLASH_SPI_MOSI_SOURCE, FLASH_SPI_MOSI_AF);
    GPIO_PinAFConfig(FLASH_SPI_MISO_GPIO_PORT, FLASH_SPI_MISO_SOURCE, FLASH_SPI_MISO_AF);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_SCK_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MOSI_PIN;
    GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_MISO_PIN;
    GPIO_Init(FLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

    // ʹ���������CS����
    GPIO_InitStructure.GPIO_Pin = FLASH_SPI_CS_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &GPIO_InitStructure);
}

static void SPI_Mode_Config(void)
{
    SPI_InitTypeDef SPI_InitStructure;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;   
    // mode 0
    SPI_InitStructure.SPI_CPOL = SPI_CPHA_1Edge;                
    SPI_InitStructure.SPI_CPHA = SPI_CPOL_Low;                
    SPI_InitStructure.SPI_CRCPolynomial = 0;       
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;            
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;           
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;                
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;            
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;                 

    SPI_Init(FLASH_SPI, &SPI_InitStructure);
    SPI_Cmd(FLASH_SPI, ENABLE);

}

/**
 * @brief  SPI ����(FLASH)��ʼ��
 * @param  ��
 * @retval ��
*/
void SPI_FLASH_Init(void)
{
    SPI_GPIO_Init();
    SPI_Mode_Config();
}


/**
 * @brief ͨ��SPI����һ���ֽڵ�FLASH��
 * @param data: Ҫ���͵�����
 * @retval ret_data: ���յ�������
*/
uint8_t SPI_FLASH_ByteWrite(uint8_t data)
{
    uint8_t ret_data;

    // �ȴ� TXE ��־
    SPITimeout = SPI_FLAG_TIMEOUT;
    while(SPI_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_TXE) == RESET){
        if((SPITimeout--) == 0)
            return SPI_TIMETOUT_UserCallback(1);
    }

    // ��������
    SPI_SendData(FLASH_SPI, data);

    // �ȴ� RXNE ��־��ȷ�Ϸ�����ɣ���׼����ȡ����
    SPITimeout = SPI_FLAG_TIMEOUT;
    while(SPI_GetFlagStatus(FLASH_SPI, SPI_I2S_FLAG_RXNE) == RESET){
        if((SPITimeout--) == 0)
            return SPI_TIMETOUT_UserCallback(2);
    }

    // ��������
    ret_data = SPI_ReceiveData(FLASH_SPI);
    return ret_data;
}

/**
 * @brief ��ID0-ID7
*/
uint8_t SPI_FLASH_Read_ID(void)
{
    uint8_t id;
    // ����Ƭѡ����
    FLASH_SPI_CS_LOW();

    // ָ�����
    SPI_FLASH_ByteWrite(W25X_DeviceID);

    SPI_FLASH_ByteWrite(DUMMY);
    SPI_FLASH_ByteWrite(DUMMY);
    SPI_FLASH_ByteWrite(DUMMY);

    // ���ն�ȡ��������
    id = SPI_FLASH_ByteWrite(DUMMY);
    FLASH_SPI_CS_HIGH();
    return id;
}

/**
 * @brief ��������
 * @param addr: ������뵽Ҫ�������������׵�ַ
*/
void SPI_FLASH_Erase_Sector(uint32_t addr)
{
    // дʹ��
    SPI_FLASH_Write_Enable();

    // ����Ƭѡ����
    FLASH_SPI_CS_LOW();

    // ָ�����
    SPI_FLASH_ByteWrite(W25X_SectorErase);

    // ����Ҫ�����ĵ�ַ
    SPI_FLASH_ByteWrite((addr>>16) & 0xFF );
    SPI_FLASH_ByteWrite((addr>>8) & 0xFF );
    SPI_FLASH_ByteWrite(addr & 0xFF);

    FLASH_SPI_CS_HIGH();

    // �ȴ��ڲ�ʱ�����
    SPI_FLASH_Wait_For_Standby();
}


/**
 * @brief ��ȡ����
 * @param addr: Ҫ��ȡ���ݵ��׵�ַ
 * @param buf: �洢��ȡ�������ݵ�ָ��
 * @param size: Ҫ��ȡ���ٸ�����
*/
void SPI_FLASH_Read_Buff(uint32_t addr, uint8_t *buf, uint32_t size)
{
    // ����Ƭѡ����
    FLASH_SPI_CS_LOW();

    // ָ�����
    SPI_FLASH_ByteWrite(W25X_ReadData);

    // ����Ҫ��ȡ�ĵ�ַ
    SPI_FLASH_ByteWrite((addr>>16) & 0xFF );
    SPI_FLASH_ByteWrite((addr>>8) & 0xFF );
    SPI_FLASH_ByteWrite(addr & 0xFF);

    while(size--){
        *buf = SPI_FLASH_ByteWrite(DUMMY);
        buf ++;
    }

    FLASH_SPI_CS_HIGH();
}

/**
 * @brief д������
 * @param addr: Ҫ�������ݵ��׵�ַ
 * @param buf: Ҫд������ݵ�ָ��
 * @param size: Ҫд����ٸ����ݣ����ܳ���256
 * 
 * ע����������е����⣬��10��ַ��ʼд4096���ֽڣ��ڿ���ĩβ�ĵط�����10���ط�д��
*/
void SPI_FLASH_Page_Write(uint32_t addr, uint8_t *buf, uint32_t size)
{
    uint32_t count = 0;
    while(size --) {
        count ++;
        if(count==1 || (count%256)==1 || (addr%4096)==0){
            FLASH_SPI_CS_HIGH();

            // �ȴ��ڲ�ʱ�����
            SPI_FLASH_Wait_For_Standby();

            // дʹ��
            SPI_FLASH_Write_Enable();

            // ����Ƭѡ����
            FLASH_SPI_CS_LOW();

            // ָ�����
            SPI_FLASH_ByteWrite(W25X_PageProgram);

            // ����Ҫд��ĵĵ�ַ
            SPI_FLASH_ByteWrite((addr>>16) & 0xFF );
            SPI_FLASH_ByteWrite((addr>>8) & 0xFF );
            SPI_FLASH_ByteWrite(addr & 0xFF);
        }

        SPI_FLASH_ByteWrite(*buf);
        buf++;
        addr++;
    }
    FLASH_SPI_CS_HIGH();

    // �ȴ��ڲ�ʱ�����
    SPI_FLASH_Wait_For_Standby();

}
/**
 * @brief дʹ��
*/
void SPI_FLASH_Write_Enable(void)
{
    // ����Ƭѡ����
    FLASH_SPI_CS_LOW();
    // ָ�����
    SPI_FLASH_ByteWrite(W25X_WriteEnable);
    FLASH_SPI_CS_HIGH();
}

/**
 * @brief �ȴ�ֱ������״̬
*/
void SPI_FLASH_Wait_For_Standby(void)
{
    uint8_t status;
    // ����Ƭѡ����
    FLASH_SPI_CS_LOW();
    
    // ָ�����
    SPI_FLASH_ByteWrite(W25X_ReadStatusReg);

    SPITimeout = SPI_LONG_TIMEOUT;
    while(1) {
        status = SPI_FLASH_ByteWrite(DUMMY);

        // �������������˵������״̬
        if((status & 0x01) == 0)
            break;

        // ��SPITimeoutΪ0����ʾ�Ѽ�⵽SPITimeout�ζ���Ϊbusy������ѭ��
        if((SPITimeout--) == 0) {
            SPI_TIMETOUT_UserCallback(3);
            break;
        }
    }
    FLASH_SPI_CS_HIGH();
}

static uint32_t SPI_TIMETOUT_UserCallback(uint8_t errorCode)
{
    FLASH_ERROR("SPI �ȴ���ʱ!errorCode = %d", errorCode);   
    return 0;
}

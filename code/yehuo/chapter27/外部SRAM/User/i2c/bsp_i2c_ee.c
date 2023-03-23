#include "bsp_i2c_ee.h"

#define TIME_OUT 0x0000FFFF

uint32_t count_wait = TIME_OUT;

uint8_t Error_CallBack(uint8_t code);

/**
 * @brief I2C1 I/O配置
 * @param 无
 * @retval 无
*/
static void I2C_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStruct;

    /* EEPROM_I2C Periph clock enable */
    RCC_APB1PeriphClockCmd(EEPROM_I2C_CLK, ENABLE);

    /* STM32 I2C相关引脚时钟初始化  */
    RCC_AHB1PeriphClockCmd(EEPROM_I2C_SCL_GPIO_CLK 
                            | EEPROM_I2C_SCL_GPIO_CLK, ENABLE);
    
    /* 配置引脚复用 */
    GPIO_PinAFConfig(EEPROM_I2C_SCL_GPIO_PORT, EEPROM_I2C_SCL_SOURCE, EEPROM_I2C_SCL_AF);
    GPIO_PinAFConfig(EEPROM_I2C_SDA_GPIO_PORT, EEPROM_I2C_SDA_SOURCE, EEPROM_I2C_SDA_AF);

    /* 配置GPIO引脚 SCL SDA*/
    GPIO_InitStruct.GPIO_Pin = EEPROM_I2C_SCL_PIN;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(EEPROM_I2C_SCL_GPIO_PORT, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Pin = EEPROM_I2C_SDA_PIN;
    GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * @brief  I2C 工作模式配置
 * @param  无
 * @retval 无
*/
static void I2C_Mode_Config(void)
{
    I2C_InitTypeDef I2C_InitStructure;

    /* I2C 配置 */
    I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
    I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1 = I2C_OWN_ADDRESS;
    I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(EEPROM_I2C, &I2C_InitStructure);

    /* 使能 I2C */
    I2C_Cmd(EEPROM_I2C, ENABLE);

    // I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);

}



/**
 * @brief  I2C 外设（EEPROM）初始化
 * @param  无
 * @retval 无
*/
void I2C_EE_Init(void)
{
    I2C_GPIO_Config();

    I2C_Mode_Config();

}

/**
 * @brief 向EEPROM写一个字节
 * @param addr: 要写入的存储单元地址
 * @param data: 要写入的数据
 * @return 0 成功；非0 失败
*/
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(1);
        }
    }

    // 要发送的EEPROM设备地址，并设置为写方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Transmitter);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(2);
        }
    }

    // 发送要写入的存储单元地址
    I2C_SendData(EEPROM_I2C, addr);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV8_2事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(3);
        }
    }

    // 发送要写入的数据
    I2C_SendData(EEPROM_I2C, data); 

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV8_2事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(4);
        }
    }

    // 产生停止信号
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);

    // 等待写入完成
    return Wait_For_Standby();
}

/**
 * @brief 向EEPROM写一页的数据
 * @param addr: 要写入的存储单元首地址
 * @param data: 要写入的数据指针
 * @param size: 要写入的数据长度 (size <= 8)
 * @return 0 成功；非0 失败 */
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size)
{
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(1);
        }
    }

    // 要发送的EEPROM设备地址，并设置为写方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Transmitter);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(2);
        }
    }

    // 发送要写入的存储单元地址
    I2C_SendData(EEPROM_I2C, addr);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV8_2事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(3);
        }
    }

    while(size --){
        // 发送要写入的数据
        I2C_SendData(EEPROM_I2C, *data); 
        // 重置 count_wait
        count_wait = TIME_OUT;
        // 等待EV8_2事件，直到检测成功
        while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
        {
            count_wait --;
            if(count_wait == 0){
                return Error_CallBack(4);
            }
        }
        data++;
    }

    // 产生停止信号
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);

    // 等待写入完成
    return Wait_For_Standby();
}

/**
 * @brief 向EEPROM写入一段数据
 * @param addr: 要写入的存储单元首地址
 * @param data: 要写入的数据指针
 * @param size: 要写入的数据长度 
 * @return 0 成功；非0 失败 */
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size)
{
    uint8_t num_of_page = 0;
    uint8_t single_byte = 0;
    uint8_t single_addr = size % EEPROM_PAGE_SIZE;
    uint8_t first_size = 0;
    uint16_t remain = 0;

    if(single_addr == 0){
        num_of_page = size / EEPROM_PAGE_SIZE;
        single_byte = size % EEPROM_PAGE_SIZE;
        while(num_of_page --){
            EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);

            // 等待写入完成
            Wait_For_Standby();

            addr += EEPROM_PAGE_SIZE;
            data += EEPROM_PAGE_SIZE;
        }

        EEPROM_Page_Write(addr, data, single_byte);
        Wait_For_Standby();
    } 
    else {
        // 第一次写入
        first_size = EEPROM_PAGE_SIZE - single_addr;
        // 调用页写入
        EEPROM_Page_Write(addr, data, first_size);
        // 等待写入完成
        Wait_For_Standby();

        addr += first_size;
        data += first_size;

        // 剩余要写入的数据大小
        remain = size - first_size;
        single_byte = remain % EEPROM_PAGE_SIZE;
        single_addr = remain % EEPROM_PAGE_SIZE;

        while(num_of_page --){
            EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
            // 等待写入完成
            Wait_For_Standby();
            addr += EEPROM_PAGE_SIZE;
            data += EEPROM_PAGE_SIZE;
        }

        EEPROM_Page_Write(addr, data, single_byte);
        Wait_For_Standby();
    }
    return 0;
}

/**
 * @brief 向EEPROM读取一个字节
 * @param addr: 要读取的存储单元地址
 * @param data: 保存读取的数据
 * @return 0 成功；非0 失败
*/
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
    /*********发送要读取的地址*********************/
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(1);
        }
    }

    // 要发送的EEPROM设备地址，并设置为写方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Transmitter);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(2);
        }
    }

    // 发送要读取的存储单元地址
    I2C_SendData(EEPROM_I2C, addr);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV8_2事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(3);
        }
    }


    /*********重新发起起始信号，开始读取数据*********************/
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(4);
        }
    }

    // 要发送的EEPROM设备地址，并设置为读方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Receiver);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(5);
        }
    }

    // 做出非应答信号(在接收数据前配置好，等待接收后再用 I2C_ReceiveData 从寄存器中读取数据)
    I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV7事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(6);
        }
    }

    // 开始读取数据
    *data = I2C_ReceiveData(EEPROM_I2C);

    // 产生停止信号
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    return 0;

}

/**
 * @brief 从EEPROM连续读取数据
 * @param addr: 要读取的存储单元地址
 * @param data: 保存读取的数据
 * @param size: 要读取多少个数据
 * @return 0 成功；非0 失败
*/
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size)
{
    /*********发送要读取的地址*********************/
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(15);
        }
    }

    // 要发送的EEPROM设备地址，并设置为写方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Transmitter);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(16);
        }
    }

    // 发送要读取的存储单元地址
    I2C_SendData(EEPROM_I2C, addr);
    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV8_2事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(17);
        }
    }


    /*********重新发起起始信号，开始读取数据*********************/
    // 产生起始信号
    I2C_GenerateSTART(EEPROM_I2C, ENABLE);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV5事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(18);
        }
    }

    // 要发送的EEPROM设备地址，并设置为读方向
    I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Receiver);

    // 重置 count_wait
    count_wait = TIME_OUT;
    // 等待EV6事件，直到检测成功
    while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS)
    {
        count_wait --;
        if(count_wait == 0){
            return Error_CallBack(19);
        }
    }

    while(size--){
        if(size == 0){
            // 做出非应答信号
            I2C_AcknowledgeConfig(EEPROM_I2C, DISABLE);
        }
        else {
            // 做出应答信号
            I2C_AcknowledgeConfig(EEPROM_I2C, ENABLE);
        }

        count_wait = TIME_OUT;
        // 等待EV7事件，直到检测成功
        while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS)
        {
            count_wait --;
            if(count_wait == 0){
                return Error_CallBack(20);
            }
        }

        // 开始读取数据
        *data = I2C_ReceiveData(EEPROM_I2C);
        data ++;
    }

    // 产生停止信号
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    return 0;

}

/**
 * @brief 等待EEPROM内部写入操作完成
 * @return 0 成功；非0 失败
*/
uint8_t Wait_For_Standby(void)
{

    uint32_t check_count = 0xFFFFF;
    while(check_count --) {
        // 产生起始信号
        I2C_GenerateSTART(EEPROM_I2C, ENABLE);
        // 重置 count_wait
        count_wait = TIME_OUT;
        // 等待EV5事件，直到检测成功
        while(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS)
        {
            count_wait --;
            if(count_wait == 0){
                return Error_CallBack(11);
            }
        }

        // 要发送的EEPROM设备地址，并设置为写方向
        I2C_Send7bitAddress(EEPROM_I2C, EEPROM_I2C_ADDRESS, I2C_Direction_Transmitter);
        // 重置 count_wait
        count_wait = TIME_OUT;
        // 等待EV6事件，直到检测成功
        while(count_wait --){

            // 若检测到响应，说明内部写时序完成，跳出等待函数
            if(I2C_CheckEvent(EEPROM_I2C, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS) {
                // 退出前停止本次通信
                I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
                return 0;
            }
        }

    }

    // 退出前停止本次通信
    I2C_GenerateSTOP(EEPROM_I2C, ENABLE);
    return 1;
}

uint8_t Error_CallBack(uint8_t code)
{
    printf("\r\nI2C error occur,code=%d\r\n", code);
    return code;
}

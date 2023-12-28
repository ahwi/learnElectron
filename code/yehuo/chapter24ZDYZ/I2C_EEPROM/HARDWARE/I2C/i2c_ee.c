#include "i2c_ee.h"

#include "stm32f4xx_i2c.h"
#include "usart.h"


#define TIME_OUT 0x0000FFF

uint32_t count_wait = TIME_OUT;

uint8_t Error_CallBack(uint8_t code);
uint8_t Wait_For_Standby(void);


/**
* I2C的GPIO配置
* IIC_SCL-PB8  IIC_SDA-PB9
*/
void I2C_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// 配置时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	// 配置GPIO引脚
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStruct.GPIO_OType = GPIO_OType_OD;
  GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_I2C1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_I2C1);
}

/**
* I2C 模式配置
*/
void I2C_Mode_Config(void)
{
	I2C_InitTypeDef I2C_InitStruct;
	I2C_InitStruct.I2C_ClockSpeed = I2C_SPEED;
	I2C_InitStruct.I2C_Mode = I2C_Mode_I2C; 
	I2C_InitStruct.I2C_DutyCycle = I2C_DutyCycle_16_9;
	I2C_InitStruct.I2C_OwnAddress1 = I2C_ADDR;
	I2C_InitStruct.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStruct.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C1, &I2C_InitStruct);
	
	// 使能I2C
	I2C_Cmd(I2C1, ENABLE);
}

void I2C_EE_Init(void)
{
	I2C_GPIO_Config();
	I2C_Mode_Config();
}

/**
* @brief 向EEPROM写入一个字节
* @param addr: 要写入的存储单元地址
* @param data: 要写入的数据
* @return 0 成功; 非0 失败
*/
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
	// 产生起始信号
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(1);
		}
	}
	
	// 发送EEPROM设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV6事件
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(2);
		}
	}
	
	// 发送要写入的数据地址
	I2C_SendData(I2C1, addr);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV8_2 事件，移位寄存器为空，数据寄存器为空
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(3);
		}
	}
	
	// 发送要写入的数据
	I2C_SendData(I2C1, data);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV8_2 事件，移位寄存器为空，数据寄存器为空
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(3);
		}
	}
	
	// 产生停止信号
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return Wait_For_Standby();
}

/**
* @brief 向EEPROM写入一页数据
* @param addr: 要写入的EEPROM地址
* @param data: 要写入的数据指针
* @param size: 要写入的数据大小
* @return 0 成功; 非0 失败
*/
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size)
{
	// 产生起始信号
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(4);
		}
	}
	
	// 发送EEPROM设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV6事件
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(5);
		}
	}
	
	// 发送要写入的数据地址
	I2C_SendData(I2C1, addr);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV8_2 事件，移位寄存器为空，数据寄存器为空
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(6);
		}
	}
	
	while(size --){
		// 发送要写入的数据
		I2C_SendData(I2C1, *data);
		
		// 重置 count_wait
		count_wait = TIME_OUT;
		// 等待EV8_2 事件，移位寄存器为空，数据寄存器为空
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(7);
			}
		}
		data ++;
	}

	
	// 产生停止信号
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return Wait_For_Standby();
}

/**
* @brief 向EEPROM写入一段数据
* @param addr: 要写入的EERPOM存储单元的首地址
* @param data: 要写入的数据指针
* @param size: 要写入的数据长度
* return 0 成功; 非0 失败
*/
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size)
{
	// 页对齐，计算出第一页要写的大小 firstSize
	uint8_t remainder1 = addr % EEPROM_PAGE_SIZE;
	uint8_t firstSize = EEPROM_PAGE_SIZE - remainder1;
	
	// 扣除第一页写的大小，剩余要写的数据
	uint8_t remainSize = size - firstSize;
	uint8_t remainder2 = remainSize % EEPROM_PAGE_SIZE;
	// 剩余要写的页大小
	uint8_t remainPage = remainSize / EEPROM_PAGE_SIZE;
	
	if(firstSize == (uint8_t)(EEPROM_PAGE_SIZE)){ //第一页刚好是对齐的
		remainPage += 1; // 把第一页也加上去

	} 
	else{ // 未对齐，先把第一页的数据写上
		EEPROM_Page_Write(addr, data, firstSize);
		Wait_For_Standby();
		addr += firstSize;
		data += firstSize;
	}

	while(remainPage -- ){ // 一页一页写
		EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
		Wait_For_Standby();
		addr += EEPROM_PAGE_SIZE;
		data += EEPROM_PAGE_SIZE;
	}
		
	// 写剩余的数据
	if(remainder2 != 0){
		EEPROM_Page_Write(addr, data, remainder2);
		Wait_For_Standby();
		addr += remainder2;
		data += remainder2;
	}
	
	return 0;
}

/**
* @brief 从EEPROM读取一个字节数据
* @param addr: 要读取的地址
* @param data: 保存读取的数据
* @return 0 成功; 非0 失败
*/
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
	// 起始信号
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(9);
		}
	}
	
	// 发送要读取的I2C设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Transmitter);
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV6事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(10);
		}
	}
	
	// 发送要读取的EEPROM数据地址
	I2C_SendData(I2C1, addr);
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(11);
		}
	}
	
	
	/********** 重新发送起始信号，开始读取数据 ***************/
	// 起始信号
	I2C_GenerateSTART(I2C1, DISABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(12);
		}
	}
	
	// 发送要读取的I2C设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Receiver);
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV6事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(13);
		}
	}
	
	// 做出非应答信号(在接收数据前配置好)
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV7事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(14);
		}
	}
	
	// 读取数据
	*data = I2C_ReceiveData(I2C1);
	
	// 产生停止信号
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 0;
}

/**
* @brief 从EEPROM连续读取数据
* @param addr: 要读取的数据单元格地址
* @param data: 保存读取的数据
* @param size: 要读取多少个数据
* @return 0 成功; 非0 失败
*/
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size)
{
		// 起始信号
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(9);
		}
	}
	
	// 发送要读取的I2C设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Transmitter);
	
	// 等待EV6事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(10);
		}
	}
	
	// 发送要读取的EEPROM数据地址
	I2C_SendData(I2C1, addr);
	// 等待EV8_2事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(11);
		}
	}
	
	
	/********** 重新发送起始信号，开始读取数据 ***************/
	// 起始信号
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV5事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(12);
		}
	}
	
	// 发送要读取的I2C设备地址，并设置为写方向
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Receiver);
	// 重置 count_wait
	count_wait = TIME_OUT;
	// 等待EV6事件，直到检测成功
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(13);
		}
	}
	
	// 读取数据
	while(size --){
		if(size == 0){
			// 做出非应答信号(在接收数据前配置好)
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		} else {
			// 做出应答信号(在接收数据前配置好)
			I2C_AcknowledgeConfig(I2C1, ENABLE);
		}

		// 重置 count_wait
		count_wait = TIME_OUT;
		// 等待EV7事件，直到检测成功
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(14);
			}
		}
		
		*data++ = I2C_ReceiveData(I2C1);
	}
	
	
	// 产生停止信号
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 0;
}

/**
* @brief 等待EEPROM内部写入操作完成
* @return 0 成功; 1 失败；
*/
uint8_t Wait_For_Standby(void)
{
	uint32_t check_count = 0xFFFFF;
	while(check_count --){
		// 产生起始信号
		I2C_GenerateSTART(I2C1, ENABLE);
		
		// 等待EV5事件，直到检测成功
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(8);
			}
		}
		
		// 发送EEPROM设备地址，并设置为写方向
		I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
		
		// 重置 count_wait
		count_wait = TIME_OUT;
		// 等待EV6事件
		while(count_wait --){
			// 若检测到响应，说明内部写时序完成，跳出等待函数
			if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS){
				// 退出前停止本次通信
				I2C_GenerateSTOP(I2C1, ENABLE);
				return 0;
			}
		}
	}
	// 退出前停止本次通信
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 1;
}

uint8_t Error_CallBack(uint8_t code)
{
	printf("\r\nI2C error occur, code=%d\r\n", code);
	return code;
}

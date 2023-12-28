#include "i2c_ee.h"

#include "stm32f4xx_i2c.h"
#include "usart.h"


#define TIME_OUT 0x0000FFF

uint32_t count_wait = TIME_OUT;

uint8_t Error_CallBack(uint8_t code);
uint8_t Wait_For_Standby(void);


/**
* I2C��GPIO����
* IIC_SCL-PB8  IIC_SDA-PB9
*/
void I2C_GPIO_Config(void)
{
	
	GPIO_InitTypeDef GPIO_InitStruct;
	
	// ����ʱ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	// ����GPIO����
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
* I2C ģʽ����
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
	
	// ʹ��I2C
	I2C_Cmd(I2C1, ENABLE);
}

void I2C_EE_Init(void)
{
	I2C_GPIO_Config();
	I2C_Mode_Config();
}

/**
* @brief ��EEPROMд��һ���ֽ�
* @param addr: Ҫд��Ĵ洢��Ԫ��ַ
* @param data: Ҫд�������
* @return 0 �ɹ�; ��0 ʧ��
*/
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data)
{
	// ������ʼ�ź�
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(1);
		}
	}
	
	// ����EEPROM�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV6�¼�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(2);
		}
	}
	
	// ����Ҫд������ݵ�ַ
	I2C_SendData(I2C1, addr);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV8_2 �¼�����λ�Ĵ���Ϊ�գ����ݼĴ���Ϊ��
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(3);
		}
	}
	
	// ����Ҫд�������
	I2C_SendData(I2C1, data);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV8_2 �¼�����λ�Ĵ���Ϊ�գ����ݼĴ���Ϊ��
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(3);
		}
	}
	
	// ����ֹͣ�ź�
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return Wait_For_Standby();
}

/**
* @brief ��EEPROMд��һҳ����
* @param addr: Ҫд���EEPROM��ַ
* @param data: Ҫд�������ָ��
* @param size: Ҫд������ݴ�С
* @return 0 �ɹ�; ��0 ʧ��
*/
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size)
{
	// ������ʼ�ź�
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(4);
		}
	}
	
	// ����EEPROM�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
	
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV6�¼�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(5);
		}
	}
	
	// ����Ҫд������ݵ�ַ
	I2C_SendData(I2C1, addr);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV8_2 �¼�����λ�Ĵ���Ϊ�գ����ݼĴ���Ϊ��
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(6);
		}
	}
	
	while(size --){
		// ����Ҫд�������
		I2C_SendData(I2C1, *data);
		
		// ���� count_wait
		count_wait = TIME_OUT;
		// �ȴ�EV8_2 �¼�����λ�Ĵ���Ϊ�գ����ݼĴ���Ϊ��
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(7);
			}
		}
		data ++;
	}

	
	// ����ֹͣ�ź�
	I2C_GenerateSTOP(I2C1, ENABLE);
	
	return Wait_For_Standby();
}

/**
* @brief ��EEPROMд��һ������
* @param addr: Ҫд���EERPOM�洢��Ԫ���׵�ַ
* @param data: Ҫд�������ָ��
* @param size: Ҫд������ݳ���
* return 0 �ɹ�; ��0 ʧ��
*/
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size)
{
	// ҳ���룬�������һҳҪд�Ĵ�С firstSize
	uint8_t remainder1 = addr % EEPROM_PAGE_SIZE;
	uint8_t firstSize = EEPROM_PAGE_SIZE - remainder1;
	
	// �۳���һҳд�Ĵ�С��ʣ��Ҫд������
	uint8_t remainSize = size - firstSize;
	uint8_t remainder2 = remainSize % EEPROM_PAGE_SIZE;
	// ʣ��Ҫд��ҳ��С
	uint8_t remainPage = remainSize / EEPROM_PAGE_SIZE;
	
	if(firstSize == (uint8_t)(EEPROM_PAGE_SIZE)){ //��һҳ�պ��Ƕ����
		remainPage += 1; // �ѵ�һҳҲ����ȥ

	} 
	else{ // δ���룬�Ȱѵ�һҳ������д��
		EEPROM_Page_Write(addr, data, firstSize);
		Wait_For_Standby();
		addr += firstSize;
		data += firstSize;
	}

	while(remainPage -- ){ // һҳһҳд
		EEPROM_Page_Write(addr, data, EEPROM_PAGE_SIZE);
		Wait_For_Standby();
		addr += EEPROM_PAGE_SIZE;
		data += EEPROM_PAGE_SIZE;
	}
		
	// дʣ�������
	if(remainder2 != 0){
		EEPROM_Page_Write(addr, data, remainder2);
		Wait_For_Standby();
		addr += remainder2;
		data += remainder2;
	}
	
	return 0;
}

/**
* @brief ��EEPROM��ȡһ���ֽ�����
* @param addr: Ҫ��ȡ�ĵ�ַ
* @param data: �����ȡ������
* @return 0 �ɹ�; ��0 ʧ��
*/
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data)
{
	// ��ʼ�ź�
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(9);
		}
	}
	
	// ����Ҫ��ȡ��I2C�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Transmitter);
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(10);
		}
	}
	
	// ����Ҫ��ȡ��EEPROM���ݵ�ַ
	I2C_SendData(I2C1, addr);
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(11);
		}
	}
	
	
	/********** ���·�����ʼ�źţ���ʼ��ȡ���� ***************/
	// ��ʼ�ź�
	I2C_GenerateSTART(I2C1, DISABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(12);
		}
	}
	
	// ����Ҫ��ȡ��I2C�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Receiver);
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(13);
		}
	}
	
	// ������Ӧ���ź�(�ڽ�������ǰ���ú�)
	I2C_AcknowledgeConfig(I2C1, ENABLE);
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV7�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(14);
		}
	}
	
	// ��ȡ����
	*data = I2C_ReceiveData(I2C1);
	
	// ����ֹͣ�ź�
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 0;
}

/**
* @brief ��EEPROM������ȡ����
* @param addr: Ҫ��ȡ�����ݵ�Ԫ���ַ
* @param data: �����ȡ������
* @param size: Ҫ��ȡ���ٸ�����
* @return 0 �ɹ�; ��0 ʧ��
*/
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size)
{
		// ��ʼ�ź�
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(9);
		}
	}
	
	// ����Ҫ��ȡ��I2C�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Transmitter);
	
	// �ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(10);
		}
	}
	
	// ����Ҫ��ȡ��EEPROM���ݵ�ַ
	I2C_SendData(I2C1, addr);
	// �ȴ�EV8_2�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(11);
		}
	}
	
	
	/********** ���·�����ʼ�źţ���ʼ��ȡ���� ***************/
	// ��ʼ�ź�
	I2C_GenerateSTART(I2C1, ENABLE);
	
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV5�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(12);
		}
	}
	
	// ����Ҫ��ȡ��I2C�豸��ַ��������Ϊд����
	I2C_Send7bitAddress(I2C1, (uint8_t)(EEPROM_ADDR), I2C_Direction_Receiver);
	// ���� count_wait
	count_wait = TIME_OUT;
	// �ȴ�EV6�¼���ֱ�����ɹ�
	while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED) != SUCCESS){
		count_wait --;
		if(count_wait == 0){
			return Error_CallBack(13);
		}
	}
	
	// ��ȡ����
	while(size --){
		if(size == 0){
			// ������Ӧ���ź�(�ڽ�������ǰ���ú�)
			I2C_AcknowledgeConfig(I2C1, DISABLE);
		} else {
			// ����Ӧ���ź�(�ڽ�������ǰ���ú�)
			I2C_AcknowledgeConfig(I2C1, ENABLE);
		}

		// ���� count_wait
		count_wait = TIME_OUT;
		// �ȴ�EV7�¼���ֱ�����ɹ�
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(14);
			}
		}
		
		*data++ = I2C_ReceiveData(I2C1);
	}
	
	
	// ����ֹͣ�ź�
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 0;
}

/**
* @brief �ȴ�EEPROM�ڲ�д��������
* @return 0 �ɹ�; 1 ʧ�ܣ�
*/
uint8_t Wait_For_Standby(void)
{
	uint32_t check_count = 0xFFFFF;
	while(check_count --){
		// ������ʼ�ź�
		I2C_GenerateSTART(I2C1, ENABLE);
		
		// �ȴ�EV5�¼���ֱ�����ɹ�
		while(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT) != SUCCESS){
			count_wait --;
			if(count_wait == 0){
				return Error_CallBack(8);
			}
		}
		
		// ����EEPROM�豸��ַ��������Ϊд����
		I2C_Send7bitAddress(I2C1, EEPROM_ADDR, I2C_Direction_Transmitter);
		
		// ���� count_wait
		count_wait = TIME_OUT;
		// �ȴ�EV6�¼�
		while(count_wait --){
			// ����⵽��Ӧ��˵���ڲ�дʱ����ɣ������ȴ�����
			if(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) == SUCCESS){
				// �˳�ǰֹͣ����ͨ��
				I2C_GenerateSTOP(I2C1, ENABLE);
				return 0;
			}
		}
	}
	// �˳�ǰֹͣ����ͨ��
	I2C_GenerateSTOP(I2C1, ENABLE);
	return 1;
}

uint8_t Error_CallBack(uint8_t code)
{
	printf("\r\nI2C error occur, code=%d\r\n", code);
	return code;
}

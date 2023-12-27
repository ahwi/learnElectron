#include "i2c_ee.h"

#include "stm32f4xx_i2c.h"

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

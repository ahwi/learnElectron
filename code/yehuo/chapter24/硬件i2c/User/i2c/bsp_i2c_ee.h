#ifndef __BSP_I2C_EE_H
#define __BSP_I2C_EE_H

#include "stm32f4xx.h"
#include "bsp_debug_usart.h"

/* STM32 I2C 快速模式 400Kbit*/
#define I2C_Speed 400000 

#define EEPROM_PAGE_SIZE 8

/* EEPROM 地址 */
#define EEPROM_I2C_ADDRESS 0xA0

/* STM32 I2C地址，只要跟外挂的I2C器件地址不一样即可 */
#define I2C_OWN_ADDRESS 0x0A

/* I2C接口 */
#define EEPROM_I2C              I2C1
#define EEPROM_I2C_CLK          RCC_APB1Periph_I2C1

/* I2C_SCK PB8; I2C_SDA PB9 */
#define EEPROM_I2C_SCL_PIN          GPIO_Pin_8
#define EEPROM_I2C_SCL_GPIO_PORT    GPIOB
#define EEPROM_I2C_SCL_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define EEPROM_I2C_SCL_SOURCE       GPIO_PinSource8
#define EEPROM_I2C_SCL_AF           GPIO_AF_I2C1

#define EEPROM_I2C_SDA_PIN          GPIO_Pin_9
#define EEPROM_I2C_SDA_GPIO_PORT    GPIOB
#define EEPROM_I2C_SDA_GPIO_CLK     RCC_AHB1Periph_GPIOB
#define EEPROM_I2C_SDA_SOURCE       GPIO_PinSource9
#define EEPROM_I2C_SDA_AF           GPIO_AF_I2C1

/* 等待超时时间 */


void I2C_EE_Init(void);
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data);
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size);
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data);
uint8_t Wait_For_Standby(void);
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size);
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size);

#endif

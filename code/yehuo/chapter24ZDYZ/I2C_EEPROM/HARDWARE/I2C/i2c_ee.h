#ifndef __I2C_EE_H
#define __I2C_EE_H

#include "stm32f4xx.h"

#define I2C_SPEED 400000
#define I2C_ADDR  0x01
#define EEPROM_ADDR 0xA0
#define EEPROM_PAGE_SIZE 8


void I2C_EE_Init(void);
uint8_t EEPROM_Byte_Write(uint8_t addr, uint8_t data);
uint8_t EEPROM_Page_Write(uint8_t addr, uint8_t *data, uint8_t size);
uint8_t EEPROM_Buffer_Write(uint8_t addr, uint8_t *data, uint16_t size);
uint8_t EEPROM_Random_Read(uint8_t addr, uint8_t *data);
uint8_t EEPROM_Buffer_Read(uint8_t addr, uint8_t *data, uint16_t size);


#endif

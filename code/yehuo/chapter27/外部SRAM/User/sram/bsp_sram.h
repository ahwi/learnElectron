#ifndef __bsp_sram_h
#define __bsp_sram_h

#include "stm32f4xx.h"

/**
FSMC引脚:
    FSMC_A0 ~ A18 行地址
    FSMC_D0 ~ FSMC_D15 数据线
    FSMC_NE3  片选信号
    FSMC_NWE  写入使能
    FSMC_NOE  输出使能
    FSMC_NBL0 数据掩码信号
    FSMC_NBL1 数据掩码信号
 * 
 */

#define Bank1_SRAM3_ADDR    ((uint32_t)0x68000000)

// FSMC_A0~A18 行地址
#define FSMC_A0_GPIO_PORT           GPIOF
#define FSMC_A0_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A0_GPIO_PIN            GPIO_Pin_0
#define FSMC_A0_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A1_GPIO_PORT           GPIOF
#define FSMC_A1_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A1_GPIO_PIN            GPIO_Pin_1
#define FSMC_A1_GPIO_PinSource      GPIO_PinSource1

#define FSMC_A2_GPIO_PORT           GPIOF
#define FSMC_A2_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A2_GPIO_PIN            GPIO_Pin_2
#define FSMC_A2_GPIO_PinSource      GPIO_PinSource2

#define FSMC_A3_GPIO_PORT           GPIOF
#define FSMC_A3_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A3_GPIO_PIN            GPIO_Pin_3
#define FSMC_A3_GPIO_PinSource      GPIO_PinSource3

#define FSMC_A4_GPIO_PORT           GPIOF
#define FSMC_A4_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A4_GPIO_PIN            GPIO_Pin_4
#define FSMC_A4_GPIO_PinSource      GPIO_PinSource4

#define FSMC_A5_GPIO_PORT           GPIOF
#define FSMC_A5_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A5_GPIO_PIN            GPIO_Pin_5
#define FSMC_A5_GPIO_PinSource      GPIO_PinSource5

#define FSMC_A6_GPIO_PORT           GPIOF
#define FSMC_A6_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A6_GPIO_PIN            GPIO_Pin_12
#define FSMC_A6_GPIO_PinSource      GPIO_PinSource12

#define FSMC_A7_GPIO_PORT           GPIOF
#define FSMC_A7_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A7_GPIO_PIN            GPIO_Pin_13
#define FSMC_A7_GPIO_PinSource      GPIO_PinSource13

#define FSMC_A8_GPIO_PORT           GPIOF
#define FSMC_A8_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A8_GPIO_PIN            GPIO_Pin_14
#define FSMC_A8_GPIO_PinSource      GPIO_PinSource14

#define FSMC_A9_GPIO_PORT           GPIOF
#define FSMC_A9_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A9_GPIO_PIN            GPIO_Pin_15
#define FSMC_A9_GPIO_PinSource      GPIO_PinSource15

#define FSMC_A10_GPIO_PORT           GPIOG
#define FSMC_A10_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A10_GPIO_PIN            GPIO_Pin_0
#define FSMC_A10_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A11_GPIO_PORT           GPIOG
#define FSMC_A11_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A11_GPIO_PIN            GPIO_Pin_1
#define FSMC_A11_GPIO_PinSource      GPIO_PinSource1

#define FSMC_A12_GPIO_PORT           GPIOG
#define FSMC_A12_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A12_GPIO_PIN            GPIO_Pin_2
#define FSMC_A12_GPIO_PinSource      GPIO_PinSource2

#define FSMC_A13_GPIO_PORT           GPIOG
#define FSMC_A13_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A13_GPIO_PIN            GPIO_Pin_3
#define FSMC_A13_GPIO_PinSource      GPIO_PinSource3

#define FSMC_A14_GPIO_PORT           GPIOG
#define FSMC_A14_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A14_GPIO_PIN            GPIO_Pin_4
#define FSMC_A14_GPIO_PinSource      GPIO_PinSource4

#define FSMC_A15_GPIO_PORT           GPIOG
#define FSMC_A15_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_A15_GPIO_PIN            GPIO_Pin_5
#define FSMC_A15_GPIO_PinSource      GPIO_PinSource5

#define FSMC_A16_GPIO_PORT           GPIOD
#define FSMC_A16_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_A16_GPIO_PIN            GPIO_Pin_11
#define FSMC_A16_GPIO_PinSource      GPIO_PinSource11

#define FSMC_A17_GPIO_PORT           GPIOD
#define FSMC_A17_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_A17_GPIO_PIN            GPIO_Pin_12
#define FSMC_A17_GPIO_PinSource      GPIO_PinSource12

#define FSMC_A18_GPIO_PORT           GPIOD
#define FSMC_A18_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_A18_GPIO_PIN            GPIO_Pin_13
#define FSMC_A18_GPIO_PinSource      GPIO_PinSource13

// FSMC_D0 ~ FSMC_D15 数据线
#define FSMC_D0_GPIO_PORT           GPIOD
#define FSMC_D0_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D0_GPIO_PIN            GPIO_Pin_14
#define FSMC_D0_GPIO_PinSource      GPIO_PinSource14

#define FSMC_D1_GPIO_PORT           GPIOD
#define FSMC_D1_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D1_GPIO_PIN            GPIO_Pin_15
#define FSMC_D1_GPIO_PinSource      GPIO_PinSource15

#define FSMC_D2_GPIO_PORT           GPIOD
#define FSMC_D2_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D2_GPIO_PIN            GPIO_Pin_0
#define FSMC_D2_GPIO_PinSource      GPIO_PinSource0

#define FSMC_D3_GPIO_PORT           GPIOD
#define FSMC_D3_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D3_GPIO_PIN            GPIO_Pin_1
#define FSMC_D3_GPIO_PinSource      GPIO_PinSource1

#define FSMC_D4_GPIO_PORT           GPIOE
#define FSMC_D4_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D4_GPIO_PIN            GPIO_Pin_7
#define FSMC_D4_GPIO_PinSource      GPIO_PinSource7

#define FSMC_D5_GPIO_PORT           GPIOE
#define FSMC_D5_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D5_GPIO_PIN            GPIO_Pin_8
#define FSMC_D5_GPIO_PinSource      GPIO_PinSource8

#define FSMC_D6_GPIO_PORT           GPIOE
#define FSMC_D6_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D6_GPIO_PIN            GPIO_Pin_9
#define FSMC_D6_GPIO_PinSource      GPIO_PinSource9

#define FSMC_D7_GPIO_PORT           GPIOE
#define FSMC_D7_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D7_GPIO_PIN            GPIO_Pin_10
#define FSMC_D7_GPIO_PinSource      GPIO_PinSource10

#define FSMC_D8_GPIO_PORT           GPIOE
#define FSMC_D8_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D8_GPIO_PIN            GPIO_Pin_11
#define FSMC_D8_GPIO_PinSource      GPIO_PinSource11

#define FSMC_D9_GPIO_PORT           GPIOE
#define FSMC_D9_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D9_GPIO_PIN            GPIO_Pin_12
#define FSMC_D9_GPIO_PinSource      GPIO_PinSource12

#define FSMC_D10_GPIO_PORT           GPIOE
#define FSMC_D10_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D10_GPIO_PIN            GPIO_Pin_13
#define FSMC_D10_GPIO_PinSource      GPIO_PinSource13

#define FSMC_D11_GPIO_PORT           GPIOE
#define FSMC_D11_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D11_GPIO_PIN            GPIO_Pin_14
#define FSMC_D11_GPIO_PinSource      GPIO_PinSource14

#define FSMC_D12_GPIO_PORT           GPIOE
#define FSMC_D12_GPIO_CLCK           RCC_AHB1Periph_GPIOE
#define FSMC_D12_GPIO_PIN            GPIO_Pin_15
#define FSMC_D12_GPIO_PinSource      GPIO_PinSource15

#define FSMC_D13_GPIO_PORT           GPIOD
#define FSMC_D13_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D13_GPIO_PIN            GPIO_Pin_8
#define FSMC_D13_GPIO_PinSource      GPIO_PinSource8

#define FSMC_D14_GPIO_PORT           GPIOD
#define FSMC_D14_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D14_GPIO_PIN            GPIO_Pin_9
#define FSMC_D14_GPIO_PinSource      GPIO_PinSource9

#define FSMC_D15_GPIO_PORT           GPIOD
#define FSMC_D15_GPIO_CLCK           RCC_AHB1Periph_GPIOD
#define FSMC_D15_GPIO_PIN            GPIO_Pin_10
#define FSMC_D15_GPIO_PinSource      GPIO_PinSource10

// SRAM 片选引脚
#define FSMC_CS_GPIO_PORT           GPIOG
#define FSMC_CS_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_CS_GPIO_PIN            GPIO_Pin_10
#define FSMC_CS_GPIO_PinSource      GPIO_PinSource10
// SRAM 写使能
#define FSMC_WR_GPIO_PORT        GPIOD
#define FSMC_WR_GPIO_CLCK        RCC_AHB1Periph_GPIOD
#define FSMC_WR_GPIO_PIN         GPIO_Pin_5
#define FSMC_WR_GPIO_PinSource   GPIO_PinSource5
// SRAM 输出使能
#define FSMC_RD_GPIO_PORT        GPIOD
#define FSMC_RD_GPIO_CLCK        RCC_AHB1Periph_GPIOD
#define FSMC_RD_GPIO_PIN         GPIO_Pin_4
#define FSMC_RD_GPIO_PinSource   GPIO_PinSource4
// UB 数据掩码信号
#define FSMC_UDQM_GPIO_PORT        GPIOE
#define FSMC_UDQM_GPIO_CLCK        RCC_AHB1Periph_GPIOE
#define FSMC_UDQM_GPIO_PIN         GPIO_Pin_1
#define FSMC_UDQM_GPIO_PinSource   GPIO_PinSource1
// LB 数据掩码信号
#define FSMC_LDQM_GPIO_PORT        GPIOE
#define FSMC_LDQM_GPIO_CLCK        RCC_AHB1Periph_GPIOE
#define FSMC_LDQM_GPIO_PIN         GPIO_Pin_0
#define FSMC_LDQM_GPIO_PinSource   GPIO_PinSource0

void FSMC_GPIO_Init(void);
void FSMC_Init(void);

#endif

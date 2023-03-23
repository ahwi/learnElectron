#ifndef __bsp_sram_h
#define __bsp_sram_h

#include "stm32f4xx.h"

/**
FSMC����:
    FSMC_A0 ~ A18 �е�ַ
    FSMC_D0 ~ FSMC_D15 ������
    FSMC_NE3  Ƭѡ�ź�
    FSMC_NWE  д��ʹ��
    FSMC_NOE  ���ʹ��
    FSMC_NBL0 ���������ź�
    FSMC_NBL1 ���������ź�
 * 
 */

// FSMC_A0~A18 �е�ַ
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
#define FSMC_A2_GPIO_PIN            GPIO_Pin_0
#define FSMC_A2_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A3_GPIO_PORT           GPIOF
#define FSMC_A3_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A3_GPIO_PIN            GPIO_Pin_0
#define FSMC_A3_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A4_GPIO_PORT           GPIOF
#define FSMC_A4_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A4_GPIO_PIN            GPIO_Pin_0
#define FSMC_A4_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A5_GPIO_PORT           GPIOF
#define FSMC_A5_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A5_GPIO_PIN            GPIO_Pin_0
#define FSMC_A5_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A6_GPIO_PORT           GPIOF
#define FSMC_A6_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A6_GPIO_PIN            GPIO_Pin_0
#define FSMC_A6_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A7_GPIO_PORT           GPIOF
#define FSMC_A7_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A7_GPIO_PIN            GPIO_Pin_0
#define FSMC_A7_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A8_GPIO_PORT           GPIOF
#define FSMC_A8_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A8_GPIO_PIN            GPIO_Pin_0
#define FSMC_A8_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A9_GPIO_PORT           GPIOF
#define FSMC_A9_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A9_GPIO_PIN            GPIO_Pin_0
#define FSMC_A9_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A10_GPIO_PORT           GPIOF
#define FSMC_A10_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A10_GPIO_PIN            GPIO_Pin_0
#define FSMC_A10_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A11_GPIO_PORT           GPIOF
#define FSMC_A11_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A11_GPIO_PIN            GPIO_Pin_0
#define FSMC_A11_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A12_GPIO_PORT           GPIOF
#define FSMC_A12_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A12_GPIO_PIN            GPIO_Pin_0
#define FSMC_A12_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A13_GPIO_PORT           GPIOF
#define FSMC_A13_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A13_GPIO_PIN            GPIO_Pin_0
#define FSMC_A13_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A14_GPIO_PORT           GPIOF
#define FSMC_A14_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A14_GPIO_PIN            GPIO_Pin_0
#define FSMC_A14_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A15_GPIO_PORT           GPIOF
#define FSMC_A15_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A15_GPIO_PIN            GPIO_Pin_0
#define FSMC_A15_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A16_GPIO_PORT           GPIOF
#define FSMC_A16_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A16_GPIO_PIN            GPIO_Pin_0
#define FSMC_A16_GPIO_PinSource      GPIO_PinSource0

#define FSMC_A17_GPIO_PORT           GPIOF
#define FSMC_A17_GPIO_CLCK           RCC_AHB1Periph_GPIOF
#define FSMC_A17_GPIO_PIN            GPIO_Pin_0
#define FSMC_A17_GPIO_PinSource      GPIO_PinSource0

// SRAM Ƭѡ����
#define FSMC_CS_GPIO_PORT           GPIOG
#define FSMC_CS_GPIO_CLCK           RCC_AHB1Periph_GPIOG
#define FSMC_CS_GPIO_PIN            GPIO_Pin_10
#define FSMC_CS_GPIO_PinSource      GPIO_PinSource10
// SRAM дʹ��
#define FSMC_WR_GPIO_PORT        GPIOD
#define FSMC_WR_GPIO_CLCK        RCC_AHB1Periph_GPIOD
#define FSMC_WR_GPIO_PIN         GPIO_Pin_5
#define FSMC_WR_GPIO_PinSource   GPIO_PinSource5
// SRAM ���ʹ��
#define FSMC_RD_GPIO_PORT        GPIOD
#define FSMC_RD_GPIO_CLCK        RCC_AHB1Periph_GPIOD
#define FSMC_RD_GPIO_PIN         GPIO_Pin_4
#define FSMC_RD_GPIO_PinSource   GPIO_PinSource4
// UB ���������ź�
#define FSMC_UDQM_GPIO_PORT        GPIOE
#define FSMC_UDQM_GPIO_CLCK        RCC_AHB1Periph_GPIOE
#define FSMC_UDQM_GPIO_PIN         GPIO_Pin_1
#define FSMC_UDQM_GPIO_PinSource   GPIO_PinSource1
// LB ���������ź�
#define FSMC_LDQM_GPIO_PORT        GPIOE
#define FSMC_LDQM_GPIO_CLCK        RCC_AHB1Periph_GPIOE
#define FSMC_LDQM_GPIO_PIN         GPIO_Pin_0
#define FSMC_LDQM_GPIO_PinSource   GPIO_PinSource0


#endif
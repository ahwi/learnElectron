#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "stm32f4xx.h"
// #include "stm32f4xx_fsmc.h"

/********************************************************
2^26 = 0x0400 0000 = 64M,ÿ�� BANK ��4*64MB = 256MB
(26Ϊ26����ַ��)
64MB: FSMC_Bank1_NORSRAM1:0x6000 0000 ~ 0x63FF FFFF 
64MB: FSMC_Bank1_NORSRAM2:0x6400 0000 ~ 0x67FF FFFF 
64MB: FSMC_Bank1_NORSRAM3:0x6800 0000 ~ 0x6BFF FFFF 
64MB: FSMC_Bank1_NORSRAM4:0x6c00 0000 ~ 0x6FFF FFFF 
 
 ѡ��BANK1-NORSRAM3 ���� TFT����ַ��ΧΪ0x6800 0000 ~ 0x6BFF FFFF
 FSMC_A0 ��LCD��DC(�Ĵ���/����ѡ��)��
 �Ĵ�������ַ = 0x6800 0000
**********************************************************/

/************************** ILI9806g ��ʾ���� FSMC ��������*******************************/
// FSMC_Bank1_NORSRAM ����LCD��������ĵ�ַ

#define FSMC_Addr_ILI9806G_CMD ((uint32_t) 0x68000000)

// FSMC_Bank1_NORSRAM ����LCD��������ĵ�ַ
#define FSMC_Addr_ILI9806G_DATA ((uint32_t) 0x68000002)

// ��Ƭѡ���ž�����NOR/SRAM��
#define FSMC_Bank1_NORSRAMx  FSMC_Bank1_NORSRAM3

/**************************** ILI98-6g ��ʾ��8080ͨѶ���Ŷ��� ******************************/
/*********�����ź���***********/
#define FSMC_AF                     GPIO_AF_FSMC
//Ƭѡ��ѡ��NOR/SRAM��
#define ILI9806G_CS_CLK             RCC_AHB1Periph_GPIOG
#define ILI9806G_CS_PORT            GPIOG
#define ILI9806G_CS_PIN             GPIO_Pin_10
#define ILI9806G_CS_PinSource       GPIO_PinSource10

//DC���ţ�ʹ��FSMC�ĵ�ַ�źſ��ƣ������ž����˷���LCDʱʹ�õĵ�ַ
//PF0ΪFSMC_A0
#define ILI9806G_DC_CLK             RCC_AHB1Periph_GPIOF
#define ILI9806G_DC_PORT            GPIOF
#define ILI9806G_DC_PIN             GPIO_Pin_0
#define ILI9806G_DC_PinSource       GPIO_PinSource0

//дʹ��
#define ILI9806G_WR_CLK             RCC_AHB1Periph_GPIOD
#define ILI9806G_WR_PORT            GPIOD
#define ILI9806G_WR_PIN             GPIO_Pin_5
#define ILI9806G_WR_PinSource       GPIO_PinSource5

//��ʹ��
#define ILI9806G_RD_CLK             RCC_AHB1Periph_GPIOD
#define ILI9806G_RD_PORT            GPIOD
#define ILI9806G_RD_PIN             GPIO_Pin_4
#define ILI9806G_RD_PinSource       GPIO_PinSource4

//��λ����
#define ILI9806G_RST_CLK            RCC_AHB1Periph_GPIOF
#define ILI9806G_RST_PORT           GPIOF
#define ILI9806G_RST_PIN            GPIO_Pin_11

//��������
#define ILI9806G_BK_CLK            RCC_AHB1Periph_GPIOF
#define ILI9806G_BK_PORT           GPIOF
#define ILI9806G_BK_PIN            GPIO_Pin_9

/********�����ź���***************/
#define      ILI9806G_D0_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D0_PORT               GPIOD
#define      ILI9806G_D0_PIN                GPIO_Pin_14
#define      ILI9806G_D0_PinSource          GPIO_PinSource14

#define      ILI9806G_D1_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D1_PORT               GPIOD
#define      ILI9806G_D1_PIN                GPIO_Pin_15
#define      ILI9806G_D1_PinSource          GPIO_PinSource15

#define      ILI9806G_D2_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D2_PORT               GPIOD
#define      ILI9806G_D2_PIN                GPIO_Pin_0
#define      ILI9806G_D2_PinSource          GPIO_PinSource0

#define      ILI9806G_D3_CLK                RCC_AHB1Periph_GPIOD  
#define      ILI9806G_D3_PORT               GPIOD
#define      ILI9806G_D3_PIN                GPIO_Pin_1
#define      ILI9806G_D3_PinSource          GPIO_PinSource1

#define      ILI9806G_D4_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D4_PORT               GPIOE
#define      ILI9806G_D4_PIN                GPIO_Pin_7
#define      ILI9806G_D4_PinSource          GPIO_PinSource7

#define      ILI9806G_D5_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D5_PORT               GPIOE
#define      ILI9806G_D5_PIN                GPIO_Pin_8
#define      ILI9806G_D5_PinSource          GPIO_PinSource8

#define      ILI9806G_D6_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D6_PORT               GPIOE
#define      ILI9806G_D6_PIN                GPIO_Pin_9
#define      ILI9806G_D6_PinSource          GPIO_PinSource9

#define      ILI9806G_D7_CLK                RCC_AHB1Periph_GPIOE  
#define      ILI9806G_D7_PORT               GPIOE
#define      ILI9806G_D7_PIN                GPIO_Pin_10
#define      ILI9806G_D7_PinSource          GPIO_PinSource10

#define      ILI9806G_D8_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D8_PORT               GPIOE
#define      ILI9806G_D8_PIN                GPIO_Pin_11
#define      ILI9806G_D8_PinSource          GPIO_PinSource11

#define      ILI9806G_D9_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D9_PORT               GPIOE
#define      ILI9806G_D9_PIN                GPIO_Pin_12
#define      ILI9806G_D9_PinSource          GPIO_PinSource12

#define      ILI9806G_D10_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D10_PORT               GPIOE
#define      ILI9806G_D10_PIN                GPIO_Pin_13
#define      ILI9806G_D10_PinSource          GPIO_PinSource13

#define      ILI9806G_D11_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D11_PORT               GPIOE
#define      ILI9806G_D11_PIN                GPIO_Pin_14
#define      ILI9806G_D11_PinSource          GPIO_PinSource14

#define      ILI9806G_D12_CLK                RCC_AHB1Periph_GPIOE   
#define      ILI9806G_D12_PORT               GPIOE
#define      ILI9806G_D12_PIN                GPIO_Pin_15
#define      ILI9806G_D12_PinSource          GPIO_PinSource15

#define      ILI9806G_D13_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D13_PORT               GPIOD
#define      ILI9806G_D13_PIN                GPIO_Pin_8
#define      ILI9806G_D13_PinSource          GPIO_PinSource8

#define      ILI9806G_D14_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D14_PORT               GPIOD
#define      ILI9806G_D14_PIN                GPIO_Pin_9
#define      ILI9806G_D14_PinSource          GPIO_PinSource9

#define      ILI9806G_D15_CLK                RCC_AHB1Periph_GPIOD   
#define      ILI9806G_D15_PORT               GPIOD
#define      ILI9806G_D15_PIN                GPIO_Pin_10
#define      ILI9806G_D15_PinSource          GPIO_PinSource10

/************************ ����Ԥ�� ***************************************/
#define DEBUG_DELAY()   Delay(0x5000)

/************************ ILI9806 ��ʾ�������ʼ������������� ***************************************/
#define ILI9806G_DispWindow_X_Start 0   //��ʼ���x���� 
#define ILI9806G_DispWindow_Y_Start 0   //��ʼ���y���� 

#define ILI9806G_LESS_PIXEL 480 //Һ�����϶̷�������ؿ���
#define ILI9806G_MORE_PIXEL 854 //Һ�����ϳ���������ؿ���

//����Һ��ɨ�跽����仯��XY���ؿ���
//����ILI9806G_GramScan�������÷���ʱ���Զ�����
extern uint16_t LCD_X_LENGTH, LCD_Y_LENGTH;

//Һ����ɨ��ģʽ
//������ѡֵΪ0-7
extern uint8_t  LCD_SCAN_MODE;

/************************* ����ILI9806��ʾ��������ɫ ***************/
#define BACKGROUND  BLACK   //Ĭ�ϱ�����ɫ

#define      WHITE                         0x0000  //��ɫ
#define      BLACK                         0x0000	   //��ɫ 
#define      GREY                          0xF7DE	   //��ɫ 
#define      BLUE                          0x001F	   //��ɫ 
#define      BLUE2                         0x051F	   //ǳ��ɫ 
#define      RED                           0xF800	   //��ɫ 
#define      MAGENTA                       0xF81F	   //����ɫ�����ɫ 
#define      GREEN                         0x07E0	   //��ɫ 
#define      CYAN                          0x7FFF	   //����ɫ����ɫ 
#define      YELLOW                        0xFFE0	   //��ɫ 
#define      BRED                          0xF81F
#define      GRED                          0xFFE0
#define      GBLUE                         0x07FF

/************************* ����ILI9806�������� *******************/
#define CMD_SetCoordinateX  0x2A    //����X����
#define CMD_SetCoordinateY  0x2B    //����Y����
#define CMD_SetPixel        0x2c    //�������

/************************* ����ILI9806���� *******************/
void ILI9806G_Init(void);
void ILI9806G_Rst(void);
void ILI9806G_GramScan(uint8_t ucOtion);
void ILI9806G_OpenWindow(uint16_t usX, uint16_t usY, uint16_t usWindth, uint16_t usHeight);
void ILI9806G_SetPointPixel(uint16_t usX, uint16_t usY);
uint16_t ILI9806G_GetPointPixel(uint16_t usX , uint16_t usY);
void ILI9806G_DrawLine(uint16_t usX1, uint16_t usY1, uint16_t usX2, uint16_t usY2);

void ILI9806G_Clear(uint16_t usX, uint16_t usY, uint16_t usWidth, uint16_t usHeight);
void LCD_SetColors(uint16_t TextColor, uint16_t BackColor);
void LCD_GetColors(uint16_t *TextColor, uint16_t *BackColor);
void LCD_SetTextColor(uint16_t Color);

#endif

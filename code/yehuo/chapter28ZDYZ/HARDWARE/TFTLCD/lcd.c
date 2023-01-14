#include "lcd.h"
#include "usart.h"
#include "delay.h"

#if 1
#define YEHUO 1	//ʹ��Ұ��ӿ�
#else
#define ZDYZ 1	//ʹ������ԭ�ӽӿ�
#endif

//����Һ��ɨ�跽����仯��XY���ؿ��
//����NT35510_GramScan�������÷���ʱ���Զ�����
uint16_t LCD_X_LENGTH = NT35510_MORE_PIXEL;
uint16_t LCD_Y_LENGTH = NT35510_LESS_PIXEL;

//Һ����ɨ��ģʽ����������Ҫ���ڷ���ѡ�������ļ������
//������ѡֵΪ0-7
//Ĭ��Ϊ0�������ҡ����ϵ��½���ɨ��
//����NT35510_GramScan�������÷���ʱ���Զ�����
//LCD�ճ�ʼ�����ʱ��ʹ�ñ�Ĭ��ֵ
uint8_t LCD_SCAN_MODE = 0;
uint16_t lcd_id = 0;

// ����LCD��Ҫ����
// Ĭ��Ϊ����
_lcd_dev lcddev; 

// static sFONT *LCD_Currentfonts = &Font16x32;    //Ӣ������
// static uint16_t CurrentTextColor = WHITE;   //ǰ��ɫ
// static uint16_t CurrentBackColor = WHITE;   //����ɫ

//static void Delay(__IO uint32_t nCount);
__inline void LCD_Write_Cmd(uint16_t usCmd);
__inline void LCD_Write_Data(uint16_t usData);
__inline uint16_t LCD_Read_Data(void);
__inline void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg);


#ifdef YEHUO  //Ұ����Ľӿ�

/**
 * @brief ��LCD������д������
 * @param usCmd: Ҫд��������Ĵ�����
 * @return __inline 
 */
__inline void LCD_Write_Cmd(uint16_t usCmd)
{
    *(__IO uint16_t *) ( FSMC_Addr_NT35510_CMD ) = usCmd;
}

/**
 * @brief ��LCD������д������ 
 * @param usData : Ҫд�������
 * @retval ��
 */
__inline void LCD_Write_Data(uint16_t usData)
{
    *(__IO uint16_t *) ( FSMC_Addr_NT35510_DATA ) = usData;
}

/**
 * @brief ��LCD��������ȡ���� 
 * @param ��
 * @retval ��ȡ��������
 */
__inline uint16_t LCD_Read_Data(void)
{
    return (* (__IO uint16_t *)(FSMC_Addr_NT35510_DATA));
}

/**
 * @brief д�Ĵ��� 
 * @param LCD_Reg  �Ĵ�����ַ
 * @param LCD_RegValue Ҫд�������
 * @return ��
 */
__inline void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD_Write_Cmd(LCD_Reg);
	LCD_Write_Data(LCD_RegValue);
}

/**
 * @brief ���Ĵ���
 * 
 * @param LCD_Reg: �Ĵ�����ַ 
 * @return�� ����������
 */
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
	LCD_Write_Cmd(LCD_Reg);
	delay_us(5);
	return LCD_Read_Data();
} 
#endif


#ifdef ZDYZ

/** 
 * @brief ��LCD������д������
 * 
 * @param usCmd: Ҫд��������Ĵ����� 
 */
void LCD_Write_Cmd(vu16 usCmd)
{
	usCmd = usCmd;	//ʹ��-O2�Ż���ʱ�򣬱���������ʱ
	LCD->LCD_REG = usCmd;	//д��Ҫд��ļĴ������
}

/**
 * @brief ��LCD������д������ 
 * 
 * @param data: Ҫд���ֵ
 */
void LCD_Write_Data(vu16 usData)
{
	usData = usData;	//ʹ��-O2�Ż���ʱ�򣬱���������ʱ
	LCD->LCD_RAM = usData;
}

/**
 * @brief ��LCD���ƶ�ȡ����
 * 
 * @return: ������ֵ 
 */
u16 LCD_Read_Data(void)
{
	vu16 ram;		//��ֹ���Ż�
	ram = LCD->LCD_RAM;
	return ram;
}

/**
 * @brief д�Ĵ���
 * 
 * @param LCD_Reg: �Ĵ�����ַ 
 * @param LCD_RegValue: Ҫд������� 
 */
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
	LCD->LCD_REG = LCD_Reg;			//д��Ҫд�ļĴ������
	LCD->LCD_RAM = LCD_RegValue;	//д������
}

/**
 * @brief ���Ĵ���
 * 
 * @param LCD_Reg: �Ĵ�����ַ 
 * @return: ���������� 
 */
u16 LCD_ReadReg(u16 LCD_Reg)
{
	LCD_Write_Cmd(LCD_Reg);	//д��Ҫ���ļĴ������
	delay_us(5);
	return LCD_Read_Data();
}

#endif



#ifdef YEHUO	//Ұ����Ľӿ�
/**
 * @brief LCD FSMC ģʽ����
 * 		����ΪģʽB���Ҷ�дʱ����
 * @param ��
 * @retval ��
 */
static void NT35510_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming;

    // ʹ��FSMCʱ��
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    // ��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK (16 * 1/168)M=96ns
    // readWriteTiming.FSMC_AddressSetupTime = 0xF;   //��ַ����ʱ��
    readWriteTiming.FSMC_AddressSetupTime = 0x04;   //��ַ����ʱ��
    // ���ݱ���ʱ�䣨DATASET�� + 1��HCLK = 5��168M=30ns
    // readWriteTiming.FSMC_DataSetupTime = 60;   //���ݽ���ʱ�� 60��HCK = 6*60=360ns
    readWriteTiming.FSMC_DataSetupTime = 0x04;   //���ݽ���ʱ�� 60��HCK = 6*60=360ns
    // ѡ����Ƶ�ģʽ
    // ģʽB���첽NOR FLASHģʽ����NT35510��8080ʱ��ƥ��
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;

    // ����������ģʽB�޹�
    // ��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //��ַ����ʱ��
    // ��������ת�����ڣ������ڸ���ģʽ��NOR����
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // ����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // ���ݱ���ʱ�䣬������ͬ���͵�NOR
    readWriteTiming.FSMC_DataLatency = 0x00;

    FSMC_NORSRAMInitStructure.FSMC_Bank             = FSMC_Bank1_NORSRAMx;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux   = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType       = FSMC_MemoryType_NOR;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth  = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode  = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity  = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait  = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode  = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive  = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation  = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal  = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode  = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst  = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct  = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct  = &readWriteTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    //ʹ��FSMC_Bank1_NORSRAM3
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE);

}

/**
 * @brief LCD����LED����
 * @param enumState : �����Ƿ�ʹ�ܱ���LED 
 *      �ò���Ϊ����ֵ֮һ��
 *      @arg ENABLE: ʹ�ܱ���LED
 *      @arg DISABLE: ���ñ���LED
 * @retval ��
 */
void BackLed_Control(FunctionalState enumState)
{
    if(enumState)
        GPIO_SetBits(NT35510_BK_PORT, NT35510_BK_PIN);
    else
        GPIO_ResetBits(NT35510_BK_PORT, NT35510_BK_PIN);
}

/**
 * @brief ����NT35510��GRAMɨ�跽�� 
 * 
 * @param dir: ѡ��GRAM��ɨ�跽��
 * 		0��������ң����ϵ���
 * 		��������ο�LCD�ֲ��0x3600ָ�ֻҪ��עMY MX MV�����ֶε�ֵ
 * 		ע������ԭ����Ļ��ɨ�跽��ֵ��Ұ����Ļ��ɨ�跽��ֵ��һ��
 */
void LCD_Display_Dir(uint8_t ucOption)
{
    //������飬ֻ������0-7
    if(ucOption > 7)
        return;
    
    //����ģʽ����LCD_SCAN_MODE��ֵ����Ҫ���ڴ�����ѡ��������
    if(ucOption%2 == 0)
    {
        //0 2 4 6ģʽ��x�������ؿ��Ϊ480��Y����Ϊ854
        LCD_X_LENGTH = NT35510_LESS_PIXEL;
        LCD_Y_LENGTH = NT35510_MORE_PIXEL;
    }
    else
    {
        //1 2 5 7ģʽ��x�������ؿ��Ϊ854��Y����Ϊ480
        LCD_X_LENGTH = NT35510_MORE_PIXEL;
        LCD_Y_LENGTH = NT35510_LESS_PIXEL;
    }

	lcddev.wramcmd = 0x2C00;
	lcddev.setxcmd = 0x2A00;
	lcddev.setycmd = 0x2B00;
	lcddev.width = 480;
	lcddev.height = 800;
    
    //0x36��������ĸ�3λ����������GRAMɨ�跽��
    LCD_Write_Cmd(0x36);
    LCD_Write_Data(0x00 | (ucOption<<5)); //����ucOption��ֵ����LCD��������0-7��ģʽ

    LCD_Write_Cmd(CMD_SetCoordinateX);
    LCD_Write_Data(0x00);  /*x ��ʼ�����8λ */
    LCD_Write_Cmd(CMD_SetCoordinateX+1);
    LCD_Write_Data(0x00);  /*x ��ʼ�����8λ */
    LCD_Write_Cmd(CMD_SetCoordinateX+2);
    LCD_Write_Data(((LCD_X_LENGTH-1) >> 8) &0xFF);  /*x ���������8λ */
    LCD_Write_Cmd(CMD_SetCoordinateX+3);
    LCD_Write_Data((LCD_X_LENGTH-1) & 0xFF);  /*x ���������8λ */

    LCD_Write_Cmd(CMD_SetCoordinateY);
    LCD_Write_Data(0x00);  /*y ��ʼ�����8λ */
    LCD_Write_Cmd(CMD_SetCoordinateY+1);
    LCD_Write_Data(0x00);  /*y ��ʼ�����8λ */
    LCD_Write_Cmd(CMD_SetCoordinateY+2);
    LCD_Write_Data(((LCD_Y_LENGTH-1) >> 8) &0xFF);  /*y ���������8λ */
    LCD_Write_Cmd(CMD_SetCoordinateY+3);
    LCD_Write_Data((LCD_Y_LENGTH-1) &0xFF);  /*y ���������8λ */

}

#endif


#ifdef ZDYZ	//����ԭ�ӷ��Ĵ���
/**
 * @brief LCD FSMC ģʽ����
 * 		����ΪģʽA���Ҷ�дʱ��ֿ�
 * @param ��
 * @retval ��
 */
static void NT35510_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming;
    FSMC_NORSRAMTimingInitTypeDef writeTiming;

    // ʹ��FSMCʱ��
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    // ��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK (16 * 1/168)M=96ns
    readWriteTiming.FSMC_AddressSetupTime = 0xF;   //��ַ����ʱ��
    // ���ݱ���ʱ�䣨DATASET�� + 1��HCLK = 5��168M=30ns
    readWriteTiming.FSMC_DataSetupTime = 60;   //���ݽ���ʱ�� 60��HCK = 6*60=360ns
    // ѡ����Ƶ�ģʽ
    // ģʽB���첽NOR FLASHģʽ����NT35510��8080ʱ��ƥ��
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    // ����������ģʽA�޹�
    // ��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //��ַ����ʱ��
    // ��������ת�����ڣ������ڸ���ģʽ��NOR����
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // ����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // ���ݱ���ʱ�䣬������ͬ���͵�NOR
    readWriteTiming.FSMC_DataLatency = 0x00;

    // ��ַ����ʱ�䣨ADDSET��Ϊ16��HCLK (9 * 1/168)M=54ns
    readWriteTiming.FSMC_AddressSetupTime = 9;   //��ַ����ʱ��
    // ���ݱ���ʱ�䣨DATASET�� + 1��HCLK = 5��168M=30ns
    readWriteTiming.FSMC_DataSetupTime = 8;   //���ݽ���ʱ�� 9��HCK = 6*9=54ns
    // ѡ����Ƶ�ģʽ
    // ģʽB���첽NOR FLASHģʽ����NT35510��8080ʱ��ƥ��
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    // ����������ģʽA�޹�
    // ��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //��ַ����ʱ��
    // ��������ת�����ڣ������ڸ���ģʽ��NOR����
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // ����ʱ�ӷ�Ƶ��������ͬ�����͵Ĵ洢��
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // ���ݱ���ʱ�䣬������ͬ���͵�NOR
    readWriteTiming.FSMC_DataLatency = 0x00;


    FSMC_NORSRAMInitStructure.FSMC_Bank             = FSMC_Bank1_NORSRAMx;
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux   = FSMC_DataAddressMux_Disable;
    FSMC_NORSRAMInitStructure.FSMC_MemoryType       = FSMC_MemoryType_SRAM;
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth  = FSMC_MemoryDataWidth_16b;
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode  = FSMC_BurstAccessMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity  = FSMC_WaitSignalPolarity_Low;
    FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait  = FSMC_AsynchronousWait_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WrapMode  = FSMC_WrapMode_Disable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive  = FSMC_WaitSignalActive_BeforeWaitState;
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation  = FSMC_WriteOperation_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal  = FSMC_WaitSignal_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode  = FSMC_ExtendedMode_Enable;
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst  = FSMC_WriteBurst_Disable;
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct  = &readWriteTiming;
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct  = &writeTiming;

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);

    //ʹ��FSMC_Bank1_NORSRAM3
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE);

}

/**
 * @brief LCD����LED����
 * @param enumState : �����Ƿ�ʹ�ܱ���LED 
 *      �ò���Ϊ����ֵ֮һ��
 *      @arg ENABLE: ʹ�ܱ���LED
 *      @arg DISABLE: ���ñ���LED
 * @retval ��
 */
void BackLed_Control(FunctionalState enumState)
{
    if(enumState)
		LCD_LED=1;				//��������
    else
		LCD_LED=0;				//�رձ���
}

void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
	switch(dir)
	{
		case L2R_U2D://������,���ϵ���
			regval|=(0<<7)|(0<<6)|(0<<5); 
			break;
		case L2R_D2U://������,���µ���
			regval|=(1<<7)|(0<<6)|(0<<5); 
			break;
		case R2L_U2D://���ҵ���,���ϵ���
			regval|=(0<<7)|(1<<6)|(0<<5); 
			break;
		case R2L_D2U://���ҵ���,���µ���
			regval|=(1<<7)|(1<<6)|(0<<5); 
			break;	 
		case U2D_L2R://���ϵ���,������
			regval|=(0<<7)|(0<<6)|(1<<5); 
			break;
		case U2D_R2L://���ϵ���,���ҵ���
			regval|=(0<<7)|(1<<6)|(1<<5); 
			break;
		case D2U_L2R://���µ���,������
			regval|=(1<<7)|(0<<6)|(1<<5); 
			break;
		case D2U_R2L://���µ���,���ҵ���
			regval|=(1<<7)|(1<<6)|(1<<5); 
			break;	 
	}

	// ����ɨ�跽��
	dirreg=0X3600;
	LCD_WriteReg(dirreg,regval);

	if(regval&0X20)
	{
		if(lcddev.width<lcddev.height)//����X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}else  
	{
		if(lcddev.width>lcddev.height)//����X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}  

	// ������ʼ����ͽ�������
	LCD_Write_Cmd(lcddev.setxcmd);LCD_Write_Data(0); 
	LCD_Write_Cmd(lcddev.setxcmd+1);LCD_Write_Data(0); 
	LCD_Write_Cmd(lcddev.setxcmd+2);LCD_Write_Data((lcddev.width-1)>>8); 
	LCD_Write_Cmd(lcddev.setxcmd+3);LCD_Write_Data((lcddev.width-1)&0XFF); 
	LCD_Write_Cmd(lcddev.setycmd);LCD_Write_Data(0); 
	LCD_Write_Cmd(lcddev.setycmd+1);LCD_Write_Data(0); 
	LCD_Write_Cmd(lcddev.setycmd+2);LCD_Write_Data((lcddev.height-1)>>8); 
	LCD_Write_Cmd(lcddev.setycmd+3);LCD_Write_Data((lcddev.height-1)&0XFF);
}     

/**
 * @brief ����NT35510��GRAMɨ�跽�� 
 * 
 * @param dir: ѡ��GRAM��ɨ�跽��
 * 		0��������ң����ϵ���
 * 		��������ο�LCD�ֲ��0x3600ָ�ֻҪ��עMY MX MV�����ֶε�ֵ
 * 		ע������ԭ����Ļ��ɨ�跽��ֵ��Ұ����Ļ��ɨ�跽��ֵ��һ��
 */
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)			//����
	{
		lcddev.dir=0;	//����
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=480;
		lcddev.height=800;
	}else 				//����
	{	  				
		lcddev.dir=1;	//����
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=800;
		lcddev.height=480;
	} 
	LCD_Scan_Dir(0);	//Ĭ��ɨ�跽��
}	 

#endif

/********************���ô���*******************************/
/**
 * @brief ��ʼ��NT35510��IO����
 * @param ��
 * @retval ��
 */
static void NT35510_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(
        //�����ź�
        NT35510_CS_CLK|NT35510_DC_CLK|NT35510_WR_CLK|
        // NT35510_RD_CLK|NT35510_BK_CLK|NT35510_RST_CLK|
        NT35510_RD_CLK|NT35510_BK_CLK|
        //�����ź���
        NT35510_D0_CLK|NT35510_D1_CLK|NT35510_D2_CLK|
        NT35510_D3_CLK|NT35510_D4_CLK|NT35510_D5_CLK|
        NT35510_D6_CLK|NT35510_D7_CLK|NT35510_D8_CLK|
        NT35510_D9_CLK|NT35510_D10_CLK|NT35510_D11_CLK|
        NT35510_D12_CLK|NT35510_D13_CLK|NT35510_D14_CLK|
        NT35510_D1_CLK, ENABLE);

	// RCC_AHB1PeriphClockCmd(
	// 	RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|
	// 	RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|
	// 	RCC_AHB1Periph_GPIOG, ENABLE);//ʹ��PD,PE,PF,PGʱ��  
    
    //����FSMC����ڵ������ߣ�FSMC-D0~D15
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//100MHZ

    GPIO_InitStructure.GPIO_Pin = NT35510_D0_PIN;
    GPIO_Init(NT35510_D0_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D0_PORT, NT35510_D0_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D1_PIN;
    GPIO_Init(NT35510_D1_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D1_PORT, NT35510_D1_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D2_PIN;
    GPIO_Init(NT35510_D2_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D2_PORT, NT35510_D2_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D3_PIN;
    GPIO_Init(NT35510_D3_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D3_PORT, NT35510_D3_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D4_PIN;
    GPIO_Init(NT35510_D4_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D4_PORT, NT35510_D4_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D5_PIN;
    GPIO_Init(NT35510_D5_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D5_PORT, NT35510_D5_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D6_PIN;
    GPIO_Init(NT35510_D6_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D6_PORT, NT35510_D6_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D7_PIN;
    GPIO_Init(NT35510_D7_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D7_PORT, NT35510_D7_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D8_PIN;
    GPIO_Init(NT35510_D8_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D8_PORT, NT35510_D8_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D9_PIN;
    GPIO_Init(NT35510_D9_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D9_PORT, NT35510_D9_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D10_PIN;
    GPIO_Init(NT35510_D10_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D10_PORT, NT35510_D10_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D11_PIN;
    GPIO_Init(NT35510_D11_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D11_PORT, NT35510_D11_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D12_PIN;
    GPIO_Init(NT35510_D12_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D12_PORT, NT35510_D12_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D13_PIN;
    GPIO_Init(NT35510_D13_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D13_PORT, NT35510_D13_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D14_PIN;
    GPIO_Init(NT35510_D14_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D14_PORT, NT35510_D14_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_D15_PIN;
    GPIO_Init(NT35510_D15_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_D15_PORT, NT35510_D15_PinSource, FSMC_AF);

    /* ����FSMC���Ӧ�Ŀ�����
    * FSMC_NOE: LCD-RD
    * FSMC_NWE: LCD-WR
    * FSMC_NE1: LCD-CS
    * FSMC_A0: LCD-DC
    */
    GPIO_InitStructure.GPIO_Pin = NT35510_RD_PIN;
    GPIO_Init(NT35510_RD_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_RD_PORT, NT35510_RD_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_WR_PIN;
    GPIO_Init(NT35510_WR_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_WR_PORT, NT35510_WR_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_CS_PIN;
    GPIO_Init(NT35510_CS_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_CS_PORT, NT35510_CS_PinSource, FSMC_AF);

    GPIO_InitStructure.GPIO_Pin = NT35510_DC_PIN;
    GPIO_Init(NT35510_DC_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(NT35510_DC_PORT, NT35510_DC_PinSource, FSMC_AF);

    // ����LCD��λRST���ƹܽ�
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// ����ԭ�ӵ�LCD����λ���Ž���ϵͳ��λ���ţ������߲���Ҫ����
    // GPIO_InitStructure.GPIO_Pin = NT35510_RST_PIN;
    // GPIO_Init(NT35510_RST_PORT, &GPIO_InitStructure);

    // ����LCD������ƹؼ�BK
    GPIO_InitStructure.GPIO_Pin = NT35510_BK_PIN;
    GPIO_Init(NT35510_BK_PORT, &GPIO_InitStructure);
}


/**
* @brief NT35510�ĳ�ʼ��
*/
void NT35510_REG_Config(void)
{
	//��������дʱ����ƼĴ�����ʱ��   	 							    
	FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
	FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//���ݱ���ʱ������
	FSMC_Bank1E->BWTR[6]|=3<<0;		//��ַ����ʱ��(ADDSET)Ϊ3��HCLK =18ns  	 
	FSMC_Bank1E->BWTR[6]|=2<<8; 	//���ݱ���ʱ��(DATAST)Ϊ6ns*3��HCLK=18ns

#if 0
	// NT35510�������״ζ�����ID��������������
   	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)//����ID����ȷ,����lcddev.id==0X9300�жϣ���Ϊ9341��δ����λ������»ᱻ����9300
	{	
 		//����9341 ID�Ķ�ȡ		
		LCD_Write_Cmd(0XD3);				   
		lcddev.id=LCD_RD_DATA();	//dummy read 	
 		lcddev.id=LCD_RD_DATA();	//����0X00
  		lcddev.id=LCD_RD_DATA();   	//��ȡ93								   
 		lcddev.id<<=8;
		lcddev.id|=LCD_RD_DATA();  	//��ȡ41 	   			   
 		if(lcddev.id!=0X9341)		//��9341,�����ǲ���6804
		{	
 			LCD_Write_Cmd(0XBF);				   
			lcddev.id=LCD_RD_DATA(); 	//dummy read 	 
	 		lcddev.id=LCD_RD_DATA();   	//����0X01			   
	 		lcddev.id=LCD_RD_DATA(); 	//����0XD0 			  	
	  		lcddev.id=LCD_RD_DATA();	//�������0X68 
			lcddev.id<<=8;
	  		lcddev.id|=LCD_RD_DATA();	//�������0X04	  
			if(lcddev.id!=0X6804)		//Ҳ����6804,���Կ����ǲ���NT35310
			{ 
				LCD_Write_Cmd(0XD4);				   
				lcddev.id=LCD_RD_DATA();//dummy read  
				lcddev.id=LCD_RD_DATA();//����0X01	 
				lcddev.id=LCD_RD_DATA();//����0X53	
				lcddev.id<<=8;	 
				lcddev.id|=LCD_RD_DATA();	//�������0X10	 
				if(lcddev.id!=0X5310)		//Ҳ����NT35310,���Կ����ǲ���NT35510
				{
					LCD_Write_Cmd(0XDA00);	
					lcddev.id=LCD_RD_DATA();		//����0X00	 
					LCD_Write_Cmd(0XDB00);	
					lcddev.id=LCD_RD_DATA();		//����0X80
					lcddev.id<<=8;	
					LCD_Write_Cmd(0XDC00);	
					lcddev.id|=LCD_RD_DATA();		//����0X00		
					if(lcddev.id==0x8000)lcddev.id=0x5510;//NT35510���ص�ID��8000H,Ϊ��������,����ǿ������Ϊ5510
					if(lcddev.id!=0X5510)			//Ҳ����NT5510,���Կ����ǲ���SSD1963
					{
						LCD_Write_Cmd(0XA1);
						lcddev.id=LCD_RD_DATA();
						lcddev.id=LCD_RD_DATA();	//����0X57
						lcddev.id<<=8;	 
						lcddev.id|=LCD_RD_DATA();	//����0X61	
						if(lcddev.id==0X5761)lcddev.id=0X1963;//SSD1963���ص�ID��5761H,Ϊ��������,����ǿ������Ϊ1963
					}
				}
			}
 		}  	
	} 
	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)//������⼸��IC,������WRʱ��Ϊ���
	{
		//��������дʱ����ƼĴ�����ʱ��   	 							    
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//���ݱ���ʱ������
		FSMC_Bank1E->BWTR[6]|=3<<0;		//��ַ����ʱ��(ADDSET)Ϊ3��HCLK =18ns  	 
		FSMC_Bank1E->BWTR[6]|=2<<8; 	//���ݱ���ʱ��(DATAST)Ϊ6ns*3��HCLK=18ns
	}else if(lcddev.id==0X6804||lcddev.id==0XC505)	//6804/C505�ٶ��ϲ�ȥ,�ý���
	{
		//��������дʱ����ƼĴ�����ʱ��   	 							    
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//��ַ����ʱ��(ADDSET)���� 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//���ݱ���ʱ������
		FSMC_Bank1E->BWTR[6]|=10<<0;	//��ַ����ʱ��(ADDSET)Ϊ10��HCLK =60ns  	 
		FSMC_Bank1E->BWTR[6]|=12<<8; 	//���ݱ���ʱ��(DATAST)Ϊ6ns*13��HCLK=78ns
	}
#endif

#if 1
	LCD_WriteReg(0xF000,0x55);
	LCD_WriteReg(0xF001,0xAA);
	LCD_WriteReg(0xF002,0x52);
	LCD_WriteReg(0xF003,0x08);
	LCD_WriteReg(0xF004,0x01);
	//AVDD Set AVDD 5.2V
	LCD_WriteReg(0xB000,0x0D);
	LCD_WriteReg(0xB001,0x0D);
	LCD_WriteReg(0xB002,0x0D);
	//AVDD ratio
	LCD_WriteReg(0xB600,0x34);
	LCD_WriteReg(0xB601,0x34);
	LCD_WriteReg(0xB602,0x34);
	//AVEE -5.2V
	LCD_WriteReg(0xB100,0x0D);
	LCD_WriteReg(0xB101,0x0D);
	LCD_WriteReg(0xB102,0x0D);
	//AVEE ratio
	LCD_WriteReg(0xB700,0x34);
	LCD_WriteReg(0xB701,0x34);
	LCD_WriteReg(0xB702,0x34);
	//VCL -2.5V
	LCD_WriteReg(0xB200,0x00);
	LCD_WriteReg(0xB201,0x00);
	LCD_WriteReg(0xB202,0x00);
	//VCL ratio
	LCD_WriteReg(0xB800,0x24);
	LCD_WriteReg(0xB801,0x24);
	LCD_WriteReg(0xB802,0x24);
	//VGH 15V (Free pump)
	LCD_WriteReg(0xBF00,0x01);
	LCD_WriteReg(0xB300,0x0F);
	LCD_WriteReg(0xB301,0x0F);
	LCD_WriteReg(0xB302,0x0F);
	//VGH ratio
	LCD_WriteReg(0xB900,0x34);
	LCD_WriteReg(0xB901,0x34);
	LCD_WriteReg(0xB902,0x34);
	//VGL_REG -10V
	LCD_WriteReg(0xB500,0x08);
	LCD_WriteReg(0xB501,0x08);
	LCD_WriteReg(0xB502,0x08);
	LCD_WriteReg(0xC200,0x03);
	//VGLX ratio
	LCD_WriteReg(0xBA00,0x24);
	LCD_WriteReg(0xBA01,0x24);
	LCD_WriteReg(0xBA02,0x24);
	//VGMP/VGSP 4.5V/0V
	LCD_WriteReg(0xBC00,0x00);
	LCD_WriteReg(0xBC01,0x78);
	LCD_WriteReg(0xBC02,0x00);
	//VGMN/VGSN -4.5V/0V
	LCD_WriteReg(0xBD00,0x00);
	LCD_WriteReg(0xBD01,0x78);
	LCD_WriteReg(0xBD02,0x00);
	//VCOM
	LCD_WriteReg(0xBE00,0x00);
	LCD_WriteReg(0xBE01,0x64);
	//Gamma Setting
	LCD_WriteReg(0xD100,0x00);
	LCD_WriteReg(0xD101,0x33);
	LCD_WriteReg(0xD102,0x00);
	LCD_WriteReg(0xD103,0x34);
	LCD_WriteReg(0xD104,0x00);
	LCD_WriteReg(0xD105,0x3A);
	LCD_WriteReg(0xD106,0x00);
	LCD_WriteReg(0xD107,0x4A);
	LCD_WriteReg(0xD108,0x00);
	LCD_WriteReg(0xD109,0x5C);
	LCD_WriteReg(0xD10A,0x00);
	LCD_WriteReg(0xD10B,0x81);
	LCD_WriteReg(0xD10C,0x00);
	LCD_WriteReg(0xD10D,0xA6);
	LCD_WriteReg(0xD10E,0x00);
	LCD_WriteReg(0xD10F,0xE5);
	LCD_WriteReg(0xD110,0x01);
	LCD_WriteReg(0xD111,0x13);
	LCD_WriteReg(0xD112,0x01);
	LCD_WriteReg(0xD113,0x54);
	LCD_WriteReg(0xD114,0x01);
	LCD_WriteReg(0xD115,0x82);
	LCD_WriteReg(0xD116,0x01);
	LCD_WriteReg(0xD117,0xCA);
	LCD_WriteReg(0xD118,0x02);
	LCD_WriteReg(0xD119,0x00);
	LCD_WriteReg(0xD11A,0x02);
	LCD_WriteReg(0xD11B,0x01);
	LCD_WriteReg(0xD11C,0x02);
	LCD_WriteReg(0xD11D,0x34);
	LCD_WriteReg(0xD11E,0x02);
	LCD_WriteReg(0xD11F,0x67);
	LCD_WriteReg(0xD120,0x02);
	LCD_WriteReg(0xD121,0x84);
	LCD_WriteReg(0xD122,0x02);
	LCD_WriteReg(0xD123,0xA4);
	LCD_WriteReg(0xD124,0x02);
	LCD_WriteReg(0xD125,0xB7);
	LCD_WriteReg(0xD126,0x02);
	LCD_WriteReg(0xD127,0xCF);
	LCD_WriteReg(0xD128,0x02);
	LCD_WriteReg(0xD129,0xDE);
	LCD_WriteReg(0xD12A,0x02);
	LCD_WriteReg(0xD12B,0xF2);
	LCD_WriteReg(0xD12C,0x02);
	LCD_WriteReg(0xD12D,0xFE);
	LCD_WriteReg(0xD12E,0x03);
	LCD_WriteReg(0xD12F,0x10);
	LCD_WriteReg(0xD130,0x03);
	LCD_WriteReg(0xD131,0x33);
	LCD_WriteReg(0xD132,0x03);
	LCD_WriteReg(0xD133,0x6D);
	LCD_WriteReg(0xD200,0x00);
	LCD_WriteReg(0xD201,0x33);
	LCD_WriteReg(0xD202,0x00);
	LCD_WriteReg(0xD203,0x34);
	LCD_WriteReg(0xD204,0x00);
	LCD_WriteReg(0xD205,0x3A);
	LCD_WriteReg(0xD206,0x00);
	LCD_WriteReg(0xD207,0x4A);
	LCD_WriteReg(0xD208,0x00);
	LCD_WriteReg(0xD209,0x5C);
	LCD_WriteReg(0xD20A,0x00);

	LCD_WriteReg(0xD20B,0x81);
	LCD_WriteReg(0xD20C,0x00);
	LCD_WriteReg(0xD20D,0xA6);
	LCD_WriteReg(0xD20E,0x00);
	LCD_WriteReg(0xD20F,0xE5);
	LCD_WriteReg(0xD210,0x01);
	LCD_WriteReg(0xD211,0x13);
	LCD_WriteReg(0xD212,0x01);
	LCD_WriteReg(0xD213,0x54);
	LCD_WriteReg(0xD214,0x01);
	LCD_WriteReg(0xD215,0x82);
	LCD_WriteReg(0xD216,0x01);
	LCD_WriteReg(0xD217,0xCA);
	LCD_WriteReg(0xD218,0x02);
	LCD_WriteReg(0xD219,0x00);
	LCD_WriteReg(0xD21A,0x02);
	LCD_WriteReg(0xD21B,0x01);
	LCD_WriteReg(0xD21C,0x02);
	LCD_WriteReg(0xD21D,0x34);
	LCD_WriteReg(0xD21E,0x02);
	LCD_WriteReg(0xD21F,0x67);
	LCD_WriteReg(0xD220,0x02);
	LCD_WriteReg(0xD221,0x84);
	LCD_WriteReg(0xD222,0x02);
	LCD_WriteReg(0xD223,0xA4);
	LCD_WriteReg(0xD224,0x02);
	LCD_WriteReg(0xD225,0xB7);
	LCD_WriteReg(0xD226,0x02);
	LCD_WriteReg(0xD227,0xCF);
	LCD_WriteReg(0xD228,0x02);
	LCD_WriteReg(0xD229,0xDE);
	LCD_WriteReg(0xD22A,0x02);
	LCD_WriteReg(0xD22B,0xF2);
	LCD_WriteReg(0xD22C,0x02);
	LCD_WriteReg(0xD22D,0xFE);
	LCD_WriteReg(0xD22E,0x03);
	LCD_WriteReg(0xD22F,0x10);
	LCD_WriteReg(0xD230,0x03);
	LCD_WriteReg(0xD231,0x33);
	LCD_WriteReg(0xD232,0x03);
	LCD_WriteReg(0xD233,0x6D);
	LCD_WriteReg(0xD300,0x00);
	LCD_WriteReg(0xD301,0x33);
	LCD_WriteReg(0xD302,0x00);
	LCD_WriteReg(0xD303,0x34);
	LCD_WriteReg(0xD304,0x00);
	LCD_WriteReg(0xD305,0x3A);
	LCD_WriteReg(0xD306,0x00);
	LCD_WriteReg(0xD307,0x4A);
	LCD_WriteReg(0xD308,0x00);
	LCD_WriteReg(0xD309,0x5C);
	LCD_WriteReg(0xD30A,0x00);

	LCD_WriteReg(0xD30B,0x81);
	LCD_WriteReg(0xD30C,0x00);
	LCD_WriteReg(0xD30D,0xA6);
	LCD_WriteReg(0xD30E,0x00);
	LCD_WriteReg(0xD30F,0xE5);
	LCD_WriteReg(0xD310,0x01);
	LCD_WriteReg(0xD311,0x13);
	LCD_WriteReg(0xD312,0x01);
	LCD_WriteReg(0xD313,0x54);
	LCD_WriteReg(0xD314,0x01);
	LCD_WriteReg(0xD315,0x82);
	LCD_WriteReg(0xD316,0x01);
	LCD_WriteReg(0xD317,0xCA);
	LCD_WriteReg(0xD318,0x02);
	LCD_WriteReg(0xD319,0x00);
	LCD_WriteReg(0xD31A,0x02);
	LCD_WriteReg(0xD31B,0x01);
	LCD_WriteReg(0xD31C,0x02);
	LCD_WriteReg(0xD31D,0x34);
	LCD_WriteReg(0xD31E,0x02);
	LCD_WriteReg(0xD31F,0x67);
	LCD_WriteReg(0xD320,0x02);
	LCD_WriteReg(0xD321,0x84);
	LCD_WriteReg(0xD322,0x02);
	LCD_WriteReg(0xD323,0xA4);
	LCD_WriteReg(0xD324,0x02);
	LCD_WriteReg(0xD325,0xB7);
	LCD_WriteReg(0xD326,0x02);
	LCD_WriteReg(0xD327,0xCF);
	LCD_WriteReg(0xD328,0x02);
	LCD_WriteReg(0xD329,0xDE);
	LCD_WriteReg(0xD32A,0x02);
	LCD_WriteReg(0xD32B,0xF2);
	LCD_WriteReg(0xD32C,0x02);
	LCD_WriteReg(0xD32D,0xFE);
	LCD_WriteReg(0xD32E,0x03);
	LCD_WriteReg(0xD32F,0x10);
	LCD_WriteReg(0xD330,0x03);
	LCD_WriteReg(0xD331,0x33);
	LCD_WriteReg(0xD332,0x03);
	LCD_WriteReg(0xD333,0x6D);
	LCD_WriteReg(0xD400,0x00);
	LCD_WriteReg(0xD401,0x33);
	LCD_WriteReg(0xD402,0x00);
	LCD_WriteReg(0xD403,0x34);
	LCD_WriteReg(0xD404,0x00);
	LCD_WriteReg(0xD405,0x3A);
	LCD_WriteReg(0xD406,0x00);
	LCD_WriteReg(0xD407,0x4A);
	LCD_WriteReg(0xD408,0x00);
	LCD_WriteReg(0xD409,0x5C);
	LCD_WriteReg(0xD40A,0x00);
	LCD_WriteReg(0xD40B,0x81);

	LCD_WriteReg(0xD40C,0x00);
	LCD_WriteReg(0xD40D,0xA6);
	LCD_WriteReg(0xD40E,0x00);
	LCD_WriteReg(0xD40F,0xE5);
	LCD_WriteReg(0xD410,0x01);
	LCD_WriteReg(0xD411,0x13);
	LCD_WriteReg(0xD412,0x01);
	LCD_WriteReg(0xD413,0x54);
	LCD_WriteReg(0xD414,0x01);
	LCD_WriteReg(0xD415,0x82);
	LCD_WriteReg(0xD416,0x01);
	LCD_WriteReg(0xD417,0xCA);
	LCD_WriteReg(0xD418,0x02);
	LCD_WriteReg(0xD419,0x00);
	LCD_WriteReg(0xD41A,0x02);
	LCD_WriteReg(0xD41B,0x01);
	LCD_WriteReg(0xD41C,0x02);
	LCD_WriteReg(0xD41D,0x34);
	LCD_WriteReg(0xD41E,0x02);
	LCD_WriteReg(0xD41F,0x67);
	LCD_WriteReg(0xD420,0x02);
	LCD_WriteReg(0xD421,0x84);
	LCD_WriteReg(0xD422,0x02);
	LCD_WriteReg(0xD423,0xA4);
	LCD_WriteReg(0xD424,0x02);
	LCD_WriteReg(0xD425,0xB7);
	LCD_WriteReg(0xD426,0x02);
	LCD_WriteReg(0xD427,0xCF);
	LCD_WriteReg(0xD428,0x02);
	LCD_WriteReg(0xD429,0xDE);
	LCD_WriteReg(0xD42A,0x02);
	LCD_WriteReg(0xD42B,0xF2);
	LCD_WriteReg(0xD42C,0x02);
	LCD_WriteReg(0xD42D,0xFE);
	LCD_WriteReg(0xD42E,0x03);
	LCD_WriteReg(0xD42F,0x10);
	LCD_WriteReg(0xD430,0x03);
	LCD_WriteReg(0xD431,0x33);
	LCD_WriteReg(0xD432,0x03);
	LCD_WriteReg(0xD433,0x6D);
	LCD_WriteReg(0xD500,0x00);
	LCD_WriteReg(0xD501,0x33);
	LCD_WriteReg(0xD502,0x00);
	LCD_WriteReg(0xD503,0x34);
	LCD_WriteReg(0xD504,0x00);
	LCD_WriteReg(0xD505,0x3A);
	LCD_WriteReg(0xD506,0x00);
	LCD_WriteReg(0xD507,0x4A);
	LCD_WriteReg(0xD508,0x00);
	LCD_WriteReg(0xD509,0x5C);
	LCD_WriteReg(0xD50A,0x00);
	LCD_WriteReg(0xD50B,0x81);

	LCD_WriteReg(0xD50C,0x00);
	LCD_WriteReg(0xD50D,0xA6);
	LCD_WriteReg(0xD50E,0x00);
	LCD_WriteReg(0xD50F,0xE5);
	LCD_WriteReg(0xD510,0x01);
	LCD_WriteReg(0xD511,0x13);
	LCD_WriteReg(0xD512,0x01);
	LCD_WriteReg(0xD513,0x54);
	LCD_WriteReg(0xD514,0x01);
	LCD_WriteReg(0xD515,0x82);
	LCD_WriteReg(0xD516,0x01);
	LCD_WriteReg(0xD517,0xCA);
	LCD_WriteReg(0xD518,0x02);
	LCD_WriteReg(0xD519,0x00);
	LCD_WriteReg(0xD51A,0x02);
	LCD_WriteReg(0xD51B,0x01);
	LCD_WriteReg(0xD51C,0x02);
	LCD_WriteReg(0xD51D,0x34);
	LCD_WriteReg(0xD51E,0x02);
	LCD_WriteReg(0xD51F,0x67);
	LCD_WriteReg(0xD520,0x02);
	LCD_WriteReg(0xD521,0x84);
	LCD_WriteReg(0xD522,0x02);
	LCD_WriteReg(0xD523,0xA4);
	LCD_WriteReg(0xD524,0x02);
	LCD_WriteReg(0xD525,0xB7);
	LCD_WriteReg(0xD526,0x02);
	LCD_WriteReg(0xD527,0xCF);
	LCD_WriteReg(0xD528,0x02);
	LCD_WriteReg(0xD529,0xDE);
	LCD_WriteReg(0xD52A,0x02);
	LCD_WriteReg(0xD52B,0xF2);
	LCD_WriteReg(0xD52C,0x02);
	LCD_WriteReg(0xD52D,0xFE);
	LCD_WriteReg(0xD52E,0x03);
	LCD_WriteReg(0xD52F,0x10);
	LCD_WriteReg(0xD530,0x03);
	LCD_WriteReg(0xD531,0x33);
	LCD_WriteReg(0xD532,0x03);
	LCD_WriteReg(0xD533,0x6D);
	LCD_WriteReg(0xD600,0x00);
	LCD_WriteReg(0xD601,0x33);
	LCD_WriteReg(0xD602,0x00);
	LCD_WriteReg(0xD603,0x34);
	LCD_WriteReg(0xD604,0x00);
	LCD_WriteReg(0xD605,0x3A);
	LCD_WriteReg(0xD606,0x00);
	LCD_WriteReg(0xD607,0x4A);
	LCD_WriteReg(0xD608,0x00);
	LCD_WriteReg(0xD609,0x5C);
	LCD_WriteReg(0xD60A,0x00);
	LCD_WriteReg(0xD60B,0x81);

	LCD_WriteReg(0xD60C,0x00);
	LCD_WriteReg(0xD60D,0xA6);
	LCD_WriteReg(0xD60E,0x00);
	LCD_WriteReg(0xD60F,0xE5);
	LCD_WriteReg(0xD610,0x01);
	LCD_WriteReg(0xD611,0x13);
	LCD_WriteReg(0xD612,0x01);
	LCD_WriteReg(0xD613,0x54);
	LCD_WriteReg(0xD614,0x01);
	LCD_WriteReg(0xD615,0x82);
	LCD_WriteReg(0xD616,0x01);
	LCD_WriteReg(0xD617,0xCA);
	LCD_WriteReg(0xD618,0x02);
	LCD_WriteReg(0xD619,0x00);
	LCD_WriteReg(0xD61A,0x02);
	LCD_WriteReg(0xD61B,0x01);
	LCD_WriteReg(0xD61C,0x02);
	LCD_WriteReg(0xD61D,0x34);
	LCD_WriteReg(0xD61E,0x02);
	LCD_WriteReg(0xD61F,0x67);
	LCD_WriteReg(0xD620,0x02);
	LCD_WriteReg(0xD621,0x84);
	LCD_WriteReg(0xD622,0x02);
	LCD_WriteReg(0xD623,0xA4);
	LCD_WriteReg(0xD624,0x02);
	LCD_WriteReg(0xD625,0xB7);
	LCD_WriteReg(0xD626,0x02);
	LCD_WriteReg(0xD627,0xCF);
	LCD_WriteReg(0xD628,0x02);
	LCD_WriteReg(0xD629,0xDE);
	LCD_WriteReg(0xD62A,0x02);
	LCD_WriteReg(0xD62B,0xF2);
	LCD_WriteReg(0xD62C,0x02);
	LCD_WriteReg(0xD62D,0xFE);
	LCD_WriteReg(0xD62E,0x03);
	LCD_WriteReg(0xD62F,0x10);
	LCD_WriteReg(0xD630,0x03);
	LCD_WriteReg(0xD631,0x33);
	LCD_WriteReg(0xD632,0x03);
	LCD_WriteReg(0xD633,0x6D);
	//LV2 Page 0 enable
	LCD_WriteReg(0xF000,0x55);
	LCD_WriteReg(0xF001,0xAA);
	LCD_WriteReg(0xF002,0x52);
	LCD_WriteReg(0xF003,0x08);
	LCD_WriteReg(0xF004,0x00);
	//Display control
	LCD_WriteReg(0xB100, 0xCC);
	LCD_WriteReg(0xB101, 0x00);
	//Source hold time
	LCD_WriteReg(0xB600,0x05);
	//Gate EQ control
	LCD_WriteReg(0xB700,0x70);
	LCD_WriteReg(0xB701,0x70);
	//Source EQ control (Mode 2)
	LCD_WriteReg(0xB800,0x01);
	LCD_WriteReg(0xB801,0x03);
	LCD_WriteReg(0xB802,0x03);
	LCD_WriteReg(0xB803,0x03);
	//Inversion mode (2-dot)
	LCD_WriteReg(0xBC00,0x02);
	LCD_WriteReg(0xBC01,0x00);
	LCD_WriteReg(0xBC02,0x00);
	//Timing control 4H w/ 4-delay
	LCD_WriteReg(0xC900,0xD0);
	LCD_WriteReg(0xC901,0x02);
	LCD_WriteReg(0xC902,0x50);
	LCD_WriteReg(0xC903,0x50);
	LCD_WriteReg(0xC904,0x50);
	LCD_WriteReg(0x3500,0x00);
	LCD_WriteReg(0x3A00,0x55);  //16-bit/pixel
	LCD_Write_Cmd(0x1100);
	delay_us(120);
	LCD_Write_Cmd(0x2900);
#endif

}


/**
 * @brief ��һ������(��������ɫ)
 * 
 * @param xStart 
 * @param yStart 
 * @param xEnd 
 * @param yEnd 
 * @param color 
 */
void LCD_Draw_Rect(u16 xStart, u16 yStart, u16 xEnd, u16 yEnd, u16 color)
{
	u32 i = 0;
	LCD_Write_Cmd(lcddev.setxcmd);LCD_Write_Data(xStart>>8); 
	LCD_Write_Cmd(lcddev.setxcmd+1);LCD_Write_Data(xStart&0xFF); 
	LCD_Write_Cmd(lcddev.setxcmd+2);LCD_Write_Data(xEnd>>8); 
	LCD_Write_Cmd(lcddev.setxcmd+3);LCD_Write_Data(xEnd&0XFF); 
	LCD_Write_Cmd(lcddev.setycmd);LCD_Write_Data(yStart>>8); 
	LCD_Write_Cmd(lcddev.setycmd+1);LCD_Write_Data(yStart%0xFF); 
	LCD_Write_Cmd(lcddev.setycmd+2);LCD_Write_Data(yEnd>>8); 
	LCD_Write_Cmd(lcddev.setycmd+3);LCD_Write_Data(yEnd&0XFF);

	LCD_Write_Cmd(lcddev.wramcmd);
	for(i=0; i<(xEnd-xStart+1)*(yEnd-yStart+1);i++)
		LCD_Write_Data(color);
}

/**
 * @brief ��ʼдGRAM
 * 
 */
void LCD_WriteRAM_Prepare(void)
{
	LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief ���ù��λ��
 * 
 * @param Xpos: ������ 
 * @param Ypos: ������ 
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_Write_Cmd(lcddev.setxcmd);LCD_Write_Data(Xpos>>8); 		
	LCD_Write_Cmd(lcddev.setxcmd+1);LCD_Write_Data(Xpos&0XFF);			 
	LCD_Write_Cmd(lcddev.setycmd);LCD_Write_Data(Ypos>>8);  		
	LCD_Write_Cmd(lcddev.setycmd+1);LCD_Write_Data(Ypos&0XFF);
}

/**
 * @brief ��������
 * 
 * @param color: Ҫ���������ɫ 
 */
void LCD_Clear(u16 color)
{
	uint32_t index = 0;
	uint32_t totalPoint = lcddev.width;
	totalPoint *= lcddev.height;
	LCD_SetCursor(0x00, 0x0000);	//���ù��λ��

	LCD_WriteRAM_Prepare();
	for(index=0; index < totalPoint; index++)
	{
		LCD->LCD_RAM = color;
	}


}

/**
 * @brief ��ʼ��LCD
 * 
 */
void NT35510_Init(void)
{
	vu32 i=0;

    NT35510_GPIO_Config();
    NT35510_FSMC_Config();

 	delay_ms(50); // delay 50 ms 
 	LCD_WriteReg(0x0000,0x0001);
	delay_ms(50); // delay 50 ms 
  	lcddev.id = LCD_ReadReg(0x0000);   
  	lcddev.id = 0x5510;	//LCD_ReadReg��ȡ�����⣬����ֱ�Ӹ�ֵ   

	NT35510_REG_Config(); // LCD��ʼ��(���̸��ĳ�ʼ��ָ��)
	LCD_Display_Dir(LCD_SCAN_MODE);		//����ɨ�跽��,Ĭ��Ϊ����

	BackLed_Control(ENABLE);	//��������
	
	LCD_Clear(WHITE);
}


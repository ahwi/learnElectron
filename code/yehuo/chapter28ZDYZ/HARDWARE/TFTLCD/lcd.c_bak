#include "lcd.h"
#include "usart.h"
#include "delay.h"

#if 1
#define YEHUO 1	//使用野火接口
#else
#define ZDYZ 1	//使用正点原子接口
#endif

//根据液晶扫描方向而变化的XY像素宽度
//调用NT35510_GramScan函数设置方向时会自动更改
uint16_t LCD_X_LENGTH = NT35510_MORE_PIXEL;
uint16_t LCD_Y_LENGTH = NT35510_LESS_PIXEL;

//液晶屏扫描模式，本变量主要用于方便选择触摸屏的计算参数
//参数可选值为0-7
//默认为0：从左到右、从上到下进行扫描
//调用NT35510_GramScan函数设置方向时会自动更改
//LCD刚初始化完成时会使用本默认值
uint8_t LCD_SCAN_MODE = 0;
uint16_t lcd_id = 0;

// 管理LCD重要参数
// 默认为竖屏
_lcd_dev lcddev; 

// static sFONT *LCD_Currentfonts = &Font16x32;    //英文字体
// static uint16_t CurrentTextColor = WHITE;   //前景色
// static uint16_t CurrentBackColor = WHITE;   //背景色

//static void Delay(__IO uint32_t nCount);
__inline void LCD_Write_Cmd(uint16_t usCmd);
__inline void LCD_Write_Data(uint16_t usData);
__inline uint16_t LCD_Read_Data(void);
__inline void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
__inline uint16_t LCD_ReadReg(uint16_t LCD_Reg);


#ifdef YEHUO  //野火风格的接口

/**
 * @brief 向LCD控制器写入命令
 * @param usCmd: 要写入的命令（表寄存器）
 * @return __inline 
 */
__inline void LCD_Write_Cmd(uint16_t usCmd)
{
    *(__IO uint16_t *) ( FSMC_Addr_NT35510_CMD ) = usCmd;
}

/**
 * @brief 向LCD控制器写入数据 
 * @param usData : 要写入的数据
 * @retval 无
 */
__inline void LCD_Write_Data(uint16_t usData)
{
    *(__IO uint16_t *) ( FSMC_Addr_NT35510_DATA ) = usData;
}

/**
 * @brief 从LCD控制器读取数据 
 * @param 无
 * @retval 读取到的数据
 */
__inline uint16_t LCD_Read_Data(void)
{
    return (* (__IO uint16_t *)(FSMC_Addr_NT35510_DATA));
}

/**
 * @brief 写寄存器 
 * @param LCD_Reg  寄存器地址
 * @param LCD_RegValue 要写入的数据
 * @return 无
 */
__inline void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
	LCD_Write_Cmd(LCD_Reg);
	LCD_Write_Data(LCD_RegValue);
}

/**
 * @brief 读寄存器
 * 
 * @param LCD_Reg: 寄存器地址 
 * @return： 读到的数据
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
 * @brief 向LCD控制器写入命令
 * 
 * @param usCmd: 要写入的命令（表寄存器） 
 */
void LCD_Write_Cmd(vu16 usCmd)
{
	usCmd = usCmd;	//使用-O2优化的时候，必须插入的延时
	LCD->LCD_REG = usCmd;	//写入要写入的寄存器序号
}

/**
 * @brief 向LCD控制器写入数据 
 * 
 * @param data: 要写入的值
 */
void LCD_Write_Data(vu16 usData)
{
	usData = usData;	//使用-O2优化的时候，必须插入的延时
	LCD->LCD_RAM = usData;
}

/**
 * @brief 从LCD控制读取数据
 * 
 * @return: 读到的值 
 */
u16 LCD_Read_Data(void)
{
	vu16 ram;		//防止被优化
	ram = LCD->LCD_RAM;
	return ram;
}

/**
 * @brief 写寄存器
 * 
 * @param LCD_Reg: 寄存器地址 
 * @param LCD_RegValue: 要写入的数据 
 */
void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue)
{
	LCD->LCD_REG = LCD_Reg;			//写入要写的寄存器序号
	LCD->LCD_RAM = LCD_RegValue;	//写入数据
}

/**
 * @brief 读寄存器
 * 
 * @param LCD_Reg: 寄存器地址 
 * @return: 读到的数据 
 */
u16 LCD_ReadReg(u16 LCD_Reg)
{
	LCD_Write_Cmd(LCD_Reg);	//写入要读的寄存器序号
	delay_us(5);
	return LCD_Read_Data();
}

#endif



#ifdef YEHUO	//野火风格的接口
/**
 * @brief LCD FSMC 模式配置
 * 		配置为模式B，且读写时序复用
 * @param 无
 * @retval 无
 */
static void NT35510_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming;

    // 使能FSMC时钟
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    // 地址建立时间（ADDSET）为16个HCLK (16 * 1/168)M=96ns
    // readWriteTiming.FSMC_AddressSetupTime = 0xF;   //地址建立时间
    readWriteTiming.FSMC_AddressSetupTime = 0x04;   //地址建立时间
    // 数据保持时间（DATASET） + 1个HCLK = 5、168M=30ns
    // readWriteTiming.FSMC_DataSetupTime = 60;   //数据建立时间 60个HCK = 6*60=360ns
    readWriteTiming.FSMC_DataSetupTime = 0x04;   //数据建立时间 60个HCK = 6*60=360ns
    // 选择控制的模式
    // 模式B，异步NOR FLASH模式，与NT35510的8080时序匹配
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_B;

    // 以下配置与模式B无关
    // 地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //地址保持时间
    // 设置总线转换周期，仅用于复用模式的NOR操作
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // 设置时钟分频，仅用于同步类型的存储器
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // 数据保持时间，仅用于同步型的NOR
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

    //使能FSMC_Bank1_NORSRAM3
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE);

}

/**
 * @brief LCD背光LED控制
 * @param enumState : 决定是否使能背光LED 
 *      该参数为以下值之一：
 *      @arg ENABLE: 使能背光LED
 *      @arg DISABLE: 禁用背光LED
 * @retval 无
 */
void BackLed_Control(FunctionalState enumState)
{
    if(enumState)
        GPIO_SetBits(NT35510_BK_PORT, NT35510_BK_PIN);
    else
        GPIO_ResetBits(NT35510_BK_PORT, NT35510_BK_PIN);
}

/**
 * @brief 设置NT35510的GRAM扫描方向 
 * 
 * @param dir: 选择GRAM的扫描方向
 * 		0代表从左到右，从上到下
 * 		其他方向参考LCD手册的0x3600指令，只要关注MY MX MV三个字段的值
 * 		注：正点原子屏幕的扫描方向值和野火屏幕的扫描方向值不一样
 */
void LCD_Display_Dir(uint8_t ucOption)
{
    //参数检查，只可输入0-7
    if(ucOption > 7)
        return;
    
    //根据模式更新LCD_SCAN_MODE的值，主要用于触摸屏选择计算参数
    if(ucOption%2 == 0)
    {
        //0 2 4 6模式下x方向像素宽度为480，Y方向为854
        LCD_X_LENGTH = NT35510_LESS_PIXEL;
        LCD_Y_LENGTH = NT35510_MORE_PIXEL;
    }
    else
    {
        //1 2 5 7模式下x方向像素宽度为854，Y方向为480
        LCD_X_LENGTH = NT35510_MORE_PIXEL;
        LCD_Y_LENGTH = NT35510_LESS_PIXEL;
    }

	lcddev.wramcmd = 0x2C00;
	lcddev.setxcmd = 0x2A00;
	lcddev.setycmd = 0x2B00;
	lcddev.width = 480;
	lcddev.height = 800;
    
    //0x36命令参数的高3位可用于设置GRAM扫描方向
    LCD_Write_Cmd(0x36);
    LCD_Write_Data(0x00 | (ucOption<<5)); //根据ucOption的值设置LCD参数，共0-7种模式

    LCD_Write_Cmd(CMD_SetCoordinateX);
    LCD_Write_Data(0x00);  /*x 起始坐标高8位 */
    LCD_Write_Cmd(CMD_SetCoordinateX+1);
    LCD_Write_Data(0x00);  /*x 起始坐标低8位 */
    LCD_Write_Cmd(CMD_SetCoordinateX+2);
    LCD_Write_Data(((LCD_X_LENGTH-1) >> 8) &0xFF);  /*x 结束坐标高8位 */
    LCD_Write_Cmd(CMD_SetCoordinateX+3);
    LCD_Write_Data((LCD_X_LENGTH-1) & 0xFF);  /*x 结束坐标低8位 */

    LCD_Write_Cmd(CMD_SetCoordinateY);
    LCD_Write_Data(0x00);  /*y 起始坐标高8位 */
    LCD_Write_Cmd(CMD_SetCoordinateY+1);
    LCD_Write_Data(0x00);  /*y 起始坐标低8位 */
    LCD_Write_Cmd(CMD_SetCoordinateY+2);
    LCD_Write_Data(((LCD_Y_LENGTH-1) >> 8) &0xFF);  /*y 结束坐标高8位 */
    LCD_Write_Cmd(CMD_SetCoordinateY+3);
    LCD_Write_Data((LCD_Y_LENGTH-1) &0xFF);  /*y 结束坐标低8位 */

}

#endif


#ifdef ZDYZ	//正点原子风格的代码
/**
 * @brief LCD FSMC 模式配置
 * 		配置为模式A，且读写时序分开
 * @param 无
 * @retval 无
 */
static void NT35510_FSMC_Config(void)
{
    FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef readWriteTiming;
    FSMC_NORSRAMTimingInitTypeDef writeTiming;

    // 使能FSMC时钟
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC, ENABLE);

    // 地址建立时间（ADDSET）为16个HCLK (16 * 1/168)M=96ns
    readWriteTiming.FSMC_AddressSetupTime = 0xF;   //地址建立时间
    // 数据保持时间（DATASET） + 1个HCLK = 5、168M=30ns
    readWriteTiming.FSMC_DataSetupTime = 60;   //数据建立时间 60个HCK = 6*60=360ns
    // 选择控制的模式
    // 模式B，异步NOR FLASH模式，与NT35510的8080时序匹配
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    // 以下配置与模式A无关
    // 地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //地址保持时间
    // 设置总线转换周期，仅用于复用模式的NOR操作
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // 设置时钟分频，仅用于同步类型的存储器
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // 数据保持时间，仅用于同步型的NOR
    readWriteTiming.FSMC_DataLatency = 0x00;

    // 地址建立时间（ADDSET）为16个HCLK (9 * 1/168)M=54ns
    readWriteTiming.FSMC_AddressSetupTime = 9;   //地址建立时间
    // 数据保持时间（DATASET） + 1个HCLK = 5、168M=30ns
    readWriteTiming.FSMC_DataSetupTime = 8;   //数据建立时间 9个HCK = 6*9=54ns
    // 选择控制的模式
    // 模式B，异步NOR FLASH模式，与NT35510的8080时序匹配
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;

    // 以下配置与模式A无关
    // 地址保持时间（ADDHLD）模式A未用到
    readWriteTiming.FSMC_AddressHoldTime = 0x00;    //地址保持时间
    // 设置总线转换周期，仅用于复用模式的NOR操作
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00; 
    // 设置时钟分频，仅用于同步类型的存储器
    readWriteTiming.FSMC_CLKDivision = 0x00;
    // 数据保持时间，仅用于同步型的NOR
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

    //使能FSMC_Bank1_NORSRAM3
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAMx, ENABLE);

}

/**
 * @brief LCD背光LED控制
 * @param enumState : 决定是否使能背光LED 
 *      该参数为以下值之一：
 *      @arg ENABLE: 使能背光LED
 *      @arg DISABLE: 禁用背光LED
 * @retval 无
 */
void BackLed_Control(FunctionalState enumState)
{
    if(enumState)
		LCD_LED=1;				//点亮背光
    else
		LCD_LED=0;				//关闭背光
}

void LCD_Scan_Dir(u8 dir)
{
	u16 regval=0;
	u16 dirreg=0;
	u16 temp;  
	switch(dir)
	{
		case L2R_U2D://从左到右,从上到下
			regval|=(0<<7)|(0<<6)|(0<<5); 
			break;
		case L2R_D2U://从左到右,从下到上
			regval|=(1<<7)|(0<<6)|(0<<5); 
			break;
		case R2L_U2D://从右到左,从上到下
			regval|=(0<<7)|(1<<6)|(0<<5); 
			break;
		case R2L_D2U://从右到左,从下到上
			regval|=(1<<7)|(1<<6)|(0<<5); 
			break;	 
		case U2D_L2R://从上到下,从左到右
			regval|=(0<<7)|(0<<6)|(1<<5); 
			break;
		case U2D_R2L://从上到下,从右到左
			regval|=(0<<7)|(1<<6)|(1<<5); 
			break;
		case D2U_L2R://从下到上,从左到右
			regval|=(1<<7)|(0<<6)|(1<<5); 
			break;
		case D2U_R2L://从下到上,从右到左
			regval|=(1<<7)|(1<<6)|(1<<5); 
			break;	 
	}

	// 设置扫描方向
	dirreg=0X3600;
	LCD_WriteReg(dirreg,regval);

	if(regval&0X20)
	{
		if(lcddev.width<lcddev.height)//交换X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}else  
	{
		if(lcddev.width>lcddev.height)//交换X,Y
		{
			temp=lcddev.width;
			lcddev.width=lcddev.height;
			lcddev.height=temp;
		}
	}  

	// 设置起始坐标和结束坐标
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
 * @brief 设置NT35510的GRAM扫描方向 
 * 
 * @param dir: 选择GRAM的扫描方向
 * 		0代表从左到右，从上到下
 * 		其他方向参考LCD手册的0x3600指令，只要关注MY MX MV三个字段的值
 * 		注：正点原子屏幕的扫描方向值和野火屏幕的扫描方向值不一样
 */
void LCD_Display_Dir(u8 dir)
{
	if(dir==0)			//竖屏
	{
		lcddev.dir=0;	//竖屏
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=480;
		lcddev.height=800;
	}else 				//横屏
	{	  				
		lcddev.dir=1;	//横屏
		lcddev.wramcmd=0X2C00;
		lcddev.setxcmd=0X2A00;
		lcddev.setycmd=0X2B00; 
		lcddev.width=800;
		lcddev.height=480;
	} 
	LCD_Scan_Dir(0);	//默认扫描方向
}	 

#endif

/********************公用代码*******************************/
/**
 * @brief 初始化NT35510的IO引脚
 * @param 无
 * @retval 无
 */
static void NT35510_GPIO_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(
        //控制信号
        NT35510_CS_CLK|NT35510_DC_CLK|NT35510_WR_CLK|
        // NT35510_RD_CLK|NT35510_BK_CLK|NT35510_RST_CLK|
        NT35510_RD_CLK|NT35510_BK_CLK|
        //数据信号线
        NT35510_D0_CLK|NT35510_D1_CLK|NT35510_D2_CLK|
        NT35510_D3_CLK|NT35510_D4_CLK|NT35510_D5_CLK|
        NT35510_D6_CLK|NT35510_D7_CLK|NT35510_D8_CLK|
        NT35510_D9_CLK|NT35510_D10_CLK|NT35510_D11_CLK|
        NT35510_D12_CLK|NT35510_D13_CLK|NT35510_D14_CLK|
        NT35510_D1_CLK, ENABLE);

	// RCC_AHB1PeriphClockCmd(
	// 	RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|
	// 	RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|
	// 	RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,PE,PF,PG时钟  
    
    //配置FSMC相对于的数据线，FSMC-D0~D15
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;		//上拉
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;		//复用输出
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

    /* 配置FSMC相对应的控制线
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

    // 配置LCD复位RST控制管脚
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	// 正点原子的LCD屏复位引脚接了系统复位引脚，因此这边不需要设置
    // GPIO_InitStructure.GPIO_Pin = NT35510_RST_PIN;
    // GPIO_Init(NT35510_RST_PORT, &GPIO_InitStructure);

    // 配置LCD背光控制关键BK
    GPIO_InitStructure.GPIO_Pin = NT35510_BK_PIN;
    GPIO_Init(NT35510_BK_PORT, &GPIO_InitStructure);
}


/**
* @brief NT35510的初始化
*/
void NT35510_REG_Config(void)
{
	//重新配置写时序控制寄存器的时序   	 							    
	FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
	FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
	FSMC_Bank1E->BWTR[6]|=3<<0;		//地址建立时间(ADDSET)为3个HCLK =18ns  	 
	FSMC_Bank1E->BWTR[6]|=2<<8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns

#if 0
	// NT35510读不到首次读不到ID，会进入这个流程
   	if(lcddev.id<0XFF||lcddev.id==0XFFFF||lcddev.id==0X9300)//读到ID不正确,新增lcddev.id==0X9300判断，因为9341在未被复位的情况下会被读成9300
	{	
 		//尝试9341 ID的读取		
		LCD_Write_Cmd(0XD3);				   
		lcddev.id=LCD_RD_DATA();	//dummy read 	
 		lcddev.id=LCD_RD_DATA();	//读到0X00
  		lcddev.id=LCD_RD_DATA();   	//读取93								   
 		lcddev.id<<=8;
		lcddev.id|=LCD_RD_DATA();  	//读取41 	   			   
 		if(lcddev.id!=0X9341)		//非9341,尝试是不是6804
		{	
 			LCD_Write_Cmd(0XBF);				   
			lcddev.id=LCD_RD_DATA(); 	//dummy read 	 
	 		lcddev.id=LCD_RD_DATA();   	//读回0X01			   
	 		lcddev.id=LCD_RD_DATA(); 	//读回0XD0 			  	
	  		lcddev.id=LCD_RD_DATA();	//这里读回0X68 
			lcddev.id<<=8;
	  		lcddev.id|=LCD_RD_DATA();	//这里读回0X04	  
			if(lcddev.id!=0X6804)		//也不是6804,尝试看看是不是NT35310
			{ 
				LCD_Write_Cmd(0XD4);				   
				lcddev.id=LCD_RD_DATA();//dummy read  
				lcddev.id=LCD_RD_DATA();//读回0X01	 
				lcddev.id=LCD_RD_DATA();//读回0X53	
				lcddev.id<<=8;	 
				lcddev.id|=LCD_RD_DATA();	//这里读回0X10	 
				if(lcddev.id!=0X5310)		//也不是NT35310,尝试看看是不是NT35510
				{
					LCD_Write_Cmd(0XDA00);	
					lcddev.id=LCD_RD_DATA();		//读回0X00	 
					LCD_Write_Cmd(0XDB00);	
					lcddev.id=LCD_RD_DATA();		//读回0X80
					lcddev.id<<=8;	
					LCD_Write_Cmd(0XDC00);	
					lcddev.id|=LCD_RD_DATA();		//读回0X00		
					if(lcddev.id==0x8000)lcddev.id=0x5510;//NT35510读回的ID是8000H,为方便区分,我们强制设置为5510
					if(lcddev.id!=0X5510)			//也不是NT5510,尝试看看是不是SSD1963
					{
						LCD_Write_Cmd(0XA1);
						lcddev.id=LCD_RD_DATA();
						lcddev.id=LCD_RD_DATA();	//读回0X57
						lcddev.id<<=8;	 
						lcddev.id|=LCD_RD_DATA();	//读回0X61	
						if(lcddev.id==0X5761)lcddev.id=0X1963;//SSD1963读回的ID是5761H,为方便区分,我们强制设置为1963
					}
				}
			}
 		}  	
	} 
	if(lcddev.id==0X9341||lcddev.id==0X5310||lcddev.id==0X5510||lcddev.id==0X1963)//如果是这几个IC,则设置WR时序为最快
	{
		//重新配置写时序控制寄存器的时序   	 							    
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
		FSMC_Bank1E->BWTR[6]|=3<<0;		//地址建立时间(ADDSET)为3个HCLK =18ns  	 
		FSMC_Bank1E->BWTR[6]|=2<<8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns
	}else if(lcddev.id==0X6804||lcddev.id==0XC505)	//6804/C505速度上不去,得降低
	{
		//重新配置写时序控制寄存器的时序   	 							    
		FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
		FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
		FSMC_Bank1E->BWTR[6]|=10<<0;	//地址建立时间(ADDSET)为10个HCLK =60ns  	 
		FSMC_Bank1E->BWTR[6]|=12<<8; 	//数据保存时间(DATAST)为6ns*13个HCLK=78ns
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
 * @brief 画一个矩形(填满了颜色)
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
 * @brief 开始写GRAM
 * 
 */
void LCD_WriteRAM_Prepare(void)
{
	LCD->LCD_REG = lcddev.wramcmd;
}

/**
 * @brief 设置光标位置
 * 
 * @param Xpos: 横坐标 
 * @param Ypos: 纵坐标 
 */
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	LCD_Write_Cmd(lcddev.setxcmd);LCD_Write_Data(Xpos>>8); 		
	LCD_Write_Cmd(lcddev.setxcmd+1);LCD_Write_Data(Xpos&0XFF);			 
	LCD_Write_Cmd(lcddev.setycmd);LCD_Write_Data(Ypos>>8);  		
	LCD_Write_Cmd(lcddev.setycmd+1);LCD_Write_Data(Ypos&0XFF);
}

/**
 * @brief 清屏函数
 * 
 * @param color: 要清屏的填充色 
 */
void LCD_Clear(u16 color)
{
	uint32_t index = 0;
	uint32_t totalPoint = lcddev.width;
	totalPoint *= lcddev.height;
	LCD_SetCursor(0x00, 0x0000);	//设置光标位置

	LCD_WriteRAM_Prepare();
	for(index=0; index < totalPoint; index++)
	{
		LCD->LCD_RAM = color;
	}


}

/**
 * @brief 初始化LCD
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
  	lcddev.id = 0x5510;	//LCD_ReadReg读取有问题，这里直接赋值   

	NT35510_REG_Config(); // LCD初始化(厂商给的初始化指令)
	LCD_Display_Dir(LCD_SCAN_MODE);		//设置扫描方向,默认为竖屏

	BackLed_Control(ENABLE);	//点亮背光
	
	LCD_Clear(WHITE);
}


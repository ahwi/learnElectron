#include "bsp_sram.h"




void FSMC_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio_initStruct;

    // 初始化时钟
    RCC_AHB1PeriphClockCmd(
        // 地址信号线
        FSMC_A0_GPIO_CLCK|FSMC_A1_GPIO_CLCK|FSMC_A2_GPIO_CLCK|FSMC_A3_GPIO_CLCK|FSMC_A4_GPIO_CLCK|
        FSMC_A5_GPIO_CLCK|FSMC_A6_GPIO_CLCK|FSMC_A7_GPIO_CLCK|FSMC_A8_GPIO_CLCK|FSMC_A9_GPIO_CLCK|
        FSMC_A10_GPIO_CLCK|FSMC_A11_GPIO_CLCK|FSMC_A12_GPIO_CLCK|FSMC_A13_GPIO_CLCK|FSMC_A14_GPIO_CLCK|
        FSMC_A15_GPIO_CLCK|FSMC_A16_GPIO_CLCK|FSMC_A17_GPIO_CLCK|FSMC_A18_GPIO_CLCK|
        // 数据信号线
        FSMC_D0_GPIO_CLCK|FSMC_D1_GPIO_CLCK|FSMC_D2_GPIO_CLCK|FSMC_D3_GPIO_CLCK|FSMC_D4_GPIO_CLCK|
        FSMC_D5_GPIO_CLCK|FSMC_D6_GPIO_CLCK|FSMC_D7_GPIO_CLCK|FSMC_D8_GPIO_CLCK|FSMC_D9_GPIO_CLCK|
        FSMC_D10_GPIO_CLCK|FSMC_D11_GPIO_CLCK|FSMC_D12_GPIO_CLCK|FSMC_D13_GPIO_CLCK|FSMC_D14_GPIO_CLCK|
        // 控制信号线
        FSMC_CS_GPIO_CLCK|FSMC_WR_GPIO_CLCK|FSMC_RD_GPIO_CLCK|FSMC_UDQM_GPIO_CLCK|FSMC_LDQM_GPIO_CLCK,
        ENABLE
    );

    /* 初始化 FSMC_A0 ~ A18 行地址*/
    gpio_initStruct.GPIO_Mode = GPIO_Mode_AF;
    gpio_initStruct.GPIO_OType = GPIO_OType_PP;
    // gpio_initStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_initStruct.GPIO_PuPd = GPIO_PuPd_UP;
    gpio_initStruct.GPIO_Speed = GPIO_High_Speed;

    gpio_initStruct.GPIO_Pin = FSMC_A0_GPIO_PIN;
    GPIO_Init(FSMC_A0_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A0_GPIO_PORT, FSMC_A0_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A1_GPIO_PIN;
    GPIO_Init(FSMC_A1_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A1_GPIO_PORT, FSMC_A1_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A2_GPIO_PIN;
    GPIO_Init(FSMC_A2_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A2_GPIO_PORT, FSMC_A2_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A3_GPIO_PIN;
    GPIO_Init(FSMC_A3_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A3_GPIO_PORT, FSMC_A3_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A4_GPIO_PIN;
    GPIO_Init(FSMC_A4_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A4_GPIO_PORT, FSMC_A4_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A5_GPIO_PIN;
    GPIO_Init(FSMC_A5_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A5_GPIO_PORT, FSMC_A5_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A6_GPIO_PIN;
    GPIO_Init(FSMC_A6_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A6_GPIO_PORT, FSMC_A6_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A7_GPIO_PIN;
    GPIO_Init(FSMC_A7_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A7_GPIO_PORT, FSMC_A7_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A8_GPIO_PIN;
    GPIO_Init(FSMC_A8_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A8_GPIO_PORT, FSMC_A8_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A9_GPIO_PIN;
    GPIO_Init(FSMC_A9_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A9_GPIO_PORT, FSMC_A9_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A10_GPIO_PIN;
    GPIO_Init(FSMC_A10_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A10_GPIO_PORT, FSMC_A10_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A11_GPIO_PIN;
    GPIO_Init(FSMC_A11_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A11_GPIO_PORT, FSMC_A11_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A12_GPIO_PIN;
    GPIO_Init(FSMC_A12_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A12_GPIO_PORT, FSMC_A12_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A13_GPIO_PIN;
    GPIO_Init(FSMC_A13_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A13_GPIO_PORT, FSMC_A13_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A14_GPIO_PIN;
    GPIO_Init(FSMC_A14_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A14_GPIO_PORT, FSMC_A14_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A15_GPIO_PIN;
    GPIO_Init(FSMC_A15_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A15_GPIO_PORT, FSMC_A15_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A16_GPIO_PIN;
    GPIO_Init(FSMC_A16_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A16_GPIO_PORT, FSMC_A16_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A17_GPIO_PIN;
    GPIO_Init(FSMC_A17_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A17_GPIO_PORT, FSMC_A17_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_A18_GPIO_PIN;
    GPIO_Init(FSMC_A18_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_A18_GPIO_PORT, FSMC_A18_GPIO_PinSource, GPIO_AF_FSMC);

    /* FSMC_D0 ~ FSMC_D15 数据线 */
    gpio_initStruct.GPIO_Pin = FSMC_D0_GPIO_PIN;
    GPIO_Init(FSMC_D0_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D0_GPIO_PORT, FSMC_D0_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D1_GPIO_PIN;
    GPIO_Init(FSMC_D1_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D1_GPIO_PORT, FSMC_D1_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D2_GPIO_PIN;
    GPIO_Init(FSMC_D2_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D2_GPIO_PORT, FSMC_D2_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D3_GPIO_PIN;
    GPIO_Init(FSMC_D3_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D3_GPIO_PORT, FSMC_D3_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D4_GPIO_PIN;
    GPIO_Init(FSMC_D4_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D4_GPIO_PORT, FSMC_D4_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D5_GPIO_PIN;
    GPIO_Init(FSMC_D5_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D5_GPIO_PORT, FSMC_D5_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D6_GPIO_PIN;
    GPIO_Init(FSMC_D6_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D6_GPIO_PORT, FSMC_D6_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D7_GPIO_PIN;
    GPIO_Init(FSMC_D7_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D7_GPIO_PORT, FSMC_D7_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D8_GPIO_PIN;
    GPIO_Init(FSMC_D8_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D8_GPIO_PORT, FSMC_D8_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D9_GPIO_PIN;
    GPIO_Init(FSMC_D9_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D9_GPIO_PORT, FSMC_D9_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D10_GPIO_PIN;
    GPIO_Init(FSMC_D10_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D10_GPIO_PORT, FSMC_D10_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D11_GPIO_PIN;
    GPIO_Init(FSMC_D11_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D11_GPIO_PORT, FSMC_D11_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D12_GPIO_PIN;
    GPIO_Init(FSMC_D12_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D12_GPIO_PORT, FSMC_D12_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D13_GPIO_PIN;
    GPIO_Init(FSMC_D13_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D13_GPIO_PORT, FSMC_D13_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D14_GPIO_PIN;
    GPIO_Init(FSMC_D14_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D14_GPIO_PORT, FSMC_D14_GPIO_PinSource, GPIO_AF_FSMC);

    gpio_initStruct.GPIO_Pin = FSMC_D15_GPIO_PIN;
    GPIO_Init(FSMC_D15_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_D15_GPIO_PORT, FSMC_D15_GPIO_PinSource, GPIO_AF_FSMC);
    
    // SRAM 片选引脚
    gpio_initStruct.GPIO_Pin = FSMC_CS_GPIO_PIN;
    GPIO_Init(FSMC_CS_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_CS_GPIO_PORT, FSMC_CS_GPIO_PinSource, GPIO_AF_FSMC);

    // SRAM 写使能
    gpio_initStruct.GPIO_Pin = FSMC_WR_GPIO_PIN;
    GPIO_Init(FSMC_WR_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_WR_GPIO_PORT, FSMC_WR_GPIO_PinSource, GPIO_AF_FSMC);

    // SRAM 输出使能
    gpio_initStruct.GPIO_Pin = FSMC_RD_GPIO_PIN;
    GPIO_Init(FSMC_RD_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_RD_GPIO_PORT, FSMC_RD_GPIO_PinSource, GPIO_AF_FSMC);

    // UB 数据掩码信号
    gpio_initStruct.GPIO_Pin = FSMC_UDQM_GPIO_PIN;
    GPIO_Init(FSMC_UDQM_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_UDQM_GPIO_PORT, FSMC_UDQM_GPIO_PinSource, GPIO_AF_FSMC);

    // LB 数据掩码信号
    gpio_initStruct.GPIO_Pin = FSMC_LDQM_GPIO_PIN;
    GPIO_Init(FSMC_LDQM_GPIO_PORT, &gpio_initStruct);
    GPIO_PinAFConfig(FSMC_LDQM_GPIO_PORT, FSMC_LDQM_GPIO_PinSource, GPIO_AF_FSMC);
}


void FSMC_Init(void)
{
    FSMC_NORSRAMInitTypeDef fsmc_norsramStruct;
    FSMC_NORSRAMTimingInitTypeDef fsmc_norsramTimingStruct;

    // 初始化GPIO
    FSMC_GPIO_Init();

	/*使能FSMC外设时钟*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

    // 初始化FSMC
    fsmc_norsramTimingStruct.FSMC_AddressSetupTime = 1;
    fsmc_norsramTimingStruct.FSMC_AddressHoldTime = 10;
    fsmc_norsramTimingStruct.FSMC_DataSetupTime = 5;
    fsmc_norsramTimingStruct.FSMC_BusTurnAroundDuration = 0;
    fsmc_norsramTimingStruct.FSMC_CLKDivision = 0;
    fsmc_norsramTimingStruct.FSMC_DataLatency = 0;
    fsmc_norsramTimingStruct.FSMC_AccessMode = FSMC_AccessMode_A;

    fsmc_norsramStruct.FSMC_Bank = FSMC_Bank1_NORSRAM3;
    fsmc_norsramStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
    fsmc_norsramStruct.FSMC_MemoryType = FSMC_MemoryType_SRAM;
    fsmc_norsramStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
    fsmc_norsramStruct.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
    fsmc_norsramStruct.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
    fsmc_norsramStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
    fsmc_norsramStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;
    fsmc_norsramStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
    fsmc_norsramStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
    // 待确认
    fsmc_norsramStruct.FSMC_WaitSignal = FSMC_AsynchronousWait_Disable;
    fsmc_norsramStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
    fsmc_norsramStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
    fsmc_norsramStruct.FSMC_ReadWriteTimingStruct = &fsmc_norsramTimingStruct;
    fsmc_norsramStruct.FSMC_WriteTimingStruct = &fsmc_norsramTimingStruct;

    FSMC_NORSRAMInit(&fsmc_norsramStruct);
	
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM3, ENABLE);
} 


#if 0
/**
  * @brief  初始化FSMC外设
  * @param  None. 
  * @retval None.
  */
void FSMC_SRAM_Init(void)
{	
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
	FSMC_NORSRAMTimingInitTypeDef  readWriteTiming;

	/*初始化SRAM相关的GPIO*/
	SRAM_GPIO_Config();
		
	/*使能FSMC外设时钟*/
	RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);

	//地址建立时间（ADDSET）为1个HCLK,1/168M = 6ns
	readWriteTiming.FSMC_AddressSetupTime = 0x00;	

	//地址保持时间（ADDHLD）模式A未用到
	readWriteTiming.FSMC_AddressHoldTime = 0x00;	 

	//数据保持时间（DATAST）+ 1个HCLK = 9/168M=54ns(对EM的SRAM芯片)	
	readWriteTiming.FSMC_DataSetupTime = 0x08;		  
	
	//设置总线转换周期，仅用于复用模式的NOR操作
	readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
	
	//设置时钟分频，仅用于同步类型的存储器
	readWriteTiming.FSMC_CLKDivision = 0x00;	

	//数据保持时间，仅用于同步型的NOR
	readWriteTiming.FSMC_DataLatency = 0x00;		
	
	//选择匹配SRAM的模式
	readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 
    

	// 选择FSMC映射的存储区域： Bank1 sram4
	FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;
	
	//设置地址总线与数据总线是否复用，仅用于NOR
	FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; 
	
	//设置要控制的存储器类型：SRAM类型
	FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;   
	
	//存储器数据宽度：16位
	FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b; 
	
	//设置是否使用突发访问模式，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;
	
	//设置是否使能等待信号，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	
	//设置等待信号的有效极性，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	
	//设置是否支持把非对齐的突发操作，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable; 
	
	//设置等待信号插入的时间，仅用于同步类型的存储器
	FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
	
	//存储器写使能 
	FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
	
	//不使用等待信号
	FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;  		
	
	// 不使用扩展模式，读写使用相同的时序
	FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable; 
	
	//突发写操作
	FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;  
	
	//读写时序配置
	FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming;
	
	//读写同样时序，使用扩展模式时这个配置才有效
	FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &readWriteTiming; 

	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK										  
											
}
#endif
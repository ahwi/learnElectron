#include "bsp_sram.h"




void FSMC_GPIO_Init(void)
{
    GPIO_InitTypeDef gpio_initStruct;

    // 初始化时钟
    RCC_AHB1PeriphClockCmd(
        FSMC_A0_GPIO_CLCK|FSMC_A1_GPIO_CLCK|FSMC_A2_GPIO_CLCK|FSMC_A3_GPIO_CLCK|FSMC_A4_GPIO_CLCK|
        FSMC_A5_GPIO_CLCK|FSMC_A6_GPIO_CLCK|FSMC_A7_GPIO_CLCK|FSMC_A8_GPIO_CLCK|FSMC_A9_GPIO_CLCK|
        FSMC_A10_GPIO_CLCK|FSMC_A11_GPIO_CLCK|FSMC_A12_GPIO_CLCK|FSMC_A13_GPIO_CLCK|FSMC_A14_GPIO_CLCK|
        FSMC_A15_GPIO_CLCK|FSMC_A16_GPIO_CLCK|FSMC_A17_GPIO_CLCK|FSMC_A18_GPIO_CLCK|
        FSMC_D0_GPIO_CLCK|FSMC_D1_GPIO_CLCK|FSMC_D2_GPIO_CLCK|FSMC_D3_GPIO_CLCK|FSMC_D4_GPIO_CLCK|
        FSMC_D5_GPIO_CLCK|FSMC_D6_GPIO_CLCK|FSMC_D7_GPIO_CLCK|FSMC_D8_GPIO_CLCK|FSMC_D9_GPIO_CLCK|
        FSMC_D10_GPIO_CLCK|FSMC_D11_GPIO_CLCK|FSMC_D12_GPIO_CLCK|FSMC_D13_GPIO_CLCK|FSMC_D14_GPIO_CLCK|
        FSMC_CS_GPIO_CLCK|FSMC_WR_GPIO_CLCK|FSMC_RD_GPIO_CLCK|FSMC_UDQM_GPIO_CLCK|FSMC_LDQM_GPIO_CLCK,
        ENABLE
    );

    /* 初始化 FSMC_A0 ~ A18 行地址*/
    gpio_initStruct.GPIO_Pin = FSMC_A0_GPIO_PIN;
    gpio_initStruct.GPIO_Mode = GPIO_Mode_AF;
    gpio_initStruct.GPIO_OType = GPIO_OType_PP;
    gpio_initStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_initStruct.GPIO_Speed = GPIO_High_Speed;
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
}

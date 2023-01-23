#include "bsp_clkconfig.h"

/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置PLLCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSE设置时钟
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSE_SetSysClock(25, 336, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSE_SetSysClock(25, 432, 2, 9);
 * 
 * 注：野火的外部晶振为25M 正点原子为8M
 */
void user_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)
{
    __IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  
    /* 使能 HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 
    /* 等待 HSE 启动稳定 */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    // HSE 启动成功
    if (HSEStatus == (uint32_t)0x01)
    {
        // 调压器电压输出级别配置为1，以便在器件为最大频率
        // 工作时使性能和功耗实现平衡
        RCC->APB1ENR |= RCC_APB1ENR_PWREN;
        PWR->CR |= PWR_CR_VOS;

        // 设置 AHB/APB2/APB1 的分频因子
        /* HCLK = SYSCLK / 1*/
        RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

        /* PCLK2 = HCLK / 2*/
        RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;

        /* PCLK1 = HCLK / 4*/
        RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;

        // 配置主PLL的时钟来源，设置M,N,P,Q
        RCC->PLLCFGR = m | (n << 6) | (((p >> 1) -1) << 16) |
                       (RCC_PLLCFGR_PLLSRC_HSE) | (q << 24);


        /* 使能主 PLL */
        RCC->CR |= RCC_CR_PLLON;

        /* 等待 PLL 稳定 */
        while((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
    
        // 配置FLASH预取指，指令缓存，数据缓存和等待状态
        FLASH->ACR = FLASH_ACR_PRFTEN | FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_5WS;

        // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
        RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
        RCC->CFGR |= RCC_CFGR_SW_PLL;

        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL);
        {
        }
    }
    else
    { 
          // HSE启动出错处理
    }
}


/*
 * 使用HSE时，设置系统时钟的步骤
 * 1、开启HSE ，并等待 HSE 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置PLLCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSE设置时钟
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSE_SetSysClock(25, 336, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSE_SetSysClock(25, 432, 2, 9);
 * 
 * 注：野火的外部晶振为25M 正点原子为8M
 */
void HSE_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)
{
    __IO uint32_t HSEStartUpStatus = 0;
    
    // 使能HSE，开启外部晶振，野火407使用HSE=25M，正点原子HSE=8M
    RCC_HSEConfig(RCC_HSE_ON);

    // 等待HSE启动稳定
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        // 调压器电压输出级别配置为1，以便在器件为最大频率
        // 工作时使性能和功耗实现平衡
        RCC->APB1ENR |= RCC_APB1LPENR_PWRLPEN;
        PWR->CR |= PWR_CR_VOS;

        // HCLK = SYSCLK / 1
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        // PCLK2 = HCLK / 2
        RCC_PCLK2Config(RCC_HCLK_Div2);

        // RCLK1 = HCLK / 4
        RCC_PCLK1Config(RCC_HCLK_Div4);

        // 如果要超频就设置这里的相关参数
        // 设置PLL来源时钟，设置VCO分频因子m，设置VCO倍频因子n，
        // 设置系统时钟分频因子p，设置OTG FS,SDIO,RNG分频因子q
        RCC_PLLConfig(RCC_PLLSource_HSE, m, n, p, q);

        // 使能PLL
        RCC_PLLCmd(ENABLE);

        // 等待PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        // 配置FLASH预取指，指令缓存，数据缓存和等待状态
        FLASH->ACR = FLASH_ACR_PRFTEN 
                | FLASH_ACR_ICEN 
                | FLASH_ACR_DCEN 
                | FLASH_ACR_LATENCY_5WS;

        // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
        }

    }
    else
    {   // HSE启动出错处理
        while (1);
    }

}


/*
 * 使用HSI时，设置系统时钟的步骤
 * 1、开启HSI ，并等待 HSI 稳定
 * 2、设置 AHB、APB2、APB1的预分频因子
 * 3、设置PLL的时钟来源
 *    设置VCO输入时钟 分频因子        m
 *    设置VCO输出时钟 倍频因子        n
 *    设置PLLCLK时钟分频因子          p
 *    设置OTG FS,SDIO,RNG时钟分频因子 q
 * 4、开启PLL，并等待PLL稳定
 * 5、把PLLCK切换为系统时钟SYSCLK
 * 6、读取时钟切换状态位，确保PLLCLK被选为系统时钟
 */

/*
 * m: VCO输入时钟 分频因子，取值2~63
 * n: VCO输出时钟 倍频因子，取值192~432
 * p: PLLCLK时钟分频因子  ，取值2，4，6，8
 * q: OTG FS,SDIO,RNG时钟分频因子，取值4~15
 * 函数调用举例，使用HSE设置时钟
 * SYSCLK=HCLK=168M,PCLK2=HCLK/2=84M,PCLK1=HCLK/4=42M
 * HSE_SetSysClock(25, 336, 2, 7);
 * HSE作为时钟来源，经过PLL倍频作为系统时钟，这是通常的做法
 
 * 系统时钟超频到216M爽一下
 * HSI_SetSysClock(25, 432, 2, 9);
 * 
 * 注：野火的外部晶振为25M 正点原子为8M
 */
void HSI_SetSysClock(uint32_t m, uint32_t n, uint32_t p, uint32_t q)
{
    __IO uint32_t HSIStartUpStatus = 0;
  __IO uint32_t StartUpCounter = 0, HSIStatus = 0;

    // 把RCC外设初始化成复位状态
    // RCC_DeInit();
    
    // 使能HSI，开启外部晶振，野火407使用HSE=25M，正点原子HSE=8M
    RCC_HSICmd(ENABLE);

    // 等待HSI启动稳定
    // HSIStartUpStatus = RCC->CR & RCC_CR_HSIRDY;
    do
    {
        HSIStatus = RCC->CR & RCC_CR_HSIRDY;
        StartUpCounter++;
    } while((HSIStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if(HSIStatus == RCC_CR_HSIRDY)
    {
        // 调压器电压输出级别配置为1，以便在器件为最大频率
        // 工作时使性能和功耗实现平衡
        RCC->APB1ENR |= RCC_APB1LPENR_PWRLPEN;
        PWR->CR |= PWR_CR_VOS;

        // HCLK = SYSCLK / 1
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        // PCLK2 = HCLK / 2
        RCC_PCLK2Config(RCC_HCLK_Div2);

        // RCLK1 = HCLK / 4
        RCC_PCLK1Config(RCC_HCLK_Div4);

        // 如果要超频就设置这里的相关参数
        // 设置PLL来源时钟，设置VCO分频因子m，设置VCO倍频因子n，
        // 设置系统时钟分频因子p，设置OTG FS,SDIO,RNG分频因子q
        RCC_PLLConfig(RCC_PLLSource_HSI, m, n, p, q);

        // 使能PLL
        RCC_PLLCmd(ENABLE);

        // 等待PLL稳定
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        // 配置FLASH预取指，指令缓存，数据缓存和等待状态
        FLASH->ACR = FLASH_ACR_PRFTEN 
                | FLASH_ACR_ICEN 
                | FLASH_ACR_DCEN 
                | FLASH_ACR_LATENCY_5WS;

        // 当PLL稳定之后，把PLL时钟切换为系统时钟SYSCLK
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        // 读取时钟切换状态位，确保PLLCLK被选为系统时钟
        while(RCC_GetSYSCLKSource() != 0x08)
        {
        }

    }
    else
    {   // HSE启动出错处理
        while (1);
    }

}

// MOC1 PA8 GPIO初始化
void MCO1_GPIO_Config(void)
{
    /* 定义一个 GPIO_InitTypeDef 类型的结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启LED相关的GPIO外设时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    /* 选择要控制的 GPIO 引脚*/
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;        // 输出模式
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;        // 推挽输出
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;         // 上拉模式
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;    // 引脚速率 100MHz

    /* 初始化GPIO */
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_MCO);
}

// MOC2 PC9 GPIO初始化
void MCO2_GPIO_Config(void)
{
    /* 定义一个 GPIO_InitTypeDef 类型的结构体 */
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启LED相关的GPIO外设时钟 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    /* 选择要控制的 GPIO 引脚*/
    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_AF;        // 输出模式
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;        // 推挽输出
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;         // 上拉模式
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;    // 引脚速率 100MHz

    /* 初始化GPIO */
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_PinAFConfig(GPIOC, GPIO_PinSource9, GPIO_AF_MCO);
}

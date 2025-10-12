/**
  ******************************************************************************
  * @file    plib015_rcu.c
  *
  * @brief   Файл содержит реализацию функций для работы с RCU
  *
  * @author  НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
  *
  ******************************************************************************
  * @attention
  *
  * ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ ПРЕДОСТАВЛЯЕТСЯ «КАК ЕСТЬ», БЕЗ КАКИХ-ЛИБО
  * ГАРАНТИЙ, ЯВНО ВЫРАЖЕННЫХ ИЛИ ПОДРАЗУМЕВАЕМЫХ, ВКЛЮЧАЯ ГАРАНТИИ ТОВАРНОЙ
  * ПРИГОДНОСТИ, СООТВЕТСТВИЯ ПО ЕГО КОНКРЕТНОМУ НАЗНАЧЕНИЮ И ОТСУТСТВИЯ
  * НАРУШЕНИЙ, НО НЕ ОГРАНИЧИВАЯСЬ ИМИ. ДАННОЕ ПРОГРАММНОЕ ОБЕСПЕЧЕНИЕ
  * ПРЕДНАЗНАЧЕНО ДЛЯ ОЗНАКОМИТЕЛЬНЫХ ЦЕЛЕЙ И НАПРАВЛЕНО ТОЛЬКО НА
  * ПРЕДОСТАВЛЕНИЕ ДОПОЛНИТЕЛЬНОЙ ИНФОРМАЦИИ О ПРОДУКТЕ, С ЦЕЛЬЮ СОХРАНИТЬ ВРЕМЯ
  * ПОТРЕБИТЕЛЮ. НИ В КАКОМ СЛУЧАЕ АВТОРЫ ИЛИ ПРАВООБЛАДАТЕЛИ НЕ НЕСУТ
  * ОТВЕТСТВЕННОСТИ ПО КАКИМ-ЛИБО ИСКАМ, ЗА ПРЯМОЙ ИЛИ КОСВЕННЫЙ УЩЕРБ, ИЛИ
  * ПО ИНЫМ ТРЕБОВАНИЯМ, ВОЗНИКШИМ ИЗ-ЗА ИСПОЛЬЗОВАНИЯ ПРОГРАММНОГО ОБЕСПЕЧЕНИЯ
  * ИЛИ ИНЫХ ДЕЙСТВИЙ С ПРОГРАММНЫМ ОБЕСПЕЧЕНИЕМ.
  *
  * <h2><center>&copy; 2025 АО "НИИЭТ"</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "plib015_rcu.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup RCU
  * @{
  */

/** @defgroup RCU_Private Приватные данные
  * @{
  */

/** @defgroup RCU_Private_Defines Приватные константы
  * @{
  */

#define RCU_PLLSYSCFG0_RST_VAL 0x0    /*!< Значение по сбросу регистра PLLSYSCFG0 */

/** @defgroup RCU_TIMEOUT_DEFINE Значения для таймаутов
  * @{
  */

#define RCU_SYSCLK_CHANGE_TIMEOUT 10000 /*!< Время ожидания смены источника тактирования */
#define RCU_PLLCLK_LOCK_TIMEOUT 10000   /*!< Время ожидания стабилизации выходной частоты PLL */

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCU_Private_Functions Приватные функции
  * @{
  */

/**
  * @brief   Получение значения частоты генерации выбранного источника
  * @param   Clk  Выбор тактового сигнала
  * @retval  Val  Значение Гц
  */
static uint32_t getSysClkFreq(RCU_SysClk_TypeDef Clk)
{
    uint32_t clk_freq = 0;

    switch (Clk) {
    case RCU_SysClk_HsiClk:
        clk_freq = RCU_GetHsiClkFreq();
        break;
    case RCU_SysClk_HseClk:
        clk_freq = RCU_GetHseClkFreq();
        break;
    case RCU_SysClk_SysPLL0Clk:
        clk_freq = RCU_GetSysPLL0ClkFreq();
        break;
    case RCU_SysClk_LsiClk:
        clk_freq = RCU_GetLsiClkFreq();
        break;
    }

    return clk_freq;
}

/**
  * @brief   Получение значения частоты генерации выбранного источника
  * @param   Clk  Выбор тактового сигнала
  * @retval  Val  Значение Гц
  */
static uint32_t getPeriphClkFreq(RCU_PeriphClk_TypeDef Clk)
{
    uint32_t clk_freq = 0;

    switch (Clk) {
    case RCU_PeriphClk_HsiClk:
        clk_freq = RCU_GetHsiClkFreq();
        break;
    case RCU_PeriphClk_HseClk:
        clk_freq = RCU_GetHseClkFreq();
        break;
    case RCU_PeriphClk_SysPLL0Clk:
        clk_freq = RCU_GetSysPLL0ClkFreq();
        break;
    case RCU_PeriphClk_SysPLL1Clk:
        clk_freq = RCU_GetSysPLL1ClkFreq();
        break;
    }

    return clk_freq;
}

/**
  * @brief   Получение значения частоты генерации выбранного источника
  * @param   Clk  Выбор тактового сигнала
  * @retval  Val  Значение Гц
  */
static uint32_t getIwdtClkFreq(RCU_IWDTClk_TypeDef Clk)
{
    uint32_t clk_freq = 0;

    switch (Clk) {
    case RCU_IWDTClk_HsiClk:
        clk_freq = RCU_GetHsiClkFreq();
        break;
    case RCU_IWDTClk_HseClk:
        clk_freq = RCU_GetHseClkFreq();
        break;
    case RCU_IWDTClk_LsiClk:
        clk_freq = RCU_GetLsiClkFreq();
        break;
    }

    return clk_freq;
}

/**
  * @brief   Получение значения частоты тактового сигнала HSICLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetHsiClkFreq()
{
    //Константы согласно таблицы 4.2 Руководства пользователя
    static const uint32_t hsi_clk[16] = {618000, 650000,686000,725000,766000,816000,873000,938000, 1012000, 1101000, 1208000, 1339000, 1510000, 1722000, 2009000, 2417000};
    uint32_t hsi_trim;

    hsi_trim = READ_REG(PMURTC->HSI_TRIM);
    return hsi_clk[hsi_trim];
}

/**
  * @brief   Получение значения частоты тактового сигнала HSECLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetHseClkFreq()
{
    return HSECLK_VAL;
}

/**
  * @brief   Получение значения частоты тактового сигнала LSICLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetLsiClkFreq()
{
    return (uint32_t)LSICLK_VAL;
}

/**
  * @brief   Получение значения частоты тактового сигнала SYSPLL0CLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetSysPLL0ClkFreq()
{
    uint32_t pll_div0a, pll_div0b, pll_fbdiv, pll_refdiv, pll_refclk, pll_clkFreq;
    float pll_fracdiv;
    pll_div0a = READ_REG(RCU->PLLSYSCFG0_bit.PD0A)+1;
    pll_div0b = READ_REG(RCU->PLLSYSCFG0_bit.PD0B)+1;
    pll_fbdiv = READ_REG(RCU->PLLSYSCFG2_bit.FBDIV);
    pll_refdiv = READ_REG(RCU->PLLSYSCFG0_bit.REFDIV);
    pll_refclk = HSECLK_VAL;
    if (RCU->PLLSYSCFG0_bit.DSMEN) pll_fracdiv = (float)(RCU->PLLSYSCFG1_bit.FRAC / (1 << 24));
       else pll_fracdiv = 0;

    pll_clkFreq = (uint32_t)((pll_refclk * (pll_fbdiv + pll_fracdiv)) / (pll_refdiv * pll_div0a * pll_div0b));
    return (uint32_t)(pll_clkFreq);
}

/**
  * @brief   Получение значения частоты тактового сигнала SYSPLL1CLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetSysPLL1ClkFreq()
{
    uint32_t pll_div1a, pll_div1b, pll_fbdiv, pll_refdiv, pll_refclk;
    float pll_fracdiv;
    pll_div1a = READ_REG(RCU->PLLSYSCFG0_bit.PD1A)+1;
    pll_div1b = READ_REG(RCU->PLLSYSCFG0_bit.PD1B)+1;
    pll_fbdiv = READ_REG(RCU->PLLSYSCFG2_bit.FBDIV);
    pll_refdiv = READ_REG(RCU->PLLSYSCFG0_bit.REFDIV);
    pll_refclk = HSECLK_VAL;
    if (RCU->PLLSYSCFG0_bit.DSMEN) pll_fracdiv = (float)(RCU->PLLSYSCFG1_bit.FRAC / (1 << 24));
       else pll_fracdiv = 0;    

    return (uint32_t)((pll_refclk * (pll_fbdiv + pll_fracdiv)) / (pll_refdiv * pll_div1a * pll_div1b));
}

/**
  * @brief   Получение значения частоты тактового сигнала USBPLLCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetUsbPLLClkFreq()
{
    uint32_t pll_div0a, pll_div0b, pll_fracdiv, pll_fbdiv, pll_refdiv, pll_refclk;

    pll_div0a = READ_REG(USB->PLLUSBCFG0_bit.PD0A)+1;
    pll_div0b = READ_REG(USB->PLLUSBCFG0_bit.PD0B)+1;
    pll_fracdiv = READ_REG(USB->PLLUSBCFG1_bit.FRAC);
    pll_fbdiv = READ_REG(USB->PLLUSBCFG2_bit.FBDIV);
    pll_refdiv = READ_REG(USB->PLLUSBCFG0_bit.REFDIV);
    pll_refclk = HSECLK_VAL;

    return (uint32_t)((pll_refclk * pll_fbdiv) / (pll_refdiv * pll_div0a * pll_div0b));
}

/**
  * @brief   Получение значения частоты SYSCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetSysClkFreq()
{
    RCU_SysClk_TypeDef sys_clk;

    sys_clk = RCU_SysClkStatus();

    return getSysClkFreq(sys_clk);
}

/**
  * @brief   Получение значения частоты UARTCLK
  * @param   UARTx_Num  Порядковый номер блока UART
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetUARTClkFreq(UART_Num_TypeDef UARTx_Num)
{
    RCU_PeriphClk_TypeDef uart_clk;
    uint32_t div_val;

    uart_clk = (RCU_PeriphClk_TypeDef)READ_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG_bit.CLKSEL);
    if (READ_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getPeriphClkFreq(uart_clk) / div_val;
}

/**
  * @brief   Получение значения частоты SPICLK
  * @param   SPIx_Num  Порядковый номер блока SPI
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetSPIClkFreq(SPI_Num_TypeDef SPIx_Num)
{
    RCU_PeriphClk_TypeDef spi_clk;
    uint32_t div_val;

    spi_clk = (RCU_PeriphClk_TypeDef)READ_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG_bit.CLKSEL);
    if (READ_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getPeriphClkFreq(spi_clk) / div_val;
}

/**
  * @brief   Получение значения частоты ADCSARCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetADCSARClkFreq()
{
    RCU_PeriphClk_TypeDef adc_clk;
    uint32_t div_val;

    adc_clk = (RCU_PeriphClk_TypeDef)READ_REG(RCU->ADCSARCLKCFG_bit.CLKSEL);
    if (READ_REG(RCU->ADCSARCLKCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->ADCSARCLKCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getPeriphClkFreq(adc_clk) / div_val;
}

/**
  * @brief   Получение значения частоты ADCSDCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetADCSDClkFreq()
{
    RCU_PeriphClk_TypeDef adc_clk;
    uint32_t div_val;

    adc_clk = (RCU_PeriphClk_TypeDef)READ_REG(RCU->ADCSDCLKCFG_bit.CLKSEL);
    if (READ_REG(RCU->ADCSDCLKCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->ADCSDCLKCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getPeriphClkFreq(adc_clk) / div_val;
}

/**
  * @brief   Получение значения частоты WDTCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetWDTClkFreq()
{
    RCU_PeriphClk_TypeDef wdt_clk;
    uint32_t div_val;

    wdt_clk = (RCU_PeriphClk_TypeDef)READ_REG(RCU->WDOGCLKCFG_bit.CLKSEL);
    if (READ_REG(RCU->WDOGCLKCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->WDOGCLKCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getPeriphClkFreq(wdt_clk) / div_val;
}

/**
  * @brief   Получение значения частоты IWDTCLK
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetIWDTClkFreq()
{
    RCU_IWDTClk_TypeDef iwdt_clk;

    iwdt_clk = (RCU_IWDTClk_TypeDef)READ_REG(PMURTC->IWDG_CFG_bit.CLKSRC);

    return getIwdtClkFreq(iwdt_clk);
}

/**
  * @brief   Получение значения частоты CLKOUT
  * @retval  Val  Значение Гц
  */
uint32_t RCU_GetClkOutFreq()
{
    RCU_PeriphClk_TypeDef clkout;
    uint32_t div_val;

    clkout = (RCU_SysClk_TypeDef)READ_REG(RCU->CLKOUTCFG_bit.CLKSEL);
    if (READ_REG(RCU->CLKOUTCFG_bit.DIVEN))
        div_val = 2 * (READ_REG(RCU->CLKOUTCFG_bit.DIVN) + 1);
    else
        div_val = 1;

    return getSysClkFreq(clkout) / div_val;
}

/**
  * @brief      Инициализирует SYSPLL0 согласно параметрам структуры InitStruct.
  *             Значение выходной частоты PLL вычисляется по формуле:<br><br>
  *             <center>FOUT = (FREF x FBDIV) / (REFDIV x DIV1 x DIV2),</center>
  *             где FREF – опорная частота PLL.<br>
  * @attention  При расчете коэффициентов деления PLL должны выполняться следующие условия:
  *             - 8 МГц <= FREF <= 800 МГц (REF),
  *             - 400 МГц <= FIN*FBDIV/REFDIV <= 16000 МГц (VCO),
  *             - 8 МГц <= FOUT <= 1600 МГц;
  *
  * @param      InitStruct  Указатель на структуру типа @ref RCU_PLL_Init_TypeDef,
  *                         которая содержит конфигурационную информацию
  * @retval     Status
  */
OperationStatus RCU_SYSPLL0_Init(RCU_PLL_Init_TypeDef* InitStruct)
{
    uint32_t timeout = RCU_PLLCLK_LOCK_TIMEOUT;
    OperationStatus status = OK;

    assert_param(IS_FUNCTIONAL_STATE(InitStruct->DivEn));
    assert_param(IS_RCU_PLL_FB_DIV(InitStruct->FbDiv));
    assert_param(IS_RCU_PLL_FRAC_DIV(InitStruct->FracDiv));
    assert_param(IS_RCU_PLL_REF_DIV(InitStruct->RefDiv));
    assert_param(IS_RCU_PLL_DIV0A(InitStruct->Div0A));
    assert_param(IS_RCU_PLL_DIV0B(InitStruct->Div0B));
    assert_param(IS_RCU_PLL_DIV1A(InitStruct->Div1A));
    assert_param(IS_RCU_PLL_DIV1B(InitStruct->Div1B));

    CLEAR_BIT(RCU->PLLSYSCFG0, RCU_PLLSYSCFG0_BYP_Msk | RCU_PLLSYSCFG0_PLLEN_Msk);
    MODIFY_REG(RCU->PLLSYSCFG0, (RCU_PLLSYSCFG0_REFDIV_Msk | RCU_PLLSYSCFG0_PD0A_Msk | RCU_PLLSYSCFG0_PD0B_Msk),
               (InitStruct->RefDiv << RCU_PLLSYSCFG0_REFDIV_Pos |
                InitStruct->Div0A << RCU_PLLSYSCFG0_PD0A_Pos |
                InitStruct->Div0B << RCU_PLLSYSCFG0_PD0B_Pos));
    MODIFY_REG(RCU->PLLSYSCFG2, (RCU_PLLSYSCFG2_FBDIV_Msk),
               (InitStruct->FbDiv << RCU_PLLSYSCFG2_FBDIV_Pos));

    RCU_SYSPLL0_OutCmd(ENABLE);
    while (timeout) {
        if (RCU_SYSPLL_LockStatus()) {
            break;
        } else {
            timeout--;
        }
    }
    if (!timeout) {
        status = ERROR;
    }

    return status;
}

/**
  * @brief      Инициализирует USBPLL согласно параметрам структуры InitStruct.
  *             Значение выходной частоты PLL вычисляется по формуле:<br><br>
  *             <center>FOUT = (FREF x FBDIV) / (REFDIV x DIV1 x DIV2),</center>
  *             где FREF – опорная частота PLL.<br>
  * @attention  При расчете коэффициентов деления PLL должны выполняться следующие условия:
  *             - 8 МГц <= FREF <= 800 МГц (REF),
  *             - 400 МГц <= FIN*FBDIV/REFDIV <= 16000 МГц (VCO),
  *             - 8 МГц <= FOUT <= 1600 МГц;
  *
  * @param      InitStruct  Указатель на структуру типа @ref RCU_PLL_Init_TypeDef,
  *                         которая содержит конфигурационную информацию
  * @retval     Status
  */
OperationStatus RCU_USBPLL_Init(RCU_PLL_Init_TypeDef* InitStruct)
{
    uint32_t timeout = RCU_PLLCLK_LOCK_TIMEOUT;
    OperationStatus status = OK;

    assert_param(IS_FUNCTIONAL_STATE(InitStruct->DivEn));
    assert_param(IS_RCU_PLL_FB_DIV(InitStruct->FbDiv));
    assert_param(IS_RCU_PLL_FRAC_DIV(InitStruct->FracDiv));
    assert_param(IS_RCU_PLL_REF_DIV(InitStruct->RefDiv));
    assert_param(IS_RCU_PLL_DIV0A(InitStruct->Div0A));
    assert_param(IS_RCU_PLL_DIV0B(InitStruct->Div0B));
    assert_param(IS_RCU_PLL_DIV1A(InitStruct->Div1A));
    assert_param(IS_RCU_PLL_DIV1B(InitStruct->Div1B));

    CLEAR_BIT(USB->PLLUSBCFG0, USB_PLLUSBCFG0_BYP_Msk | USB_PLLUSBCFG0_PLLEN_Msk);
    MODIFY_REG(USB->PLLUSBCFG0, (USB_PLLUSBCFG0_REFDIV_Msk | USB_PLLUSBCFG0_PD0A_Msk | USB_PLLUSBCFG0_PD0B_Msk),
               (InitStruct->RefDiv << USB_PLLUSBCFG0_REFDIV_Pos |
                InitStruct->Div0A << USB_PLLUSBCFG0_PD0A_Pos |
                InitStruct->Div0B << USB_PLLUSBCFG0_PD0B_Pos));
    MODIFY_REG(USB->PLLUSBCFG2, (USB_PLLUSBCFG2_FBDIV_Msk),
               (InitStruct->FbDiv << USB_PLLUSBCFG2_FBDIV_Pos));

    RCU_SYSPLL0_OutCmd(ENABLE);
    while (timeout) {
        if (RCU_SYSPLL_LockStatus()) {
            break;
        } else {
            timeout--;
        }
    }
    if (!timeout) {
        status = ERROR;
    }

    return status;
}

/**
  * @brief   Заполнение каждого члена структуры InitStruct значениями по умолчанию
  * @param   InitStruct  Указатель на структуру типа @ref RCU_PLL_Init_TypeDef,
  *                      которую необходимо проинициализировать
  * @retval  void
  */
void RCU_PLL_StructInit(RCU_PLL_Init_TypeDef* InitStruct)
{
    InitStruct->FbDiv = 16;
    InitStruct->RefDiv = 1;
    InitStruct->Div0A = 1;
    InitStruct->Div0B = 1;
    InitStruct->Div1A = 1;
    InitStruct->Div1B = 1;
}

/**
  * @brief   Устанавливает все регистры SYSPLL значениями по умолчанию
  * @retval  void
  */
void RCU_SYSPLL_DeInit()
{
    RCU_SYSPLL_Cmd(DISABLE);
    WRITE_REG(RCU->PLLSYSCFG0, RCU_PLLSYSCFG0_RST_VAL);
}

/**
  * @brief   Устанавливает все регистры USBPLL значениями по умолчанию
  * @retval  void
  */
void RCU_USBPLL_DeInit()
{
    RCU_USBPLL_OutCmd(DISABLE);
    WRITE_REG(USB->PLLUSBCFG0, RCU_PLLSYSCFG0_RST_VAL);
}

/**
  * @brief   Переключение источника для системного тактового сигнала
  * @param   SysClk  Выбор источника
  * @retval  void
  */
OperationStatus RCU_SysClkChangeCmd(RCU_SysClk_TypeDef SysClk)
{
    uint32_t timeout = RCU_SYSCLK_CHANGE_TIMEOUT;
    OperationStatus status = OK;

    assert_param(IS_RCU_SYS_CLK(SysClk));

    RCU_SysClkConfig(SysClk);

    while (timeout) {
        if ((RCU_SysClkStatus() != SysClk)) {
            timeout--;
        } else {
            break;
        }
    }

    if (!timeout) {
        status = ERROR;
    }

    return status;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2025 NIIET *****END OF FILE****/

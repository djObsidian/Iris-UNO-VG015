/**
  ******************************************************************************
  * @file    plib015_rcu.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          RCU (Reset & Clock control Unit), а также сопутствующие
  *          макроопределения и перечисления
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLIB015_RCU_H
#define __PLIB015_RCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup RCU
  * @brief Драйвер для работы с тактированием и сбросом периферийных блоков
  * @{
  */

/** @defgroup RCU_Exported_Defines Константы
  * @{
  */

#define HSICLK_VAL 1000000
#ifndef HSECLK_VAL
  #define HSECLK_VAL 16000000
#endif
#define LSICLK_VAL 32000

/** @defgroup RCU_ClkStatus_Define Cтатусы источников тактового сигнала
  * @{
  */

#define RCU_ClkStatus_HSEClkFail RCU_CLKSTAT_CLKERR1_Msk          /*!< Ошибка сигнала внешнего осциллятора */
#define RCU_ClkStatus_PLLClkFail RCU_CLKSTAT_CLKERR2_Msk          /*!< Ошибка сигнала с PLL */
#define RCU_ClkStatus_LSIClkFail RCU_CLKSTAT_CLKERR3_Msk          /*!< Ошибка сигнала с LSI */
#define RCU_ClkStatus_HSEClkGood RCU_CLKSTAT_CLKGOOD1_Msk         /*!< Нормальная работа сигнала внешнего осциллятора */
#define RCU_ClkStatus_PLLClkGood RCU_CLKSTAT_CLKGOOD2_Msk         /*!< Нормальная работа сигнала с PLL */
#define RCU_ClkStatus_LSIClkGood RCU_CLKSTAT_CLKGOOD3_Msk         /*!< Нормальная работа сигнала с LSI */

#define IS_RCU_CLK_STATUS(VALUE) (((VALUE) == RCU_ClkStatus_HSEClkFail) ||    \
                                  ((VALUE) == RCU_ClkStatus_PLLClkFail) ||    \
                                  ((VALUE) == RCU_ClkStatus_LSIClkFail) ||    \
                                  ((VALUE) == RCU_ClkStatus_HSEClkGood) ||    \
                                  ((VALUE) == RCU_ClkStatus_PLLClkGood) ||    \
                                  ((VALUE) == RCU_ClkStatus_LSIClkGood))
/**
  * @}
  */

/** @defgroup RCU_RstStatus_Define Источник, вызвавший последний сброс системы
  * @{
  */

#define RCU_RstStatus_POR     RCU_RSTSTAT_POR_Msk         /*!< Сброс от блока POR */
#define RCU_RstStatus_WDOG    RCU_RSTSTAT_WDOG_Msk        /*!< Сброс от сторожевого таймера */
#define RCU_RstStatus_Sys     RCU_RSTSTAT_SYSRST_Msk      /*!< Системный сброс */

#define IS_RCU_RST_STATUS(VALUE) (((VALUE) == RCU_RstStatus_POR) || \
                                  ((VALUE) == RCU_RstStatus_WDOG) || \
                                  ((VALUE) == RCU_RstStatus_Sys))
/**
  * @}
  */

/** @defgroup RCU_ITSource_Define Источники прерываний
  * @{
  */

#define RCU_ITSource_SRCClkFail RCU_INTEN_SRCCLKERR_Msk       /*!< Произошла ошибка сигнала внешнего осциллятора */
#define RCU_ITSource_PLLClkFail RCU_INTEN_PLLCLKERR_Msk       /*!< Произошла ошибка сигнала с PLL */
#define RCU_ITSource_PLLDivClkFail RCU_INTEN_PLLDIVCLKERR_Msk /*!< Произошла ошибка сигнала с деленного выхода PLL */
#define RCU_ITSource_SRCClkGood RCU_INTEN_SRCCLKOK_Msk        /*!< Произошел переход к нормальной работе сигнала внешнего осциллятора */
#define RCU_ITSource_PLLClkGood RCU_INTEN_PLLCLKOK_Msk        /*!< Произошел переход к нормальной работе сигнала с PLL */
#define RCU_ITSource_PLLDivClkGood RCU_INTEN_PLLDIVCLKOK_Msk  /*!< Произошел переход к нормальной работе сигнала с деленного выхода PLL */
#define RCU_ITSource_PLLLock RCU_INTEN_PLLLOCK_Msk            /*!< Произошел захват частоты PLL */

#define IS_RCU_IT_SOURCE(VALUE) (((VALUE) == RCU_ITSource_SRCClkFail) ||    \
                                 ((VALUE) == RCU_ITSource_PLLClkFail) ||    \
                                 ((VALUE) == RCU_ITSource_PLLDivClkFail) || \
                                 ((VALUE) == RCU_ITSource_SRCClkGood) ||    \
                                 ((VALUE) == RCU_ITSource_PLLClkGood) ||    \
                                 ((VALUE) == RCU_ITSource_PLLDivClkGood) || \
                                 ((VALUE) == RCU_ITSource_PLLLock))

/**
  * @}
  */

/** @defgroup RCU_ITStatus_Define Статусы прерываний
  * @{
  */

#define RCU_ITStatus_SRCClkFail RCU_INTSTAT_SRCCLKERR_Msk       /*!< Флаг ошибки сигнала внешнего осциллятора */
#define RCU_ITStatus_PLLClkFail RCU_INTSTAT_PLLCLKERR_Msk       /*!< Флаг ошибки сигнала с PLL */
#define RCU_ITStatus_PLLDivClkFail RCU_INTSTAT_PLLDIVCLKERR_Msk /*!< Флаг ошибки сигнала с деленного выхода PLL */
#define RCU_ITStatus_SRCClkGood RCU_INTSTAT_SRCCLKOK_Msk        /*!< Флаг перехода к нормальной работе сигнала внешнего осциллятора */
#define RCU_ITStatus_PLLClkGood RCU_INTSTAT_PLLCLKOK_Msk        /*!< Флаг перехода к нормальной работе сигнала с PLL */
#define RCU_ITStatus_PLLDivClkGood RCU_INTSTAT_PLLDIVCLKOK_Msk  /*!< Флаг перехода к нормальной работе сигнала с деленного выхода PLL */
#define RCU_ITStatus_PLLLock RCU_INTSTAT_PLLLOCK_Msk            /*!< Флаг захвата частоты PLL */
#define RCU_ITStatus_SysFail RCU_INTSTAT_SYSFAIL_Msk            /*!< Флаг сбоя системной частоты */

#define IS_RCU_IT_STATUS(VALUE) (((VALUE) == RCU_ITStatus_SRCClkFail) ||    \
                                 ((VALUE) == RCU_ITStatus_PLLClkFail) ||    \
                                 ((VALUE) == RCU_ITStatus_PLLDivClkFail) || \
                                 ((VALUE) == RCU_ITStatus_SRCClkGood) ||    \
                                 ((VALUE) == RCU_ITStatus_PLLClkGood) ||    \
                                 ((VALUE) == RCU_ITStatus_PLLDivClkGood) || \
                                 ((VALUE) == RCU_ITStatus_PLLLock) ||       \
                                 ((VALUE) == RCU_ITStatus_SysFail))

/**
  * @}
  */

/** @defgroup RCU_AHBClk_Define Управление тактированием периферийных блоков AHB
  * @{
  */

#define RCU_AHBClk_CAN      RCU_CGCFGAHB_CANEN_Msk     /*!< Управление тактированием блока CAN */
#define RCU_AHBClk_USB      RCU_CGCFGAHB_USBEN_Msk     /*!< Управление тактированием блока USB */
#define RCU_AHBClk_CRYPTO   RCU_CGCFGAHB_CRYPTOEN_Msk  /*!< Управление тактированием блока CRYPTO */
#define RCU_AHBClk_HASH     RCU_CGCFGAHB_HASHEN_Msk    /*!< Управление тактированием блока HASH */
#define RCU_AHBClk_QSPI     RCU_CGCFGAHB_QSPIEN_Msk    /*!< Управление тактированием блока QSPI */
#define RCU_AHBClk_SPI0     RCU_CGCFGAHB_SPI0EN_Msk    /*!< Управление тактированием блока SPI0 */
#define RCU_AHBClk_SPI1     RCU_CGCFGAHB_SPI1EN_Msk    /*!< Управление тактированием блока SPI1 */
#define RCU_AHBClk_GPIOA    RCU_CGCFGAHB_GPIOAEN_Msk   /*!< Управление тактированием блока GPIOA */
#define RCU_AHBClk_GPIOB    RCU_CGCFGAHB_GPIOBEN_Msk   /*!< Управление тактированием блока GPIOB */
#define RCU_AHBClk_GPIOC    RCU_CGCFGAHB_GPIOCEN_Msk   /*!< Управление тактированием блока GPIOC */
#define RCU_AHBClk_CRC0     RCU_CGCFGAHB_CRC0EN_Msk    /*!< Управление тактированием блока CRC0 */
#define RCU_AHBClk_CRC1     RCU_CGCFGAHB_CRC1EN_Msk    /*!< Управление тактированием блока CRC1 */

#define IS_RCU_AHB_CLK(VALUE)   (((VALUE) == RCU_AHBClk_CAN) || \
                                 ((VALUE) == RCU_AHBClk_USB) || \
                                 ((VALUE) == RCU_AHBClk_CRYPTO) || \
                                 ((VALUE) == RCU_AHBClk_HASH) || \
                                 ((VALUE) == RCU_AHBClk_QSPI) || \
                                 ((VALUE) == RCU_AHBClk_SPI0) || \
                                 ((VALUE) == RCU_AHBClk_SPI1) || \
                                 ((VALUE) == RCU_AHBClk_GPIOA) || \
                                 ((VALUE) == RCU_AHBClk_GPIOB) || \
                                 ((VALUE) == RCU_AHBClk_GPIOC) || \
                                 ((VALUE) == RCU_AHBClk_CRC0) || \
                                 ((VALUE) == RCU_AHBClk_CRC1))

/**
  * @}
  */

/** @defgroup RCU_APBClk_Define Управление тактированием периферийных блоков APB
  * @{
  */

#define RCU_APBClk_TMR32  RCU_CGCFGAPB_TMR32EN_Msk   /*!< Управление тактированием блока TMR32 */
#define RCU_APBClk_TMR0   RCU_CGCFGAPB_TMR0EN_Msk    /*!< Управление тактированием блока TMR 0 */
#define RCU_APBClk_TMR1   RCU_CGCFGAPB_TMR1EN_Msk    /*!< Управление тактированием блока TMR 1 */
#define RCU_APBClk_TMR2   RCU_CGCFGAPB_TMR2EN_Msk    /*!< Управление тактированием блока TMR 1 */
#define RCU_APBClk_TRNG   RCU_CGCFGAPB_TRNGEN_Msk    /*!< Управление тактированием блока TRNG */
#define RCU_APBClk_I2C    RCU_CGCFGAPB_I2CEN_Msk     /*!< Управление тактированием блока I2C */
#define RCU_APBClk_UART0  RCU_CGCFGAPB_UART0EN_Msk   /*!< Управление тактированием блока UART 0 */
#define RCU_APBClk_UART1  RCU_CGCFGAPB_UART1EN_Msk   /*!< Управление тактированием блока UART 1 */
#define RCU_APBClk_UART2  RCU_CGCFGAPB_UART2EN_Msk   /*!< Управление тактированием блока UART 2 */
#define RCU_APBClk_UART3  RCU_CGCFGAPB_UART3EN_Msk   /*!< Управление тактированием блока UART 3 */
#define RCU_APBClk_UART4  RCU_CGCFGAPB_UART4EN_Msk   /*!< Управление тактированием блока UART 4 */
#define RCU_APBClk_WDT    RCU_CGCFGAPB_WDTEN_Msk     /*!< Управление тактированием блока WDT */
#define RCU_APBClk_ADCSD  RCU_CGCFGAPB_ADCSDEN_Msk   /*!< Управление тактированием блока ADCSD */
#define RCU_APBClk_ADCSAR RCU_CGCFGAPB_ADCSAREN_Msk  /*!< Управление тактированием блока ADCSAR */
#define RCU_APBClk_CMP    RCU_CGCFGAPB_CMPEN_Msk     /*!< Управление тактированием блока CMP */

#define IS_RCU_APB_CLK(VALUE)   (((VALUE) == RCU_APBClk_TMR32) ||  \
                                 ((VALUE) == RCU_APBClk_TMR0) ||  \
                                 ((VALUE) == RCU_APBClk_TMR1) ||  \
                                 ((VALUE) == RCU_APBClk_TMR2) ||  \
                                 ((VALUE) == RCU_APBClk_TRNG) ||   \
                                 ((VALUE) == RCU_APBClk_I2C) ||   \
                                 ((VALUE) == RCU_APBClk_UART0) || \
                                 ((VALUE) == RCU_APBClk_UART1) || \
                                 ((VALUE) == RCU_APBClk_UART2) || \
                                 ((VALUE) == RCU_APBClk_UART3) || \
                                 ((VALUE) == RCU_APBClk_UART4) || \
                                 ((VALUE) == RCU_APBClk_WDT) || \
                                 ((VALUE) == RCU_APBClk_ADCSD) || \
                                 ((VALUE) == RCU_APBClk_ADCSAR) || \
                                 ((VALUE) == RCU_APBClk_CMP))

/**
  * @}
  */

/** @defgroup RCU_AHBRst_Define Управление сбросом периферийных блоков AHB
 * @{
 */

#define RCU_AHBRst_CAN      RCU_RSTDISAHB_CANEN_Msk     /*!< Управление сбросом блока CAN */
#define RCU_AHBRst_USB      RCU_RSTDISAHB_USBEN_Msk     /*!< Управление сбросом блока USB */
#define RCU_AHBRst_CRYPTO   RCU_RSTDISAHB_CRYPTOEN_Msk  /*!< Управление сбросом блока CRYPTO */
#define RCU_AHBRst_HASH     RCU_RSTDISAHB_HASHEN_Msk    /*!< Управление сбросом блока HASH */
#define RCU_AHBRst_QSPI     RCU_RSTDISAHB_QSPIEN_Msk    /*!< Управление сбросом блока QSPI */
#define RCU_AHBRst_SPI0     RCU_RSTDISAHB_SPI0EN_Msk    /*!< Управление сбросом блока SPI0 */
#define RCU_AHBRst_SPI1     RCU_RSTDISAHB_SPI1EN_Msk    /*!< Управление сбросом блока SPI1 */
#define RCU_AHBRst_GPIOA    RCU_RSTDISAHB_GPIOAEN_Msk   /*!< Управление сбросом блока GPIOA */
#define RCU_AHBRst_GPIOB    RCU_RSTDISAHB_GPIOBEN_Msk   /*!< Управление сбросом блока GPIOB */
#define RCU_AHBRst_GPIOC    RCU_RSTDISAHB_GPIOCEN_Msk   /*!< Управление сбросом блока GPIOC */
#define RCU_AHBRst_CRC0     RCU_RSTDISAHB_CRC0EN_Msk    /*!< Управление сбросом блока CRC0 */
#define RCU_AHBRst_CRC1     RCU_RSTDISAHB_CRC1EN_Msk    /*!< Управление сбросом блока CRC1 */

#define IS_RCU_AHB_RST(VALUE)   (((VALUE) == RCU_AHBRst_CAN) || \
                                 ((VALUE) == RCU_AHBRst_USB) || \
                                 ((VALUE) == RCU_AHBRst_CRYPTO) || \
                                 ((VALUE) == RCU_AHBRst_HASH) || \
                                 ((VALUE) == RCU_AHBRst_QSPI) || \
                                 ((VALUE) == RCU_AHBRst_SPI0) || \
                                 ((VALUE) == RCU_AHBRst_SPI1) || \
                                 ((VALUE) == RCU_AHBRst_GPIOA) || \
                                 ((VALUE) == RCU_AHBRst_GPIOB) || \
                                 ((VALUE) == RCU_AHBRst_GPIOC) || \
                                 ((VALUE) == RCU_AHBRst_CRC0) || \
                                 ((VALUE) == RCU_AHBRst_CRC1))

/**
 * @}
 */

/** @defgroup RCU_APBRst_Define Управление сбросом периферийных блоков APB
  * @{
  */

#define RCU_APBRst_TMR32  RCU_RSTDISAPB_TMR32EN_Msk   /*!< Управление сбросом блока TMR32 */
#define RCU_APBRst_TMR0   RCU_RSTDISAPB_TMR0EN_Msk    /*!< Управление сбросом блока TMR 0 */
#define RCU_APBRst_TMR1   RCU_RSTDISAPB_TMR1EN_Msk    /*!< Управление сбросом блока TMR 1 */
#define RCU_APBRst_TMR2   RCU_RSTDISAPB_TMR2EN_Msk    /*!< Управление сбросом блока TMR 1 */
#define RCU_APBRst_TRNG   RCU_RSTDISAPB_TRNGEN_Msk    /*!< Управление сбросом блока TRNG */
#define RCU_APBRst_I2C    RCU_RSTDISAPB_I2CEN_Msk     /*!< Управление сбросом блока I2C */
#define RCU_APBRst_UART0  RCU_RSTDISAPB_UART0EN_Msk   /*!< Управление сбросом блока UART 0 */
#define RCU_APBRst_UART1  RCU_RSTDISAPB_UART1EN_Msk   /*!< Управление сбросом блока UART 1 */
#define RCU_APBRst_UART2  RCU_RSTDISAPB_UART2EN_Msk   /*!< Управление сбросом блока UART 2 */
#define RCU_APBRst_UART3  RCU_RSTDISAPB_UART3EN_Msk   /*!< Управление сбросом блока UART 3 */
#define RCU_APBRst_UART4  RCU_RSTDISAPB_UART4EN_Msk   /*!< Управление сбросом блока UART 4 */
#define RCU_APBRst_WDT    RCU_RSTDISAPB_WDTEN_Msk     /*!< Управление сбросом блока WDT */
#define RCU_APBRst_ADCSD  RCU_RSTDISAPB_ADCSDEN_Msk   /*!< Управление сбросом блока ADCSD */
#define RCU_APBRst_ADCSAR RCU_RSTDISAPB_ADCSAREN_Msk  /*!< Управление сбросом блока ADCSAR */
#define RCU_APBRst_CMP    RCU_RSTDISAPB_CMPEN_Msk     /*!< Управление сбросом блока CMP */

#define IS_RCU_APB_RST(VALUE)   (((VALUE) == RCU_APBRst_TMR32) ||  \
                                 ((VALUE) == RCU_APBRst_TMR0) ||  \
                                 ((VALUE) == RCU_APBRst_TMR1) ||  \
                                 ((VALUE) == RCU_APBRst_TMR2) ||  \
                                 ((VALUE) == RCU_APBRst_TRNG) ||   \
                                 ((VALUE) == RCU_APBRst_I2C) ||   \
                                 ((VALUE) == RCU_APBRst_UART0) || \
                                 ((VALUE) == RCU_APBRst_UART1) || \
                                 ((VALUE) == RCU_APBRst_UART2) || \
                                 ((VALUE) == RCU_APBRst_UART3) || \
                                 ((VALUE) == RCU_APBRst_UART4) || \
                                 ((VALUE) == RCU_APBRst_WDT) || \
                                 ((VALUE) == RCU_APBRst_ADCSD) || \
                                 ((VALUE) == RCU_APBRst_ADCSAR) || \
                                 ((VALUE) == RCU_APBRst_CMP))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup RCU_Exported_Types Типы
  * @{
  */

/**
  * @brief  Выбор источника тактирования для периферийного блока
  *         c несколькими тактовыми доменами - UART, QSPI, SPI, WDT, ADCSAR, ADCSD
  */
typedef enum {
    RCU_PeriphClk_HsiClk =  RCU_UARTCLKCFG_CLKSEL_HSI,       /*!< Сигнал HSICLK */
    RCU_PeriphClk_HseClk =  RCU_UARTCLKCFG_CLKSEL_HSE,       /*!< Сигнал HSCLK */
    RCU_PeriphClk_SysPLL0Clk = RCU_UARTCLKCFG_CLKSEL_PLL0,   /*!< Сигнал SYSPLL0CLK */
    RCU_PeriphClk_SysPLL1Clk = RCU_UARTCLKCFG_CLKSEL_PLL1    /*!< Сигнал SYSPLL1CLK */
} RCU_PeriphClk_TypeDef;
#define IS_RCU_PERIPH_CLK(VALUE) (((VALUE) == RCU_PeriphClk_HsiClk) ||    \
                                  ((VALUE) == RCU_PeriphClk_HseClk)  ||    \
                                  ((VALUE) == RCU_PeriphClk_SysPLL0Clk) ||\
                                  ((VALUE) == RCU_PeriphClk_SysPLL1Clk))

/**
  * @brief  Выбор источника тактирования для периферийного блока IWDT
  */
typedef enum {
    RCU_IWDTClk_HsiClk =  PMURTC_IWDG_CFG_CLKSRC_HSI,     /*!< Сигнал HSICLK */
    RCU_IWDTClk_HseClk =  PMURTC_IWDG_CFG_CLKSRC_HSE,     /*!< Сигнал HSCLK */
    RCU_IWDTClk_LsiClk =  PMURTC_IWDG_CFG_CLKSRC_LSI,    	/*!< Сигнал LSICLK */
} RCU_IWDTClk_TypeDef;
#define IS_RCU_IWDT_CLK(VALUE) (((VALUE) == RCU_IWDTClk_HsiClk) ||    \
                                ((VALUE) == RCU_IWDTClk_HseClk) ||    \
                                ((VALUE) == RCU_IWDTClk_LsiClk))

/**
  * @brief  Выбор источника тактирования для USB
  */
typedef enum {
    RCU_USBClk_USBPLLClk = USB_PLLUSBCFG3_USBCLKSEL_PLLUSBClk,  /*!< Сигнал USBPLLCLK */
	RCU_USBClk_SysClk = USB_PLLUSBCFG3_USBCLKSEL_SYSClk,         	/*!< Сигнал SYSCLK */
} RCU_USBClk_TypeDef;
#define IS_RCU_USB_CLK(VALUE)  (((VALUE) == RCU_USBClk_SysClk) ||    \
                                ((VALUE) == RCU_USBClk_USBPLLClk))

/**
  * @brief  Выбор источника тактирования для CLKOUT
  */
typedef enum {
    RCU_ClkoutClk_HsiClk = RCU_CLKOUTCFG_CLKSEL_HSI,        /*!< Сигнал HSICLK */
    RCU_ClkoutClk_HseClk = RCU_CLKOUTCFG_CLKSEL_HSE,        /*!< Сигнал HSECLK */
    RCU_ClkoutClk_SysPLL0Clk = RCU_CLKOUTCFG_CLKSEL_PLL0,   /*!< Сигнал SYSPLL0CL */
    RCU_ClkoutClk_LsiClk = RCU_CLKOUTCFG_CLKSEL_LSI      	  /*!< Сигнал LSICLK */
} RCU_ClkoutClk_TypeDef;
#define IS_RCU_CLKOUT_CLK(VALUE) (((VALUE) == RCU_ClkoutClk_HsiClk) ||     \
                                ((VALUE) == RCU_ClkoutClk_HseClk) ||     \
                                ((VALUE) == RCU_ClkoutClk_SysPLL0Clk) || \
                                ((VALUE) == RCU_ClkoutClk_LsiClk))

/**
  * @brief  Выбор источника системной частоты
  */
typedef enum {
    RCU_SysClk_HsiClk = RCU_SYSCLKCFG_SRC_HSICLK,        	/*!< Сигнал HSICLK */
    RCU_SysClk_HseClk = RCU_SYSCLKCFG_SRC_HSECLK,        	/*!< Сигнал HSECLK */
    RCU_SysClk_SysPLL0Clk = RCU_SYSCLKCFG_SRC_SYSPLL0CLK, /*!< Сигнал SYSPLL0CLK */
    RCU_SysClk_LsiClk = RCU_SYSCLKCFG_SRC_LSICLK      		/*!< Сигнал LSICLK */
} RCU_SysClk_TypeDef;
#define IS_RCU_SYS_CLK(VALUE) (((VALUE) == RCU_SysClk_MainClk) ||   \
                               ((VALUE) == RCU_SysClk_SysPLLClk) || \
                               ((VALUE) == RCU_SysClk_Alt0Clk) ||   \
                               ((VALUE) == RCU_SysClk_Alt1Clk))

/**
  * @brief  Структура инициализации PLL
  *
  */
typedef struct
{
    FunctionalState FracDivEn;   /*!< Активация дробного делителя PLL*/
    uint32_t RefDiv;          /*!< Делитель опорного сигнала PLL (M).
                                   Параметр может принимать любое значение из диапазона 1-63. */
    uint32_t FbDiv;           /*!< Делитель обратной связи (N).
                                   Параметр может принимать любое значение из диапазона:
                                      16-160 (без дробного делителя),
                                      20-160 (с дробным делителем) */
    uint32_t FracDiv;         /*!< Дробный делитель.
                                   Параметр может принимать любое значение из диапазона 1-16777215. */                                   
    uint32_t Div0A;           /*!< Внутренний делитель PLL A канала 0 (итоговое значение (Div0A+1))
                                   Параметр может принимать любое значение из диапазона 0-63. */
    uint32_t Div0B;           /*!< Внутренний делитель PLL B канала 0 (итоговое значение (Div0BA+1))
                                   Параметр может принимать любое значение из диапазона 0-63. */
    uint32_t Div1A;           /*!< Внутренний делитель PLL A канала 1 (итоговое значение (Div1A+1))
                                   Параметр может принимать любое значение из диапазона 0-63. */
    uint32_t Div1B;           /*!< Внутренний делитель PLL B канала 1 (итоговое значение (Div1BA+1))
                                   Параметр может принимать любое значение из диапазона 0-63. */
} RCU_PLL_Init_TypeDef;

#define IS_RCU_PLL_REF_DIV(VALUE) (((VALUE) <= 63) && ((VALUE) >= 1))
#define IS_RCU_PLL_FB_DIV(VALUE) (((VALUE) <= 160) && ((VALUE) >= 16))
#define IS_RCU_PLL_FRAC_DIV(VALUE) (((VALUE) <= 16777215) && ((VALUE) >= 1))
#define IS_RCU_PLL_DIV0A(VALUE) (((VALUE) <= 63) && ((VALUE) >= 0))
#define IS_RCU_PLL_DIV0B(VALUE) (((VALUE) <= 63) && ((VALUE) >= 0))
#define IS_RCU_PLL_DIV1A(VALUE) (((VALUE) <= 63) && ((VALUE) >= 0))
#define IS_RCU_PLL_DIV1B(VALUE) (((VALUE) <= 63) && ((VALUE) >= 0))
#define IS_RCU_PLL_DIVA_DIVB(VALUE_A,VALUE_B) (VALUE_A > VALUE_B)
#define IS_RCU_PLL_REF_FREQ(VALUE) (((VALUE) <= 30000000) && ((VALUE) >= 10000000))
#define IS_RCU_PLL_OUT_FREQ(VALUE) (((VALUE) <= 60000000) && ((VALUE) >= 340000))
#define IS_RCU_PLL_FVCO_FREQ(VALUE) (((VALUE) <= 1600000000) && ((VALUE) >= 200000000))
#define IS_RCU_PLL_FREF_DIV_FREQ(VALUE) ((VALUE) >= 10000000)
#define IS_RCU_SYSCLK_FREQ(VALUE) (((VALUE) <= 60000000) && ((VALUE) >= 1000000))
#define IS_RCU_SECPRD(VALUE) (((VALUE)&0xFFFFFF00) == 0)
#define IS_RCU_PERIPH_DIV(VALUE) (((VALUE)&0xFFFFFFC0) == 0)
#define IS_RCU_CLKOUT_DIV(VALUE) (((VALUE)&0xFFFF0000) == 0)

/**
  * @}
  */

/** @defgroup RCU_Exported_Functions Функции
  * @{
  */

uint32_t RCU_GetHsiClkFreq(void);
uint32_t RCU_GetHseClkFreq(void);
uint32_t RCU_GetLsiClkFreq(void);
uint32_t RCU_GetSysPLL0ClkFreq(void);
uint32_t RCU_GetSysPLL1ClkFreq(void);
uint32_t RCU_GetUsbPLLClkFreq(void);

/**
  * @brief   Включение тактирования выбранного APB блока периферии.
  * @param   APBClk  Выбор периферии. Любая совокупность значений значений RCU_APBClk_x (@ref RCU_APBClk_Define).
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_APBClkCmd(uint32_t APBClk, FunctionalState State)
{
    assert_param(IS_RCU_APB_CLK(APBClk));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(RCU->CGCFGAPB, APBClk, State ? APBClk : 0);
}

/**
  * @brief   Включение тактирования выбранного AHB блока периферии
  * @param   AHBClk  Выбор периферии. Любая совокупность значений значений RCU_AHBClk_x (@ref RCU_AHBClk_Define).
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_AHBClkCmd(uint32_t AHBClk, FunctionalState State)
{
    assert_param(IS_RCU_AHB_CLK(AHBClk));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(RCU->CGCFGAHB, AHBClk, State ? AHBClk : 0);
}

/**
  * @brief   Вывод из состояния сброса периферийных блоков APB
  * @param   APBRst  Выбор периферийного модуля. Любая совокупность значений значений RCU_APBRst0_x (@ref RCU_APBRst0_Define).
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_APBRstCmd(uint32_t APBRst, FunctionalState State)
{
    assert_param(IS_RCU_APB_RST(APBRst));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(RCU->RSTDISAPB, APBRst, State ? APBRst : 0);
}

/**
  * @brief   Вывод из состояния сброса периферийных блоков APB
  * @param   AHBRst  Выбор периферийного модуля. Любая совокупность значений значений RCU_AHBRst_x (@ref RCU_AHBRst_Define).
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_AHBRstCmd(uint32_t AHBRst, FunctionalState State)
{
    assert_param(IS_RCU_AHB_RST(AHBRst));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(RCU->RSTDISAHB, AHBRst, State ? AHBRst : 0);
}

/**
  * @brief   Установка опорного тактового сигнала для системной частоты
  * @param   SysClk  Выбор тактового сигнала
  * @retval  void
  */
__STATIC_INLINE void RCU_SysClkConfig(RCU_SysClk_TypeDef SysClk)
{
    assert_param(IS_RCU_SYS_CLK(SysClk));

    WRITE_REG(RCU->SYSCLKCFG_bit.SRC, SysClk);
}

/**
  * @brief   Получение текущего опорного тактового сигнала для системной частоты
  * @retval  Val  Выбранный сигнал
  */
__STATIC_INLINE RCU_SysClk_TypeDef RCU_SysClkStatus(void)
{
    return (RCU_SysClk_TypeDef)READ_REG(RCU->CLKSTAT_bit.SRC);
}

/**
  * @brief   Получение статуса выбранного тактового сигнала
  * @param   ClkStatus  Выбор тактового сигнала. Любая совокупность значений значений RCU_ClkStatus_x (@ref RCU_ClkStatus_Define).
  * @retval  Status  Статус
  */
__STATIC_INLINE FlagStatus RCU_ClkStatus(uint32_t ClkStatus)
{
    return (FlagStatus)READ_BIT(RCU->CLKSTAT, ClkStatus);
}

uint32_t RCU_GetSysClkFreq(void);

/**
  * @brief   Включение системы слежения за системным тактовым сигналом
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SecurityCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->SYSCLKCFG_bit.SECEN, State);
}

/**
  * @brief   Настройка периода срабатывания системы слежения
  * @param   HsePrd  Максимальное значение счетчика слежения за сигналом HSeCLK
  * @param   SysPLL0Prd  Максимальное значение счетчика слежения за сигналом SYSPLL0CLK
  * @param   LsiPrd  Максимальное значение счетчика слежения за сигналом LSICLK
  * @retval  void
  */
__STATIC_INLINE void RCU_SecurityConfig(uint32_t HsePrd, uint32_t SysPLL0Prd, uint32_t LsiPrd)
{
    assert_param(IS_RCU_SECPRD(HsePrd));
    assert_param(IS_RCU_SECPRD(SysPLL0Prd));
    assert_param(IS_RCU_SECPRD(LsiPrd));

    WRITE_REG(RCU->SECCNT0, (HsePrd << RCU_SECCNT0_VAL1_Pos));
    WRITE_REG(RCU->SECCNT1, (LsiPrd << RCU_SECCNT1_VAL3_Pos)|SysPLL0Prd);
}

/**
  * @brief   Получение статуса выбранного типа сброса
  * @param   RstStatus  Выбранный тип сброса. Любая совокупность значений значений RCU_RstStatus_x (@ref RCU_RstStatus_Define).
  * @retval  Status  Статус активности
  */
__STATIC_INLINE FlagStatus RCU_RstStatus(uint32_t RstStatus)
{
    return (FlagStatus)READ_BIT(RCU->RSTSTAT, RstStatus);
}

/**
  * @brief   Очистка статуса выбранного типа сброса
  * @param   RstStatus  Выбранный тип сброса. Любая совокупность значений значений RCU_RstStatus_x (@ref RCU_RstStatus_Define).
  * @retval  void
  */
__STATIC_INLINE void RCU_RstStatusClear(uint32_t RstStatus)
{
    assert_param(IS_RCU_RST_STATUS(RstStatus));

    WRITE_REG(RCU->RSTSTAT, RstStatus);
}

OperationStatus RCU_SysClkChangeCmd(RCU_SysClk_TypeDef SysClk);

/** @defgroup RCU_Init_Deinit Конфигурация PLL
  * @{
  */

//OperationStatus RCU_PLL_AutoConfig(uint32_t SysClkFreq, RCU_PLL_Ref_TypeDef Ref);
OperationStatus RCU_SYSPLL0_Init(RCU_PLL_Init_TypeDef* InitStruct);
OperationStatus RCU_USBPLL_Init(RCU_PLL_Init_TypeDef* InitStruct);
void RCU_SYSPLL_DeInit(void);
void RCU_USBPLL_DeInit(void);
void RCU_PLL_StructInit(RCU_PLL_Init_TypeDef* InitStruct);

/**
  * @brief   Разрешение работы выхода SYSPLL0
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SYSPLL0_OutCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));
    if(State)  SET_BIT(RCU->PLLSYSCFG0, (1 << RCU_PLLSYSCFG0_FOUTEN_Pos));
      else   CLEAR_BIT(RCU->PLLSYSCFG0, (1 << RCU_PLLSYSCFG0_FOUTEN_Pos));
}

/**
  * @brief   Разрешение работы выхода SYSPLL1
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SYSPLL1_OutCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));
    if(State)  SET_BIT(RCU->PLLSYSCFG0, (2 << RCU_PLLSYSCFG0_FOUTEN_Pos));
      else   CLEAR_BIT(RCU->PLLSYSCFG0, (2 << RCU_PLLSYSCFG0_FOUTEN_Pos));
}

/**
  * @brief   Разрешение работы SYSPLL
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SYSPLL_Cmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(State)  MODIFY_REG(RCU->PLLSYSCFG0, RCU_PLLSYSCFG0_PLLEN_Msk,0x01);
      else   MODIFY_REG(RCU->PLLSYSCFG0, RCU_PLLSYSCFG0_PLLEN_Msk,0x00);
}

/**
  * @brief   Включение режима bypass SYSPLL0
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SYSPLL0_BypassCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(State)  SET_BIT(RCU->PLLSYSCFG0, (1 << RCU_PLLSYSCFG0_BYP_Pos));
      else   CLEAR_BIT(RCU->PLLSYSCFG0, (1 << RCU_PLLSYSCFG0_BYP_Pos));
}

/**
  * @brief   Включение режима bypass SYSPLL1
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SYSPLL1_BypassCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(State)  SET_BIT(RCU->PLLSYSCFG0, (2 << RCU_PLLSYSCFG0_BYP_Pos));
      else   CLEAR_BIT(RCU->PLLSYSCFG0, (2 << RCU_PLLSYSCFG0_BYP_Pos));
}

/**
  * @brief   Получение статуса захвата частоты SYSPLL
  * @retval  Status  Статус захвата
  */
__STATIC_INLINE FlagStatus RCU_SYSPLL_LockStatus(void)
{
    return (FlagStatus)READ_BIT(RCU->PLLSYSSTAT, RCU_PLLSYSSTAT_LOCK_Msk);
}

/**
  * @brief   Разрешение работы выхода USBPLL
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_USBPLL_OutCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));
    if(State)  MODIFY_REG(USB->PLLUSBCFG0, USB_PLLUSBCFG0_FOUTEN_Msk,0x01);
      else   MODIFY_REG(USB->PLLUSBCFG0, USB_PLLUSBCFG0_FOUTEN_Msk,0x0);
}

/**
  * @brief   Включение режима bypass USBPLL
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_USBPLL_BypassCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(State)  SET_BIT(USB->PLLUSBCFG0, (1 << USB_PLLUSBCFG0_BYP_Pos));
      else   CLEAR_BIT(USB->PLLUSBCFG0, (1 << USB_PLLUSBCFG0_BYP_Pos));
}

/**
  * @brief   Получение статуса захвата частоты USBPLL
  * @retval  Status  Статус захвата
  */
__STATIC_INLINE FlagStatus RCU_USBPLL_LockStatus(void)
{
    return (FlagStatus)READ_BIT(USB->PLLUSBSTAT, USB_PLLUSBSTAT_LOCK_Msk);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_Config_ClkOut Настройка выдачи тактового сигнала CLKOUT
  * @{
  */

uint32_t RCU_GetClkOutFreq(void);

/**
  * @brief   Настройка тактирования ClkOut
  * @param   ClkOut  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_ClkOutConfig(RCU_ClkoutClk_TypeDef ClkOut, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_CLKOUT_CLK(ClkOut));
    assert_param(IS_RCU_CLKOUT_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->CLKOUTCFG, (RCU_CLKOUTCFG_CLKSEL_Msk | RCU_CLKOUTCFG_DIVN_Msk | RCU_CLKOUTCFG_DIVEN_Msk),
               ((ClkOut << RCU_CLKOUTCFG_CLKSEL_Pos) | (DivVal << RCU_CLKOUTCFG_DIVN_Pos) | (DivState << RCU_CLKOUTCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования ClkOut
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_ClkOutCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->CLKOUTCFG_bit.CLKEN, State);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_RST_Config_UART Тактирование и сброс UART
  * @{
  */

uint32_t RCU_GetUARTClkFreq(UART_Num_TypeDef UARTx_Num);

/**
  * @brief   Настройка тактирования UART
  * @param   UARTx_Num  Порядковый номер блока UART
  * @param   UARTClk  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_UARTClkConfig(UART_Num_TypeDef UARTx_Num, RCU_PeriphClk_TypeDef UARTClk, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_PERIPH_CLK(UARTClk));
    assert_param(IS_RCU_PERIPH_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG, (RCU_UARTCLKCFG_CLKSEL_Msk | RCU_UARTCLKCFG_DIVN_Msk | RCU_UARTCLKCFG_DIVEN_Msk),
               ((UARTClk << RCU_UARTCLKCFG_CLKSEL_Pos) | (DivVal << RCU_UARTCLKCFG_DIVN_Pos) | (DivState << RCU_UARTCLKCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования UART
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_UARTClkCmd(UART_Num_TypeDef UARTx_Num, FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG_bit.CLKEN, State);
}

/**
  * @brief   Cнятие сброса UART
  * @param   UARTx_Num  Порядковый номер блока UART
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_UARTRstCmd(UART_Num_TypeDef UARTx_Num, FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->UARTCLKCFG[UARTx_Num].UARTCLKCFG_bit.RSTDIS, State);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_RST_Config_SPI Тактирование и сброс SPI
  * @{
  */

uint32_t RCU_GetSPIClkFreq(SPI_Num_TypeDef SPIx_Num);

/**
  * @brief   Настройка тактирования SPI
  * @param   SPIx_Num  Порядковый номер блока SPI
  * @param   SPIClk  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_SPIClkConfig(SPI_Num_TypeDef SPIx_Num, RCU_PeriphClk_TypeDef SPIClk, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_PERIPH_CLK(SPIClk));
    assert_param(IS_RCU_PERIPH_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG, (RCU_SPICLKCFG_CLKSEL_Msk | RCU_SPICLKCFG_DIVN_Msk | RCU_SPICLKCFG_DIVEN_Msk),
               ((SPIClk << RCU_SPICLKCFG_CLKSEL_Pos) | (DivVal << RCU_SPICLKCFG_DIVN_Pos) | (DivState << RCU_SPICLKCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования SPI
  * @param   SPIx_Num  Порядковый номер блока SPI
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SPIClkCmd(SPI_Num_TypeDef SPIx_Num, FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG_bit.CLKEN, State);
}

/**
  * @brief   Cнятие сброса SPI
  * @param   SPIx_Num  Порядковый номер блока SPI
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_SPIRstCmd(SPI_Num_TypeDef SPIx_Num, FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->SPICLKCFG[SPIx_Num].SPICLKCFG_bit.RSTDIS, State);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_RST_Config_WDT Тактирование и сброс WDT
  * @{
  */

uint32_t RCU_GetWDTClkFreq(void);

/**
  * @brief   Настройка тактирования сторожевого таймера
  * @param   WDTClk  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_WDTClkConfig(RCU_PeriphClk_TypeDef WDTClk, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_PERIPH_CLK(WDTClk));
    assert_param(IS_RCU_PERIPH_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->WDOGCLKCFG, (RCU_WDOGCLKCFG_CLKSEL_Msk | RCU_WDOGCLKCFG_DIVN_Msk | RCU_WDOGCLKCFG_DIVEN_Msk),
               ((WDTClk << RCU_WDOGCLKCFG_CLKSEL_Pos) | (DivVal << RCU_WDOGCLKCFG_DIVN_Pos) | (DivState << RCU_WDOGCLKCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования сторожевого таймера
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_WDTClkCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->WDOGCLKCFG_bit.CLKEN, State);
}

/**
  * @brief   Cнятие сброса сторожевого таймера
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_WDTRstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->WDOGCLKCFG_bit.RSTDIS, State);
}

/**
  * @}
  */

 /** @defgroup RCU_CLK_RST_Config_IWDT Тактирование и сброс IWDT
  * @{
  */

uint32_t RCU_GetIWDTClkFreq(void);

/**
  * @brief   Настройка тактирования независимого сторожевого таймера
  * @param   IWDTClk  Источник тактового сигнала
  * @retval  void
  */
__STATIC_INLINE void RCU_IWDTClkConfig(RCU_IWDTClk_TypeDef IWDTClk)
{
    assert_param(IS_RCU_IWDT_CLK(IWDTClk));

    MODIFY_REG(PMURTC->IWDG_CFG, (PMURTC_IWDG_CFG_CLKSRC_Msk),
               ((IWDTClk << PMURTC_IWDG_CFG_CLKSRC_Pos)));
}

/**
  * @brief   Cнятие сброса независимого сторожевого таймера
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_IWDTRstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(PMURTC->IWDG_CFG_bit.RSTDIS, State);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_RST_Config_ADCSAR Тактирование и сброс ADCSAR
  * @{
  */

uint32_t RCU_GetADCSARClkFreq(void);

/**
  * @brief   Настройка тактирования АЦП
  * @param   ADCSARClk  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSARClkConfig(RCU_PeriphClk_TypeDef ADCSARClk, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_PERIPH_CLK(ADCSARClk));
    assert_param(IS_RCU_PERIPH_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->ADCSARCLKCFG, (RCU_ADCSARCLKCFG_CLKSEL_Msk | RCU_ADCSARCLKCFG_DIVN_Msk | RCU_ADCSARCLKCFG_DIVEN_Msk),
               ((ADCSARClk << RCU_ADCSARCLKCFG_CLKSEL_Pos) | (DivVal << RCU_ADCSARCLKCFG_DIVN_Pos) | (DivState << RCU_ADCSARCLKCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования АЦП
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSARClkCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->ADCSARCLKCFG_bit.CLKEN, State);
}

/**
  * @brief   Cнятие сброса АЦП
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSARRstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->ADCSARCLKCFG_bit.RSTDIS, State);
}

/**
  * @}
  */

/** @defgroup RCU_CLK_RST_Config_ADCSD Тактирование и сброс ADCSD
  * @{
  */

uint32_t RCU_GetADCSDClkFreq(void);

/**
  * @brief   Настройка тактирования АЦП сигма-дельта
  * @param   ADCSDClk  Источник тактового сигнала
  * @param   DivVal  Значение делителя (деление на 2*(DivVal+1))
  * @param   DivState  Разрешение работы делителя
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSDClkConfig(RCU_PeriphClk_TypeDef ADCSDClk, uint32_t DivVal, FunctionalState DivState)
{
    assert_param(IS_RCU_PERIPH_CLK(ADCSDClk));
    assert_param(IS_RCU_PERIPH_DIV(DivVal));
    assert_param(IS_FUNCTIONAL_STATE(DivState));

    MODIFY_REG(RCU->ADCSDCLKCFG, (RCU_ADCSDCLKCFG_CLKSEL_Msk | RCU_ADCSDCLKCFG_DIVN_Msk | RCU_ADCSDCLKCFG_DIVEN_Msk),
               ((ADCSDClk << RCU_ADCSDCLKCFG_CLKSEL_Pos) | (DivVal << RCU_ADCSDCLKCFG_DIVN_Pos) | (DivState << RCU_ADCSDCLKCFG_DIVEN_Pos)));
}

/**
  * @brief   Включение тактирования АЦП сигма-дельта
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSDClkCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->ADCSDCLKCFG_bit.CLKEN, State);
}

/**
  * @brief   Cнятие сброса АЦП сигма-дельта
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void RCU_ADCSDRstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(RCU->ADCSDCLKCFG_bit.RSTDIS, State);
}

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_RCU_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2025 NIIET *****END OF FILE****/

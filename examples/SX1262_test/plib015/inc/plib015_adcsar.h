/**
  ******************************************************************************
  * @file    plib015_adcsar.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          ADCSAR, а также сопутствующие макроопределения и перечисления
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
  * <h2><center>&copy; 2024 АО "НИИЭТ"</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLIB015_ADCSAR_H
#define __PLIB015_ADCSAR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup ADCSAR
  * @brief Драйвер для работы с ADCSAR
  * @{
  */

/** @defgroup ADCSAR_Exported_Defines Константы
  * @{
  */

#define ADCSAR_SEQ_Total 2UL
#define ADCSAR_SEQ_Req_Total 8UL
#define ADCSAR_DC_Total 8UL
#define ADCSAR_CH_Total 11UL

/**
  * @}
  */

/** @defgroup ADCSAR_Exported_Types Типы
  * @{
  */

/**
  * @brief  Разрядность измерения АЦП
  */
typedef enum {
    ADCSAR_AM_Resolution_6bit = ADCSAR_ACTL_SELRES_6bit,   /*!< 6 бит */
    ADCSAR_AM_Resolution_8bit = ADCSAR_ACTL_SELRES_8bit,   /*!< 8 бит */
    ADCSAR_AM_Resolution_10bit = ADCSAR_ACTL_SELRES_10bit, /*!< 10 бит */
    ADCSAR_AM_Resolution_12bit = ADCSAR_ACTL_SELRES_12bit, /*!< 12 бит */
} ADCSAR_AM_Resolution_TypeDef;
#define IS_ADCSAR_AM_RESOLUTION(VALUE) (((VALUE) == ADCSAR_AM_Resolution_6bit) ||  \
                                     ((VALUE) == ADCSAR_AM_Resolution_8bit) ||  \
                                     ((VALUE) == ADCSAR_AM_Resolution_10bit) || \
                                     ((VALUE) == ADCSAR_AM_Resolution_12bit))

/**
  * @brief  Номер секвенсора
  */
typedef enum {
    ADCSAR_SEQ_Num_0, /*!< Севенсор 0 */
    ADCSAR_SEQ_Num_1  /*!< Севенсор 1 */
} ADCSAR_SEQ_Num_TypeDef;
#define IS_ADCSAR_SEQ_NUM(VALUE) (((VALUE) == ADCSAR_SEQ_Num_0) || \
                               ((VALUE) == ADCSAR_SEQ_Num_1))

/**
  * @brief  Номер запроса в очереди секвенсора
  */
typedef enum {
    ADCSAR_SEQ_ReqNum_0,  /*!< Запрос 0 */
    ADCSAR_SEQ_ReqNum_1,  /*!< Запрос 1 */
    ADCSAR_SEQ_ReqNum_2,  /*!< Запрос 2 */
    ADCSAR_SEQ_ReqNum_3,  /*!< Запрос 3 */
    ADCSAR_SEQ_ReqNum_4,  /*!< Запрос 4 */
    ADCSAR_SEQ_ReqNum_5,  /*!< Запрос 5 */
    ADCSAR_SEQ_ReqNum_6,  /*!< Запрос 6 */
    ADCSAR_SEQ_ReqNum_7   /*!< Запрос 7 */
} ADCSAR_SEQ_ReqNum_TypeDef;
#define IS_ADCSAR_SEQ_REQ_NUM(VALUE) (((VALUE) == ADCSAR_SEQ_ReqNum_0) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_1) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_2) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_3) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_4) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_5) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_6) ||  \
                                   ((VALUE) == ADCSAR_SEQ_ReqNum_7))

/**
  * @brief  События запуска секвенсоров
  */
typedef enum {
    ADCSAR_SEQ_StartEvent_SwReq = ADCSAR_EMUX_EM0_SwReq,       /*!< Запуск по программному запросу */
    ADCSAR_SEQ_StartEvent_TMR32 = ADCSAR_EMUX_EM0_TMR32,       /*!< Сигнал от таймера TMR32 */
    ADCSAR_SEQ_StartEvent_TMR0 = ADCSAR_EMUX_EM0_TMR0,         /*!< Сигнал от таймера TMR0 */
    ADCSAR_SEQ_StartEvent_TMR1 = ADCSAR_EMUX_EM0_TMR1,         /*!< Сигнал от таймера TMR1 */
    ADCSAR_SEQ_StartEvent_TMR2 = ADCSAR_EMUX_EM0_TMR2,         /*!< Сигнал от таймера TMR2 */
    ADCSAR_SEQ_StartEvent_GPIOA = ADCSAR_EMUX_EM0_GPIOA,       /*!< Сигнал от GPIOA */
    ADCSAR_SEQ_StartEvent_GPIOB = ADCSAR_EMUX_EM0_GPIOB,       /*!< Сигнал от GPIOB */
    ADCSAR_SEQ_StartEvent_GPIOC = ADCSAR_EMUX_EM0_GPIOC,       /*!< Сигнал от GPIOC */
    ADCSAR_SEQ_StartEvent_Cycle = ADCSAR_EMUX_EM0_Cycle,       /*!< Циклическая работа сразу после запуска секвенсора */
} ADCSAR_SEQ_StartEvent_TypeDef;
#define IS_ADCSAR_SEQ_START_EVENT(VALUE) (((VALUE) == ADCSAR_SEQ_StartEvent_SwReq) || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_TMR32) || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_TMR0)  || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_TMR1)  || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_TMR2)  || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_GPIOA) || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_GPIOB) || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_GPIOC) || \
                                       ((VALUE) == ADCSAR_SEQ_StartEvent_Cycle))

/**
  * @brief  Количество измерений для усреднения
  */
typedef enum {
    ADCSAR_SEQ_Average_2 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average2,   /*!< Усреднение по 2 измерениям */
    ADCSAR_SEQ_Average_4 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average4,   /*!< Усреднение по 4 измерениям */
    ADCSAR_SEQ_Average_8 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average8,   /*!< Усреднение по 8 измерениям */
    ADCSAR_SEQ_Average_16 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average16, /*!< Усреднение по 16 измерениям */
    ADCSAR_SEQ_Average_32 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average32, /*!< Усреднение по 32 измерениям */
    ADCSAR_SEQ_Average_64 = ADCSAR_SEQ_SRQCTL_QAVGVAL_Average64, /*!< Усреднение по 64 измерениям */
} ADCSAR_SEQ_Average_TypeDef;
#define IS_ADCSAR_SEQ_AVERAGE(VALUE) (((VALUE) == ADCSAR_SEQ_Average_2) ||  \
                                   ((VALUE) == ADCSAR_SEQ_Average_4) ||  \
                                   ((VALUE) == ADCSAR_SEQ_Average_8) ||  \
                                   ((VALUE) == ADCSAR_SEQ_Average_16) || \
                                   ((VALUE) == ADCSAR_SEQ_Average_32) || \
                                   ((VALUE) == ADCSAR_SEQ_Average_64))

/**
  * @brief  Количество результатов измерений записанных в буфер секвенсора, по достижению которого вызывается DMA
  */
typedef enum {
    ADCSAR_SEQ_DMAFIFOLevel_1 = ADCSAR_SEQ_SDMACTL_WMARK_Level1,   /*!< Запрос DMA после заполнения 1 ячейки в буффере */
    ADCSAR_SEQ_DMAFIFOLevel_2 = ADCSAR_SEQ_SDMACTL_WMARK_Level2,   /*!< Запрос DMA после заполнения 2 ячеек в буффере */
    ADCSAR_SEQ_DMAFIFOLevel_4 = ADCSAR_SEQ_SDMACTL_WMARK_Level4,   /*!< Запрос DMA после заполнения 4 ячеек в буффере */
    ADCSAR_SEQ_DMAFIFOLevel_8 = ADCSAR_SEQ_SDMACTL_WMARK_Level8,   /*!< Запрос DMA после заполнения 8 ячеек в буффере */
    ADCSAR_SEQ_DMAFIFOLevel_16 = ADCSAR_SEQ_SDMACTL_WMARK_Level16, /*!< Запрос DMA после заполнения 16 ячеек в буффере */
    ADCSAR_SEQ_DMAFIFOLevel_32 = ADCSAR_SEQ_SDMACTL_WMARK_Level32, /*!< Запрос DMA после заполнения 32 ячеек в буффере */
} ADCSAR_SEQ_DMAFIFOLevel_TypeDef;
#define IS_ADCSAR_SEQ_DMA_FIFO_LEVEL(VALUE) (((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_1) ||  \
                                          ((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_2) ||  \
                                          ((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_4) ||  \
                                          ((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_8) ||  \
                                          ((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_16) || \
                                          ((VALUE) == ADCSAR_SEQ_DMAFIFOLevel_32))

/**
  * @brief Номер цифрового компаратора
  */
typedef enum {
    ADCSAR_DC_Num_0,  /*!< Модуль цифрового компаратора 0 */
    ADCSAR_DC_Num_1,  /*!< Модуль цифрового компаратора 1 */
    ADCSAR_DC_Num_2,  /*!< Модуль цифрового компаратора 2 */
    ADCSAR_DC_Num_3,  /*!< Модуль цифрового компаратора 3 */
    ADCSAR_DC_Num_4,  /*!< Модуль цифрового компаратора 4 */
    ADCSAR_DC_Num_5,  /*!< Модуль цифрового компаратора 5 */
    ADCSAR_DC_Num_6,  /*!< Модуль цифрового компаратора 6 */
    ADCSAR_DC_Num_7,  /*!< Модуль цифрового компаратора 7 */
} ADCSAR_DC_Num_TypeDef;
#define IS_ADCSAR_DC_NUM(VALUE) (((VALUE) == ADCSAR_DC_Num_0) ||  \
                              ((VALUE) == ADCSAR_DC_Num_1) ||  \
                              ((VALUE) == ADCSAR_DC_Num_2) ||  \
                              ((VALUE) == ADCSAR_DC_Num_3) ||  \
                              ((VALUE) == ADCSAR_DC_Num_4) ||  \
                              ((VALUE) == ADCSAR_DC_Num_5) ||  \
                              ((VALUE) == ADCSAR_DC_Num_6) ||  \
                              ((VALUE) == ADCSAR_DC_Num_7))

/**
  * @brief  Режим срабатывания цифрового компаратора
  */
typedef enum {
    ADCSAR_DC_Mode_Multiple = ADCSAR_DC_DCTL_CIM_Multiple,         /*!< Многократный */
    ADCSAR_DC_Mode_Single = ADCSAR_DC_DCTL_CIM_Single,             /*!< Однократный */
    ADCSAR_DC_Mode_MultipleHyst = ADCSAR_DC_DCTL_CIM_MultipleHyst, /*!< Многократный с гистерезисом */
    ADCSAR_DC_Mode_SingleHyst = ADCSAR_DC_DCTL_CIM_SingleHyst,     /*!< Однократный с гистерезисом */
} ADCSAR_DC_Mode_TypeDef;
#define IS_ADCSAR_DC_MODE(VALUE) (((VALUE) == ADCSAR_DC_Mode_Single) ||     \
                               ((VALUE) == ADCSAR_DC_Mode_Multiple) ||   \
                               ((VALUE) == ADCSAR_DC_Mode_SingleHyst) || \
                               ((VALUE) == ADCSAR_DC_Mode_MultipleHyst))

/**
  * @brief  Условие срабатывания компаратора
  */
typedef enum {
    ADCSAR_DC_Condition_Low = ADCSAR_DC_DCTL_CIC_Low,       /*!< Результат меньше либо равен нижней границе */
    ADCSAR_DC_Condition_Window = ADCSAR_DC_DCTL_CIC_Window, /*!< Результат внутри диапазона, задаваемого границами, либо равен одной из них */
    ADCSAR_DC_Condition_High = ADCSAR_DC_DCTL_CIC_High,     /*!< Результат больше либо равен верхней границе */
} ADCSAR_DC_Condition_TypeDef;
#define IS_ADCSAR_DC_CONDITION(VALUE) (((VALUE) == ADCSAR_DC_Condition_Low) ||    \
                                    ((VALUE) == ADCSAR_DC_Condition_Window) || \
                                    ((VALUE) == ADCSAR_DC_Condition_High))

/**
  * @brief  Источник данных для компаратора
  */
typedef enum {
    ADCSAR_DC_Source_EOC,  /*!< Ококнчание измерения АЦП */
    ADCSAR_DC_Source_FIFO, /*!< Запись результатат в FIFO */
} ADCSAR_DC_Source_TypeDef;
#define IS_ADCSAR_DC_SOURCE(VALUE) (((VALUE) == ADCSAR_DC_Source_EOC) || \
                                 ((VALUE) == ADCSAR_DC_Source_FIFO))

/**
  * @brief  Номер канала
  */
typedef enum {
    ADCSAR_CH_Num_0,  /*!< Канал 0 */
    ADCSAR_CH_Num_1,  /*!< Канал 1 */
    ADCSAR_CH_Num_2,  /*!< Канал 2 */
    ADCSAR_CH_Num_3,  /*!< Канал 3 */
    ADCSAR_CH_Num_4,  /*!< Канал 4 */
    ADCSAR_CH_Num_5,  /*!< Канал 5 */
    ADCSAR_CH_Num_6,  /*!< Канал 6 */
    ADCSAR_CH_Num_7,  /*!< Канал 7 */
    ADCSAR_TSENS = 10,  /*!< Канал 10 - канал измерения датчика TSENS */

} ADCSAR_CH_Num_TypeDef;
#define IS_ADCSAR_CH_NUM(VALUE) (((VALUE) == ADCSAR_CH_Num_0) ||  \
                              ((VALUE) == ADCSAR_CH_Num_1) ||  \
                              ((VALUE) == ADCSAR_CH_Num_2) ||  \
                              ((VALUE) == ADCSAR_CH_Num_3) ||  \
                              ((VALUE) == ADCSAR_CH_Num_4) ||  \
                              ((VALUE) == ADCSAR_CH_Num_5) ||  \
                              ((VALUE) == ADCSAR_CH_Num_6) ||  \
                              ((VALUE) == ADCSAR_CH_Num_7) ||  \
                              ((VALUE) == ADCSAR_TSENS))

/**
  * @brief  Выбор приоритета канала
  */
typedef enum {
    ADCSAR_CH_Priority_Normal, /*!< Обычный уровень приоритета */
    ADCSAR_CH_Priority_High,   /*!< Высокий уровень приоритета */
} ADCSAR_CH_Priority_TypeDef;
#define IS_ADCSAR_CH_PRIORITY(VALUE) (((VALUE) == ADCSAR_CH_Priority_Normal) || \
                                   ((VALUE) == ADCSAR_CH_Priority_High))

/**
  * @brief  Структура инициализации цифровых компараторов
  */
typedef struct
{
    FunctionalState DCOutput;           /*!< Разрешает работу выходному триггеру компаратора */
    uint32_t ThresholdLow;              /*!< Нижний порог срабатывания компаратора.
                                             Параметр может принимать любое значение из диапазона 0 - 4095. */
    uint32_t ThresholdHigh;             /*!< Верхний порог срабатывания компаратора.
                                             Параметр может принимать любое значение из диапазона 0 - 4095. */
    ADCSAR_DC_Source_TypeDef Source;       /*!< Выбирает источник получения измерения */
    ADCSAR_CH_Num_TypeDef Channel;         /*!< Выбирает канал, результат измерения которого будет передан на компаратор */
    ADCSAR_DC_Mode_TypeDef Mode;           /*!< Выбирает режим срабатывания компаратора */
    ADCSAR_DC_Condition_TypeDef Condition; /*!< Выбирает условие срабатывания компаратора */
} ADCSAR_DC_Init_TypeDef;

#define IS_ADCSAR_DC_THRESHOLD(VALUE) ((VALUE) < 0x1000)

/**
  * @brief  Структура инициализации секвенсоров
  */
typedef struct
{
    ADCSAR_SEQ_StartEvent_TypeDef StartEvent;     /*!< Определяет cобытие запуска секвенсора */
    FunctionalState SWStartEn;                 /*!< Разрешает секвенсору запускаться по программному запросу */
    ADCSAR_CH_Num_TypeDef Req[ADCSAR_SEQ_Req_Total]; /*!< Выбор каналов для запросов секвенсора */
    ADCSAR_SEQ_ReqNum_TypeDef ReqMax;             /*!< Настройка глубины очереди запросов */
    ADCSAR_SEQ_Average_TypeDef ReqAverage;        /*!< Настройка усреднения сканированием очереди запросов */
    FunctionalState ReqAverageEn;              /*!< Разрешение усреднения сканированием очереди запросов */
    uint32_t RestartCount;                     /*!< Задание количества перезапусков модулей АЦП секвенсором после его запуска по событию.
                                                         0x00 - без перезапусков, 0x01 - 1 перезапуск, 0xFF - 255 перезапусков. */
    FunctionalState RestartAverageEn;          /*!< Разрешение усреднения по перезапускам */
    uint32_t RestartTimer;                     /*!< Задание задержки запуска модуля АЦП.
                                                         Параметр может принимать любое значение из диапазона 0x00000000 - 0x00FFFFFF. */
    FunctionalState DCEn[ADCSAR_DC_Total];        /*!< Разрешение работы цифровых компараторов секвенсором */
    ADCSAR_SEQ_DMAFIFOLevel_TypeDef DMAFIFOLevel; /*!< Настройка уровня заполненности буфера для генерации запросов DMA */
    FunctionalState DMAEn;                     /*!< Разрешение генерации запросов DMA */
} ADCSAR_SEQ_Init_TypeDef;

#define IS_ADCSAR_SEQ_RESTART_VAL(VALUE) ((VALUE) < 0x100)
#define IS_ADCSAR_SEQ_RESTART_TIMER_VAL(VALUE) ((VALUE) < 0x1000000)
#define IS_ADCSAR_SEQ_IT_COUNT_VAL(VALUE) ((VALUE) < 0x100)

/**
  * @}
  */

/** @defgroup ADCSAR_Exported_Functions Функции
  * @{
  */

void ADCSAR_DeInit();
void ADCSAR_SEQ_ReqConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_ReqNum_TypeDef ReqNum, ADCSAR_CH_Num_TypeDef Channel_Num);
void ADCSAR_SEQ_Init(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_Init_TypeDef* InitStruct);
void ADCSAR_SEQ_StructInit(ADCSAR_SEQ_Init_TypeDef* InitStruct);
void ADCSAR_DC_Init(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_DC_Init_TypeDef* InitStruct);
void ADCSAR_DC_StructInit(ADCSAR_DC_Init_TypeDef* InitStruct);

/**
  * @brief   Включение аналогового модуля АЦП
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_AM_Cmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->ACTL_bit.ADCEN, State);
}

/**
  * @brief   Настройка разрядности аналогового модуля АЦП
  * @param   Resolution  Выбор разрядности
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_AM_ResolutionConfig(ADCSAR_AM_Resolution_TypeDef Resolution)
{
    assert_param(IS_ADCSAR_AM_RESOLUTION(Resolution));

    WRITE_REG(ADCSAR->ACTL_bit.SELRES, Resolution);
}

/**
  * @brief   Получение значения разрядности аналогового модуля АЦП
  * @retval  Resolution разрядность АЦП
  */
__STATIC_INLINE uint32_t ADCSAR_AM_GetResolution(void)
{
    assert_param(IS_ADCSAR_AM_RESOLUTION(Resolution));

	return (uint32_t) READ_REG(ADCSAR->ACTL_bit.SELRES);
}

/**
  * @brief   Включение схемы внутренней калибровки аналогового модуля АЦП
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_AM_CalibCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->ACTL_bit.CALEN, State);
}

/**
  * @brief   Запуск схемы внутренней калибровки аналогового модуля АЦП
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_AM_CalibStartCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->ACTL_bit.CALSTART, State);
}

/**
  * @brief   Флаг активности калибровки
  * @retval  State состояние калибровки
  */
__STATIC_INLINE FunctionalState ADCSAR_AM_CalibStatus(void)
{
    return (FunctionalState) READ_BIT(ADCSAR->ACTL, ADCSAR_ACTL_CALBUSY_Msk);
}

/**
  * @brief   Внесение поправочного значения во внутреннюю схему калибровки
  * @param   Val  Значение. Диапазон значений -64…63, величина в
                  дополнительном коде.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_AM_SetCalibVal(uint32_t Val)
{
    WRITE_REG(ADCSAR->ACTL_bit.CALIN, Val);
    WRITE_REG(ADCSAR->ACTL_bit.CALLOAD, 1);
}

/**
  * @brief   Получение поправочного значения, полученного в результате внутренней калибровки
  * @retval  Val  Значение. Диапазон значений -64…63, величина в
                  дополнительном коде.
  */
__STATIC_INLINE uint32_t ADCSAR_AM_GetCalibVal()
{
    return READ_REG(ADCSAR->ACTL_bit.CALOUT);
}

/**
  * @brief   Чтение статуса готовности аналогового модуля АЦП. Флаг становится активным после того,
  *          как модуль АЦП провел внутренние процедуры иницализации.
  * @retval  Status  Статус готовности
  */
__STATIC_INLINE FlagStatus ADCSAR_AM_ReadyStatus()
{
    return (FlagStatus)READ_REG(ADCSAR->ACTL_bit.ADCRDY);
}

/**
  * @brief   Чтение статуса занятости аналогового модуля АЦП. Флаг становится активным при
  *          проведении измерения.
  * @retval  Status  Статус занятости
  */
__STATIC_INLINE FlagStatus ADCSAR_AM_BusyStatus()
{
    return (FlagStatus)READ_BIT(ADCSAR->BSTAT, ADCSAR_BSTAT_ADCBUSY_Msk);
}

/**
  * @brief   Настройка приоритета канала АЦП
  * @param   Channel_Num  Выбор канала
  * @param   Priority  Выбор приоритета
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_CH_PriorityConfig(ADCSAR_CH_Num_TypeDef Channel_Num, ADCSAR_CH_Priority_TypeDef Priority)
{
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));
    assert_param(IS_ADCSAR_CH_PRIORITY(Priority));

    WRITE_REG(ADCSAR->CHCTL[Channel_Num].CHCTL_bit.PRIORITY, Priority);
}

/**
  * @brief   Получение текущего значения коэффициента коррекции ошибки усиления
  * @param   Channel_Num  Выбор канала
  * @retval  Val  Значение. Диапазон значений -256…255, величина в
                  дополнительном коде: 100h соответствует -256, 000h - 0, 0FFh - 255.
  */
__STATIC_INLINE uint32_t ADCSAR_CH_GetGainTrim(ADCSAR_CH_Num_TypeDef Channel_Num)
{
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));

    return READ_REG(ADCSAR->CHCTL[Channel_Num].CHCTL_bit.GAINTRIM);
}

/**
  * @brief   Установка значения коэффициента коррекции ошибки усиления
  * @param   Channel_Num  Выбор канала
  * @param   Val  Значение. Диапазон значений -256…255, величина в
                  дополнительном коде: 100h соответствует -256, 000h - 0, 0FFh - 255.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_CH_SetGainTrim(ADCSAR_CH_Num_TypeDef Channel_Num, uint32_t Val)
{
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));

    WRITE_REG(ADCSAR->CHCTL[Channel_Num].CHCTL_bit.GAINTRIM, Val);
}

/**
  * @brief   Получение текущего значения коэффициента коррекции ошибки смещения нуля
  * @param   Channel_Num  Выбор канала
  * @retval  Val  Значение. Диапазон значений -256…255, величина в
                  дополнительном коде: 100h соответствует -256, 000h - 0, 0FFh - 255.
  */
__STATIC_INLINE uint32_t ADCSAR_CH_GetOffsetTrim(ADCSAR_CH_Num_TypeDef Channel_Num)
{
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));

    return READ_REG(ADCSAR->CHCTL[Channel_Num].CHCTL_bit.OFFTRIM);
}

/**
  * @brief   Установка значения коэффициента коррекции ошибки смещения нуля
  * @param   Channel_Num  Выбор канала
  * @param   Val  Значение. Диапазон значений -256…255, величина в
                  дополнительном коде: 100h соответствует -256, 000h - 0, 0FFh - 255.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_CH_SetOffsetTrim(ADCSAR_CH_Num_TypeDef Channel_Num, uint32_t Val)
{
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));

    WRITE_REG(ADCSAR->CHCTL[Channel_Num].CHCTL_bit.OFFTRIM, Val);
}

/** @defgroup ADCSAR_Exported_Functions_Init_SEQ Секвенсоры
  * @{
  */

void ADCSAR_SEQ_Init(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_Init_TypeDef* InitStruct);
void ADCSAR_SEQ_StructInit(ADCSAR_SEQ_Init_TypeDef* InitStruct);

/**
  * @brief   Включение модуля секвенсора АЦП
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_Cmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(ADCSAR->SEQEN, 1 << (uint32_t)SEQ_Num, State << (uint32_t)SEQ_Num);
}

/**
  * @brief   Включение программного запуска секвенсора АЦП
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_SwStartEnCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(ADCSAR->SEQSYNC, 1 << (uint32_t)SEQ_Num, State << (uint32_t)SEQ_Num);
}

/**
  * @brief   Генерация импульса программного запуска
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_SwStartCmd(void)
{
    WRITE_REG(ADCSAR->SEQSYNC_bit.GSYNC, 1);
}

/**
  * @brief   Чтение статуса занятости секвенсора. Флаг становится активным при
  *          проведении запусков/перезапусков.
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Статус занятости
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_BusyStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->BSTAT, 1 << (uint32_t)SEQ_Num);
}

/**
  * @brief   Чтение статуса заполнения буфера секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Статус заполнения буфера
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_FIFOFullStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_OV0_Pos));
}

/**
  * @brief   Сброс статуса заполнения буфера секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_FIFOFullStatusClear(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    WRITE_REG(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_OV0_Pos));
}

/**
  * @brief   Чтение статуса пустоты буфера секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Статус пустоты буфера
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_FIFOEmptyStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_UN0_Pos));
}

/**
  * @brief   Сброс статуса пустоты буфера секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_FIFOEmptyStatusClear(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    WRITE_REG(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_UN0_Pos));
}

/**
  * @brief   Настройка события запуска секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @param   StartEvent  Выбор события
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_StartEventConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_StartEvent_TypeDef StartEvent)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    MODIFY_REG(ADCSAR->EMUX, 0xF << ((uint32_t)SEQ_Num * 4), StartEvent << ((uint32_t)SEQ_Num * 4));
}

void ADCSAR_SEQ_ReqConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_ReqNum_TypeDef ReqNum, ADCSAR_CH_Num_TypeDef Channel_Num);

/**
  * @brief   Настройка глубины очереди запросов
  * @param   SEQ_Num  Выбор секвенсора
  * @param   ReqNumMax  Номер последнего запроса
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ReqMaxConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_ReqNum_TypeDef ReqNumMax)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_REQ_NUM(ReqNumMax));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SRQCTL_bit.RQMAX, ReqNumMax);
}

/**
  * @brief   Настройка усреднения сканированием очереди запросов
  * @param   SEQ_Num  Выбор секвенсора
  * @param   Average  Выбор режима усреднения
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ReqAverageConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_Average_TypeDef Average)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_AVERAGE(Average));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SRQCTL_bit.QAVGVAL, Average);
}

/**
  * @brief   Включение усреднения сканированием очереди запросов
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ReqAverageCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SRQCTL_bit.QAVGEN, State);
}

/**
  * @brief   Получение текущего номера запроса в очереди
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Номер запроса
  */
__STATIC_INLINE ADCSAR_SEQ_ReqNum_TypeDef ADCSAR_SEQ_GetReqCurrent(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (ADCSAR_SEQ_ReqNum_TypeDef)READ_REG(ADCSAR->SEQ[SEQ_Num].SRQSTAT_bit.RQPTR);
}

/**
  * @brief   Чтение статуса занятости запроса секвенсора. Флаг становится активным при
  *          выставленном запросе.
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Статус занятости
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_ReqBusyStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_REG(ADCSAR->SEQ[SEQ_Num].SRQSTAT_bit.RQBUSY);
}

/**
  * @brief   Настройка генерации запросов DMA
  * @param   SEQ_Num  Выбор секвенсора
  * @param   DMAFIFOLevel  Выбор уровня заполнения буфера для генерации запросов DMA
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_DMAConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_SEQ_DMAFIFOLevel_TypeDef DMAFIFOLevel)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_DMA_FIFO_LEVEL(DMAFIFOLevel));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SDMACTL_bit.WMARK, DMAFIFOLevel);
}

/**
  * @brief   Включение генерации запросов DMA
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_DMACmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SDMACTL_bit.DMAEN, State);
}

/**
  * @brief   Чтение статуса ошибки генерации запросов DMA
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Статус ошибки
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_DMAErrorStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_DOV0_Pos));
}

/**
  * @brief   Сброс статуса ошибки генерации запросов DMA
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_DMAErrorStatusClear(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    WRITE_REG(ADCSAR->FSTAT, 1 << ((uint32_t)SEQ_Num + ADCSAR_FSTAT_DOV0_Pos));
}

/**
  * @brief   Настройка количества перезапусков очереди запросов
  * @param   SEQ_Num  Выбор секвенсора
  * @param   RestartVal  Количество. 0x00 - без перезапусков,
  *                      0x01 - 1 перезапуск, 0xFF - 255 перезапусков.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_RestartConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, uint32_t RestartVal)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_RESTART_VAL(RestartVal));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SCCTL_bit.RCNT, RestartVal);
}

/**
  * @brief   Включение режима усреднения по перезапускам.
  *          При этом количество перезапусков должно равнятся 2^p - 1 (p=1..8).
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_RestartAverageCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SCCTL_bit.RAVGEN, State);
}

/**
  * @brief   Получение текущего количества совершенных перезапусков
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Номер запроса
  */
__STATIC_INLINE uint32_t ADCSAR_SEQ_GetRestartCurrent(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return READ_REG(ADCSAR->SEQ[SEQ_Num].SCVAL_bit.RCNT);
}

/**
  * @brief   Разрешение поступления данных на выбранный цифровой компаратор
  * @param   SEQ_Num  Выбор секвенсора
  * @param   DC_Num  Выбор компаратора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_DCEnableCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, ADCSAR_DC_Num_TypeDef DC_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(ADCSAR->SEQ[SEQ_Num].SDC, 1 << ((uint32_t)DC_Num), State << ((uint32_t)DC_Num));
}

/**
  * @brief   Установка значения задержки перезапуска секвенсора в тактак ACLK
  * @param   SEQ_Num  Выбор секвенсора
  * @param   TimerVal  Значение. 0 - означает отсутствие задержки и немедленный перезапуск (если активен).
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_SetRestartTimer(ADCSAR_SEQ_Num_TypeDef SEQ_Num, uint32_t TimerVal)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_RESTART_TIMER_VAL(TimerVal));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SRTMR_bit.VAL, TimerVal);
}
/**
  * @brief   Получение текущего значения задержки перезапуска секвенсора в тактак ACLK
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Значение. 0 - означает отсутствие задержки и немедленный перезапуск (если активен).
  */
__STATIC_INLINE uint32_t ADCSAR_SEQ_GetRestartTimer(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return READ_REG(ADCSAR->SEQ[SEQ_Num].SRTMR_bit.VAL);
}

/**
  * @brief   Разрешение обновления значения задержки по событиям перезапуска (по умолчанию, только по запускам)
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_RestartTimerUpdateCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SRTMR_bit.NOWAIT, State);
}

/**
  * @brief   Получение текущего значения количества результатов в буфере секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Значение
  */
__STATIC_INLINE uint32_t ADCSAR_SEQ_GetFIFOLoad(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return READ_REG(ADCSAR->SEQ[SEQ_Num].SFLOAD_bit.VAL);
}

/**
  * @brief   Получение результата измерения из буфера секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Значение
  */
__STATIC_INLINE uint32_t ADCSAR_SEQ_GetFIFOData(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return READ_REG(ADCSAR->SEQ[SEQ_Num].SFIFO_bit.DATA);
}

/**
  * @}
  */

/** @defgroup ADCSAR_Exported_Functions_Init_DC Цифровые компараторы
  * @{
  */

void ADCSAR_DC_Init(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_DC_Init_TypeDef* InitStruct);
void ADCSAR_DC_StructInit(ADCSAR_DC_Init_TypeDef* InitStruct);

/**
  * @brief   Разрешение работы цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_OutputCmd(ADCSAR_DC_Num_TypeDef DC_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->DC[DC_Num].DCTL_bit.CTE, State);
}

/**
  * @brief   Настройка источника данных цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Source  Выбор источника
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_SourceConfig(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_DC_Source_TypeDef Source)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_DC_SOURCE(Source));

    WRITE_REG(ADCSAR->DC[DC_Num].DCTL_bit.SRC, Source);
}

/**
  * @brief   Выбор канала АЦП для получения данных цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Source  Выбор источника
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_ChannelConfig(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_CH_Num_TypeDef Channel_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_CH_NUM(Channel_Num));

    WRITE_REG(ADCSAR->DC[DC_Num].DCTL_bit.CHNL, Channel_Num);
}

/**
  * @brief   Настройка режима и условия срабатывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Mode  Выбор режима
  * @param   Condition  Выбор условия
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_Config(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_DC_Mode_TypeDef Mode, ADCSAR_DC_Condition_TypeDef Condition)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_DC_MODE(Mode));
    assert_param(IS_ADCSAR_DC_CONDITION(Condition));

    MODIFY_REG(ADCSAR->DC[DC_Num].DCTL, ADCSAR_DC_DCTL_CTC_Msk | ADCSAR_DC_DCTL_CTM_Msk,
               ((Mode << ADCSAR_DC_DCTL_CTM_Pos) |
                (Condition << ADCSAR_DC_DCTL_CTC_Pos)));
}

/**
  * @brief   Установка значения нижней границы цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Val  Значение. Диапазон 0-0xFFF.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_SetThresholdLow(ADCSAR_DC_Num_TypeDef DC_Num, uint32_t Val)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_DC_THRESHOLD(Val));

    WRITE_REG(ADCSAR->DC[DC_Num].DCMP_bit.CMPL, Val);
}

/**
  * @brief   Получение значения нижней границы цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Val  Значение. Диапазон 0-0xFFF.
  */
__STATIC_INLINE uint32_t ADCSAR_DC_GetThresholdLow(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return READ_REG(ADCSAR->DC[DC_Num].DCMP_bit.CMPL);
}

/**
  * @brief   Установка значения верхней границы цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Val  Значение. Диапазон 0-0xFFF.
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_SetThresholdHigh(ADCSAR_DC_Num_TypeDef DC_Num, uint32_t Val)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_DC_THRESHOLD(Val));

    WRITE_REG(ADCSAR->DC[DC_Num].DCMP_bit.CMPH, Val);
}

/**
  * @brief   Получение значения верхней границы цифрового компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Val  Значение. Диапазон 0-0xFFF.
  */
__STATIC_INLINE uint32_t ADCSAR_DC_GetThresholdHigh(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return READ_REG(ADCSAR->DC[DC_Num].DCMP_bit.CMPH);
}

/**
  * @brief   Чтение статуса события сравнения компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Status  Статус
  */
__STATIC_INLINE FlagStatus ADCSAR_DC_CmpEventStatus(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return (FlagStatus)READ_BIT(ADCSAR->DCEV, 1 << ((uint32_t)DC_Num));
}

/**
  * @brief   Сброс статуса события сравнения компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_CmpEventStatusClear(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    WRITE_REG(ADCSAR->DCEV, 1 << ((uint32_t)DC_Num));
}

/**
  * @brief   Чтение статуса выходного триггера компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Status  Статус
  */
__STATIC_INLINE FlagStatus ADCSAR_DC_TrigStatus(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return (FlagStatus)READ_BIT(ADCSAR->DCTRIG, 1 << ((uint32_t)DC_Num));
}

/**
  * @brief   Сброс выходного триггера компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_TrigStatusClear(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    WRITE_REG(ADCSAR->DCTRIG, 1 << ((uint32_t)DC_Num));
}

/**
  * @brief   Получение последнего значения, использованного для сравнения
  * @param   DC_Num  Выбор компаратора
  * @retval  Val  Значение. Диапазон 0-0xFFF.
  */
__STATIC_INLINE uint32_t ADCSAR_DC_GetLastData(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return READ_REG(ADCSAR->DC[DC_Num].DDATA);
}

/**
  * @}
  */

/** @defgroup ADCSAR_Exported_Functions_Int Конфигурация прерываний
  * @{
  */

/** @defgroup ADCSAR_Exported_Functions_Int_DC Цифровые компараторы
  * @{
  */

/**
  * @brief   Включение генерации прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_ITCmd(ADCSAR_DC_Num_TypeDef DC_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(ADCSAR->DC[DC_Num].DCTL_bit.CIE, State);
}

/**
  * @brief   Настройка условий и режима работы для генерации прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   Mode  Выбор режима
  * @param   Condition  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_ITConfig(ADCSAR_DC_Num_TypeDef DC_Num, ADCSAR_DC_Mode_TypeDef Mode, ADCSAR_DC_Condition_TypeDef Condition)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_ADCSAR_DC_MODE(Mode));
    assert_param(IS_ADCSAR_DC_CONDITION(Condition));

    MODIFY_REG(ADCSAR->DC[DC_Num].DCTL, ADCSAR_DC_DCTL_CIC_Msk | ADCSAR_DC_DCTL_CIM_Msk,
               ((Mode << ADCSAR_DC_DCTL_CIM_Pos) |
                (Condition << ADCSAR_DC_DCTL_CIC_Pos)));
}

/**
  * @brief   Маскирование прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_ITMaskCmd(ADCSAR_DC_Num_TypeDef DC_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(ADCSAR->IM, 1 << ((uint32_t)DC_Num + ADCSAR_IM_DCIM0_Pos), State << ((uint32_t)DC_Num + ADCSAR_IM_DCIM0_Pos));
}

/**
  * @brief   Запрос немаскированного состояния прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Status  Состояние
  */
__STATIC_INLINE FlagStatus ADCSAR_DC_ITRawStatus(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return (FlagStatus)READ_BIT(ADCSAR->RIS, 1 << ((uint32_t)DC_Num + ADCSAR_RIS_DCRIS0_Pos));
}

/**
  * @brief   Запрос маскированного состояния прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  Status  Состояние
  */
__STATIC_INLINE FlagStatus ADCSAR_DC_ITMaskedStatus(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    return (FlagStatus)READ_BIT(ADCSAR->MIS, 1 << ((uint32_t)DC_Num + ADCSAR_MIS_DCMIS0_Pos));
}

/**
  * @brief   Сброс флага прерывания компаратора
  * @param   DC_Num  Выбор компаратора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_DC_ITStatusClear(ADCSAR_DC_Num_TypeDef DC_Num)
{
    assert_param(IS_ADCSAR_DC_NUM(DC_Num));

    WRITE_REG(ADCSAR->IC, 1 << ((uint32_t)DC_Num + ADCSAR_IC_DCIC0_Pos));
}

/**
  * @}
  */

/** @defgroup ADCSAR_Exported_Functions_Int_SEQ Секвенсоры
  * @{
  */

/**
  * @brief   Маскирование прерывания секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ITCmd(ADCSAR_SEQ_Num_TypeDef SEQ_Num, FunctionalState State)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_FUNCTIONAL_STATE(State));

    MODIFY_REG(ADCSAR->IM, 1 << ((uint32_t)SEQ_Num + ADCSAR_IM_SEQIM0_Pos), State << ((uint32_t)SEQ_Num + ADCSAR_IM_SEQIM0_Pos));
}

/**
  * @brief   Настройка генерации прерывания секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @param   ITCount  Количество запросов модуля АЦП для генерации прерывания.
  *                   0 - по каждому запросу, 0xFF - каждые 256 запросов.
  * @param   ITCountNoRst  Активация режима, где счетчик прерывания не будет сбрасываться по запуску секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ITConfig(ADCSAR_SEQ_Num_TypeDef SEQ_Num, uint32_t ITCount, FunctionalState ITCountNoRst)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));
    assert_param(IS_ADCSAR_SEQ_IT_COUNT_VAL(ITCount));
    assert_param(IS_FUNCTIONAL_STATE(ITCountNoRst));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SCCTL_bit.ICNT, ITCount);
    MODIFY_REG(ADCSAR->CICNT, 1 << ((uint32_t)SEQ_Num + ADCSAR_CICNT_ICNT0_Pos), ITCountNoRst << ((uint32_t)SEQ_Num + ADCSAR_CICNT_ICNT0_Pos));
}

/**
  * @brief   Получение текущего состояния счетчика запросов, используемого для генерации прерываний
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Val  Значение. Диапазон 0-0xFF.
  */
__STATIC_INLINE uint32_t ADCSAR_SEQ_GetITCountCurrent(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return READ_REG(ADCSAR->SEQ[SEQ_Num].SCVAL_bit.ICNT);
}

/**
  * @brief   Сброс счетчика запросов, используемого для генерации прерываний
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ITCountRst(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    WRITE_REG(ADCSAR->SEQ[SEQ_Num].SCVAL_bit.ICLR, 1);
}

/**
  * @brief   Запрос немаскированного состояния прерывания секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Состояние
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_ITRawStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->RIS, 1 << ((uint32_t)SEQ_Num + ADCSAR_RIS_SEQRIS0_Pos));
}

/**
  * @brief   Запрос маскированного состояния прерывания секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  Status  Состояние
  */
__STATIC_INLINE FlagStatus ADCSAR_SEQ_ITMaskedStatus(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    return (FlagStatus)READ_BIT(ADCSAR->MIS, 1 << ((uint32_t)SEQ_Num + ADCSAR_MIS_SEQMIS0_Pos));
}

/**
  * @brief   Сброс флага прерывания секвенсора
  * @param   SEQ_Num  Выбор секвенсора
  * @retval  void
  */
__STATIC_INLINE void ADCSAR_SEQ_ITStatusClear(ADCSAR_SEQ_Num_TypeDef SEQ_Num)
{
    assert_param(IS_ADCSAR_SEQ_NUM(SEQ_Num));

    WRITE_REG(ADCSAR->IC, 1 << ((uint32_t)SEQ_Num + ADCSAR_IC_SEQIC0_Pos));
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

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_ADCSAR_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

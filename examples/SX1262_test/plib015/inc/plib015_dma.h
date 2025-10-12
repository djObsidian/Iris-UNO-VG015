/**
  ******************************************************************************
  * @file    plib015_dma.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          DMA, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_DMA_H
#define __PLIB015_DMA_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup DMA
  * @brief Драйвер для работы с DMA
  * @{
  */

/** @defgroup DMA_Exported_Defines Константы
  * @{
  */

/** @defgroup DMA_Channel_Define Маски каналов DMA
   * @{
   */

/** @defgroup DMA_Channel_Num_Define Маски каналов по номеру
  * @{
  */

#define DMA_Channel_0 0x00000001UL   /*!< Канал DMA 0 */
#define DMA_Channel_1 0x00000002UL   /*!< Канал DMA 1 */
#define DMA_Channel_2 0x00000004UL   /*!< Канал DMA 2 */
#define DMA_Channel_3 0x00000008UL   /*!< Канал DMA 3 */
#define DMA_Channel_4 0x00000010UL   /*!< Канал DMA 4 */
#define DMA_Channel_5 0x00000020UL   /*!< Канал DMA 5 */
#define DMA_Channel_6 0x00000040UL   /*!< Канал DMA 6 */
#define DMA_Channel_7 0x00000080UL   /*!< Канал DMA 7 */
#define DMA_Channel_8 0x00000100UL   /*!< Канал DMA 8 */
#define DMA_Channel_9 0x00000200UL   /*!< Канал DMA 9 */
#define DMA_Channel_10 0x00000400UL  /*!< Канал DMA 10 */
#define DMA_Channel_11 0x00000800UL  /*!< Канал DMA 11 */
#define DMA_Channel_12 0x00001000UL  /*!< Канал DMA 12 */
#define DMA_Channel_13 0x00002000UL  /*!< Канал DMA 13 */
#define DMA_Channel_14 0x00004000UL  /*!< Канал DMA 14 */
#define DMA_Channel_15 0x00008000UL  /*!< Канал DMA 15 */
#define DMA_Channel_16 0x00010000UL  /*!< Канал DMA 16 */
#define DMA_Channel_17 0x00020000UL  /*!< Канал DMA 17 */
#define DMA_Channel_18 0x00040000UL  /*!< Канал DMA 18 */
#define DMA_Channel_19 0x00080000UL  /*!< Канал DMA 19 */
#define DMA_Channel_20 0x00100000UL  /*!< Канал DMA 20 */
#define DMA_Channel_21 0x00200000UL  /*!< Канал DMA 21 */
#define DMA_Channel_22 0x00400000UL  /*!< Канал DMA 22 */
#define DMA_Channel_23 0x00800000UL  /*!< Канал DMA 23 */
#define DMA_Channel_All 0x00FFFFFFUL /*!< Все каналы DMA */

/**
   * @}
   */

/** @defgroup DMA_Channel_Periph_Define Маски каналов по имени
  * @{
  */

#define DMA_Channel_GPIOA DMA_Channel_0  /*!< Канал DMA от GPIOA */
#define DMA_Channel_GPIOB DMA_Channel_1  /*!< Канал DMA от GPIOB */
#define DMA_Channel_GPIOC DMA_Channel_2  /*!< Канал DMA от GPIOC */
#define DMA_Channel_TMR32 DMA_Channel_4  /*!< Канал DMA от TMR32 */
#define DMA_Channel_TMR0  DMA_Channel_5  /*!< Канал DMA от TMR0 */
#define DMA_Channel_TMR1  DMA_Channel_6  /*!< Канал DMA от TMR1 */
#define DMA_Channel_TMR2  DMA_Channel_7  /*!< Канал DMA от TMR2 */
#define DMA_Channel_UART0_TX DMA_Channel_8   /*!< Канал DMA по передаче от UART0 */
#define DMA_Channel_UART1_TX DMA_Channel_9   /*!< Канал DMA по передаче от UART1 */
#define DMA_Channel_UART2_TX DMA_Channel_10  /*!< Канал DMA по передаче от UART2 */
#define DMA_Channel_UART0_RX DMA_Channel_11  /*!< Канал DMA по приёму от UART0 */
#define DMA_Channel_UART1_RX DMA_Channel_12  /*!< Канал DMA по приёму от UART1 */
#define DMA_Channel_UART2_RX DMA_Channel_13  /*!< Канал DMA по приёму от UART2 */
#define DMA_Channel_ADCSAR_SEQ0 DMA_Channel_14  /*!< Канал DMA секвенсора 0 АЦП SAR */
#define DMA_Channel_ADCSAR_SEQ1 DMA_Channel_15  /*!< Канал DMA секвенсора 1 АЦП SAR */
#define DMA_Channel_QSPI_TX DMA_Channel_16  /*!< Канал DMA по передаче от QSPI */
#define DMA_Channel_SPI0_TX DMA_Channel_17  /*!< Канал DMA по передаче от SPI0 */
#define DMA_Channel_SPI1_TX DMA_Channel_18  /*!< Канал DMA по передаче от SPI1 */
#define DMA_Channel_QSPI_RX DMA_Channel_19  /*!< Канал DMA по приёму от QSPI */
#define DMA_Channel_SPI0_RX DMA_Channel_20  /*!< Канал DMA по приёму от SPI0 */
#define DMA_Channel_SPI1_RX DMA_Channel_21  /*!< Канал DMA по приёму от SPI1 */
#define DMA_Channel_HASH DMA_Channel_22  /*!< Канал DMA от HASH */

/**
  * @}
  */

#define IS_DMA_CHANNEL(VALUE) ((VALUE) != 0)

#define IS_GET_DMA_CHANNEL(VALUE) (((VALUE) == (DMA_Channel_0)) ||  \
                                   ((VALUE) == (DMA_Channel_1)) ||  \
                                   ((VALUE) == (DMA_Channel_2)) ||  \
                                   ((VALUE) == (DMA_Channel_3)) ||  \
                                   ((VALUE) == (DMA_Channel_4)) ||  \
                                   ((VALUE) == (DMA_Channel_5)) ||  \
                                   ((VALUE) == (DMA_Channel_6)) ||  \
                                   ((VALUE) == (DMA_Channel_7)) ||  \
                                   ((VALUE) == (DMA_Channel_8)) ||  \
                                   ((VALUE) == (DMA_Channel_9)) ||  \
                                   ((VALUE) == (DMA_Channel_10)) || \
                                   ((VALUE) == (DMA_Channel_11)) || \
                                   ((VALUE) == (DMA_Channel_12)) || \
                                   ((VALUE) == (DMA_Channel_13)) || \
                                   ((VALUE) == (DMA_Channel_14)) || \
                                   ((VALUE) == (DMA_Channel_15)) || \
                                   ((VALUE) == (DMA_Channel_16)) || \
                                   ((VALUE) == (DMA_Channel_17)) || \
                                   ((VALUE) == (DMA_Channel_18)) || \
                                   ((VALUE) == (DMA_Channel_19)) || \
                                   ((VALUE) == (DMA_Channel_20)) || \
                                   ((VALUE) == (DMA_Channel_21)) || \
                                   ((VALUE) == (DMA_Channel_22)))

/**
  * @}
  */

/**
  * @}
  */

/** @defgroup DMA_Exported_Types Типы
  * @{
  */

/**
  * @brief Выбор режима работы DMA
  */

typedef enum {
    DMA_Mode_Disable = DMA_CHANNEL_CFG_CYCLE_CTRL_Stop,                         /*!< Неактивное состояние */
    DMA_Mode_Basic = DMA_CHANNEL_CFG_CYCLE_CTRL_Basic,                          /*!< Основной режим передачи */
    DMA_Mode_AutoReq = DMA_CHANNEL_CFG_CYCLE_CTRL_AutoReq,                      /*!< Режим передачи с авто-запросом */
    DMA_Mode_PingPong = DMA_CHANNEL_CFG_CYCLE_CTRL_PingPong,                    /*!< Режим передачи "пинг-понг" */
    DMA_Mode_PrmMemScatGath = DMA_CHANNEL_CFG_CYCLE_CTRL_MemScatGathPrim,       /*!< Работа с памятью в режиме "разборка-сборка" с использованием первичной управляющей структуры */
    DMA_Mode_AltMemScatGath = DMA_CHANNEL_CFG_CYCLE_CTRL_MemScatGathAlt,        /*!< Работа с памятью в режиме "разборка-сборка" с использованием альтернативной управляющей структуры */
    DMA_Mode_PrmPeriphScatGath = DMA_CHANNEL_CFG_CYCLE_CTRL_PeriphScatGathPrim, /*!< Работа с периферией в режиме "разборка-сборка" с использованием первичной управляющей структуры */
    DMA_Mode_AltPeriphScatGath = DMA_CHANNEL_CFG_CYCLE_CTRL_PeriphScatGathAlt   /*!< Работа с периферией в режиме "разборка-сборка" с использованием альтернативной управляющей структуры */
} DMA_Mode_TypeDef;
#define IS_DMA_MODE(VALUE) (((VALUE) == DMA_Mode_Disable) ||           \
                            ((VALUE) == DMA_Mode_Basic) ||             \
                            ((VALUE) == DMA_Mode_AutoReq) ||           \
                            ((VALUE) == DMA_Mode_PingPong) ||          \
                            ((VALUE) == DMA_Mode_PrmMemScatGath) ||    \
                            ((VALUE) == DMA_Mode_AltMemScatGath) ||    \
                            ((VALUE) == DMA_Mode_PrmPeriphScatGath) || \
                            ((VALUE) == DMA_Mode_AltPeriphScatGath))

/**
   * @brief Выбор количества передач до выполнения переарбитрации
   */
typedef enum {
    DMA_ArbitrationRate_1,   /*!< Переарбитрация каждую передачу DMA */
    DMA_ArbitrationRate_2,   /*!< Переарбитрация каждые 2 передачи DMA */
    DMA_ArbitrationRate_4,   /*!< Переарбитрация каждые 4 передачи DMA */
    DMA_ArbitrationRate_8,   /*!< Переарбитрация каждые 8 передач DMA */
    DMA_ArbitrationRate_16,  /*!< Переарбитрация каждые 16 передач DMA */
    DMA_ArbitrationRate_32,  /*!< Переарбитрация каждые 32 передачи DMA */
    DMA_ArbitrationRate_64,  /*!< Переарбитрация каждые 64 передачи DMA */
    DMA_ArbitrationRate_128, /*!< Переарбитрация каждые 128 передач DMA */
    DMA_ArbitrationRate_256, /*!< Переарбитрация каждые 256 передач DMA */
    DMA_ArbitrationRate_512, /*!< Переарбитрация каждые 512 передач DMA */
    DMA_ArbitrationRate_1024 /*!< Переарбитрация каждые 1024 передачи DMA */
} DMA_ArbitrationRate_TypeDef;
#define IS_DMA_ARBITRATION_RATE(VALUE) (((VALUE) == DMA_ArbitrationRate_1) ||   \
                                        ((VALUE) == DMA_ArbitrationRate_2) ||   \
                                        ((VALUE) == DMA_ArbitrationRate_4) ||   \
                                        ((VALUE) == DMA_ArbitrationRate_8) ||   \
                                        ((VALUE) == DMA_ArbitrationRate_16) ||  \
                                        ((VALUE) == DMA_ArbitrationRate_32) ||  \
                                        ((VALUE) == DMA_ArbitrationRate_64) ||  \
                                        ((VALUE) == DMA_ArbitrationRate_128) || \
                                        ((VALUE) == DMA_ArbitrationRate_256) || \
                                        ((VALUE) == DMA_ArbitrationRate_512) || \
                                        ((VALUE) == DMA_ArbitrationRate_1024))

/**
  * @brief  Разрядность данных источника или приемника
  */
typedef enum {
    DMA_DataSize_8 = DMA_CHANNEL_CFG_SRC_SIZE_Byte,      /*!< Разрядность данных 8 бит */
    DMA_DataSize_16 = DMA_CHANNEL_CFG_SRC_SIZE_Halfword, /*!< Разрядность данных 16 бит */
    DMA_DataSize_32 = DMA_CHANNEL_CFG_SRC_SIZE_Word      /*!< Разрядность данных 32 бит */
} DMA_DataSize_TypeDef;
#define IS_DMA_DATA_SIZE(VALUE) (((VALUE) == DMA_DataSize_8) ||  \
                                 ((VALUE) == DMA_DataSize_16) || \
                                 ((VALUE) == DMA_DataSize_32))

/**
  * @brief  Шаг инкремента адреса источника при чтении или приемника при записи
  */
typedef enum {
    DMA_DataInc_8 = DMA_CHANNEL_CFG_SRC_INC_Byte,      /*!< Инкремент данных 8 бит */
    DMA_DataInc_16 = DMA_CHANNEL_CFG_SRC_INC_Halfword, /*!< Инкремент данных 16 бит */
    DMA_DataInc_32 = DMA_CHANNEL_CFG_SRC_INC_Word,     /*!< Инкремент данных 32 бит */
    DMA_DataInc_Disable = DMA_CHANNEL_CFG_SRC_INC_None /*!< Инкремент отсутствует */
} DMA_DataInc_TypeDef;
#define IS_DMA_DATA_INC(VALUE) (((VALUE) == DMA_DataInc_8) ||  \
                                ((VALUE) == DMA_DataInc_16) || \
                                ((VALUE) == DMA_DataInc_32) || \
                                ((VALUE) == DMA_DataInc_Disable))

/**
  * @brief  Возможные состояния конечного автомата управления контроллером DMA
  */
typedef enum {
    DMA_State_Free = DMA_STATUS_CHNLS_Free,                           /*!< В покое */
    DMA_State_ReadConfigData = DMA_STATUS_CHNLS_ReadConfigData,       /*!< Чтение управляющих данных канала */
    DMA_State_ReadSrcDataEndPtr = DMA_STATUS_CHNLS_ReadSrcDataEndPtr, /*!< Чтение указателя конца данных источника */
    DMA_State_ReadDstDataEndPtr = DMA_STATUS_CHNLS_ReadDstDataEndPtr, /*!< Чтение указателя конца данных приемника */
    DMA_State_ReadSrcData = DMA_STATUS_CHNLS_ReadSrcData,             /*!< Чтение данных источника */
    DMA_State_WriteDstData = DMA_STATUS_CHNLS_WrireDstData,           /*!< Запись данных в приемник */
    DMA_State_WaitReq = DMA_STATUS_CHNLS_WaitReq,                     /*!< Ожидание запроса на выполнение прямого доступа */
    DMA_State_WriteConfigData = DMA_STATUS_CHNLS_WriteConfigData,     /*!< Запись управляющих данных канала */
    DMA_State_Pause = DMA_STATUS_CHNLS_Pause,                         /*!< Приостановлен */
    DMA_State_Done = DMA_STATUS_CHNLS_Done,                           /*!< Выполнен */
    DMA_State_PeriphScatGath = DMA_STATUS_CHNLS_PeriphScatGath        /*!< Работа с периферией в режиме "разборка-сборка" */
} DMA_State_TypeDef;
#define IS_DMA_STATE(VALUE) (((VALUE) == DMA_State_Free) ||              \
                             ((VALUE) == DMA_State_ReadConfigData) ||    \
                             ((VALUE) == DMA_State_ReadSrcDataEndPtr) || \
                             ((VALUE) == DMA_State_ReadDstDataEndPtr) || \
                             ((VALUE) == DMA_State_ReadSrcData) ||       \
                             ((VALUE) == DMA_State_WriteDstData) ||      \
                             ((VALUE) == DMA_State_WaitReq) ||           \
                             ((VALUE) == DMA_State_Pause) ||             \
                             ((VALUE) == DMA_State_Done) ||              \
                             ((VALUE) == DMA_State_PeriphScatGath))

/**
  * @brief  Защита шины при чтении из источника или записи в приемник через DMA
  */
typedef struct
{
    FunctionalState Priveleged; /*!< Управление привелегированным доступом */
    FunctionalState Bufferable; /*!< Управление буфферизацией доступа */
    FunctionalState Cacheable;  /*!< Управление кэшированием доступа */
} DMA_Protect_TypeDef;

/**
  * @brief  Структура инициализации канала DMA
  */
typedef struct
{
    void* SrcDataEndPtr;                         /*!< Указатель конца данных источника */
    void* DstDataEndPtr;                         /*!< Указатель конца данных приемника */
    DMA_Mode_TypeDef Mode;                       /*!< Выбор режима работы DMA. */
    FunctionalState NextUseburst;                /*!< Контроль установки соответсвующего каналу бита в регистре NT_DMA->CHNL_USEBURST_SET */
    uint32_t TransfersTotal;                     /*!< Общее количество передач DMA.
                                                      Параметр может принимать любое значение из диапазона 1-1024 */
    DMA_ArbitrationRate_TypeDef ArbitrationRate; /*!< Выбор количества передач до выполнения переарбитрации */
    DMA_Protect_TypeDef SrcProtect;              /*!< Защита шины при чтении из источника через DMA */
    DMA_Protect_TypeDef DstProtect;              /*!< Защита шины при записи в приемник через DMA */
    DMA_DataSize_TypeDef SrcDataSize;            /*!< Разрядность данных источника */
    DMA_DataSize_TypeDef DstDataSize;            /*!< Разрядность данных приемника */
    DMA_DataInc_TypeDef SrcDataInc;              /*!< Шаг инкремента адреса источника при чтении */
    DMA_DataInc_TypeDef DstDataInc;              /*!< Шаг инкремента адреса приемника при записи */
} DMA_ChannelInit_TypeDef;
#define IS_DMA_TRANSFERS_TOTAL(VALUE) (((VALUE) <= 1024) && ((VALUE) >= 1))

/**
  * @brief  Структура инициализации контроллера DMA
  */
typedef struct
{
    uint32_t Channel;                /*!< Определяет каналы, которые будут настроены.
                                          Параметр может принимать значение любой комбинации масок DMA_Channel_x из @ref DMA_Channel_Define. */
    DMA_Protect_TypeDef CtrlProtect; /*!< Управление защитой шины при обращении DMA к управляющим данным */
    FunctionalState UseBurst;        /*!< Установка пакетного обмена каналов DMA */
    FunctionalState ReqMask;         /*!< Маскирование (игнорирование) запросов от периферии на обслуживание каналов DMA */
    FunctionalState AltCtrl;         /*!< Установка альтернативной управляющей структуры каналов DMA */
    FunctionalState HighPriority;    /*!< Установка высокого приоритета каналов DMA */
    FunctionalState ChannelEnable;   /*!< Разрешение работы каналов DMA */
} DMA_Init_TypeDef;

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions Функции
  * @{
  */

/** @defgroup DMA_Exported_Functions_Init_Channel Инициализация каналов DMA
  * @{
  */

void DMA_ChannelDeInit(DMA_Channel_TypeDef* ChannelStruct);
void DMA_ChannelInit(DMA_Channel_TypeDef* ChannelStruct, DMA_ChannelInit_TypeDef* ChannelInitStruct);
void DMA_ChannelStructInit(DMA_ChannelInit_TypeDef* ChannelInitStruct);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Init Инициализация контроллера DMA
  * @{
  */

void DMA_DeInit(void);
void DMA_Init(DMA_Init_TypeDef* InitStruct);
void DMA_StructInit(DMA_Init_TypeDef* InitStruct);

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Config Конфигурация контроллера DMA
  * @{
  */

/**
  * @brief   Установка базового адреса управляющих каналов
  * @param   BasePtr  Значение базового адреса
  * @retval  void
  */
__STATIC_INLINE void DMA_BasePtrConfig(uint32_t BasePtr)
{
    WRITE_REG(DMA->BASEPTR, BasePtr);
}

/**
  * @brief   Управление защитой шины при обращении контроллера DMA к управляющим данным
  * @param   CtrlProtect  Структура, содержащая конфигурацию защиты
  * @retval  void
  */
__STATIC_INLINE void DMA_ProtectConfig(DMA_Protect_TypeDef* CtrlProtect)
{
    assert_param(IS_FUNCTIONAL_STATE(CtrlProtect->Bufferable));
    assert_param(IS_FUNCTIONAL_STATE(CtrlProtect->Cacheable));
    assert_param(IS_FUNCTIONAL_STATE(CtrlProtect->Priveleged));

    MODIFY_REG(DMA->CFG, DMA_CFG_CHPROT_Msk, ((CtrlProtect->Priveleged << (DMA_CFG_CHPROT_Pos + 0)) |
                                              (CtrlProtect->Bufferable << (DMA_CFG_CHPROT_Pos + 1)) |
                                              (CtrlProtect->Cacheable << (DMA_CFG_CHPROT_Pos + 2))));
}

/**
  * @brief      Разрешения работы контроллера DMA
  * @attention  Прежде чем включать DMA, необходимо проинициализоровать каналы
  *             с помощью @ref DMA_ChannelInit и сконфигурировать контроллер DMA через функцию
  *             инициализации @ref DMA_Init или вручную - @ref DMA_Exported_Functions_Config.
  * @param      State  Выбор состояния
  * @retval     void
  */
__STATIC_INLINE void DMA_MasterEnableCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(DMA->CFG_bit.MASTEREN, State);
}

/**
  * @brief   Программный запрос на осуществление передач DMA по выбранным каналам
  * @param   Channel  Выбор канала.
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @retval  void
  */
__STATIC_INLINE void DMA_SwRequestCmd(uint32_t Channel)
{
    assert_param(IS_DMA_CHANNEL(Channel));

    WRITE_REG(DMA->SWREQ, Channel);
}

/**
  * @brief   Установка пакетного обмена каналов DMA
  * @param   Channel  Выбор канала.
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void DMA_UseBurstCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->USEBURSTSET, Channel);
    else
        WRITE_REG(DMA->USEBURSTCLR, Channel);
}

/**
  * @brief   Установка циклического режима каналов DMA
  * @param   Channel  Выбор канала.
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void DMA_CircularCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->CIRCULARSET, Channel);
    else
        WRITE_REG(DMA->CIRCULARCLR, Channel);
}

/**
  * @brief      Маскирование каналов DMA
  * @attention  По маскированным каналам игнорируются запросы на передачи
  * @param      Channel  Выбор канала
  *                      Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param      State  Выбор состояния
  * @retval     void
  */
__STATIC_INLINE void DMA_ReqMaskCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->REQMASKSET, Channel);
    else
        WRITE_REG(DMA->REQMASKCLR, Channel);
}

/**
  * @brief   Активация каналов DMA
  * @param   Channel  Выбор канала
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void DMA_ChannelEnableCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->ENSET, Channel);
    else
        WRITE_REG(DMA->ENCLR, Channel);
}

/**
  * @brief   Установка альтернативной управляющей структуры каналов DMA
  * @param   Channel  Выбор канала.
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void DMA_AltCtrlCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->PRIALTSET, Channel);
    else
        WRITE_REG(DMA->PRIALTCLR, Channel);
}

/**
  * @brief   Установка высокого приоритета каналов DMA
  * @param   Channel  Выбор канала.
  *                   Параметр принимает любую комбинацию масок DMA_Channel_x из @ref DMA_Channel_Define.
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void DMA_HighPriorityCmd(uint32_t Channel, FunctionalState State)
{
    assert_param(IS_DMA_CHANNEL(Channel));
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == ENABLE)
        WRITE_REG(DMA->PRIORITYSET, Channel);
    else
        WRITE_REG(DMA->PRIORITYCLR, Channel);
}

/**
  * @}
  */

/** @defgroup DMA_Exported_Functions_Status Статусная информация
  * @{
  */

/**
  * @brief   Доступ к текущему конечного автомата контроллера DMA
  * @retval  State  Текущее состояние конечного автомата
  */
__STATIC_INLINE DMA_State_TypeDef DMA_StateStatus(void)
{
    return (DMA_State_TypeDef)READ_REG(DMA->STATUS_bit.STATE);
}

/**
  * @brief   Состояние контроллера DMA
  * @retval  State  Текущее состояние контроллера DMA
  */
__STATIC_INLINE FunctionalState DMA_MasterEnableStatus(void)
{
    return (FunctionalState)READ_BIT(DMA->STATUS, DMA_STATUS_MASTEREN_Msk);
}

/**
  * @brief   Состояние канала DMA
  * @param   Channel  Выбор канала
  * @retval  State  Текущее состояние контроллера DMA
  */
__STATIC_INLINE FunctionalState DMA_ChannelEnableStatus(uint32_t Channel)
{
    assert_param(IS_GET_DMA_CHANNEL(Channel));

    return (FunctionalState)READ_BIT(DMA->ENSET, Channel);
}

/**
  * @brief   Показывает поддерживает ли канал одиночные SREQ запросы
  * @param   Channel  Выбор канала
  * @retval  State  Одно из значений @ref FunctionalState:
  *                 - ENABLE - поддерживаются SREQ (как и блочные BREQ);
  *                 - DISABLE - поддерживаются только блочные запросы BREQ.
  */
__STATIC_INLINE FunctionalState DMA_WaitOnReqStatus(uint32_t Channel)
{
    assert_param(IS_GET_DMA_CHANNEL(Channel));

    return (FunctionalState)READ_BIT(DMA->WAITONREQ, Channel);
}

/**
  * @brief   Показывает наличие ошибки на шине
  * @retval  Status  Одно из значений @ref OperationStatus:
  *                  - OK - ошибок не было;
  *                  - ERROR - произошла ошибка.
  */
__STATIC_INLINE OperationStatus DMA_ErrorStatus(void)
{
    return (OperationStatus)READ_BIT(DMA->ERRCLR, DMA_ERRCLR_VAL_Msk);
}

/**
  * @brief   Сброс флага ошибки на шине
  * @retval  void
  */
__STATIC_INLINE void DMA_ClearErrorStatus(void)
{
    WRITE_REG(DMA->ERRCLR, DMA_ERRCLR_VAL_Msk);
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

#endif /* __PLIB015_DMA_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

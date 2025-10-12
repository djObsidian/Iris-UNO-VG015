/**
  ******************************************************************************
  * @file    plib015_flash.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          FLASH, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_FLASH_H
#define __PLIB015_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup FLASH
  * @brief Драйвер для работы с FLASH
  * @{
  */

/** @defgroup FLASH_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup FLASH_Exported_Types Типы
  * @{
  */

/**
  * @brief  Команды контроллера флеш-памяти
  */
typedef enum {
    FLASH_Cmd_Read = FLASH_CMD_RD_Msk,                                 /*!< Команда чтения */
    FLASH_Cmd_Write = FLASH_CMD_WR_Msk,                                /*!< Команда записи */
    FLASH_Cmd_EraseFull = FLASH_CMD_ERSEC_Msk | FLASH_CMD_ALLSEC_Msk, /*!< Команда стирания всей памяти */
    FLASH_Cmd_ErasePage = FLASH_CMD_ERSEC_Msk,                         /*!< Команда стирания страницы */
} FLASH_Cmd_TypeDef;
#define IS_FLASH_CMD(VALUE) (((VALUE) == FLASH_Cmd_Read) ||      \
                              ((VALUE) == FLASH_Cmd_Write) ||     \
                              ((VALUE) == FLASH_Cmd_EraseFull) || \
                              ((VALUE) == FLASH_Cmd_ErasePage))

/**
  * @brief  Выбор региона флеш-памяти для исполнения команд
  */
typedef enum {
    FLASH_Region_Main = 0UL,                 /*!< Основная область */
    FLASH_Region_NVR = FLASH_CMD_NVRON_Msk, /*!< NVR область (загрузочная) */
} FLASH_Region_TypeDef;
#define IS_FLASH_REGION(VALUE) (((VALUE) == FLASH_Region_Main) || \
                                 ((VALUE) == FLASH_Region_NVR))

#define IS_FLASH_MAIN_ADDR(MAIN_ADDR) (MAIN_ADDR < MEM_FLASH_SIZE)
#define IS_FLASH_MAIN_PAGE_NUM(MAIN_PAGE_NUM) (MAIN_PAGE_NUM < MEM_FLASH_PAGE_TOTAL)
#define IS_FLASH_NVR_ADDR(NVR_ADDR) (NVR_ADDR < MEM_FLASH_NVR_SIZE)
#define IS_FLASH_NVR_PAGE_NUM(NVR_PAGE_NUM) (NVR_PAGE_NUM < MEM_FLASH_NVR_PAGE_TOTAL)
#define IS_FLASH_DATA_NUM(DATA_NUM) (DATA_NUM < MEM_FLASH_BUS_WIDTH_WORDS)
#define IS_FLASH_LATENCY(LATENCY) (LATENCY < 15)

/**
  * @}
  */

/** @defgroup FLASH_Exported_Functions Функции
  * @{
  */

/** @defgroup FLASH_Cmd Управление контроллером флеш-памяти
  * @{
  */

/**
  * @brief   Установка значения адреса
  * @param   AddrVal  Значение адреса
  * @retval  void
  */
__STATIC_INLINE void FLASH_SetAddr(uint32_t AddrVal)
{
    WRITE_REG(FLASH->ADDR, AddrVal);
}

/**
  * @brief   Установка выбранного слова данных
  * @param   DataNum  Номер слова данных
  * @param   DataVal  Значение слова данных
  * @retval  void
  */
__STATIC_INLINE void FLASH_SetData(uint32_t DataNum, uint32_t DataVal)
{
    assert_param(IS_FLASH_DATA_NUM(DataNum));

    WRITE_REG(FLASH->DATA[DataNum].DATA, DataVal);
}

/**
  * @brief   Получение выбранного слова данных
  * @param   DataNum  Номер слова данных
  * @retval  Val  Значение слова данных
  */
__STATIC_INLINE uint32_t FLASH_GetData(uint32_t DataNum)
{
    assert_param(IS_FLASH_DATA_NUM(DataNum));

    return READ_REG(FLASH->DATA[DataNum].DATA);
}

/**
  * @brief   Передача команды контроллеру флеш-памяти
  * @param   Cmd  Команда
  * @param   Region  Область
  * @retval  void
  */
__STATIC_INLINE void FLASH_SetCmd(FLASH_Cmd_TypeDef Cmd, FLASH_Region_TypeDef Region)
{
    WRITE_REG(FLASH->CMD, ((uint32_t)FLASH_CMD_KEY_Access << FLASH_CMD_KEY_Pos) | (uint32_t)Region | (uint32_t)Cmd);
}

/**
  * @brief   Получение статуса занятости контроллера флеш-памяти
  * @retval  Status
  */
__STATIC_INLINE FlagStatus FLASH_BusyStatus(void)
{
    return (FlagStatus)READ_BIT(FLASH->STAT, FLASH_STAT_BUSY_Msk);
}

void FLASH_ReadData(uint32_t AddrVal, uint32_t* DataArr, FLASH_Region_TypeDef Region);
void FLASH_WriteData(uint32_t AddrVal, uint32_t* DataArr, FLASH_Region_TypeDef Region);
void FLASH_ErasePage(uint32_t AddrVal, FLASH_Region_TypeDef Region);
void FLASH_EraseFull(FLASH_Region_TypeDef Region);

/**
  * @}
  */

/** @defgroup FLASH_ExecCtrl Настройка исполнения программ
  * @{
  */

/**
  * @brief   Настройка количества тактов ожидания чтения из флеш
  * @param   LatencyVal  Значение
  * @retval  void
  */
__STATIC_INLINE void FLASH_LatencyConfig(uint32_t LatencyVal)
{
    assert_param(IS_FLASH_LATENCY(LatencyVal));

    WRITE_REG(FLASH->CTRL_bit.LAT, LatencyVal);
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

#endif /* __PLIB015_FLASH_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

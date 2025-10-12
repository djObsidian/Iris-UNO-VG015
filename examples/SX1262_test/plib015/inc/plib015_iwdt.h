/**
  ******************************************************************************
  * @file    plib015_iwdt.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          IWDT, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_IWDT_H
#define __PLIB015_IWDT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup IWDT
  * @brief Драйвер для работы с IWDT
  * @{
  */

/** @defgroup IWDT_Exported_Defines Константы
  * @{
  */

#define IWDT_LOCK_VAL 0xDEADC0DEUL   /*!< Любое значение для блокировки записи в регистры таймера */
#define IWDT_UNLOCK_VAL 0x1ACCE551UL /*!< Значение для разблокировки записи в регистры таймера */

/**
  * @}
  */

/** @defgroup IWDT_Exported_Types Типы
  * @{
  */

#define IS_IWDT_LOAD(VALUE) ((VALUE) > 0)

/**
  * @}
  */

/** @defgroup IWDT_Exported_Functions Функции
  * @{
  */

/**
  * @brief   Разрешение счета сторожевого таймера и маскирование (включение) его прерывания
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void IWDT_Cmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(IWDT->CTRL_bit.INTEN, State);
}

/**
  * @brief   Установка значения перезагрузки
  * @param   LoadVal  Значение перезагрузки (0x1 - 0xFFFFFFFF)
  * @retval  void
  */
__STATIC_INLINE void IWDT_SetLoad(uint32_t LoadVal)
{
    assert_param(IS_IWDT_LOAD(LoadVal));

    WRITE_REG(IWDT->LOAD, LoadVal);
}

/**
  * @brief   Получение текущего значения перезагрузки
  * @retval  Val  Значение перезагрузки
  */
__STATIC_INLINE uint32_t IWDT_GetLoad()
{
    return READ_REG(IWDT->LOAD);
}

/**
  * @brief   Получение текущего значения счетчика
  * @retval  Val  Значение счетчика
  */
__STATIC_INLINE uint32_t IWDT_GetCounter()
{
    return READ_REG(IWDT->VALUE);
}

/**
  * @brief   Разрешение сброса по сторожевому таймеру.
  *          Сброс будет произведен когда счетчик досчитает до нуля при установленном
  *          ранее и несброшенном флаге прерывания
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void IWDT_RstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(IWDT->CTRL_bit.RESEN, State);
}

/**
  * @brief   Запрещение записи во все регистры сторожевого таймера для
  *          предотвращения его отключения сбойными программами
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void IWDT_LockCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if (State == DISABLE) {
        WRITE_REG(IWDT->LOCK, IWDT_UNLOCK_VAL);
    } else {
        WRITE_REG(IWDT->LOCK, IWDT_LOCK_VAL);
    }
}

/**
  * @brief   Чтение немаскированного флага прерывания сторожевого таймера
  * @retval  Status  Статус прерывания
  */
__STATIC_INLINE FlagStatus IWDT_ITRawStatus()
{
    return (FlagStatus)READ_BIT(IWDT->RIS, IWDT_RIS_RAWIWDTINT_Msk);
}

/**
  * @brief  Чтение маскированного флага прерывания сторожевого таймера
  * @retval  Status  Статус прерывания
  */
__STATIC_INLINE FlagStatus IWDT_ITMaskedStatus()
{
    return (FlagStatus)READ_BIT(IWDT->MIS, IWDT_MIS_IWDTINT_Msk);
}

/**
  * @brief   Очищение статусного бита прерывания сторожевого таймера
  * @retval  void
  */
__STATIC_INLINE void IWDT_ITStatusClear()
{
    WRITE_REG(IWDT->INTCLR, IWDT_INTCLR_IWDTCLR_Msk);
}

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_IWDT_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

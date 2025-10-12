/**
  ******************************************************************************
  * @file    plib015.h
  *
  * @brief   Низкоуровневая библиотека периферии для микроконтроллера НИИЭТ К1921ВКХХХ
  *          Этот файл содержит:
  *           - Главный заголовочный файл целевого устройства, с описанием всех регистров его периферии
  *           - Область настройки драйвера
  *           - Макросы для доступа к регистрам периферии
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

/** @addtogroup Plib015 Библиотека периферии
  * @{
  */

#ifndef __PLIB015_H
#define __PLIB015_H

#ifdef __cplusplus
extern "C" {
#endif

#include "K1921VG015.h"

/** @addtogroup Exported_macro Макросы
  * @{
  */

#define __STATIC_INLINE static inline

#define SET_BIT(REG, BIT) ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT) ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT) (((REG) & (BIT)) ? (0x1) : (0x0))

#define CLEAR_REG(REG) ((REG) = (0x0))

#define WRITE_REG(REG, VAL) ((REG) = (VAL))

#define READ_REG(REG) ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK) WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))

/**
  * @}
  */

/** @addtogroup Exported_Types Типы
  * @{
  */

/**
  * @brief Описывает логическое состояние периферии.
  * Используется для операций включения/выключения периферийных блоков или их функций.
  */
typedef enum {
    DISABLE = 0UL,
    ENABLE = 1UL
} FunctionalState;
#define IS_FUNCTIONAL_STATE(VALUE) (((VALUE) == DISABLE) || ((VALUE) == ENABLE))

/**
  * @brief Описывает коды возврата при выполнении какой-либо операции
  */
typedef enum {
    OK = 0UL,
    ERROR = 1UL
} OperationStatus;

/**
  * @brief Описывает возможные состояния флага или бита
  */
typedef enum {
    CLEAR = 0UL,
    SET = 1UL
} FlagStatus,
    BitState;
#define IS_BIT_STATE(VALUE) (((VALUE) == CLEAR) || ((VALUE) == SET))

/**
  * @}
  */

/** @defgroup Misc Дополнительные модули
  * @{
  */

#include "plib015_assert.h"
#include "plib015_version.h"

/**
  * @}
  */

/** @addtogroup Peripheral Периферия
  * @{
  */

#include "plib015_conf.h"

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_H */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

/**
  ******************************************************************************
  * @file    plib015_crc.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          блока CRC, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_CRC_H
#define __PLIB015_CRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup ADCSD
  * @brief Драйвер для работы с CRC
  * @{
  */

/** @defgroup CRC_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup CRC_Exported_Types Типы
  * @{
  */

#define IS_CRC_SOMETHING(VALUE) ((VALUE) < 0x10000)

/**
  * @brief  Обращение входных данных блока CRC
  */
typedef enum {
	CRC_REV_IN_Nothing = CRC_CR_REV_IN_Disable,				/*!< Без изменения порядка битов */
	CRC_REV_IN_Byte = CRC_CR_REV_IN_REV_BYTE,				/*!< Бит-реверсный формат, внутри каждого байта выходных данных */
	CRC_REV_IN_Halfword = CRC_CR_REV_IN_REV_HALFWORD, 		/*!< Бит-реверсный формат, внутри каждого полуслова выходных данных */
	CRC_REV_IN_Word = CRC_CR_REV_IN_REV_WORD				/*!< Бит-реверсный формат, внутри слова выходных данных */
} CRC_REV_IN_TypeDef;
#define IS_CRC_REV_IN(VALUE) (((VALUE) == CRC_REV_IN_Nothing) ||  \
							((VALUE) == CRC_REV_IN_Byte) ||  \
							((VALUE) == CRC_REV_IN_Halfword) ||  \
							((VALUE) == CRC_REV_IN_Word))

/**
  * @brief  Размер полинома блока CRC
  */

typedef enum {
	CRC_POLYSIZE_32 = CRC_CR_POLYSIZE_POL32,
	CRC_POLYSIZE_16 = CRC_CR_POLYSIZE_POL16,
	CRC_POLYSIZE_8 = CRC_CR_POLYSIZE_POL8,
	CRC_POLYSIZE_7 = CRC_CR_POLYSIZE_POL7
} CRC_POLYSIZE_TypeDef;
#define IS_CRC_POLYSIZE(VALUE) (((VALUE) == CRC_POLYSIZE_32) ||  \
							((VALUE) == CRC_POLYSIZE_16) ||  \
							((VALUE) == CRC_POLYSIZE_8) ||  \
							((VALUE) == CRC_POLYSIZE_7))

/**
  * @brief  Структура инициализации АЦП
  */
typedef struct
{
    uint32_t Init; 						/*!< Начальное значение блока */
    CRC_REV_IN_TypeDef RevIn;			/*!< Обращение входных данных */
    FunctionalState RevOut;				/*!< Обращение выходных данных */
    FunctionalState Mode;				/*!< Режим работы */
    FunctionalState XorOut;				/*!< Исключающее-или для выходного значения */
    CRC_POLYSIZE_TypeDef Polysize;		/*!< Размер полинома */
    uint32_t Pol;						/*!< Коэффициенты порождающего полинома */

} CRC_Init_TypeDef;

/**
  * @}
  */

/** @defgroup ADCSD_Exported_Functions Функции
  * @{
  */

void CRC_DeInit(CRC_TypeDef* CRCx);
void CRC_Init(CRC_TypeDef* CRCx, CRC_Init_TypeDef* InitStruct);
void CRC_StructInit(CRC_Init_TypeDef* InitStruct);

/**
  * @brief   Установка данных для записи в блок CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   data Данные для записи в регистр
  * @retval  void
  */
__STATIC_INLINE void CRC_SetData(CRC_TypeDef* CRCx, uint32_t data)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	WRITE_REG(CRCx->DR, data);
}

/**
  * @brief   Получение вычисленного значения блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  val Значение блока
  */
__STATIC_INLINE uint32_t CRC_GetData(CRC_TypeDef* CRCx)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	return (uint32_t) READ_REG(CRCx->DR);
}

/**
  * @brief   Получение данных в постобработке блоком CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  val Постобработанное значение блока CRC
  */
__STATIC_INLINE uint32_t CRC_GetPost(CRC_TypeDef* CRCx)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	return (uint32_t) READ_REG(CRCx->POST);
}

/**
  * @brief   Установка сброса блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   state Бит сброса
  * @retval  void
  */
__STATIC_INLINE void CRC_ResetCmd(CRC_TypeDef* CRCx, FunctionalState state)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRCx->CR, CRC_CR_RESET_Msk, state << CRC_CR_RESET_Pos);
}

/**
  * @brief   Установка режима работы блока подсчёта CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   state Выбор режима
  * @retval  void
  */
__STATIC_INLINE void CRC_ModeCmd(CRC_TypeDef* CRCx, FunctionalState state)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRCx->CR, CRC_CR_MODE_Msk, state << CRC_CR_MODE_Pos);
}

/**
  * @brief   Установка режима для побитового исклющающего или после обращения выходных данных
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   state Выбор режима
  * @retval  void
  */
__STATIC_INLINE void CRC_XOROutCmd(CRC_TypeDef* CRCx, FunctionalState state)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRCx->CR, CRC_CR_XOROUT_Msk, state << CRC_CR_XOROUT_Pos);
}

/**
  * @brief   Установка размера порождающего полинома блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   polysize размер порождающего полинома
  * @retval  void
  */
__STATIC_INLINE void CRC_SetPolysize(CRC_TypeDef* CRCx, CRC_POLYSIZE_TypeDef polysize)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_CRC_POLYSIZE(polysize));

	MODIFY_REG(CRCx->CR, CRC_CR_POLYSIZE_Msk, polysize << CRC_CR_POLYSIZE_Pos);
}

/**
  * @brief   Получение размера порождающего полинома блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  polysize размер порождающего полинома
  */
__STATIC_INLINE CRC_POLYSIZE_TypeDef CRC_GetPolysize(CRC_TypeDef* CRCx)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	return (CRC_POLYSIZE_TypeDef) (READ_REG(CRCx->CR) & CRC_CR_POLYSIZE_Msk) >> CRC_CR_POLYSIZE_Pos;
}

/**
  * @brief   Установка обращения входных данных в блок CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   revin Обращение входных данных
  * @retval  void
  */
__STATIC_INLINE void CRC_SetRevIn(CRC_TypeDef* CRCx, CRC_REV_IN_TypeDef revin)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_CRC_REV_IN(revin));

	MODIFY_REG(CRCx->CR, CRC_CR_REV_IN_Msk, revin << CRC_CR_REV_IN_Pos);
}

/**
  * @brief   Получение обращения входных данных в блок CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  revin Обращение входных данных
  */
__STATIC_INLINE void CRC_GetRevIn(CRC_TypeDef* CRCx, CRC_REV_IN_TypeDef revin)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_CRC_REV_IN(revin));

	MODIFY_REG(CRCx->CR, CRC_CR_REV_IN_Msk, revin << CRC_CR_REV_IN_Pos);
}

/**
  * @brief   Установка обращения выходных данных из блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param	 state бит обращения выходных данных
  * @retval  void
  */
__STATIC_INLINE void CRC_RevOutCmd(CRC_TypeDef* CRCx, FunctionalState state)
{
	assert_param(IS_CRC_PERIPH(CRCx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRCx->CR, CRC_CR_REV_OUT_Msk, state << CRC_CR_REV_OUT_Pos);
}

/**
  * @brief   Установка начального значения блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   val Начальное значение блока
  * @retval  void
  */
__STATIC_INLINE void CRC_SetInit(CRC_TypeDef* CRCx, uint32_t val)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	WRITE_REG(CRCx->INIT, val);
}

/**
  * @brief   Получение начального значения блока CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  val Начальное значение блока
  */
__STATIC_INLINE uint32_t CRC_GetInit(CRC_TypeDef* CRCx)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	return (uint32_t)READ_REG(CRCx->INIT);
}

/**
  * @brief   Установка коэффициентов порождающего полинома CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @param   val Значение коэффициентов порождающего полинома
  * @retval  void
  */
__STATIC_INLINE void CRC_SetPol(CRC_TypeDef* CRCx, uint32_t val)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	WRITE_REG(CRCx->POL, val);
}

/**
  * @brief   Получение коэффициентов порождающего полинома CRC
  * @param	 CRCx Выбор модуля CRC, где x = 0 | 1
  * @retval  val Значение коэффициентов порождающего полинома
  */
__STATIC_INLINE uint32_t CRC_GetPol(CRC_TypeDef* CRCx)
{
	assert_param(IS_CRC_PERIPH(CRCx));

	return (uint32_t)READ_REG(CRCx->POL);
}




/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_ADCSD_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

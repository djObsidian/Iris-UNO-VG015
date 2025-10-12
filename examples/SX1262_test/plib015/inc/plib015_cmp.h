/**
  ******************************************************************************
  * @file    plib015_cmp.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          CMP, а также сопутствующие макроопределения и перечисления
  *
  * @author  НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
  * @author  НИИЭТ, Филипп Штоколов 
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
#ifndef __PLIB015_ACMP_H
#define __PLIB015_ACMP_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup CMP
  * @brief Драйвер для работы с CMP
  * @{
  */

/** @defgroup CMP_Exported_Defines Константы
  * @{
  */

/** @defgroup CMP_ITSource_Define Источники прерываний CMP
  * @{
  */

/**
   * @}
   */

/** @defgroup CMP_Flag_Define Флаги работы CMP
  * @{
  */


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup CMP_Exported_Types Типы
  * @{
  */

#define CMP0 &CMP->ACMP0CTL
#define CMP1 &CMP->ACMP1CTL
#define IS_CMP(VALUE) ((VALUE) == CMP0 || \
						(VALUE) == CMP1)

#define CMP_DAC_REF0 0x0
#define CMP_DAC_REF1 0x8
#define IS_CMP_DAC_REF(VALUE) (((VALUE) == CMP_REF0) || \
							((VALUE) == CMP_REF1))

/**
  * @brief  Выбор сигнала для отрицательного входа компаратора CMPx
  */
typedef enum {
	CMP_Ref_Inx = 0x0,	/*!< Вывод микроконтроллера для соответствующего CMPx */
	CMP_Ref_DAC0 = 0x1,	/*!< Выход ЦАП REF0 */
	CMP_Ref_DAC1 = 0x2	/*!< ВЫХОД ЦАП REF1 */
} CMP_Ref_TypeDef;
#define IS_CMP_REF(VALUE) (((VALUE) == CMP_Ref_Inx) || \
							((VALUE) == CMP_DAC0) || \
							((VALUE) == CMP_DAC1))

/**
  * @brief  Выбор события для реагирования, используется как событие формирования прерывания или как событие
  * 		пробуждения микроконтроллера
  */
typedef enum {
	CMP_Event_No = 0x0,			/*!< Нет события, на которое должна последовать реакция*/
	CMP_Event_RiseEdge = 0x1,	/*!< Положительный фронт */
	CMP_Event_FallEdge = 0x2,	/*!< Отрицательный фронт */
	CMP_Event_AnyEdge = 0x3,	/*!< Любой фронт */
	CMP_Event_High = 0x4,		/*!< Уровень логической единицы */
	CMP_Event_Low = 0x5			/*!< Уровень логического нуля */
} CMP_Event_TypeDef;
#define IS_CMP_EVENT(VALUE) (((VALUE) == CMP_Event_No) || \
							((VALUE) == CMP_Event_RiseEdge) || \
							((VALUE) == CMP_Event_FallEdge) || \
							((VALUE) == CMP_Event_AnyEdge) || \
							((VALUE) == CMP_Event_High) || \
							((VALUE) == CMP_Event_Low))

#define IS_CMP_REFVAL(VALUE) ((VALUE) < 0x10)

/**
  * @}
  */

/** @defgroup CMP_Exported_Functions Функции
  * @{
  */

/**
  * @brief   Разрешение работы ЦАП компаратора CMP
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void CMP_DAC_Cmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    if(State) WRITE_REG(CMP->DACCTL_bit.EN, 0);
    else WRITE_REG(CMP->DACCTL_bit.EN, 1);
}

/**
  * @brief   Установка напряженения на выходе ЦАП REF0
  * @param   refVal Уровень напряжения на выходе ЦАП
  * @param   CMP_DAC_REFx Выбор выхода ЦАП, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_SetRef(uint32_t REFx, uint32_t refVal)
{
	  assert_param(IS_CMP_DAC_REF(REFx));
    assert_param(IS_CMP_REFVAL(refVal));

    MODIFY_REG(CMP->DACCTL, 0xF << REFx, refVal << REFx);
}

/**
  * @brief   Разрешение работы компаратора CMPx
  * @param   state Бит разрешения работы
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_Cmd(uint32_t *CMPx, FunctionalState state)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_EN_Msk, state << CMP_ACMP0CTL_EN_Pos);
}

/**
  * @brief   Сброс компаратора CMPx
  * @param   state Бит сброса
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_RstCmd(uint32_t *CMPx, FunctionalState state)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_RST_Msk, state << CMP_ACMP0CTL_RST_Pos);
}

/**
  * @brief   Инверсия выходного канала CMPx
  * @param   state Бит разрешения работы
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_InvCmd(uint32_t *CMPx, FunctionalState state)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_INV_Msk, state << CMP_ACMP0CTL_INV_Pos);
}

/**
  * @brief   Выбор выходного сигнала, подключаемого на отрицательный выход компаратора CMPx
  * @param   ref  Сигнал, поступающий на вход компаратора типа @ref CMP_Ref_TypeDef
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_RefConfig(uint32_t *CMPx, CMP_Ref_TypeDef ref)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_CMP_REF(ref));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_SELREF_Msk, ref << CMP_ACMP0CTL_SELREF_Pos);
}

/**
  * @brief   Выбор события для формирования прерывания CMPx
  * @param   intSrc Событие для формирования прерывания @ref CMP_Event_TypeDef
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_IntSourceConfig(uint32_t *CMPx, CMP_Event_TypeDef intSrc)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_CMP_INTSOURCE(intSrc));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_INTSRC_Msk, intSrc << CMP_ACMP0CTL_INTSRC_Pos);
}

/**
  * @brief   Выбор события CMPx для пробуждения микроконтроллера
  * @param   trigSrc Событие для формирования сигнала пробуждения @ref CMP_Event_TypeDef
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_TriggerSourceConfig(uint32_t *CMPx, CMP_Event_TypeDef trigSrc)
{
	assert_param(IS_CMP(CMPx));
    assert_param(IS_CMP_EVENT(trigSrc));

    MODIFY_REG(*CMPx, CMP_ACMP0CTL_TRIGSRC_Msk, trigSrc << CMP_ACMP0CTL_TRIGSRC_Pos);
}

/**
  * @brief   Состояние выхода компаратора CMPx
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  status Состояние компаратора
  */
__STATIC_INLINE FunctionalState CMP_Status(uint32_t *CMPx)
{
	assert_param(IS_CMP(CMPx));

    return READ_BIT(CMP->ACSTATUS,(*CMPx >> 0x2) & 0x3);
}

/**
  * @brief   Разрешение прерывания компаратора CMPx
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @param   state Флаг разрешения прерывания
  * @retval  void
  */
__STATIC_INLINE void CMP_ITCmd(uint32_t *CMPx, FunctionalState state)
{
	assert_param(IS_CMP(CMPx));
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CMP->INTEN, ((*CMPx >> 0x2) & 0x3), state << ((*CMPx >> 0x2) & 0x3));
}

/**
  * @brief   Статус немаскированного прерывания компаратора CMPx
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  state Запрос на прерывание CMPx
  */
__STATIC_INLINE FunctionalState CMP_ITRawStatus(uint32_t *CMPx)
{
	assert_param(IS_CMP(CMPx));

    return READ_BIT(CMP->RIS, (*CMPx >> 0x2) & 0x3);
}

/**
  * @brief   Статус маскированного прерывания компаратора CMPx
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  state Запрос на прерывание CMPx
  */
__STATIC_INLINE FunctionalState CMP_ITMaskedStatus(uint32_t *CMPx)
{
	assert_param(IS_CMP(CMPx));

    return READ_BIT(CMP->MIS, (*CMPx >> 0x2) & 0x3);
}

/**
  * @brief   Сброс прерывания от компаратора CMPx
  * @param   CMPx Выбор компаратора, где x = 0|1
  * @retval  void
  */
__STATIC_INLINE void CMP_ITClear(uint32_t *CMPx)
{
	assert_param(IS_CMP(CMPx));

    SET_BIT(CMP->ICLR, (*CMPx >> 0x2) & 0x3);
}


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_CMP_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

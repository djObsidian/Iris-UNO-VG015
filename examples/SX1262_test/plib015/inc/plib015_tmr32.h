/**
  ******************************************************************************
  * @file    plib015_tmr32.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          TMR32, а также сопутствующие макроопределения и перечисления
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
  * <h2><center>&copy; 2025 АО "НИИЭТ"</center></h2>
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __PLIB015_TMR32_H
#define __PLIB015_TMR32_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup TMR32
  * @brief Драйвер для работы с TMR32
  * @{
  */

/** @defgroup TMR32_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup TMR32_Exported_Types Типы
  * @{
  */

/**
  * @brief  Настройка способа счёта таймера
  */
typedef enum {
  TMR32_Mode_Stop = TMR32_CTRL_MODE_Stop,             /*!< Останов счёта */
  TMR32_Mode_Capcom_Up = TMR32_CTRL_MODE_Up,          /*!< Счёт вверх до CAPCOM0.VAL */
  TMR32_Mode_Multiple = TMR32_CTRL_MODE_Multiple, 	  /*!< Непрерывный счёт */
  TMR32_Mode_Capcom_UpDown = TMR32_CTRL_MODE_UpDown,  /*!< Счёт вверх/вниз от 0 до CAPCOM0.VAL и обратно */
} TMR32_Mode_TypeDef;
#define IS_TMR32_MODE(VALUE) (((VALUE) == TMR32_Mode_Stop) || \
                              ((VALUE) == TMR32_Mode_Up) || \
                              ((VALUE) == TMR32_Mode_Multiple) || \
                              ((VALUE) == TMR32_Mode_UpDown))

/**
  * @brief  Настройка выходного делителя частоты таймера
  */
typedef enum {
  TMR32_Div_1 = TMR32_CTRL_DIV_Div1,	/*!< Деление выходной частоты на 1 */
	TMR32_Div_2 = TMR32_CTRL_DIV_Div2,  /*!< Деление выходной частоты на 2 */
	TMR32_Div_4 = TMR32_CTRL_DIV_Div4, 	/*!< Деление выходной частоты на 4 */
	TMR32_Div_8 = TMR32_CTRL_DIV_Div8,  /*!< Деление выходной частоты на 8 */
} TMR32_Div_TypeDef;
#define IS_TMR32_DIV(VALUE) (((VALUE) == TMR32_Div_1) || \
                              ((VALUE) == TMR32_Div_2) || \
                              ((VALUE) == TMR32_Div_4) || \
                              ((VALUE) == TMR32_Div_8))

/**
  * @brief  Выбор источника тактированного сигнала
  */
typedef enum {
	TMR32_Clksel_SysClk = TMR32_CTRL_CLKSEL_SysClk,	/*!< Тактовый сигнал SYSCLK */
	TMR32_Clksel_ExtClk = TMR32_CTRL_CLKSEL_ExtClk, /*!< Внешний источник синхронизации */
} TMR32_Clksel_TypeDef;
#define IS_TMR32_CLKSEL(VALUE) (((VALUE) == TMR32_CTRL_CLKSEL_SysClk) || \
                              ((VALUE) == TMR32_CTRL_CLKSEL_ExtClk))

/**
  * @brief  Настройка режима захвата
  */
typedef enum {
  TMR32_CAPCOM_Mode_None = TMR32_CAPCOM_CTRL_CAPMODE_None,     /*!< Нет захвата */
  TMR32_CAPCOM_Mode_Raise = TMR32_CAPCOM_CTRL_CAPMODE_Raise,   /*!< Захват по переднему фронту */
  TMR32_CAPCOM_Mode_Fail = TMR32_CAPCOM_CTRL_CAPMODE_Fail,     /*!< Захват по заднему фронту */
  TMR32_CAPCOM_Mode_Edge = TMR32_CAPCOM_CTRL_CAPMODE_Edge,     /*!< Захват по обоим фронтам */
} TMR32_CAPCOM_Mode_TypeDef;
#define IS_TMR32_CAPCOM_MODE(VALUE) (((VALUE) == TMR32_CAPCOM_Mode_None) ||  \
                                  ((VALUE) == TMR32_CAPCOM_Mode_Raise) || \
                                  ((VALUE) == TMR32_CAPCOM_Mode_Fail)  || \
								  ((VALUE) == TMR32_CAPCOM_Mode_Edge))

/**
  * @brief  Настройка режима выхода CAPCOM
  */
typedef enum {
  TMR32_CAPCOM_OutMode_BitOUT = TMR32_CAPCOM_CTRL_OUTMODE_BitOUT,     /*!< Выход правляется значение бита OUT */
  TMR32_CAPCOM_OutMode_Set = TMR32_CAPCOM_CTRL_OUTMODE_Set,           /*!< установка (Set) */
  TMR32_CAPCOM_OutMode_Toggle_Reset = TMR32_CAPCOM_CTRL_OUTMODE_Toggle_Reset,  /*!< переключение/сброс (Toggle/Reset) */
  TMR32_CAPCOM_OutMode_Set_Reset = TMR32_CAPCOM_CTRL_OUTMODE_Set_Reset,     /*!< установка/сброс (Set/Reset) */
  TMR32_CAPCOM_OutMode_Toggle = TMR32_CAPCOM_CTRL_OUTMODE_Toggle,        /*!< переключение (Toggle) */
  TMR32_CAPCOM_OutMode_Reset = TMR32_CAPCOM_CTRL_OUTMODE_Reset,         /*!< сброс (Reset) */
  TMR32_CAPCOM_OutMode_Toggle_Set = TMR32_CAPCOM_CTRL_OUTMODE_Toggle_Set,    /*!< переключение/установка (Toggle/Set) */
  TMR32_CAPCOM_OutMode_Reset_Set = TMR32_CAPCOM_CTRL_OUTMODE_Reset_Set,     /*!< сброс/установка (Reset/Set) */

} TMR32_CAPCOM_OutMode_TypeDef;
#define IS_TMR32_CAPCOM_OUTMODE(VALUE) (((VALUE) == TMR32_CAPCOM_OutMode_BitOUT) ||  \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Set) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Toggle_Reset) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Set_Reset) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Toggle) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Reset) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Toggle_Set) || \
                                  ((VALUE) == TMR32_CAPCOM_OutMode_Reset_Set))

/**
  * @brief  Конфигурируемые регистры захвата/сравнения
  */
typedef enum {
	TMR32_CAPCOM_0,
	TMR32_CAPCOM_1,
	TMR32_CAPCOM_2,
	TMR32_CAPCOM_3
} TMR32_CAPCOM_Num_TypeDef;
#define IS_TMR32_CAPCOM_NUM(VALUE) (((VALUE) == TMR32_CAPCOM_0) || \
                              ((VALUE) == TMR32_CAPCOM_1) || \
                              ((VALUE) == TMR32_CAPCOM_2) || \
                              ((VALUE) == TMR32_CAPCOM_3))

/**
  * @brief  Поля для регистров прерывания блока TMR32
  */
typedef enum {
	TMR32_IT_TimerUpdate	= 0,
	TMR32_IT_CAPCOM_0		  = 1,
	TMR32_IT_CAPCOM_1		  = 2,
	TMR32_IT_CAPCOM_2		  = 3,
	TMR32_IT_CAPCOM_3		  = 4
} TMR32_IT_TypeDef;
#define IS_TMR32_IT(VALUE) (((VALUE) == TMR32_IT_TimerUpdate) || \
                            ((VALUE) == TMR32_IT_CAPCOM_0) || \
                            ((VALUE) == TMR32_IT_CAPCOM_1) || \
                            ((VALUE) == TMR32_IT_CAPCOM_2) || \
							  ((VALUE) == TMR32_IT_CAPCOM_3))

/**
  * @brief  Поля для регистров формирования запросов блока TMR32
  */
typedef enum {
	TMR32_REQ_TimerUpdate	= 0x1,
	TMR32_REQ_CAPCOM_0 		= 0x2,
	TMR32_REQ_CAPCOM_1 		= 0x4,
	TMR32_REQ_CAPCOM_2 		= 0x8,
	TMR32_REQ_CAPCOM_3 		= 0x10
} TMR32_REQ_TypeDef;
#define IS_TMR32_REQ(VALUE) (((VALUE) == TMR32_REQ_TimerUpdate) || \
                              ((VALUE) == TMR32_REQ_CAPCOM_0) || \
                              ((VALUE) == TMR32_REQ_CAPCOM_1) || \
                              ((VALUE) == TMR32_REQ_CAPCOM_2) || \
							  ((VALUE) == TMR32_REQ_CAPCOM_3))

/**
  * @brief  Настройка входа захвата/сравнения
  */
typedef enum {
	TMR32_CAPCOM_CapChannel_CCIA, /*!< Вход CCIA */
	TMR32_CAPCOM_CapChannel_CCIB, /*!< Вход CCIB */
	TMR32_CAPCOM_CapChannel_Low,	/*!< Уровень логического нуля   */
	TMR32_CAPCOM_CapChannel_High	/*!< Уровень логической единицы */
} TMR32_CAPCOM_CAPCOM_Channel_Typedef;
#define IS_TMR32_CAPCOM_CHANNEL (((VALUE) == TMR32_CAPCOM_CapChannel_CCIA) || \
								((VALUE) == TMR32_CAPCOM_CapChannel_CCIB) || \
								((VALUE) == TMR32_CAPCOM_CapChannel_Low) || \
								((VALUE) == TMR32_CAPCOM_CapChannel_High))

/**
  * @}
  */

/** @defgroup TMR32_Exported_Functions Функции
  * @{
  */

/**
  * @brief   Сброс счётчика, делителя и направления счёта
  * @retval  void
  */
__STATIC_INLINE void TMR32_Clear()
{
  SET_BIT(TMR32->CTRL, TMR32_CTRL_CLR_Msk);
}

/**
  * @brief   Выбор режима счёта
  * @param   mode Режим счёта
  * @retval  void
  */
__STATIC_INLINE void TMR32_SetMode(TMR32_Mode_TypeDef mode)
{
	assert_param(IS_TMR32_MODE(mode));

  MODIFY_REG(TMR32->CTRL, TMR32_CTRL_MODE_Msk, (uint32_t) mode << TMR32_CTRL_MODE_Pos);
}

/**
  * @brief   Выбор выходного делителя частоты таймера
  * @param   div Делитель частоты
  * @retval  void
  */
__STATIC_INLINE void TMR32_SetDivider(TMR32_Div_TypeDef div)
{
	assert_param(IS_TMR32_DIV(div));

  MODIFY_REG(TMR32->CTRL, TMR32_CTRL_DIV_Msk, (uint32_t) div << TMR32_CTRL_DIV_Pos);
}

/**
  * @brief   Выбор источника тактированного сигнала
  * @param   sel Источник тактирования
  * @retval  void
  */
__STATIC_INLINE void TMR32_SetClksel(TMR32_Clksel_TypeDef sel)
{
	assert_param(IS_TMR32_CLKSEL(sel));

  MODIFY_REG(TMR32->CTRL, TMR32_CTRL_CLKSEL_Msk, (uint32_t) sel << TMR32_CTRL_CLKSEL_Pos);
}

/**
  * @brief   Установка значения счетчика
  * @param   CountVal  Значение счетчика
  * @retval  void
  */
__STATIC_INLINE void TMR32_SetCounter(uint32_t CountVal)
{
  WRITE_REG(TMR32->COUNT, CountVal);
}

/**
  * @brief   Получение значения счетчика
  * @retval  Val  Значение счетчика
  */
__STATIC_INLINE uint32_t TMR32_GetCounter()
{
  return READ_REG(TMR32->COUNT);
}

//						 IT

/**
  * @brief   Установка флага для маскированного прерывания
  * @param   it Номер маскированного прерывания типа @ref TMR32_IT_TypeDef
  * @param   state Флаг для включения маскированного прерывания
  * @retval  void
  */
__STATIC_INLINE void TMR32_ITCmd(TMR32_IT_TypeDef it, FunctionalState state)
{
  assert_param(IS_TMR32_IT(it));
  assert_param(IS_FUNCTIONAL_STATE(state));

  MODIFY_REG(TMR32->IM, it, (uint32_t) state * (uint32_t) it);
}


/**
  * @brief   Установка значения регистра сравнения
  * @param   it Маскированное прерывание прерывания типа @ref TMR32_IT_TypeDef
  * @retval  void
  */
__STATIC_INLINE FunctionalState TMR32_ITMaskedStatus(TMR32_IT_TypeDef it)
{
  assert_param(IS_TMR32_IT(it));

  return READ_BIT(TMR32->MIS, it);
}

/**
  * @brief   Чтение значения немаскированного прерывания.
  * @param   it Маскированное прерывание прерывания типа @ref TMR32_IT_TypeDef
  * @retval  void
  */
__STATIC_INLINE FunctionalState TMR32_ITRawStatus(TMR32_IT_TypeDef it)
{
  assert_param(IS_TMR32_IT(it));

  return READ_BIT(TMR32->RIS, it);
}

/**
  * @brief   Сброс прерываний
  * @param   it Маскированное прерывание прерывания типа @ref TMR32_IT_TypeDef
  * @retval  void
  */
__STATIC_INLINE void TMR32_ITClear(TMR32_IT_TypeDef it)
{
  assert_param(IS_TMR32_IT(it));

  SET_BIT(TMR32->IC, it);
}

/**
  * @brief   Разрешение формирования запросов DMA
  * @param   req Источник запроса типа @ref TMR32_REQ_TypeDef
  * @param   state Флаг для разрешения формирования запросов
  * @retval  void
  */
__STATIC_INLINE void TMR32_DMAReqCmd(TMR32_REQ_TypeDef req, FunctionalState state)
{
  assert_param(IS_TMR32_REQ(req));
  assert_param(IS_FUNCTIONAL_STATE(state));

  if(state)  MODIFY_REG(TMR32->DMA_IM, req,0x01);
      else   MODIFY_REG(TMR32->DMA_IM, req,0x0);
}

/**
  * @brief   Разрешение формирования запросов ADC SAR
  * @param   req Источник запроса типа @ref TMR32_REQ_TypeDef
  * @param   state Флаг для разрешения формирования запросов
  * @retval  void
  */
__STATIC_INLINE void TMR32_ADCReqCmd(TMR32_REQ_TypeDef req, FunctionalState state)
{
  assert_param(IS_TMR32_REQ(req));
  assert_param(IS_FUNCTIONAL_STATE(state));

  if(state)  MODIFY_REG(TMR32->ADC_IM, req,0x01);
      else   MODIFY_REG(TMR32->ADC_IM, req,0x0);
}

// CAPCOM

/**
  * @brief   Установка значения регистра сравнения
  * @param   capcomx номер регистра capcom @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   CapComVal  Значение регистра сравнения
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_SetComparator(TMR32_CAPCOM_Num_TypeDef capcomx, uint32_t capcomVal)
{
  assert_param(IS_TMR32_CAPCOM(capcomx));

  WRITE_REG(TMR32->CAPCOM[capcomx].VAL, capcomVal);
}

/**
  * @brief   Получение статуса переполнения.
  * @param   capcomx номер регистра capcom @ref TMR32_CAPCOM_Num_TypeDef.
  * @retval  FunctionalState сосотяние переполнения
  */
__STATIC_INLINE FunctionalState TMR32_CAPCOM_OverflowStatus(TMR32_CAPCOM_Num_TypeDef capcomx)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));

  return READ_BIT(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_OVF_Msk);
}

/**
  * @brief   Сброс статуса переполнения.
  * @param   capcomx номер регистра capcom @ref TMR32_CAPCOM_Num_TypeDef.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_OverflowClear(TMR32_CAPCOM_Num_TypeDef capcomx)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));

  SET_BIT(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_OVF_Msk);
}

/**
  * @brief   Выбор состояния выхода, которое будет выставлено при OUTMODE = TMR32_CAPCOM_OutMode_BitOUT = 0.
  * @param   capcomx номер регистра capcom @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   out состояние выхода.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_OutBitConfig(TMR32_CAPCOM_Num_TypeDef capcomx, FunctionalState out)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));
	assert_param(IS_FUNCTIONAL_STATE(out));

  MODIFY_REG(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_OUT_Msk, (uint32_t) out << TMR32_CAPCOM_CTRL_OUT_Pos);
}

/**
  * @brief   Выбор режима вывода.
  * @param   capcomx Нномер регистра capcom @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   outMode Режим вывода.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_OutModeConfig(TMR32_CAPCOM_Num_TypeDef capcomx, TMR32_CAPCOM_OutMode_TypeDef outMode)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));
	assert_param(IS_TMR32_CAPCOM_OUTMODE(outMode));

  MODIFY_REG(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_OUTMODE_Msk, (uint32_t) outMode << TMR32_CAPCOM_CTRL_OUTMODE_Pos);
}

/**
  * @brief   Выбор режима захвата/сравнения.
  * @param   capcomx Номер регистра capcomx @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   capMode Режим вывода.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_CapModeConfig(TMR32_CAPCOM_Num_TypeDef capcomx, TMR32_CAPCOM_Mode_TypeDef capcomMode)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));
	assert_param(IS_TMR32_CAPCOM_MODE(capcomMode));

  MODIFY_REG(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_CAPMODE_Msk, (uint32_t) capcomMode << TMR32_CAPCOM_CTRL_CAPMODE_Pos);
}

/**
  * @brief   Выбор режима входа захвата/сравнения.
  * @param   capcomx Нномер регистра capcomx @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   capMode Режим вывода.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_CapChannelConfig(TMR32_CAPCOM_Num_TypeDef capcomx, TMR32_CAPCOM_CAPCOM_Channel_Typedef capcomChannel)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));
	assert_param(IS_TMR32_CAPCOM_CHANNEL(capcomChannel));

  MODIFY_REG(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_CCISEL_Msk, (uint32_t) capcomChannel << TMR32_CAPCOM_CTRL_CCISEL_Pos);
}

/**
  * @brief   Получение состояния синхронизированного входа захвата/сравнения.
  * @param   capcomx Нномер регистра capcomx @ref TMR32_CAPCOM_Num_TypeDef.
  * @retval  statys сосотяние выбранного синхронизированного входа CapCom
  */
__STATIC_INLINE FunctionalState TMR32_CAPCOM_GetSyncedCapComInput(TMR32_CAPCOM_Num_TypeDef capcomx)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));

  return (FunctionalState) READ_BIT(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_SCCI_Msk);
}

/**
  * @brief   Получение состояния входа захвата/сравнения.
  * @param   capcomx Нномер регистра capcomx @ref TMR32_CAPCOM_Num_TypeDef.
  * @retval  status состояние выбранного входа CapCom
  */
__STATIC_INLINE FunctionalState TMR32_CAPCOM_GetCapComInput(TMR32_CAPCOM_Num_TypeDef capcomx)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));

  return (FunctionalState) READ_BIT(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_CCI_Msk);
}

/**
  * @brief   Выбор режима захвата/сравнения.
  * @param   capcomx Нномер регистра capcomx @ref TMR32_CAPCOM_Num_TypeDef.
  * @param   state Режим захвата 0 - режим сравнения; 1 - режим захвата.
  * @retval  void
  */
__STATIC_INLINE void TMR32_CAPCOM_CaptureConfig(TMR32_CAPCOM_Num_TypeDef capcomx, FunctionalState state)
{
	assert_param(IS_TMR32_CAPCOM_NUM(capcomx));
	assert_param(IS_FUNCTIONAL_STATE(state));

  MODIFY_REG(TMR32->CAPCOM[capcomx].CTRL, TMR32_CAPCOM_CTRL_CAP_Msk, (uint32_t) state << TMR32_CAPCOM_CTRL_CAP_Pos);
}



/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_TMR32_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2025 NIIET *****END OF FILE****/

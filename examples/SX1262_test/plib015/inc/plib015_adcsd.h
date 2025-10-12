/**
  ******************************************************************************
  * @file    plib015_adcsd.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          ADCSD, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_ADCSD_H
#define __PLIB015_ADCSD_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup ADCSD
  * @brief Драйвер для работы с ADCSD
  * @{
  */

/** @defgroup ADCSD_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup ADCSD_Exported_Types Типы
  * @{
  */

#define IS_ADCSD_START_DIV(VALUE) ((VALUE) < 0x10000)
#define IS_ADCSD_PRESENT_PERIOD(VALUE) ((VALUE) < 0x100)
#define IS_ADCSD_RESET_PERIOD(VALUE) ((VALUE) < 0x100)
#define IS_ADCSD_BIT_PERIOD(VALUE) ((VALUE) < 0x100)
#define IS_ADCSD_DATA(VALUE) ((VALUE) < 0x100
#define IS_ADCSD_WTCYC(VALUE) ((VALUE) < 0x8)
#define IS_ADCSD_MDC(VALUE) ((VALUE) < 0x8)
#define IS_ADCSD_DR(VALUE) ((VALUE) < 0x4)

/**
  * @brief  Номер канала
  */
typedef enum {
    ADCSD_CH_Num_0,  /*!< Канал 0 */
    ADCSD_CH_Num_1,  /*!< Канал 1 */
    ADCSD_CH_Num_2,  /*!< Канал 2 */
    ADCSD_CH_Num_3,  /*!< Канал 3 */
    ADCSD_CH_Num_4,  /*!< Канал 4 */
    ADCSD_CH_Num_5,  /*!< Канал 5 */
    ADCSD_CH_Num_6,  /*!< Канал 6 */
    ADCSD_CH_Num_7,  /*!< Канал 7 */
} ADCSD_CH_Num_TypeDef;

#define IS_ADCSD_CH_NUM(VALUE) (((VALUE) == ADCSD_CH_Num_0) ||  \
                                ((VALUE) == ADCSD_CH_Num_1) ||  \
                                ((VALUE) == ADCSD_CH_Num_2) ||  \
                                ((VALUE) == ADCSD_CH_Num_3) ||  \
                                ((VALUE) == ADCSD_CH_Num_4) ||  \
                                ((VALUE) == ADCSD_CH_Num_5) ||  \
                                ((VALUE) == ADCSD_CH_Num_6) ||  \
                                ((VALUE) == ADCSD_CH_Num_7))

/**
  * @brief Выбор основного делителя частоты
  */
typedef enum {
	ADCSD_MainDiv_Disable,	  /*!< Делитель выключен */
	ADCSD_MainDiv_2,			    /*!< Делитель 1/2 */
	ADCSD_MainDiv_3,          /*!< Делитель 1/3 */
	ADCSD_MainDiv_4,			    /*!< Делитель 1/4 */
	ADCSD_MainDiv_5			      /*!< Делитель 1/5 */  
} ADCSD_MainDiv_TypeDef;

#define IS_ADCSD_MAINDIV(VALUE) (((VALUE) == ADCSD_MainDiv_Disable) ||  \
							                   ((VALUE) == ADCSD_MainDiv_Div_2) ||  \
							                   ((VALUE) == ADCSD_MainDiv_Div_3) ||  \
							                   ((VALUE) == ADCSD_MainDiv_Div_4) ||  \
							                   ((VALUE) == ADCSD_MainDiv_Div_5))

/**
  * @brief Выбор делителя коэффициента прореживания
  */
typedef enum {
	ADCSD_SamleDiv_2048,	  /*!< Делитель 2048 */
	ADCSD_SamleDiv_1024,		/*!< Делитель 1024 */
	ADCSD_SamleDiv_512,     /*!< Делитель 512 */
	ADCSD_SamleDiv_256			/*!< Делитель 256 */
} ADCSD_SamleDiv_TypeDef;

#define IS_ADCSD_SAMPLEDIV(VALUE) (((VALUE) == ADCSD_SampleDiv_2048) ||  \
							                    ((VALUE) == ADCSD_SampleDiv_1024) ||  \
							                    ((VALUE) == ADCSD_SampleDiv_512) ||  \
							                    ((VALUE) == ADCSD_SampleDiv_256))

/**
  * @brief Выбор режима канала
  */
typedef enum {
	ADCSD_MODE_NoStart,				 /*!< Нет запуска */
	ADCSD_MODE_SingleStart,			 /*!< Однократный запуск с последующим отключением канала */
	ADCSD_MODE_SingleStartKeepAlive, /*!< Однократный запуск без отключения канала */
	ADCSD_MODE_CycledStart			 /*!< Циклический запуск */
} ADCSD_MODE_TypeDef;
#define IS_ADCSD_MODE(VALUE) (((VALUE) == ADCSD_MODE_NoStart) ||  \
							((VALUE) == ADCSD_MODE_SingleStart) ||  \
							((VALUE) == ADCSD_MODE_SingleStartKeepAlive) ||  \
							((VALUE) == ADCSD_MODE_CycledStart))



/**
  * @brief Выбор усиления каналов
  */

typedef enum {
	ADCSD_AMPL_0,  /*!< Коэфициент усиления 0 дБ */
	ADCSD_AMPL_6,  /*!< Коэфициент усиления 6 дБ */
	ADCSD_AMPL_12, /*!< Коэфициент усиления 12 дБ */
	ADCSD_AMPL_18, /*!< Коэфициент усиления 18 дБ */
	ADCSD_AMPL_20, /*!< Коэфициент усиления 20 дБ */
	ADCSD_AMPL_26, /*!< Коэфициент усиления 26 дБ */
	ADCSD_AMPL_32, /*!< Коэфициент усиления 32 дБ */
	ADCSD_AMPL_38  /*!< Коэфициент усиления 38 дБ */
} ADCSD_AMPL_TypeDef;
#define IS_ADCSD_AMPL(VALUE) (((VALUE) == ADCSD_AMPL_0Db) ||  \
					((VALUE) == ADCSD_AMPL_6Db) ||  \
					((VALUE) == ADCSD_AMPL_12Db) ||  \
					((VALUE) == ADCSD_AMPL_18Db) ||  \
					((VALUE) == ADCSD_AMPL_20Db) ||  \
					((VALUE) == ADCSD_AMPL_26Db) ||  \
					((VALUE) == ADCSD_AMPL_32Db) ||  \
					((VALUE) == ADCSD_AMPL_38Db))

/**
  * @brief  Структура инициализации АЦП
  */
typedef struct
{
    uint32_t WaitCycle; 				/*!< Количество тактов ожидания
     	 	 	 	 	 	 	 	 	 	 принимает значения от 0 до 7 */
    uint32_t MainDiv;					/*!< Значение основного делителя частоты
     	 	 	 	 	 	 	 	 	 	0, 5, 6, 7 - делитель выключен
     	 	 	 	 	 	 	 	 	 	1: 1/2,
     	 	 	 	 	 	 	 	 	 	2: 1/3,
     	 	 	 	 	 	 	 	 	 	3: 1/4,
     	 	 	 	 	 	 	 	 	 	4: 1/5							*/
    uint32_t SampleDiv;					/*!< Значение делителя коэффициента прореживания
     	 	 	 	 	 	 	 	 	 	0: 1/2048
     	 	 	 	 	 	 	 	 	 	1: 1/1024
     	 	 	 	 	 	 	 	 	 	2: 1/512
     	 	 	 	 	 	 	 	 	 	3: 1/256						*/
} ADCSD_Init_TypeDef;

/**
  * @brief  Структура инициализации канала АЦП
  */
typedef struct
{
    ADCSD_MODE_TypeDef Mode;            /*!< Выбор режима работы */
    ADCSD_AMPL_TypeDef Amplifier;		/*!< Выбор коэфициента усиления*/
} ADCSD_CH_Init_TypeDef;

/**
  * @}
  */

/** @defgroup ADCSD_Exported_Functions Функции
  * @{
  */

void ADCSD_DeInit(void);
void ADCSD_Init(ADCSD_Init_TypeDef* InitStruct);
void ADCSD_StructInit(ADCSD_Init_TypeDef* InitStruct);
void ADCSD_CH_Init(ADCSD_CH_Num_TypeDef ch_num, ADCSD_CH_Init_TypeDef* InitStruct);
void ADCSD_CH_StructInit(ADCSD_CH_Init_TypeDef* InitStruct);

/**
  * @brief   Выбор количества тактов ожидания АЦП сигма-дельта
  * @param   waitClkAmount Количество тактов ожидания
  * @retval  void
  */
__STATIC_INLINE void ADCSD_WaitCycleCmd(uint32_t WaitCycle)
{
	assert_param(IS_ADCSD_WTCYC(WaitCycle));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_WTCYC_Msk, WaitCycle << ADCSD_CTRL_WTCYC_Pos);
}

/**
  * @brief   Выбор основного делителя частоты АЦП сигма-дельта
  * @param   mainDiv Значение основного делителя частоты
  * @retval  void
  */
__STATIC_INLINE void ADCSD_MainDivCmd(ADCSD_MainDiv_TypeDef mainDiv)
{
	assert_param(IS_ADCSD_MAINDIV(mainDiv));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_MDC_Msk, mainDiv << ADCSD_CTRL_MDC_Pos);
}

/**
  * @brief   Выбор делителя коэффициента прореживания АЦП сигма-дельта
  * @param   sampleDiv Значение делителя коэффициента прореживания
  * @retval  void
  */
__STATIC_INLINE void ADCSD_SampleDivCmd(ADCSD_SamleDiv_TypeDef sampleDiv)
{
	assert_param(IS_ADCSD_SAMPLEDIV(sampleDiv));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_DR_Msk, sampleDiv << ADCSD_CTRL_DR_Pos);
}

/**
  * @brief   Установка программного сброса АЦП сигма-дельта
  * @param   state Бит программного сброса
  * @retval  void
  */
__STATIC_INLINE void ADCSD_SfResetCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_SFRST_Msk, state << ADCSD_CTRL_SFRST_Pos);
}

/**
  * @brief   Установка сброса АЦП сигма-дельта
  * @param   state Бит сброса
  * @retval  void
  */
__STATIC_INLINE void ADCSD_ResetCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_RST_Msk, state << ADCSD_CTRL_RST_Pos);
}

/**
  * @brief   Установка внутреннего источника опорного напряжения АЦП сигма-дельта
  * @param   state Бит включения внутреннего источника опорного напряжения
  * @retval  void
  */
__STATIC_INLINE void ADCSD_BandGapCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_PUREF_Msk, state << ADCSD_CTRL_PUREF_Pos);
}

/**
  * @brief   Разрешение работы АЦП сигма-дельта
  * @param   state Бит разрешения работы
  * @retval  void
  */
__STATIC_INLINE void ADCSD_EnableCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(ADCSD->CTRL, ADCSD_CTRL_ENB_Msk, state << ADCSD_CTRL_ENB_Pos);
}

/**
  * @brief   Выбор режима работы канала АЦП сигма-дельта
  * @param   ch_num Выбор канала АЦП
  * @param   mode Выбор режима
  * @retval  void
  */
__STATIC_INLINE void ADCSD_SetMode(ADCSD_CH_Num_TypeDef ch_num, ADCSD_MODE_TypeDef mode)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));
	assert_param(IS_ADCSD_MODE(mode));

	MODIFY_REG(ADCSD->MODE, ADCSD_MODE_CH0_Msk << ((uint32_t)ch_num << 2), mode << ((uint32_t)ch_num << 2));
}

/**
  * @brief   Выбор усиления канала АЦП сигма-дельта
  * @param   ch_num Выбор канала АЦП сигма-дельта
  * @param 	 ampl Выбор усиления канала
  * @retval  void
  */
__STATIC_INLINE void ADCSD_SetAmplification(ADCSD_CH_Num_TypeDef ch_num, ADCSD_AMPL_TypeDef ampl)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));
	assert_param(IS_ADCSD_AMPL(ampl));

	MODIFY_REG(ADCSD->AMPL, ADCSD_AMPL_CH0_Msk << ((uint32_t)ch_num << 2), (uint32_t)ampl << ((uint32_t)ch_num << 2));
}

/**
  * @brief   Получение текущего режима работы канала АЦП сигма-дельта
  * @param   ch_num Выбор канала АЦП сигма-дельта
  * @retval  mode Текущий режим рыботы канала ch_num
  */
__STATIC_INLINE ADCSD_MODE_TypeDef ADCSD_GetMode(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

	return (ADCSD_MODE_TypeDef) (READ_REG(ADCSD->MODE & (ADCSD_MODE_CH0_Msk << ((uint32_t)ch_num << 2))) >> ((uint32_t)ch_num >> 2));
}

/**
  * @brief   Получение текущего усиления канала АЦП сигма-дельта
  * @param   ch_num Выбор канала АЦП сигма-дельта
  * @retval  ampl Текущее усилинеие канала ch_num
  */
__STATIC_INLINE ADCSD_AMPL_TypeDef ADCSD_GetAmplification(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

	return (ADCSD_AMPL_TypeDef) (READ_REG(ADCSD->AMPL & (ADCSD_AMPL_CH0_Msk << ((uint32_t)ch_num << 2))) >> ((uint32_t)ch_num >> 2));
}

/**
  * @brief   Включение преобразования канала АЦП сигма-дельта
  * @param   ch_num Выбор канала
  * @param   state  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSD_EnableTransformCmd(ADCSD_CH_Num_TypeDef ch_num, FunctionalState state)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(ADCSD->ENB, 1 << ((uint32_t)ch_num + ADCSD_ENB_CH0_Pos), state << ((uint32_t)ch_num + ADCSD_ENB_CH0_Pos));
}

/**
  * @brief   Включение дифференциального режима канала АЦП сигма-дельта
  * @param   ch_num Выбор канала
  * @param   state  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSD_DIFFCmd(ADCSD_CH_Num_TypeDef ch_num, FunctionalState state)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(ADCSD->DIFF, 1 << ((uint32_t)ch_num + ADCSD_ENB_CH0_Pos), state << ((uint32_t)ch_num + ADCSD_ENB_CH0_Pos));
}

/**
  * @brief   Текущее состояние готовности канала АЦП сигма-дельта
  * @param   ch_num Выбор канала
  * @retval  state готовность канала ch_num
  */
__STATIC_INLINE FunctionalState ADCSD_ReadyStatus(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

	return (FunctionalState) READ_REG(ADCSD->READY & (1 << ((uint32_t)ch_num + ADCSD_READY_CH0_Pos)));
}

/**
  * @brief   Текущее состояние преобразования канала АЦП сигма-дельта
  * @param   ch_num Выбор канала
  * @retval  state состояние преобразования канала ch_num
  */
__STATIC_INLINE FunctionalState ADCSD_DATAUPDStatus(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

	return (FunctionalState) READ_REG(ADCSD->DATAUPD & (1 << ((uint32_t)ch_num + ADCSD_DATAUPD_CH0_Pos)));
}

/**
  * @brief   Маскирование прерывания по окончанию преобразования канала АЦП сигма-дельта
  * @param   ch_num  Выбор канала
  * @param   state  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void ADCSD_ITCmd(ADCSD_CH_Num_TypeDef ch_num, FunctionalState state)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));
    assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(ADCSD->IM, 1 << ((uint32_t)ch_num), state << ((uint32_t)ch_num + ADCSD_IM_CH0_Pos));
}

/**
  * @brief   Запрос маскированного состояния прерывания канала АЦП сигма-дельта
  * @param   ch_num  Выбор канала АЦП
  * @retval  status  Состояние
  */
__STATIC_INLINE FlagStatus ADCSD_ITMaskedStatus(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

    return (FlagStatus)READ_BIT(ADCSD->MIS, 1 << ((uint32_t)ch_num + ADCSD_MIS_CH0_Pos));
}

/**
  * @brief   Сброс флага прерывания канала АЦП сигма-дельта
  * @param   ch_num  Выбор канала АЦП сигма-дельта
  * @retval  void
  */
__STATIC_INLINE void ADCSD_ITStatusClear(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

    WRITE_REG(ADCSD->IC, 1 << ((uint32_t)ch_num + ADCSD_IC_CH0_Pos));
}

/**
  * @brief   Получение результата измерения из канала
  * @param   ch_num  Выбор канала АЦП сигма-дельта
  * @retval  Val  Значение
  */
__STATIC_INLINE uint32_t ADCSD_GetData(ADCSD_CH_Num_TypeDef ch_num)
{
	assert_param(IS_ADCSD_CH_NUM(ch_num));

    return (uint32_t)READ_REG(ADCSD->DATA[ch_num].DATA);
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

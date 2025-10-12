/**
  ******************************************************************************
  * @file    plib015_TRNG.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          блока TRNG, а также сопутствующие макроопределения и перечисления
  *
  * @author  НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
  *
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
#ifndef __PLIB015_TRNG_H
#define __PLIB015_TRNG_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup TRNG
  * @brief Драйвер для работы с TRNG
  * @{
  */

/** @defgroup TRNG_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup TRNG_Exported_Types Типы
  * @{
  */

#define IS_TRNG_COUNTBLOCK(VALUE) (((VALUE) < 0x10) && ((VALUE) != 0))
#define IS_TRNG_REPEATTESTCUTOFF(VALUE) ((VALUE) < 0x40)
#define IS_TRNG_PROPTESTCUTOFF(VALUE) ((VALUE) < 0x200)
#define IS_TRNG_CUTOFF(VALUE) ((VALUE) < 0x10000)
#define IS_TRNG_FIFO(VALUE) ((VALUE) < 0x20)

/**
  * @brief
  */
typedef enum {
    TRNG_AsyncFreeRunOsc	= TRNG_CR_LFSR_AsyncFreeRunOsc,  /*!< Генератор "истинных" случайных чисел с асинхронным осциллятором */
	TRNG_SyncOsc	 		= TRNG_CR_LFSR_SyncOsc   		 /*!< Псевдослучайный генератор с синхронным осциллятором для симуляции */
} TRNG_GenratorMode_TypeDef;
#define IS_TRNG_GENERATORMODE(VALUE) (((VALUE) == TRNG_AsyncFreeRunOsc) || \
                                   ((VALUE) == TRNG_SyncOsc))

/**
  * @brief  Отдельные проверки смещения в тесте на автокорреляцию
  */
typedef enum {
    TRNG_AUTOCORRELATIONDISABLE_Nothing	= 0x00,  /*!< Нет пропусков */
	TRNG_AUTOCORRELATIONDISABLE_Next	= 0x01,  /*!< По сравнению со следующим образцом того же самого кольцевого генератора, нулевое смещение */
	TRNG_AUTOCORRELATIONDISABLE_Later	= 0x10   /*!< По сравнению с более поздним образцом того же самого кольцевого генератора, смещение +1 */
} TRNG_AUTOCORRELATIONDISABLE_TypeDef;
#define IS_TRNG_AUTOCORRELATIONDISABLE(VALUE) ((VALUE) & (IS_TRNG_AUTOCORRELATIONDISABLE_Next | IS_TRNG_AUTOCORRELATIONDISABLE_Later))

/**
  * @brief  Отдельные проверки смещения в тесте на корреляцию
  */
typedef enum {
	TRNG_CORRELATIONDISABLE_Nothing		= 0x000,  /*!< Нет пропусков */
    TRNG_CORRELATIONDISABLE_Same		= 0x001,  /*!< По сравнению с такой же выборкой другого кольцевого генератора, нулевое смещение */
	TRNG_CORRELATIONDISABLE_Backward	= 0x010,  /*!< По сравнению с предыдущей выборкой другого кольцевого генератора, смещение -1 */
	TRNG_CORRELATIONDISABLE_Forward	 	= 0x100   /*!< По сравнению со следующей выборкой другого кольцевого генератора, смещение +1 */
} TRNG_CORRELATIONDISABLE_TypeDef;
#define IS_TRNG_CORRELATIONDISABLE(VALUE) ((VALUE) & (IS_TRNG_CORRELATIONDISABLE_Same | IS_TRNG_CORRELATIONDISABLE_Backward | IS_TRNG_CORRELATIONDISABLE_Forward))

/**
  * @brief  Режимы смешивания
  */
typedef enum {
	TRNG_BLENDMETHOD_Concatenation			= TRNG_CR_BLENDMETHOD_Concatenation,  		 /*!< Объединение */
	TRNG_BLENDMETHOD_XORLevel_1				= TRNG_CR_BLENDMETHOD_XOR_LEVEL_1,    		 /*!< Сокращение с 32 до 4 бит */
	TRNG_BLENDMETHOD_XORLevel_2				= TRNG_CR_BLENDMETHOD_XOR_LEVEL_2,		     /*!< Сокращение с 4 до 1 бита */
	TRNG_BLENDMETHOD_Von_Neumann_Debiasing	= TRNG_CR_BLENDMETHOD_VON_NEUMANN_debiasing  /*!< Алгоритм исключения систематической ошибки Фон-Неймана */
} TRNG_BLENDMETHOD_TypeDef;
#define IS_TRNG_BLENDMETHOD(VALUE) (((VALUE) == TRNG_BLENDMETHOD_Concatenation) || \
									((VALUE) == TRNG_BLENDMETHOD_XORLevel_1) || \
									((VALUE) == TRNG_BLENDMETHOD_XORLevel_2) || \
									((VALUE) == TRNG_BLENDMETHOD_Von_Neumann_Debiasing))

/**
  * @brief  32-битные слова частей ключа
  */
typedef enum {
	TRNG_Key0,	/*!< Нулевой регистр ключа */
	TRNG_Key1,	/*!< Первый регистр ключа */
	TRNG_Key2,	/*!< Второй регистр ключа */
	TRNG_Key3,	/*!< Третий регистр ключа */
} TRNG_KEY_TypeDef;
#define IS_TRNG_KEY(VALUE) (((VALUE) == TRNG_Key0) || \
							((VALUE) == TRNG_Key1) || \
							((VALUE) == TRNG_Key2) || \
							((VALUE) == TRNG_Key3))

/**
  * @brief  Состояния контрольного автомата
  */
typedef enum {
	TRNG_STATE_Reset 			= TRNG_STAT_STATE_Reset,			/*!< Сброс */
	TRNG_STATE_StartUp 			= TRNG_STAT_STATE_StartUp,			/*!< Запуск */
	TRNG_STATE_Idle_Or_FIFOfull	= TRNG_STAT_STATE_Idle_FIFOfull,	/*!< Холостая работа / FIFO заполнен */
	TRNG_STATE_FIFOfill			= TRNG_STAT_STATE_FIFOfill,			/*!< Заполнение FIFO */
	TRNG_STATE_Error 			= TRNG_STAT_STATE_Error				/*!< Ошибка */
} TRNG_STATE_TypeDef;
#define IS_TRNG_STATE(VALUE) (((VALUE) == TRNG_STATE_Reset) || \
								((VALUE) == TRNG_STATE_StartUp) || \
								((VALUE) == TRNG_STATE_Idle_FIFOfull) || \
								((VALUE) == TRNG_STATE_FIFOfill) || \
								((VALUE) == TRNG_STATE_Error))

/**
  * @brief  Кольца генератора
  */
typedef enum {
	TRNG_OSC_0,		/*!< Кольцо генератора 0 */
	TRNG_OSC_1,		/*!< Кольцо генератора 1 */
	TRNG_OSC_2,		/*!< Кольцо генератора 2 */
	TRNG_OSC_3,		/*!< Кольцо генератора 3 */
	TRNG_OSC_4,		/*!< Кольцо генератора 4 */
	TRNG_OSC_5,		/*!< Кольцо генератора 5 */
	TRNG_OSC_6,		/*!< Кольцо генератора 6 */
	TRNG_OSC_7,		/*!< Кольцо генератора 7 */
	TRNG_OSC_8,		/*!< Кольцо генератора 8 */
	TRNG_OSC_9,		/*!< Кольцо генератора 9 */
	TRNG_OSC_10,	/*!< Кольцо генератора 10 */
	TRNG_OSC_11,	/*!< Кольцо генератора 11 */
	TRNG_OSC_12,	/*!< Кольцо генератора 12 */
	TRNG_OSC_13,	/*!< Кольцо генератора 13 */
	TRNG_OSC_14,	/*!< Кольцо генератора 14 */
	TRNG_OSC_15,	/*!< Кольцо генератора 15 */
	TRNG_OSC_16,	/*!< Кольцо генератора 16 */
	TRNG_OSC_17,	/*!< Кольцо генератора 17 */
	TRNG_OSC_18,	/*!< Кольцо генератора 18 */
	TRNG_OSC_19,	/*!< Кольцо генератора 19 */
	TRNG_OSC_20,	/*!< Кольцо генератора 20 */
	TRNG_OSC_21,	/*!< Кольцо генератора 21 */
	TRNG_OSC_22,	/*!< Кольцо генератора 22 */
	TRNG_OSC_23,	/*!< Кольцо генератора 23 */
	TRNG_OSC_24,	/*!< Кольцо генератора 24 */
	TRNG_OSC_25,	/*!< Кольцо генератора 25 */
	TRNG_OSC_26,	/*!< Кольцо генератора 26 */
	TRNG_OSC_27,	/*!< Кольцо генератора 27 */
	TRNG_OSC_28,	/*!< Кольцо генератора 28 */
	TRNG_OSC_29,	/*!< Кольцо генератора 29 */
	TRNG_OSC_30,	/*!< Кольцо генератора 30 */
	TRNG_OSC_31,	/*!< Кольцо генератора 31 */
} TRNG_OSC_Num_TypeDef;
#define IS_TRNG_OSC_NUM(VALUE)  (((VALUE) == TRNG_OSC_0) ||  \
								((VALUE) == TRNG_OSC_1) ||  \
								((VALUE) == TRNG_OSC_2) ||  \
								((VALUE) == TRNG_OSC_3) ||  \
								((VALUE) == TRNG_OSC_4) ||  \
								((VALUE) == TRNG_OSC_5) ||  \
								((VALUE) == TRNG_OSC_6) ||  \
								((VALUE) == TRNG_OSC_7) ||  \
								((VALUE) == TRNG_OSC_8) ||  \
								((VALUE) == TRNG_OSC_9) ||  \
								((VALUE) == TRNG_OSC_10) || \
								((VALUE) == TRNG_OSC_11) || \
								((VALUE) == TRNG_OSC_12) || \
								((VALUE) == TRNG_OSC_13) || \
								((VALUE) == TRNG_OSC_14) || \
								((VALUE) == TRNG_OSC_15) || \
								((VALUE) == TRNG_OSC_16) ||  \
								((VALUE) == TRNG_OSC_17) ||  \
								((VALUE) == TRNG_OSC_18) ||  \
								((VALUE) == TRNG_OSC_19) ||  \
								((VALUE) == TRNG_OSC_20) ||  \
								((VALUE) == TRNG_OSC_21) ||  \
								((VALUE) == TRNG_OSC_22) ||  \
								((VALUE) == TRNG_OSC_23) ||  \
								((VALUE) == TRNG_OSC_24) ||  \
								((VALUE) == TRNG_OSC_25) || \
								((VALUE) == TRNG_OSC_26) || \
								((VALUE) == TRNG_OSC_27) || \
								((VALUE) == TRNG_OSC_28) || \
								((VALUE) == TRNG_OSC_29) || \
								((VALUE) == TRNG_OSC_30) || \
								((VALUE) == TRNG_OSC_31))

typedef struct {
	FunctionalState 					PseudoRandomEnable;			/*!< Выбор между ИГСЧ и псевдослучайным генератором											*/
//	FunctionalState 					TestSourceEnable;			/*!< Выбор источника входных данных между:
//	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 0: Источник шума
//	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 	 1: Регистр с тестовыми данными TESTDATA													*/
	FunctionalState 					BypassHandler;				/*!< Флаг пропуска функции обработки 														*/
//	FunctionalState 					ITOnAnyTestFail;			/*!< Включение прерываний при провале какого-либо теста работоспособности					*/
//	FunctionalState 					ITOnFIFOfull;				/*!< Включение прерывания при заполнении буфера FIFO										*/
	FunctionalState 					ForceGenerator;				/*!< Принудительный запуск генераторов при заполнении буфера FIFO							*/
//	FunctionalState 					IgnoreHardwareTests;		/*!< Игнорирование результатов тестов работоспобности										*/
	uint32_t 							AmountBlocksForHandler;		/*!< Число 128-битных блоков в функции обработки принимает значения от 1 до 15		     	*/
	FunctionalState 					FIFOfillOnStart;			/*!< Флаг разрешения записи в буфер FIFO выборок во время запуска							*/
//	FunctionalState						RepeatTestDisable;			/*!< Отключение всех тестов на повторения													*/
//	FunctionalState 					ProportionTestDisable;		/*!< Отключение всех тестов на пропорции													*/
//	TRNG_AUTOCORRELATIONDISABLE_TypeDef AutocorrelationTestDisable;	/*!< Отключение отдельных проверок со смещением в тесте на автокорреляцию					*/
//	TRNG_CORRELATIONDISABLE_TypeDef 	CorrelationTestDisable;		/*!< Отключение отдельных проверок со смещением в тесте на корреляцию						*/
	TRNG_BLENDMETHOD_TypeDef 			BlendMethod;				/*!< Выбор метода смешивания																*/

	uint32_t WarmPeriod;
	uint32_t CoolPeriod;
	uint32_t SamplePeriod;
} TRNG_Init_TypeDef;

// todo Возможно вынести тесты в отдельную структуру

/**
  * @}
  */

/** @defgroup TRNG_Exported_Functions Функции
  * @{
  */

void TRNG_DeInit(void);
void TRNG_Init(TRNG_Init_TypeDef* InitStruct);
void TRNG_StructInit(TRNG_Init_TypeDef* InitStruct);
void TRNG_GenerateKey(uint32_t *key, uint32_t keyLength);

/**
  * @brief   Запуск ИГСЧ
  * @param   state Состояние запуска ИГСЧ
  * @retval  void
  */
__STATIC_INLINE void TRNG_StartCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_START_Msk, state << TRNG_CR_START_Pos);
}

/**
  * @brief   Выбор между ИГСЧ и псевдослучайным генератором
  * @param   state Выбор режима 0 - ИГСЧ асинхронный независимый генератор, 1 - псевдослучайный генератор
  * @retval  void
  */
__STATIC_INLINE void TRNG_PseudorandomGeneratorCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_LFSR_Msk, state << TRNG_CR_LFSR_Pos);
}

/**
  * @brief   Выбор источника данных для функции обработки и непрерывных тестов
  * @param   state Источник данных 0 - шум, 1 - тестовые данные
  * @retval  void
  */
__STATIC_INLINE void TRNG_TestSourceCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_TESTEN_Msk, state << TRNG_CR_TESTEN_Pos);
}

/**
  * @brief   Пропуск функции обработки
  * @param   state Флаг использования функции обработки 0 - использование функции обработки, 1 - пропуск функции обработки
  * @retval  void
  */
__STATIC_INLINE void TRNG_BypassHandlerCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_CONDBYPASS_Msk, state << TRNG_CR_CONDBYPASS_Pos);
}

/**
  * @brief   Включить прерывание по провалу теста
  * @param   state Флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void TRNG_ITTestFailCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_TFAILINTEN_Msk, state << TRNG_CR_TFAILINTEN_Pos);
}

/**
  * @brief   Включить прерывание по заполнению буфера FIFO
  * @param   state Флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void TRNG_ITFIFOfullCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_FFULLINTEN_Msk, state << TRNG_CR_FFULLINTEN_Pos);
}

/**
  * @brief   Очистка информационного канала и переход КА в режим сброса.
  * 		 Этот бит не очищается автоматически!
  * @param   state Флаг включения сброса
  * @retval  void
  */
__STATIC_INLINE void TRNG_SwResetCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_SOFTRST_Msk, state << TRNG_CR_SOFTRST_Pos);
}

/**
  * @brief   Принудительный запуск генераторов, когда FIFO заполнен
  * @param   state Флаг принудительного запуска генераторов
  * @retval  void
  */
__STATIC_INLINE void TRNG_ForceGeneratorCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_FORCEROS_Msk, state << TRNG_CR_FORCEROS_Pos);
}

/**
  * @brief   Игнорирование результатов тестов работоспособности во время запуска и работы,
  * 		 также обход фазы StartUp КА
  * @param   state Флаг игнорирования тестов
  * @retval  void
  */
__STATIC_INLINE void TRNG_IgnoreHardwareTestsCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_FORCEROS_Msk, state << TRNG_CR_FORCEROS_Pos);
}

/**
  * @brief   Установка количество 128-битных блоков для функции обработки
  * @param   countBlock Количество блоков для функции обработки
  * 		 Нулевое значение не допускается
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetBlockAmountForHandler(uint32_t countBlock)
{
	assert_param(IS_TRNG_COUNTBLOCK(countBlock));

	MODIFY_REG(TRNG->CR, TRNG_CR_COUNTBLOCK_Msk, countBlock << TRNG_CR_COUNTBLOCK_Pos);
}

/**
  * @brief   Получние количества 128-битных блоков для функции обработки
  * @retval  countBlock Количество блоков для функции обработки
  */
__STATIC_INLINE uint32_t TRNG_GetBlockAmountForHandlerCmd()
{
	return (uint32_t) ((READ_REG(TRNG->CR) & TRNG_CR_COUNTBLOCK_Msk) >> TRNG_CR_COUNTBLOCK_Pos);
}

/**
  * @brief   Разрешение записи выборок в FIFO во время запуска
  * @param   state Флаг разрешения записи
  * @retval  void
  */
__STATIC_INLINE void TRNG_FIFOfillOnStartCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_FIFOFILLST_Msk, state << TRNG_CR_FIFOFILLST_Pos);
}

/**
  * @brief   Отключение тестов на повторения
  * @param   state Флаг отключения тестов
  * @retval  void
  */
__STATIC_INLINE void TRNG_RepeatTestDisableCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_REPTSTDIS_Msk, state << TRNG_CR_REPTSTDIS_Pos);
}

/**
  * @brief   Отключение тестов на пропорции
  * @param   state флаг отключения тестов
  * @retval  void
  */
__STATIC_INLINE void TRNG_ProportionTestDisableCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_PROPTSTDIS_Msk, state << TRNG_CR_PROPTSTDIS_Pos);
}

/**
  * @brief   Отключение отдельных проверок со смещением на автокорреляцию
  * @param   state флаги отключения тестов
  * @retval  void
  */
__STATIC_INLINE void TRNG_AutoCorrelationTestDisableConfig(TRNG_AUTOCORRELATIONDISABLE_TypeDef state)
{
	assert_param(IS_TRNG_AUTOCORRELATIONDISABLE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_AUTOCORRDIS_Msk, state << TRNG_CR_AUTOCORRDIS_Pos);
}

/**
  * @brief   Отключение отдельных проверок со смещением на корреляцию
  * @param   state флаги отключения тестов
  * @retval  void
  */
__STATIC_INLINE void TRNG_CorrelationTestDisableConfig(TRNG_CORRELATIONDISABLE_TypeDef state)
{
	assert_param(IS_TRNG_CORRELATIONDISABLE(state));

	MODIFY_REG(TRNG->CR, TRNG_CR_CORRTSTDIS_Msk, state << TRNG_CR_CORRTSTDIS_Pos);
}

/**
  * @brief   Выбор метода смешивания
  * @param   method метод смешнивания
  * @retval  void
  */
__STATIC_INLINE void TRNG_BlendMethodConfig(TRNG_BLENDMETHOD_TypeDef method)
{
	assert_param(IS_TRNG_BLENDMETHOD(method));

	MODIFY_REG(TRNG->CR, TRNG_CR_BLENDMETHOD_Msk, method << TRNG_CR_BLENDMETHOD_Pos);
}


/**
  * @brief   Очистка буфера FIFO
  * @retval  void
  */
__STATIC_INLINE void TRNG_ClearFIFO()
{
	WRITE_REG(TRNG->FIFOLEV, 0);
}

/**
  * @brief   Получение количества доступных 32-битных слов в буфере FIFO
  * @retval  length количество доступных 32-битных слов в буфере FIFO
  */
__STATIC_INLINE uint32_t TRNG_GetFIFOlength()
{
	return (uint32_t) READ_REG(TRNG->FIFOLEV);
}

/**
  * @brief   Установка порогового уровня буфера FIFO, ниже которого модуль начинает пополнять FIFO,
  * 		 выражен в количестве 128-битных блоков
  * @param   threshold Пороговый уровень буфера FIFO, выражен в количестве 128-битных блоков
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetFIFOthreshold(uint32_t threshold)
{
	WRITE_REG(TRNG->FIFOTHR, threshold);
}

/**
  * @brief   Получение порогового уровня буфера FIFO, ниже которого модуль начинает пополнять FIFO,
  * 		 Выражен в количестве 128-битных блоков
  * @retval  threshold Пороговый уровень буфера FIFO, выражен в количестве 128-битных блоков
  */
__STATIC_INLINE uint32_t TRNG_GetFIFOthreshold()
{
	return (uint32_t) READ_REG(TRNG->FIFOTHR);
}

/**
  * @brief   Получение макимального количества 32-разрядных слов, которые могут быть сохранены в FIFO
  * @retval  depth максимальное количество 32-разрядных слов, которые могут быть сохранены в FIFO
  */
__STATIC_INLINE uint32_t TRNG_GetFIFOdepth()
{
	return (uint32_t) READ_REG(TRNG->FIFODEP);
}

/**
  * @brief   Получение 32-битного слова, которое составляет часть ключа AES, который используется в функции обработки
  * @param   idx Индекс 32-битного слова
  * 		 0 - байты [0-3], 1 - байты [4-7], 2 - байты [8-11], 3 - байты [12-15] ключа AES
  * @retval  key значение байт AES ключа
  */
__STATIC_INLINE uint32_t TRNG_GetKeyWord(TRNG_KEY_TypeDef key)
{
	assert_param(IS_TRNG_KEY(key));

	return (uint32_t) READ_REG(TRNG->KEY[(uint32_t) key].KEY);
}

/**
  * @brief   Установка 32-битного слова, которое составляет часть ключа AES, который используется в функции обработки
  * @param   key Индекс 32-битного слова
  * 		 0 - байты [0-3], 1 - байты [4-7], 2 - байты [8-11], 3 - байты [12-15] ключа AES
  * @param   val значение байт AES ключа
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetKeyWord(TRNG_KEY_TypeDef key, uint32_t val)
{
	assert_param(IS_TRNG_KEY(key));

	WRITE_REG(TRNG->KEY[(uint32_t) key].KEY, val);
}

/**
  * @brief   Установка тестовых данных для функции обработки или непрерывных тестов
  * @param   testData Тестовые данные
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetTestData(uint32_t testData)
{
	WRITE_REG(TRNG->TESTDATA, testData);
}

/**
  * @brief   Получение тестовых данных для функции обработки или непрерывных тестов
  * @retval  testData Тестовые данные
  */
__STATIC_INLINE uint32_t TRNG_GetTestData()
{
	return (uint32_t) READ_REG(TRNG->TESTDATA);
}

/**
  * @brief   Установка предельного значения для теста на повторение
  * @param   cutOff Предельное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetRepeatTestCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_REPEATTESTCUTOFF(cutOff));

	WRITE_REG(TRNG->REPTSTCUTOFF, cutOff);
}

/**
  * @brief   Получение предельного значения для теста на повторение
  * @retval  cutOff Предельное значение
  */
__STATIC_INLINE uint32_t TRNG_GetRepeatTestCutOff()
{
	return (uint32_t) READ_REG(TRNG->REPTSTCUTOFF);
}

/**
  * @brief   Установка предельного значения для теста на пропорции
  * @param   cutOff Предельное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetProportionTestCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_PROPTESTCUTOFF(cutOff));

	WRITE_REG(TRNG->PROPTESTCUTOFF, cutOff);
}

/**
  * @brief   Получение предельного значения для теста на пропорции
  * @retval  cutOff Предельное значение
  */
__STATIC_INLINE uint32_t TRNG_GetProportionTestCutOff()
{
	return (uint32_t) READ_REG(TRNG->PROPTESTCUTOFF);
}


/**
  * @brief   Возвращает состояние записи в регистр TESTDATA
  * @retval  state Состояние записи
  */
__STATIC_INLINE FunctionalState TRNG_IsTestDataWriting()
{
	return (FunctionalState) ((READ_REG(TRNG->STAT) & TRNG_STAT_DATABUSYTEST_Msk) >> TRNG_STAT_DATABUSYTEST_Pos);
}

/**
  * @brief   Возвращает состояние контрольного автомата
  * @retval  state Состояние КА
  */
__STATIC_INLINE TRNG_STATE_TypeDef TRNG_GetState()
{
	return (TRNG_STATE_TypeDef) ((READ_REG(TRNG->STAT) & TRNG_STAT_STATE_Msk) >> TRNG_STAT_STATE_Pos);
}

/**
  * @brief   Возвращает флаг провала теста на повторения
  * @retval  status Состояние теста
  */
__STATIC_INLINE OperationStatus TRNG_IsRepeatTestFail()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_REPTESTFAIL_Msk) >> TRNG_STAT_REPTESTFAIL_Pos);
}

/**
  * @brief   Возвращает флаг провала теста на пропорции
  * @retval  status Состояние теста
  */
__STATIC_INLINE OperationStatus TRNG_IsProportionTestFail()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_PROPTESTFAIL_Msk) >> TRNG_STAT_PROPTESTFAIL_Pos);
}

/**
  * @brief   Возвращает флаг, информирующий о том, что любой из включенных тестов работоспособности провален
  * @retval  status Состояние теста
  */
__STATIC_INLINE OperationStatus TRNG_IsAnyTestFail()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_ANYTESTFAIL_Msk) >> TRNG_STAT_ANYTESTFAIL_Pos);
}

/**
  * @brief   Возвращает флаг, информирующий о том, буфер FIFO заполнен
  * @retval  status Состояние полного буфера FIFO
  */
__STATIC_INLINE OperationStatus TRNG_IsFIFOfull()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_FIFOFULL_Msk) >> TRNG_STAT_FIFOFULL_Pos);
}

/**
  * @brief   Возвращает флаг, информирующий о том, что произошел сбой хотя бы одного теста запуска
  * @retval  status Состояние тестов запуска
  */
__STATIC_INLINE OperationStatus TRNG_IsStartUpFail()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_STARTUPFAIL_Msk) >> TRNG_STAT_STARTUPFAIL_Pos);
}

/**
  * @brief   Возвращает долю проваленных тестов на повторения
  * @retval  Val Доля проваленных тестов на повторения
  */
__STATIC_INLINE uint32_t TRNG_GetRepeatTestFails()
{
	return (uint32_t) ((READ_REG(TRNG->STAT) & TRNG_STAT_REPTSTFAILSH_Msk) >> TRNG_STAT_REPTSTFAILSH_Pos);
}

/**
  * @brief   Возвращает долю проваленных тестов на пропорции
  * @retval  Val Доля проваленных тестов на пропорции
  */
__STATIC_INLINE uint32_t TRNG_GetProportionsTestFails()
{
	return (uint32_t) ((READ_REG(TRNG->STAT) & TRNG_STAT_PRTSTFAILSH_Msk) >> TRNG_STAT_PRTSTFAILSH_Pos);
}

/**
  * @brief   Возвращает флаг, информирующий о том, что функция обработки прорабатывает данные медленнее, чем они ей выдаюстя
  * @retval  status Флаг, информирующий, что функция обработки прорабатывает данные медленнее, чем они ей выдаюстя
  */
__STATIC_INLINE OperationStatus TRNG_IsHandlerSlow()
{
	return (OperationStatus) ((READ_REG(TRNG->STAT) & TRNG_STAT_CONDSLOW_Msk) >> TRNG_STAT_CONDSLOW_Pos);
}

/**
  * @brief   Установка количества тактов, ожидаемых во время процесса прогрева
  * @param   val Количество тактов
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetWarmPeriod(uint32_t val)
{
	WRITE_REG(TRNG->WARMPERIOD, val);
}

/**
  * @brief   Получение количества тактов, ожидаемых во время процесса прогрева
  * @retval  val Количество тактов
  */
__STATIC_INLINE uint32_t TRNG_GetWarmPeriod()
{
	return (uint32_t) READ_REG(TRNG->WARMPERIOD);
}


/**
  * @brief   Переключение состояния осциллятора генератора
  * @param	 state Новое состояние осицллятора
  * @param   osc Номер осциллятора
  * @retval  void
  */
__STATIC_INLINE void TRNG_OscillatorCmd(FunctionalState state, TRNG_OSC_Num_TypeDef osc)
{
	assert_param(IS_FUNCTIONAL_STATE(state));
	assert_param(IS_TRNG_OSC_NUM(osc));

	MODIFY_REG(TRNG->DISOSC, 1 << (uint32_t) osc, state << (uint32_t) osc);
}

/**
  * @brief   Установка количества тактов между моментами выборки
  * @param	 period Количество тактов
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetSamplePeriod(uint32_t period)
{
	WRITE_REG(TRNG->SAMPERIOD, period);
}

/**
  * @brief   Получение количества тактов между моментами выборки
  * @retval  period Количество тактов
  */
__STATIC_INLINE uint32_t TRNG_GetSamplePeriod()
{
	return (uint32_t) READ_REG(TRNG->SAMPERIOD);
}

/**
  * @brief   Получение количества инверторов
  * @retval  Val Количество инверторов
  */
__STATIC_INLINE uint32_t TRNG_GetInvertorCount()
{
	return (uint32_t) ((READ_REG(TRNG->HWCFG) & TRNG_HWCFG_INVCOUNT_Msk) >> TRNG_HWCFG_INVCOUNT_Pos);
}

/**
  * @brief   Получение количества тестов на автокорреляцию
  * @retval  Val Количество тестов
  */
__STATIC_INLINE uint32_t TRNG_GetAutoCorrelationTestCount()
{
	return (uint32_t) ((READ_REG(TRNG->HWCFG) & TRNG_HWCFG_AUTOCORRTEST_Msk) >> TRNG_HWCFG_AUTOCORRTEST_Pos);
}

/**
  * @brief   Плучение значение глубины буфера FIF
  * @retval  Val Глубина буфера
  */
__STATIC_INLINE uint32_t TRNG_GetFIFOHardwareDepth()
{
	return (uint32_t) ((READ_REG(TRNG->HWCFG) & TRNG_HWCFG_FIFODEP_Msk) >> TRNG_HWCFG_FIFODEP_Pos);
}

/**
  * @brief   Получение количества тактов, ожидаемых во время цикла ожидания в холодном режиме
  * @param   val Количество тактов
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetCoolPeriod(uint32_t val)
{
	WRITE_REG(TRNG->COOLDPERIOD, val);
}


/**
  * @brief   Получение количества тактов, ожидаемых во время цикла ожидания в холодном режиме
  * @retval  val Количество тактов
  */
__STATIC_INLINE uint32_t TRNG_GetCoolPeriod()
{
	return (uint32_t) READ_REG(TRNG->COOLDPERIOD);
}

/**
  * @brief   Установка граничного значения для задержки выборки 0 в автокорреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetAutoCorrelationZeroCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->AUTOCORRTESTCUTOFF0, TRNG_AUTOCORRTESTCUTOFF0_ZEROCUTOFF_Msk, cutOff << (uint32_t) TRNG_AUTOCORRTESTCUTOFF0_ZEROCUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки 0 в автокорреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetAutoCorrelationZeroCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->AUTOCORRTESTCUTOFF0) & TRNG_AUTOCORRTESTCUTOFF0_ZEROCUTOFF_Msk) >> TRNG_AUTOCORRTESTCUTOFF0_ZEROCUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +1 в автокорреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetAutoCorrelationOneCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->AUTOCORRTESTCUTOFF0, TRNG_AUTOCORRTESTCUTOFF0_ONECUTOFF_Msk, cutOff << (uint32_t) TRNG_AUTOCORRTESTCUTOFF0_ONECUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +1 в автокорреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetAutoCorrelationOneCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->AUTOCORRTESTCUTOFF0) & TRNG_AUTOCORRTESTCUTOFF0_ONECUTOFF_Msk) >> TRNG_AUTOCORRTESTCUTOFF0_ONECUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +2 в автокорреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetAutoCorrelationTwoCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->AUTOCORRTESTCUTOFF1, TRNG_AUTOCORRTESTCUTOFF1_TWOCUTOFF_Msk, cutOff << (uint32_t) TRNG_AUTOCORRTESTCUTOFF1_TWOCUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +2 в автокорреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetAutoCorrelationTwoCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->AUTOCORRTESTCUTOFF1) & TRNG_AUTOCORRTESTCUTOFF1_TWOCUTOFF_Msk) >> TRNG_AUTOCORRTESTCUTOFF1_TWOCUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +3 в автокорреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetAutoCorrelationThreeCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->AUTOCORRTESTCUTOFF1, TRNG_AUTOCORRTESTCUTOFF1_THREECUTOFF_Msk, cutOff << (uint32_t) TRNG_AUTOCORRTESTCUTOFF1_THREECUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +3 в автокорреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetAutoCorrelationThreeCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->AUTOCORRTESTCUTOFF1) & TRNG_AUTOCORRTESTCUTOFF1_THREECUTOFF_Msk) >> TRNG_AUTOCORRTESTCUTOFF1_THREECUTOFF_Pos);
}


/**
  * @brief   Установка граничного значения для задержки выборки 0 в корреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetCorrelationZeroCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->CORRTESTCUTOFF0, TRNG_CORRTESTCUTOFF0_ZEROCUTOFF_Msk, cutOff << (uint32_t) TRNG_CORRTESTCUTOFF0_ZEROCUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки 0 в корреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetCorrelationZeroCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->CORRTESTCUTOFF0) & TRNG_CORRTESTCUTOFF0_ZEROCUTOFF_Msk) >> TRNG_CORRTESTCUTOFF0_ZEROCUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +1 в корреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetCorrelationOneCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->CORRTESTCUTOFF0, TRNG_CORRTESTCUTOFF0_ONECUTOFF_Msk, cutOff << (uint32_t) TRNG_CORRTESTCUTOFF0_ONECUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +1 в корреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetCorrelationOneCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->CORRTESTCUTOFF0) & TRNG_CORRTESTCUTOFF0_ONECUTOFF_Msk) >> TRNG_CORRTESTCUTOFF0_ONECUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +2 в корреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetCorrelationTwoCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->CORRTESTCUTOFF1, TRNG_CORRTESTCUTOFF1_TWOCUTOFF_Msk, cutOff << (uint32_t) TRNG_CORRTESTCUTOFF1_TWOCUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +2 в корреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetCorrelationTwoCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->CORRTESTCUTOFF1) & TRNG_CORRTESTCUTOFF1_TWOCUTOFF_Msk) >> TRNG_CORRTESTCUTOFF1_TWOCUTOFF_Pos);
}

/**
  * @brief   Установка граничного значения для задержки выборки +3 в корреляционном тесте
  * @param   cutOff Граничное значение
  * @retval  void
  */
__STATIC_INLINE void TRNG_SetCorrelationThreeCutOff(uint32_t cutOff)
{
	assert_param(IS_TRNG_CUTOFF(cutOff));

	MODIFY_REG(TRNG->CORRTESTCUTOFF1, TRNG_CORRTESTCUTOFF1_THREECUTOFF_Msk, cutOff << (uint32_t) TRNG_CORRTESTCUTOFF1_THREECUTOFF_Pos);
}

/**
  * @brief   Получение граничного значения для задержки выборки +3 в корреляционном тесте
  * @retval  cutOff Граничное значение
  */
__STATIC_INLINE uint32_t TRNG_GetCorrelationThreeCutOff()
{
	return (uint32_t) ((READ_REG(TRNG->CORRTESTCUTOFF1) & TRNG_CORRTESTCUTOFF1_THREECUTOFF_Msk) >> TRNG_CORRTESTCUTOFF1_THREECUTOFF_Pos);
}

/**
  * @brief   Получение значение ошибки автокорреляционного теста в кольцевом генераторе
  * @param   osc Номер кольца генератора
  * @retval  status Состояние ошибки
  */
__STATIC_INLINE OperationStatus TRNG_IsAutoCorrelationTestFailed(TRNG_OSC_Num_TypeDef osc)
{
	assert_param(IS_TRNG_OSC_NUM(osc));

	return (OperationStatus) ((READ_REG(TRNG->AUTOCORRTESTFAILED) & (1 << (uint32_t) osc)) >> (uint32_t) osc);
}

/**
  * @brief   Получение значение ошибки корреляционного теста в кольцевом генераторе
  * @param   osc Номер кольца генератора
  * @retval  status Состояние ошибки
  */
__STATIC_INLINE OperationStatus TRNG_IsCorrelationTestFailed(TRNG_OSC_Num_TypeDef osc)
{
	assert_param(IS_TRNG_OSC_NUM(osc));

	return (OperationStatus) ((READ_REG(TRNG->CORRTESTFAILED) & (1 << (uint32_t) osc)) >> (uint32_t) osc);
}

/**
  * @brief   Получение версии оборудования
  * @retval  version Версия оборудования
  */
__STATIC_INLINE uint32_t TRNG_GetHardwareVersion()
{
	return (uint32_t) ((READ_REG(TRNG->HWVERSION) & TRNG_HWVERSION_HWVER_Msk) >> TRNG_HWVERSION_HWVER_Pos);
}

/**
  * @brief   Получение значение в FIFO буфере
  * @retval  Val значение ячейки в FIFO
  */
__STATIC_INLINE uint32_t TRNG_GetFIFOValue()
{
	return (uint32_t) READ_REG(TRNG->FIFO[0].FIFO);
}

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_TRNG_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

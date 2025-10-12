/**
  ******************************************************************************
  * @file    plib015_HASH.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          блока HASH, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_HASH_H
#define __PLIB015_HASH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup HASH
  * @brief Драйвер для работы с HASH
  * @{
  */

/** @defgroup HASH_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup HASH_Exported_Types Типы
  * @{
  */

#define IS_HASH_NBLW(VALUE) ((VALUE) < 0x100000)
#define IS_HASH_HR(VALUE) ((VALUE) < 0x1000)

/**
  * @brief  Режим алгоритма
  */
typedef enum {
    HASH_MODE_Hash = HASH_CR_MODE_HASH,
	HASH_MODE_Hmac = HASH_CR_MODE_HMAC
} HASH_MODE_TypeDef;
#define IS_HASH_CR_MODE(VALUE) (((VALUE) == HASH_MODE_Hash) ||  \
                              ((VALUE) == HASH_MODE_Hmac))

/**
  * @brief  Длина ключа
  */
typedef enum {
    HASH_LKEY_ShortKey = HASH_CR_LKEY_HMAC_SHORT_KEY,
	HASH_LKEY_LongKey = HASH_CR_LKEY_HMAC_LONG_KEY
} HASH_LKEY_TypeDef;
#define IS_HASH_CR_LKEY(VALUE) (((VALUE) == HASH_LKEY_ShortKey) ||  \
                              ((VALUE) == HASH_LKEY_LongKey))

/**
  * @brief  Формат данных
  */
typedef enum {
    HASH_DATATYPE_Word = HASH_CR_DATATYPE_WORD,
	HASH_DATATYPE_Hword = HASH_CR_DATATYPE_HWORD,
	HASH_DATATYPE_Byte = HASH_CR_DATATYPE_BYTE,
	HASH_DATATYPE_Bit = HASH_CR_DATATYPE_BIT
} HASH_DATATYPE_TypeDef;
#define IS_HASH_CR_DATATYPE(VALUE) (((VALUE) == HASH_DATATYPE_Word) ||  \
                              ((VALUE) == HASH_DATATYPE_Hword)  ||  \
							  ((VALUE) == HASH_DATATYPE_Byte)  ||  \
							  ((VALUE) == HASH_DATATYPE_Bit))

/**
  * @brief  Алгоритм обработки
  */
typedef enum {
    HASH_ALGO_SHA1 = HASH_CR_ALGO_SHA1,
	HASH_ALGO_MD5 = HASH_CR_ALGO_MD5,
	HASH_ALGO_SHA224 = HASH_CR_ALGO_SHA224,
	HASH_ALGO_SHA256 = HASH_CR_ALGO_SHA256
} HASH_ALGO_TypeDef;
#define IS_HASH_CR_ALGO(VALUE) (((VALUE) == HASH_ALGO_SHA1) ||  \
                              ((VALUE) == HASH_ALGO_MD5)  ||  \
							  ((VALUE) == HASH_ALGO_SHA224)  ||  \
							  ((VALUE) == HASH_ALGO_SHA256))

/**
  * @brief  Структура инициализации HASH
  */
typedef struct
{
    HASH_MODE_TypeDef Mode; 				/*!< Режим алгоритма 																		*/
    HASH_LKEY_TypeDef LongKey; 				/*!< Выбор длины ключа для HMAC режима 														*/
    FunctionalState SameKey;				/*!< Использовать одинаковые внешние и внутренние ключи при использовании длинного ключа 	*/
    HASH_DATATYPE_TypeDef DataType;			/*!< Определяет формат данных для загрузки в регистр данных
     	 	 	 	 	 	 	 	 	 	 	 0: 32-битные данные, слова
     	 	 	 	 	 	 	 	 	 	 	 1: 16-битные данные, полуслова
     	 	 	 	 	 	 	 	 	 	 	 2: 8-битные данные, байты
     	 	 	 	 	 	 	 	 	 	 	 3: битовые данные																		*/
    FunctionalState DMATransmition;			/*!< Включение механизма DMA 																*/
    FunctionalState MultyDMATransmition; 	/*!< Множественная передача данных 															*/
    HASH_ALGO_TypeDef Algo;					/*!< Алгоритм хеш-функции
     	 	 	 	 	 	 	 	 	 	 	 0: SHA-1
     	 	 	 	 	 	 	 	 	 	 	 1: MD5
     	 	 	 	 	 	 	 	 	 	 	 2: SHA-224
     	 	 	 	 	 	 	 	 	 	 	 3: SHA-256																				*/
} HASH_Init_TypeDef;

/**
  * @}
  */

/** @defgroup HASH_Exported_Functions Функции
  * @{
  */

uint32_t HASH_GetHashLen(HASH_ALGO_TypeDef algo);
uint32_t HASH_GetHashBuffer(uint32_t* buffer);
void HASH_SetHashBuffer(uint32_t* buffer, uint32_t len);
void HASH_DeInit(void);
void HASH_Init(HASH_Init_TypeDef* InitStruct);
void HASH_StructInit(HASH_Init_TypeDef* InitStruct);


/**
  * @brief   Инициализация хеш-процессора
  * @param   state Состояние инициализации
  * @retval  void
  */
__STATIC_INLINE void HASH_InitCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->CR, HASH_CR_INIT_Msk, state << HASH_CR_INIT_Pos);
}

/**
  * @brief   Выбор режима алгоритма
  * @param   state Режим алгоритма
  * @retval  void
  */
__STATIC_INLINE void HASH_ModeCmd(HASH_MODE_TypeDef mode)
{
	assert_param(IS_HASH_CR_MODE(mode));

	MODIFY_REG(HASH->CR, HASH_CR_MODE_Msk, mode << HASH_CR_MODE_Pos);
}

/**
  * @brief   Выбор длинного ключа
  * @param   length Длина ключа
  * @retval  void
  */
__STATIC_INLINE void HASH_KeyLengthCmd(HASH_LKEY_TypeDef length)
{
	assert_param(IS_HASH_CR_LKEY(length));

	MODIFY_REG(HASH->CR, HASH_CR_LKEY_Msk, length << HASH_CR_LKEY_Pos);
}

/**
  * @brief   Использование одинаковыч внешних и внутренних ключей
  * @param   state Разрешение использования одинакового ключа
  * @retval  void
  */
__STATIC_INLINE void HASH_SameKeyCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->CR, HASH_CR_SAMK_Msk, state << HASH_CR_SAMK_Pos);
}

/**
  * @brief   Выбор формата данных
  * @param   dt формат данных
  * @retval  void
  */
__STATIC_INLINE void HASH_DataTypeConfig(HASH_DATATYPE_TypeDef dt)
{
	assert_param(IS_HASH_CR_DATATYPE(dt));

	MODIFY_REG(HASH->CR, HASH_CR_DATATYPE_Msk, dt << HASH_CR_DATATYPE_Pos);
}

/**
  * @brief   Включение механизма DMA
  * @param   state Состояние передач DMA
  * @retval  void
  */
__STATIC_INLINE void HASH_DMACmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->CR, HASH_CR_DMAE_Msk, state << HASH_CR_DMAE_Pos);
}

/**
  * @brief   Включение механизма MDMAT
  * @param   state Состояние передачи MDMAT
  * @retval  void
  */
__STATIC_INLINE void HASH_SetMultyDMATransmit(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->CR, HASH_CR_MDMAT_Msk, state << HASH_CR_MDMAT_Pos);
}

/**
  * @brief   Состояние MDMAT передачи
  * @retval  state Состояние передачи MDMAT
  */
__STATIC_INLINE FunctionalState HASH_GetMultyDMATransmit()
{
	return (FunctionalState) ((READ_REG(HASH->CR) & HASH_CR_MDMAT_Msk) >> HASH_CR_MDMAT_Pos);
}

/**
  * @brief   Получение количества слов в хранящихся в буфере FIFO
  * @retval  amount Количество слов в FIFO
  */
__STATIC_INLINE uint32_t HASH_GetBufferWordsAmount()
{
	return (uint32_t) ((READ_REG(HASH->CR) & HASH_CR_NBW_Msk) >> HASH_CR_NBW_Pos);
}

/**
  * @brief   Получение состояния записи в регистр DIN
  * @retval  state Состояние записи в регистр DIN
  */
__STATIC_INLINE FunctionalState HASH_DataInStatus()
{
	return (FunctionalState) ((READ_REG(HASH->CR) & HASH_CR_DINNE_Msk) >> HASH_CR_DINNE_Pos);
}

/**
  * @brief   Выбор алгоритма хэш-функции
  * @param   algo алгоритм хем-функции
  * @retval  void
  */
__STATIC_INLINE void HASH_SetAlgo(HASH_ALGO_TypeDef algo)
{
	assert_param(IS_HASH_CR_ALGO(algo));

	MODIFY_REG(HASH->CR, HASH_CR_ALGO_Msk, algo << HASH_CR_ALGO_Pos);
}

/**
  * @brief   Получение выбранного алгоритма хэш-функции
  * @retval  algo алгоритм хем-функции
  */
__STATIC_INLINE HASH_ALGO_TypeDef HASH_GetAlgo()
{
	return (HASH_ALGO_TypeDef) ((READ_REG(HASH->CR) & HASH_CR_ALGO_Msk) >> HASH_CR_ALGO_Pos);
}

/**
  * @brief   Добавление данных для формирования хеш-суммы
  * @param   data Данные для добавления
  * @retval  void
  */
__STATIC_INLINE void HASH_SetData(uint32_t data)
{
	WRITE_REG(HASH->DATAIN_bit.VAL, data);
}

/**
  * @brief   Получение последних записанных в регистр данных
  * @retval  data Последние добавленные данные
  */
__STATIC_INLINE uint32_t HASH_GetData()
{
	return (uint32_t) READ_REG(HASH->DATAIN);
}

/**
  * @brief   Выбор длины последнего слова в битах
  * @param   length длина слова в битах
  * @retval  void
  */
__STATIC_INLINE void HASH_SetLastWordLength(uint32_t length)
{
	assert_param(IS_HASH_NBLW(length));

	MODIFY_REG(HASH->STR, HASH_STR_NBLW_Msk, length << HASH_STR_NBLW_Pos);
}

/**
  * @brief   Бит начала процесса вычисления хэш-суммы
  * @param   state Бит начала процесса
  * @retval  void
  */
__STATIC_INLINE void HASH_StartCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->STR, HASH_STR_DCAL_Msk, state << HASH_STR_DCAL_Pos);
}

/**
  * @brief   Разрешение прерывания по готовности блока принятия новых данных
  * @param   state Бит разрешения прерывания
  * @retval  void
  */
__STATIC_INLINE void HASH_ITReadyReadCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->IMR, HASH_IMR_DINIE_Msk, state << HASH_IMR_DINIE_Pos);
}

/**
  * @brief   Разрешение прерывания по окончанию вычисления хеш-суммы сообщения
  * @param   state Бит разрешения прерывания
  * @retval  void
  */
__STATIC_INLINE void HASH_ITCalculationEndCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(HASH->IMR, HASH_IMR_DCIE_Msk, state << HASH_IMR_DCIE_Pos);
}

/**
  * @brief   Получение занятости хещ-процессора
  * @retval  state Бит занятости хеш-процессора
  */
__STATIC_INLINE FunctionalState HASH_BusyStatus()
{
	return (FunctionalState) ((READ_REG(HASH->SR) & HASH_SR_BUSY_Msk) >> HASH_SR_BUSY_Pos);
}

/**
  * @brief   Получение занятости интерфейса ПДП
  * @retval  state Бит занятости интерфейса ПДП
  */
__STATIC_INLINE FunctionalState HASH_DMAStatus()
{
	return (FunctionalState) ((READ_REG(HASH->SR) & HASH_SR_DMAS_Msk) >> HASH_SR_DMAS_Pos);
}

/**
  * @brief   Очистить статус прерывания о готовности принятия новых данных
  * @retval  void
  */
__STATIC_INLINE void HASH_ITReadyReadClear()
{
	MODIFY_REG(HASH->IMR, HASH_IMR_DINIE_Msk, 0 << HASH_IMR_DINIE_Pos);
}

/**
  * @brief   Очистить статус прерывания об окончании вычисления хеш-суммы
  * @retval  void
  */
__STATIC_INLINE void HASH_ITCalculationEndClear()
{
	MODIFY_REG(HASH->IMR, HASH_IMR_DCIE_Msk, 0 << HASH_IMR_DCIE_Pos);
}

/**
  * @brief   Получение последних записанных в регистр данных
  * @retval  data Последние добавленные данные
  */
__STATIC_INLINE uint32_t HASH_GetHash(uint32_t idx)
{
	assert_param(IS_HASH_HR(idx));

	return (uint32_t) READ_REG(HASH->HR[idx].HR);
}


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_HASH_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

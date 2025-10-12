/**
  ******************************************************************************
  * @file    plib015_crypto.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          CRYPTO, а также сопутствующие макроопределения и перечисления
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
#ifndef __PLIB015_CRYPTO_H
#define __PLIB015_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup CRYPTO
  * @brief Драйвер для работы с CRYPTO
  * @{
  */

/** @defgroup CRYPTO_Exported_Defines Константы
  * @{
  */

/**
  * @}
  */

/** @defgroup CRYPTO_Exported_Types Типы
  * @{
  */

#define IS_CRYPTO_IV(VALUE) ((VALUE) < 0x100)
#define IS_CRYPTO_TEXT_IN(VALUE) ((VALUE) < 0x100)
#define IS_CRYPTO_TEXT_OUT(VALUE) ((VALUE) < 0x100)
#define IS_CRYPTO_KEY(VALUE) ((VALUE) < 0x1000)


/**
  * @brief  Выбор режима
  */
typedef enum {
    CRYPTO_Mode_ECB = CRYPTO_CONTROL_MODE_ECB,  /*!< Режим электронной кодовой книги */
    CRYPTO_Mode_CBC = CRYPTO_CONTROL_MODE_CBC, 	/*!< Режим сцепления блоков шифротекста */
    CRYPTO_Mode_CTR = CRYPTO_CONTROL_MODE_CTR,  /*!< Режим счётчика */
    CRYPTO_Mode_GCM = CRYPTO_CONTROL_MODE_GCM 	/*!< Режим счётчика с аутентификацией Галуа */
} CRYPTO_Mode_TypeDef;

#define IS_CRYPTO_MODE(VALUE) (((VALUE) == CRYPTO_Mode_ELECTRONIC_CODEBOOK) ||    \
                                  ((VALUE) == CRYPTO_Mode_CIPHER_BLOCK_CHAINING) ||    \
                                  ((VALUE) == CRYPTO_Mode_COUNTER_MODE) || \
                                  ((VALUE) == CRYPTO_Mode_GALOIS_COUNTER_MODE))

/**
  * @brief  Выбор алгоритма
  */
typedef enum {
    CRYPTO_Algo_AES_128 =  CRYPTO_CONTROL_ALGORITHM_AES_128,
    CRYPTO_Algo_AES_256 =  CRYPTO_CONTROL_ALGORITHM_AES_256,
    CRYPTO_Algo_MAGMA = CRYPTO_CONTROL_ALGORITHM_Magma,
    CRYPTO_Algo_KUZNECHIK = CRYPTO_CONTROL_ALGORITHM_Kuznechik
} CRYPTO_Algo_TypeDef;

#define IS_CRYPTO_ALGO(VALUE) (((VALUE) == CRYPTO_Algo_AES_128) ||    \
                                  ((VALUE) == CRYPTO_Algo_AES_256) ||    \
                                  ((VALUE) == CRYPTO_Algo_MAGMA) || \
                                  ((VALUE) == CRYPTO_Algo_KUZNECHIK))

/**
  * @brief  Выбор направлени
  */
typedef enum {
    CRYPTO_Dir_Encrypt = CRYPTO_CONTROL_DIRECTION_Encrypt,   /*!< Шифрование */
    CRYPTO_Dir_Decrypt = CRYPTO_CONTROL_DIRECTION_Decrypt,   /*!< Дешифрование */
} CRYPTO_Dir_TypeDef;

#define IS_CRYPTO_DIR(VALUE) (((VALUE) == CRYPTO_Dir_Encryption) ||    \
                              ((VALUE) == CRYPTO_Dir_Decryption))

/**
  * @brief  Выбор фазы обработки пакета в режиме GALOIS_COUNTER_MODE
  */
typedef enum {
    CRYPTO_GCM_PHASE_INIT =  CRYPTO_CONTROL_GCM_PHASE_GCM_INIT,   			/*!< Инициализационная фаза режима Галуа */
    CRYPTO_GCM_PHASE_HEADER =  CRYPTO_CONTROL_GCM_PHASE_GCM_HEADER,		    /*!< Создание блока дополнительных аутентификаций режима Галуа */
    CRYPTO_GCM_PHASE_PAYLOAD = CRYPTO_CONTROL_GCM_PHASE_GCM_PAYLOAD,      	/*!< Непосредственно шифрование в режиме Галуа */
    CRYPTO_GCM_PHASE_LAST_BLOCK = CRYPTO_CONTROL_GCM_PHASE_GCM_LAST_BLOCK	/*!< Запись последнего шифрованного блока в режиме Галуа в специальном формате */
} CRYPTO_GCM_PHASE_TypeDef;

#define IS_CRYPTO_GCM_PHASE(VALUE) (((VALUE) == CRYPTO_GCM_PHASE_INIT) ||    \
                                  ((VALUE) == CRYPTO_GCM_PHASE_HEADER) ||    \
                                  ((VALUE) == CRYPTO_GCM_PHASE_PAYLOAD) || \
                                  ((VALUE) == CRYPTO_GCM_PHASE_LAST_BLOCK))

/**
  * @brief  Сведения об обнаруженных некорректных словах в прочитаном дескрипторе
  */
typedef enum {
	CRYPTO_BAD_DESCR_NO_ERROR = 0x0,		/*!< Нет ошибок */
	CRYPTO_BAD_DESCR_CONTROL = 0x1,			/*!< Ошибка в слове управления DMA */
	CRYPTO_BAD_DESCR_TEXT_IN_ADDR = 0x2,	/*!< Ошибка в адресе текста источника */
	CRYPTO_BAD_DESCR_TEXT_OUT_ADDR = 0x4,	/*!< Ошибка в адресе текста назначения*/
	CRYPTO_BAD_DESCR_NEXT_DESCR = 0x8		/*!< Ошибка в адресе следующего дескриптора */
} CRYPTO_BAD_DESCR_TypeDef;

/**
  * @brief  Сведения об области памяти на которую пришелся ответ ERROR на транзакцию по шине AHB
  */
typedef enum {
	CRYPTO_AHB_ERROR_NO_ERROR = 0x0,
	CRYPTO_AHB_ERROR_READ_DESCR = 0x1,
	CRYPTO_AHB_ERROR_READ_TEXT_IN = 0x2,
	CRYPTO_AHB_ERROR_WRITE_TEXT_OUT = 0x4
} CRYPTO_AHB_ERROR_TypeDef;

/**
  * @brief  Наличие ключей для криптографических алгоритмов в регистре STATUS
  */
typedef enum {
	CRYPTO_KEYS_STORED_AES128 = 0x1,
	CRYPTO_KEYS_STORED_AES256 = 0x2,
	CRYPTO_KEYS_STORED_MAGMA = 0x4,
	CRYPTO_KEYS_STORED_KUZNECHIK = 0x8
} CRYPTO_KEYS_STORED_TypeDef;

/**
  * @brief  Структура адреса дескриптора DMA
  */

/**
  * @brief  Структура инициализации блока CRYPTO
  */
typedef struct {
	CRYPTO_Dir_TypeDef Direction;
	CRYPTO_Algo_TypeDef Algorithm;
	CRYPTO_Mode_TypeDef Mode;
	FunctionalState InitVectorAutoUpdate;
	FunctionalState UpdateKey;
	CRYPTO_GCM_PHASE_TypeDef GCMPhase;
} CRYPTO_Init_TypeDef;

/**
  * @brief  Структура инициализации для передачи по DMA блока CRYPTO
  */
typedef struct {
	FunctionalState ByteSwap;
	FunctionalState WordSwap;
	FunctionalState LastDescriptor;
	FunctionalState ITEnable;
	uint32_t BlocksCount;
	CRYPTO_Init_TypeDef* CryptoSettings;
	// Pointer to @ref CRYPTO_DMAInit_TypeDef
	void* NextDescriptor;
	void* SourceAddress;
	void* DestinationAddress;
	CRYPTO_DMA_DESCR_TypeDef* DescriptorPtr;
} CRYPTO_DMAInit_TypeDef;



/**
  * @}
  */

/** @defgroup CRYPTO_Exported_Functions Функции
  * @{
  */

void CRYPTO_StructInit(CRYPTO_Init_TypeDef* InitStruct);
void CRYPTO_DMAStructInit(CRYPTO_DMAInit_TypeDef* DMAStruct, CRYPTO_Init_TypeDef* InitStruct);
uint32_t CRYPTO_InitDMADescriptor(CRYPTO_DMAInit_TypeDef* DMAStruct);
void CRPYTO_ProcessData(CRYPTO_DMAInit_TypeDef* DMAStruct);
void CRYPTO_SetKey(uint32_t* key, uint32_t len);

/**
  * @brief   Принудительное обновление раундовых ключей на основе значений регистров KEY_0...KEY_7
  * 		 или регистров KEY_0...KEY_3 для алгоритма AES-128
  * @pararm  state флаг обновления ключа
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_UpdateKeyCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_UPDATE_KEY_Msk, state << CRYPTO_CONTROL_UPDATE_KEY_Pos);
}

/**
  * @brief   Запрос на выполнение криптографической операции.
  * 		 Непосредственный старт может быть отложен до завершения обновления ключей.
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_StartCmd()
{
	SET_BIT(CRYPTO->CONTROL, CRYPTO_CONTROL_UPDATE_KEY_Msk);
}

/**
  * @brief   Выбор направления криптографической операции
  * @param   dir Направление криптографической операции 0 - кодирование, 1 - декодирование
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DirectionConfig(CRYPTO_Dir_TypeDef dir)
{
	assert_param(IS_CRYPTO_DIR(dir));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_DIRECTION_Msk, dir << CRYPTO_CONTROL_DIRECTION_Pos);
}

/**
  * @brief   Выбор криптографической алгоритма операции
  * @param   algo алгоритм криптографической операции
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_AlgoConfig(CRYPTO_Algo_TypeDef algo)
{
	assert_param(IS_CRYPTO_ALGO(algo));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_ALGORITHM_Msk, algo << CRYPTO_CONTROL_ALGORITHM_Pos);
}

/**
  * @brief   Выбор режима выполнения криптографической операции
  * @param   mode режим выполнения криптографической операции
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_ModeConfig(CRYPTO_Mode_TypeDef mode)
{
	assert_param(IS_CRYPTO_MODE(mode));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_MODE_Msk, mode << CRYPTO_CONTROL_MODE_Pos);
}

/**
  * @brief   Выбор режима выполнения криптографической операции
  * @param   phase установка фазы обработки пакета только для режима GCM
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_GCMPhaseConfig(CRYPTO_GCM_PHASE_TypeDef phase)
{
	assert_param(IS_CRYPTO_GCM_PHASE(phase));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_GCM_PHASE_Msk, phase << CRYPTO_CONTROL_GCM_PHASE_Pos);
}

/**
  * @brief   Разрешение автоматического обновления регистров IV_* при завершении криптографической операции
  * @param   state флаг разрешения
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_InitVectorAutoUpdateCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(CRYPTO->CONTROL, CRYPTO_CONTROL_SELF_UPDATE_Msk, state << CRYPTO_CONTROL_SELF_UPDATE_Pos);
}

/**
  * @brief   Экстренное завершение операции
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_TerminateCmd()
{
    WRITE_REG(CRYPTO->TERMINATE, 0xD0);
}

/**
  * @brief   Установка значения элемента массива вектора инициализации
  * @param   idx индекс в массиве вектора инициализации
  * @param   val значение части вектора инициализации
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_SetInitVector(uint32_t idx, uint32_t val)
{
	assert_param(IS_CRYPTO_IV(idx));

	WRITE_REG(CRYPTO->IV[idx], val);
}

/**
  * @brief   Установка значения элемента массива входного текста
  * @param   idx индекс в массиве входного текста
  * @param   val значение входного текста
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_SetTextInput(uint32_t idx, uint32_t val)
{
	assert_param(IS_CRYPTO_TEXT_IN(idx));

	WRITE_REG(CRYPTO->TEXT_IN[idx], val);
}

/**
  * @brief   Установка значения элемента массива раундовых ключей
  * @param   idx индекс в массиве раундовых ключей
  * @param   val значение элемента раундового ключа
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_SetKeyInReg(uint32_t idx, uint32_t val)
{
	assert_param(IS_CRYPTO_KEY(idx));

	WRITE_REG(CRYPTO->KEY[idx], val);
}

/**
  * @brief   Установка значения элемента массива раундовых ключей
  * @param   idx индекс в массиве раундовых ключей
  * @retval  void
  */
__STATIC_INLINE uint32_t CRYPTO_GetTextOutput(uint32_t idx)
{
	assert_param(IS_CRYPTO_TEXT_OUT(idx));

	return (uint32_t) READ_REG(CRYPTO->TEXT_OUT[idx]);
}

/**
  * @brief   Получение флага, который сообщает, что на выходе криптографического подмодуля находится результат операции над данными
  * @retval  state флаг валидности данных в TEXT_OUT
  */
__STATIC_INLINE FunctionalState CRYPTO_OutputValidStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_OUT_VALID_Msk);
}

/**
  * @brief   Получение флага, который сообщает, что раундовые ключи для текущего активного криптографического алгоритма сгенерированы
  * @retval  state флаг генерации ключей
  */
__STATIC_INLINE FunctionalState CRYPTO_KeysReadyStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_KEYS_READY_Msk);
}

/**
  * @brief   Получение флага о готовности модуля выполнять очередную криптографическую операцию и/или обновлять раундовые ключи шифрования
  * @retval  state флаг готовности модуля
  */
__STATIC_INLINE FunctionalState CRYPTO_ReadyStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_READY_Msk);
}

/**
  * @brief   Получение сведений о расчитанных раундовых ключах для алгоритмов
  * @retval  status стуктура типа @ref CRYPTO_KEYS_STORED_Typedef
  */
__STATIC_INLINE CRYPTO_KEYS_STORED_TypeDef CRYPTO_KeysStoredForAlgo()
{
	return (CRYPTO_KEYS_STORED_TypeDef) READ_REG((CRYPTO->STATUS & CRYPTO_STATUS_KEYS_STORED_Msk) >> CRYPTO_STATUS_KEYS_STORED_Pos);
}

//-----------------------IRQ-----------------------

/**
  * @brief   Включение прерывания при записи в регистры CONTROL, TEXT_IN_*, IV_* пока STATUS.READY сброшен
  * @param   state флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_ITWriteIgnoredConfig(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRYPTO->IRQ_ENABLE, CRYPTO_IRQ_ENABLE_WR_IGNORED_Msk, state << CRYPTO_IRQ_ENABLE_WR_IGNORED_Pos);
}

/**
  * @brief   Включение прерывания при переходе в режим готовности
  * @param   state флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_ITDoneConfig(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRYPTO->IRQ_ENABLE, CRYPTO_IRQ_ENABLE_DONE_Msk, state << CRYPTO_IRQ_ENABLE_DONE_Pos);
}

/**
  * @brief   Получение флага о том, что хотя бы один бит в регистре IRQ не сброшен
  * @retval  state флаг сброса в регистре IRQ
  */
__STATIC_INLINE FunctionalState CRYPTO_ITPendingStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_IRQ_PENDING_Msk);
}

//-----------------------DMA-----------------------

/**
  * @brief   Устанаваливает базовый дескриптор для DMA
  * @param   address адрес базового дескриптора, являющийся структурой типа @ref CRYPTO_DMA_DesciptorAddress_TypeDef
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_SetBaseDescriptor(uint32_t address)
{
    WRITE_REG(CRYPTO->BASE_DESCRIPTOR, address);
}

/**
  * @brief   Запускает последовательность операций в режиме DMA
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_StartCmd()
{
	SET_BIT(CRYPTO->DMA_CONTROL, CRYPTO_DMA_CONTROL_START_Msk);
}

/**
  * @brief   Инвертирование порядка байт припосылке на шину AHB
  * @param   state флаг инвертирования
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_ByteSwapCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(CRYPTO->DMA_CONTROL, CRYPTO_DMA_CONTROL_BYTES_SWAP_Msk, state << CRYPTO_DMA_CONTROL_BYTES_SWAP_Pos);
}

/**
  * @brief   Инвертирование порядка слов припосылке на шину AHB
  * @param   state флаг инвертирования
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_WordSwapCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

    MODIFY_REG(CRYPTO->DMA_CONTROL, CRYPTO_DMA_CONTROL_WORDS_SWAP_Msk, state << CRYPTO_DMA_CONTROL_WORDS_SWAP_Pos);
}

/**
  * @brief   Флаг, информирующий о том, что прочитанный дескриптор является последним
  * @retval  state является ли прочитанный дескриптор последним
  */
__STATIC_INLINE FunctionalState CRYPTO_DMA_LastStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_DMA_LAST_Msk);
}

/**
  * @brief   Получение количества обработанного DMA блоков текста
  * @retval  val количество блоков текста
  */
__STATIC_INLINE uint32_t CRYPTO_DMA_GetCounter()
{
	return (uint32_t) READ_REG((CRYPTO->STATUS & CRYPTO_STATUS_DMA_COUNTER_Msk) >> CRYPTO_STATUS_DMA_COUNTER_Pos);
}

//-----------------------IRQ-----------------------

/**
  * @brief   Включение прерывания при ошибке DMA
  * @param   state флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_ITFailConfig(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRYPTO->IRQ_ENABLE, CRYPTO_IRQ_ENABLE_DMA_FAIL_Msk, state << CRYPTO_IRQ_ENABLE_DMA_FAIL_Pos);
}

/**
  * @brief   Включение прерывания успешном выполнении дескриптора DMA
  * @param   state флаг включения прерывания
  * @retval  void
  */
__STATIC_INLINE void CRYPTO_DMA_ITDoneConfig(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	MODIFY_REG(CRYPTO->IRQ_ENABLE, CRYPTO_IRQ_ENABLE_DMA_DONE_Msk, state << CRYPTO_IRQ_ENABLE_DMA_DONE_Pos);
}


/**
  * @brief   Получение сведений об обнаруженных некорректных словах типа
  * @retval  status стуктура типа @ref CRYPTO_BAD_DESCR_TypeDef
  */
__STATIC_INLINE CRYPTO_BAD_DESCR_TypeDef CRYPTO_DMA_BadDescriptionStatus()
{
	return (CRYPTO_BAD_DESCR_TypeDef) READ_REG((CRYPTO->STATUS & CRYPTO_STATUS_BAD_DESCR_Msk) >> CRYPTO_STATUS_BAD_DESCR_Pos);
}

/**
  * @brief   Получение сведений об области памяти на которую пришелся ответ ERROR
  * @retval  status стуктура типа @ref CRYPTO_AHB_ERROR_Typedef
  */
__STATIC_INLINE CRYPTO_AHB_ERROR_TypeDef CRYPTO_DMA_AHBErrorStatus()
{
	return (CRYPTO_AHB_ERROR_TypeDef) READ_REG((CRYPTO->STATUS & CRYPTO_STATUS_AHB_ERROR_Msk) >> CRYPTO_STATUS_AHB_ERROR_Pos);
}

/**
  * @brief   Получение флага о занятости DMA выполнением дескриптора
  * @retval  state флаг занятости DMA
  */
__STATIC_INLINE FunctionalState CRYPTO_DMA_ActiveStatus()
{
	return (FunctionalState) READ_BIT(CRYPTO->STATUS, CRYPTO_STATUS_DMA_ACTIVE_Msk);
}


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_CRYPTO_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

/**
  ******************************************************************************
  * @file    plib015_qspi.h
  *
  * @brief   Файл содержит прототипы и компактные inline реализации функций для
  *          QSPI, а также сопутствующие макроопределения и перечисления
  *
  * @author  НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
  * @author  НИИЭТ, Штоколов Филипп
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
#ifndef __PLIB015_QSPI_H
#define __PLIB015_QSPI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "plib015.h"

/** @addtogroup Peripheral
  * @{
  */

/** @defgroup QSPI
  * @brief Драйвер для работы с QSPI
  * @{
  */

/** @defgroup QSPI_Exported_Defines Константы
  * @{
  */

/** @defgroup QSPI_ITSource_Define Источники прерываний QSPI
  * @{
  */

/**
   * @}
   */

/** @defgroup QSPI_Flag_Define Флаги работы QSPI
  * @{
  */


/**
  * @}
  */

/**
  * @}
  */

/** @defgroup QSPI_Exported_Types Типы
  * @{
  */

typedef enum {
	QSPI_Mode_SPI = QSPI_DCR_FMOD_SPI,			/*!< Стандартный режим SPI */
	QSPI_Mode_QSPI = QSPI_DCR_FMOD_QSPI,		/*!< Режим QSPI */
	QSPI_Mode_LoopBack = QSPI_DCR_FMOD_LOOPBACK	/*!< Test Loopback */
} QSPI_Mode_TypeDef;
#define IS_QSPI_MODE(VALUE) (((VALUE) == QSPI_DCR_FMOD_SPI) || \
                            ((VALUE) == QSPI_DCR_FMOD_QSPI)  || \
							((VALUE) == QSPI_DCR_FMOD_LOOPBACK))

/**
  * @brief  Выбор фазы сигнала SCK
  */
typedef enum {
    QSPI_SCKPhase_CaptureRise, /*!< Захват данных по переднему фронту SCK, установка по заднему */
    QSPI_SCKPhase_CaptureFall  /*!< Захват данных по заднему фронту SCK, установка по переднему */
} QSPI_SCKPhase_TypeDef;
#define IS_QSPI_SCK_PHASE(VALUE) (((VALUE) == QSPI_SCKPhase_CaptureRise) || \
                                 ((VALUE) == QSPI_SCKPhase_CaptureFall))

/**
  * @brief  Выбор полярности сигнала SCK
  */
typedef enum {
    QSPI_SCKPolarity_SteadyLow, /*!< В режиме ожидания SCK удерживается в состоянии нуля */
    QSPI_SCKPolarity_SteadyHigh /*!< В режиме ожидания SCK удерживается в состоянии единицы */
} QSPI_SCKPolarity_TypeDef;
#define IS_QSPI_SCK_POLARITY(VALUE) (((VALUE) == QSPI_SCKPolarity_SteadyLow) || \
                                    ((VALUE) == QSPI_SCKPolarity_SteadyHigh))

/**
  * @brief  Выбор направления передачи
  */
typedef enum {
    QSPI_LSBF_MSB = QSPI_TCR_LSBF_MSB, /*!< Передача старшим битом вперед */
    QSPI_LSBF_LSB = QSPI_TCR_LSBF_LSB  /*!< Передача младшим битом вперед */
} QSPI_LSBF_TypeDef;
#define IS_QSPI_LSBF(VALUE) (((VALUE) == QSPI_LSBF_MSB) || \
                            ((VALUE) == QSPI_LSBF_LSB))

/**
  * @brief  Выбор скорости передачи для стандартной передачи SPI
  */
typedef enum {
    QSPI_SPI_DataRate_Single = QSPI_TCR_DDR_SDR, /*!< Изменение данных по одному фронту QSPI_SCK */
    QSPI_SPI_DataRate_Double = QSPI_TCR_DDR_DDR  /*!< Изменение данных по обоим фронту QSPI_SCK */
} QSPI_SPI_DataRate_TypeDef;
#define IS_QSPI_SPI_DR(VALUE) (((VALUE) == QSPI_SPI_DR_Single) || \
                            ((VALUE) == QSPI_SPI_DR_Double))

/**
  * @brief  Выбор количества линий передачи для стандартной передачи SPI
  */
typedef enum {
    QSPI_SPI_IOMode_Single = QSPI_TCR_IOM_Single,	/*!< Пеоедача по одной линии данных */
    QSPI_SPI_IOMode_Double = QSPI_TCR_IOM_Double,	/*!< Передача по двум линиям данных */
	QSPI_SPI_IOMode_Quad = QSPI_TCR_IOM_Quad		/*!< Передача по четырем линиям данных */
} QSPI_SPI_IOMode_TypeDef;
#define IS_QSPI_SPI_IOMODE(VALUE) (((VALUE) == QSPI_SPI_IOMode_Single) || \
                            ((VALUE) == QSPI_SPI_IOMode_Double)			|| \
							((VALUE) == QSPI_SPI_IOMode_Quad))

/**
  * @brief  Выбор количества линий передачи для интерфейса QuadSPI
  */
typedef enum {
    QSPI_Lines_No,	/*!< Нет передачи */
    QSPI_Lines_SIO,	/*!< Пеоедача по одной линии данных */
	QSPI_Lines_DIO,	/*!< Передача по двум линиям данных */
	QSPI_Lines_QIO	/*!< Передача по четырем линиям данных */
} QSPI_IOMode_TypeDef;
#define IS_QSPI_IOMODE(VALUE) (((VALUE) == QSPI_QSPI_Lines_No) || \
                            ((VALUE) == QSPI_QSPI_Lines_SIO)	|| \
							((VALUE) == QSPI_QSPI_Lines_DIO) || \
							((VALUE) == QSPI_QSPI_Lines_QIO))

/**
  * @brief  Размер передваемых данных, актуально для фазы адреса и фазы дополнительных данных
  */
typedef enum {
    QSPI_DataSize_8,	/*!< Использование 8-ми битных данных */
	QSPI_DataSize_16,	/*!< Использование 16-ти битных данных */
	QSPI_DataSize_24,	/*!< Использование 24-ех битных данных */
	QSPI_DataSize_32	/*!< Использование 32-го битных данных */
} QSPI_DataSize_TypeDef;
#define IS_QSPI_DATASIZE(VALUE) (((VALUE) == QSPI_QSPI_DataSize_8)  || \
									((VALUE) == QSPI_QSPI_DataSize_16) || \
									((VALUE) == QSPI_QSPI_DataSize_24) || \
									((VALUE) == QSPI_QSPI_DataSize_32))
/**
  * @brief Выбор скорости передачи для интерфейса QuadSPI
  */
typedef enum {
    QSPI_DataRate_Single,	/*!< Изменение данных по одному фронту QSPI_SCK */
    QSPI_DataRate_Double	/*!< Изменение данных по обоим фронту QSPI_SCK */
} QSPI_DataRate_TypeDef;
#define IS_QSPI_DATARATE(VALUE) (((VALUE) == QSPI_QSPI_DataRate_Single)  || \
									((VALUE) == QSPI_QSPI_DataRate_Double))

/**
  * @brief  Выбор направления передачи данных для интерфейса QuadSPI
  */
typedef enum {
    QSPI_Direction_Write = QSPI_QCC_DIOD_WR, /*!< Передача данных во внешнее устройство */
    QSPI_Direction_Read  = QSPI_QCC_DIOD_RD  /*!< Чтение данных из внешнего устройства */
} QSPI_Direction_TypeDef;
#define IS_QSPI_DIR(VALUE) (((VALUE) == QSPI_QSPI_Direction_Write) || \
                            ((VALUE) == QSPI_QSPI_Direction_Read))

/**
  * @brief  Прерывания модуля QSPI
  */
typedef enum {
    QSPI_IT_Transfer_Complete = QSPI_IMR_TCIM_Msk,	/*!< Завершение передачи  */
    QSPI_IT_Transfer_Stall = QSPI_IMR_TSIM_Msk,		/*!< Останов передачи */
	QSPI_IT_TXFIFO_Empty = QSPI_IMR_TEIM_Msk,		/*!< Опустошение буфера передатчика */
	QSPI_IT_TXFIFO_Full = QSPI_IMR_TFIM_Msk,		/*!< Заполнение буфера передатчика */
	QSPI_IT_RXFIFO_Empty = QSPI_IMR_REIM_Msk,		/*!< Опустошение буфера приемника */
	QSPI_IT_RXFIFO_Full = QSPI_IMR_RFIM_Msk,		/*!< Заполнение буфера приемника */
	QSPI_IT_TX_WaterMark = QSPI_IMR_TWMIM_Msk,		/*!< Пороговое заполнение буфера передатчика */
	QSPI_IT_RX_WaterMark = QSPI_IMR_RWMIM_Msk		/*!< Пороговое заполнение буфера приемника */
} QSPI_IT_TypeDef;
#define IS_QSPI_IT(VALUE) (((VALUE) == QSPI_IT_Transfer_Complete) || \
                            ((VALUE) == QSPI_IT_Transfer_Stall) || \
							((VALUE) == QSPI_IT_TXFIFO_Empty) || \
							((VALUE) == QSPI_IT_TXFIFO_Full) || \
							((VALUE) == QSPI_IT_RXFIFO_Empty) || \
							((VALUE) == QSPI_IT_RXFIFO_Full) || \
							((VALUE) == QSPI_IT_TX_WaterMark) || \
							((VALUE) == QSPI_IT_RX_WaterMark))

/**
  * @brief  Инициализационная структура для обычной передачи SPI
  */
typedef struct {
	QSPI_SPI_IOMode_TypeDef IOMode;		/*!< Количество линий для передачи */
	QSPI_SPI_DataRate_TypeDef dataRate;	/*!< Скорость передачи */
	uint32_t dataWidth;					/*!< Размер слова передачи */
	FunctionalState TxEnable;			/*!< Флаг разрешения приема */
	FunctionalState RxEnable;			/*!< Флаг разрешения передачи */
	uint32_t SCKDiv;					/*!< Делитель частоты */
} QSPI_SPI_Init_TypeDef;

/**
  * @brief  Инициализационная структура для передачи в режиме QuadSPI
  */
typedef struct {
	uint8_t instruction;					/*!< Код инструкции для внешнего устройства */
	QSPI_IOMode_TypeDef instructionMode;	/*!< Количество линий для передачи инструкции */

	QSPI_IOMode_TypeDef addressMode;		/*!< Количество линий для передачи адреса */
	QSPI_DataSize_TypeDef addressSize;		/*!< Размер адреса */

	QSPI_IOMode_TypeDef additionalMode;		/*!< Количество линий для передачи дополнительных данных */
	QSPI_DataSize_TypeDef additionalSize;	/*!< Размер дополнительных данных */

	uint32_t waitCycles;					/*!< Количество циклов ожидания без отправки или получения данных */

	QSPI_IOMode_TypeDef dataMode;			/*!< Количество линий для передачи данных */
	QSPI_Direction_TypeDef dataDirection;	/*!< Выбор направления данных прием/передача */

	QSPI_DataRate_TypeDef dataRate;			/*!< Установка скорости передачи */
	uint32_t SCKDiv;						/*!< Делитель частоты */
} QSPI_Init_TypeDef;



#define IS_QSPI_CDIV(VALUE) ((VALUE) < 0x100)
#define IS_QSPI_WORD(VALUE) ((VALUE) < 0x20)
#define IS_QSPI_DCYCS(VALUE) ((VALUE) < 0x20)
#define IS_QSPI_WATERMARK(VALUE) ((VALUE) < 0x20)

/**
  * @}
  */

/** @defgroup QSPI_Exported_Functions Функции
  * @{
  */

/**
  * @brief   Разрешение работы приемопередатчика QSPI
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void QSPI_Cmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(QSPI->HCR_bit.DEN, State);
}

/**
  * @brief   Сброс устройства QSPI (останова активной передачи)
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void QSPI_RstCmd(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(QSPI->HCR_bit.DRS, State);
}

/**
  * @brief   Бит очистки приемного буфера FIFO
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void QSPI_RxClear(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(QSPI->HCR_bit.RXFCLR, State);
}

/**
  * @brief   Бит очистки передающего буфера FIFO
  * @param   State  Выбор состояния
  * @retval  void
  */
__STATIC_INLINE void QSPI_TxClear(FunctionalState State)
{
    assert_param(IS_FUNCTIONAL_STATE(State));

    WRITE_REG(QSPI->HCR_bit.RXFCLR, State);
}

/**
  * @brief   Настройка полярности и фазы SCK
  * @param   SCKPhase  Режим фазы
  * @param   SCKPolarity  Режим полярности
  * @retval  void
  */
__STATIC_INLINE void QSPI_SCKConfig(QSPI_SCKPhase_TypeDef SCKPhase, QSPI_SCKPolarity_TypeDef SCKPolarity)
{
  assert_param(IS_QSPI_SCK_PHASE(SCKPhase));
  assert_param(IS_QSPI_SCK_POLARITY(SCKPolarity));

  MODIFY_REG(QSPI->DCR, QSPI_DCR_CPOL_Msk | QSPI_DCR_CPHA_Msk, (SCKPhase << QSPI_DCR_CPHA_Pos) | (SCKPolarity << QSPI_DCR_CPOL_Pos));
}

/**
  * @brief   Выбор режима работы
  * @param   mode Режим работы
  * @retval  void
  */
__STATIC_INLINE void QSPI_ModeConfig(QSPI_Mode_TypeDef mode)
{
    assert_param(IS_QSPI_MODE(mode));

    WRITE_REG(QSPI->DCR_bit.FMOD, mode);
}

/**
  * @brief   Настройка делителя для получение нужной частоты SCK
  * @param   div	 Основной делитель.
  *                  Параметр принимает любое значение из диапазона 0-255.
  * @retval  void
  */
__STATIC_INLINE void QSPI_SCKDivConfig(uint32_t div)
{
    assert_param(IS_QSPI_CDIV(div));

    WRITE_REG(QSPI->DCR_bit.CDIV, div);
}

/**
  * @brief   Получение количества элементов в буфере FIFO приемника
  * @retval  count Количество элементов в буфере FIFO приемника
  */
__STATIC_INLINE uint32_t QSPI_GetRxCount()
{
    return READ_REG((QSPI->DSR & QSPI_DSR_RXFCNT_Msk) >> QSPI_DSR_RXFCNT_Pos);
}

/**
  * @brief   Получение количества элементов в буфере FIFO передатчика
  * @retval  count Количество элементов в буфере FIFO передатчика
  */
__STATIC_INLINE uint32_t QSPI_GetTxCount()
{
	return READ_REG((QSPI->DSR & QSPI_DSR_TXFCNT_Msk) >> QSPI_DSR_TXFCNT_Pos);
}

/**
  * @brief   Статус заполнения FIFO буфера приемника
  * @retval  status Флаг, информирующий о том, что FIFO буфер приемника заполнен
  */
__STATIC_INLINE FunctionalState QSPI_RFIFOFullStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_RFF_Msk);
}

/**
  * @brief   Статус пустоты FIFO буфера приемника
  * @retval  status Флаг, информирующий о том, что FIFO буфер приемника пуст
  */
__STATIC_INLINE FunctionalState QSPI_RFIFOEmptyStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_RFE_Msk);
}

/**
  * @brief   Статус заполнения буфера FIFO передатчика
  * @retval  status Флаг, информирующий о том, что FIFO буфер передатчика заполнен
  */
__STATIC_INLINE FunctionalState QSPI_TFIFOFullStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_TFF_Msk);
}

/**
  * @brief   Статус пустоты FIFO буфера передатчика
  * @retval  status Флаг, информирующий о том, что FIFO буфер передатчика пуст
  */
__STATIC_INLINE FunctionalState QSPI_TFIFOEmptyStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_TFE_Msk);
}

/**
  * @brief   Статус остановки передачи
  * @retval  status Флаг, информирующий о том, что передача приостановлена
  */
__STATIC_INLINE FunctionalState QSPI_StopStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_TST_Msk);
}

/**
  * @brief   Статус передачи
  * @retval  status Флаг, информирующий о том, что передача в процессе
  */
__STATIC_INLINE FunctionalState QSPI_InProcessStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_TIP_Msk);
}

/**
  * @brief   Статус занятости приемопередатчика
  * @retval  status Флаг, информирующий о том, что приемопередатчик занят
  */
__STATIC_INLINE FunctionalState QSPI_BusyStatus()
{
	return READ_BIT(QSPI->DSR, QSPI_DSR_BUSY_Msk);
}

/**
  * @brief   Установка размера слова данных
  * @param   length длина слова, значение от 1 до 32
  * @retval  void
  */
__STATIC_INLINE void QSPI_SetWordLength(uint32_t length)
{
	assert_param(IS_QSPI_WORD(length));

	WRITE_REG(QSPI->TCR_bit.LEN, length);
}

/**
  * @brief   Напрпавление передачи
  * @param   state Выбор направления передачи типа @ref QSPI_LSBF_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_SignificantBitConfig(QSPI_LSBF_TypeDef state)
{
	assert_param(IS_QSPI_LSBF(state));

	WRITE_REG(QSPI->TCR_bit.LSBF, state);
}

/**
  * @brief   Установка скорости передачи данных
  * @param   dataRate скорость передачи данных типа @ref QSPI_DR_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_SPIDataRateConfig(QSPI_SPI_DataRate_TypeDef dataRate)
{
	assert_param(IS_QSPI_SPI_DR(dataRate));

	WRITE_REG(QSPI->TCR_bit.DDR, dataRate);
}

/**
  * @brief   Разрешение передачи
  * @param   state Флаг разрешения
  * @retval  void
  */
__STATIC_INLINE void QSPI_TxCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	WRITE_REG(QSPI->TCR_bit.TXE, state);
}

/**
  * @brief   Разрешение приема
  * @param   state Флаг разрешения
  * @retval  void
  */
__STATIC_INLINE void QSPI_RxCmd(FunctionalState state)
{
	assert_param(IS_FUNCTIONAL_STATE(state));

	WRITE_REG(QSPI->TCR_bit.RXE, state);
}

/**
  * @brief   Выбор количества линий данных
  * @param   mode Количество линий типа @ref QSPI_IOMode_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_SPITransactionModeConfig(QSPI_SPI_IOMode_TypeDef mode)
{
	assert_param(IS_QSPI_SPI_IOMODE(mode));

	WRITE_REG(QSPI->TCR_bit.IOM, mode);
}

/**
  * @brief   Запись данных для передачи в регистр FIFO
  * @param   data данные для передачи
  * @retval  void
  */
__STATIC_INLINE void QSPI_SetTransactionData(uint32_t data)
{
	WRITE_REG(QSPI->TDR, data);
}

/**
  * @brief   Получение данных приемника из буфера FIFO
  * @retval  data данные приемника
  */
__STATIC_INLINE uint32_t QSPI_GetTransactionData()
{
	return READ_REG(QSPI->TDR);
}

/**
  * @brief   Запись количества слов в FIFO для передачи
  * @param   size Количество слов для передачи
  * @retval  void
  */
__STATIC_INLINE void QSPI_SetTransactionSize(uint32_t size)
{
	WRITE_REG(QSPI->TDS, size);
}

/**
  * @brief   Получение количества слов из буфера FIFO
  * @retval  size Количество слов приемника
  */
__STATIC_INLINE uint32_t QSPI_GetTransactionSize()
{
	return READ_REG(QSPI->TDS);
}

/**
  * @brief   Установка кода инструкции для внешнего устройства
  * @param   instruction Код инструкции, отправляемый во внешнее устройство по QuadSPI
  * @retval  void
  */
__STATIC_INLINE void QSPI_InstructionConfig(uint8_t instruction)
{
	WRITE_REG(QSPI->QCC_bit.INST, instruction);
}

/**
  * @brief   Установка режима фазы инструкции для QuadSPI
  * @param   mode режим передачи типа @ref QSPI_QSPI_IOMode_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_InstructionModeConfig(QSPI_IOMode_TypeDef mode)
{
	assert_param(IS_QSPI_IOMODE(mode));

	WRITE_REG(QSPI->QCC_bit.IMOD, mode);
}


/**
  * @brief   Установка режима фазы адреса для QuadSPI
  * @param   mode режим передачи типа @ref QSPI_QSPI_IOMode_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_AddressModeConfig(QSPI_IOMode_TypeDef mode)
{
	assert_param(IS_QSPI_IOMODE(mode));

	WRITE_REG(QSPI->QCC_bit.ADMOD, mode);
}

/**
  * @brief   Установка размера адреса для QuadSPI
  * @param   size размер типа @ref QSPI_QSPI_DataSize_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_AddressSizeConfig(QSPI_DataSize_TypeDef size)
{
	assert_param(IS_QSPI_DATASIZE(size));

	WRITE_REG(QSPI->QCC_bit.ADSIZ, size);
}

/**
  * @brief   Установка режима фазы дополнительных данных для QuadSPI
  * @param   mode режим передачи типа @ref QSPI_QSPI_IOMode_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_AdditionalModeConfig(QSPI_IOMode_TypeDef mode)
{
	assert_param(IS_QSPI_IOMODE(mode));

	WRITE_REG(QSPI->QCC_bit.ABMOD, mode);
}

/**
  * @brief   Установка размера дополнительных данных для QuadSPI
  * @param   size размер типа @ref QSPI_QSPI_DataSize_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_AdditionalSizeConfig(QSPI_DataSize_TypeDef size)
{
	assert_param(IS_QSPI_DATASIZE(size));

	WRITE_REG(QSPI->QCC_bit.ABSIZ, size);
}

/**
  * @brief   Установка количества циклов ожидания для QuadSPI
  * @param   waitCycles количество циклов ожидания принимает значения от 0 до 31
  * @retval  void
  */
__STATIC_INLINE void QSPI_WaitCyclesConfig(uint32_t waitCycles)
{
	assert_param(IS_QSPI_DCYCS(waitCycles));

	WRITE_REG(QSPI->QCC_bit.DCYCS, waitCycles);
}

/**
  * @brief   Установка режима фазы данных для QuadSPI
  * @param   mode режим передачи типа @ref QSPI_QSPI_IOMode_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_DataModeConfig(QSPI_IOMode_TypeDef mode)
{
	assert_param(IS_QSPI_IOMODE(mode));

	WRITE_REG(QSPI->QCC_bit.DMOD, mode);
}

/**
  * @brief   Установка направления передачи данных для QuadSPI
  * @param   dir напавление передачи данных типа @ref QSPI_QSPI_Direction_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_DataDirectionConfig(QSPI_Direction_TypeDef dir)
{
	assert_param(IS_QSPI_DIR(dir));

	WRITE_REG(QSPI->QCC_bit.DIOD, dir);
}

/**
  * @brief   Установка скорости передачи данных
  * @param   dataRate скорость передачи данных типа @ref QSPI_QSPI_DataRate_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_DataRateConfig(QSPI_DataRate_TypeDef dataRate)
{
	assert_param(IS_QSPI_DATARATE(dataRate));

	WRITE_REG(QSPI->QCC_bit.DDRM, dataRate);
}

/**
  * @brief   Установка адреса
  * @param   address Адрес, передаваемый во внешнюю память
  * @retval  void
  */
__STATIC_INLINE void QSPI_SetAddress(uint32_t address)
{
	WRITE_REG(QSPI->QAD, address);
}

/**
  * @brief   Установка флага для маскированного прерывания
  * @param   it Номер маскированного прерывания типа @ref QSPI_IT_TypeDef
  * @param   state Флаг для включения маскированного прерывания
  * @retval  void
  */
__STATIC_INLINE void QSPI_ITCmd(QSPI_IT_TypeDef it, FunctionalState state)
{
	assert_param(IS_QSPI_IT(it));

	MODIFY_REG(QSPI->IMR, 1 << it, state << it);
}

/**
  * @brief   Очистка прерывания
  * @param   it Номер прерывания типа @ref QSPI_IT_TypeDef
  * @retval  void
  */
__STATIC_INLINE void QSPI_ITClear(QSPI_IT_TypeDef it)
{
	assert_param(IS_QSPI_IT(it));

	MODIFY_REG(QSPI->ICR, 1 << it, 1 << it);
}

/**
  * @brief   Состояние немаскированного прерывания
  * @param   it Номер прерывания типа @ref QSPI_IT_TypeDef
  * @retval  state состояние немаскированного прерывания
  */
__STATIC_INLINE FunctionalState QSPI_ITRawStatus(QSPI_IT_TypeDef it)
{
	assert_param(IS_QSPI_IT(it));

	return READ_BIT(QSPI->RIS, it);
}

/**
  * @brief   Очистка прерывания
  * @param   it Номер прерывания типа @ref QSPI_IT_TypeDef
  * @retval  state состояние маскированного прерывания
  */
__STATIC_INLINE FunctionalState QSPI_ITMaskedStatus(QSPI_IT_TypeDef it)
{
	assert_param(IS_QSPI_IT(it));

	return READ_BIT(QSPI->MIS, it);
}

/**
  * @brief   Установка уровня порогового заполнения приемника, по достижени. которого будет выставлен флаг RWRIS
  * @param   waterMark Уровень порогового заполнения
  * @retval  void
  */
__STATIC_INLINE void QSPI_RxWaterMarkConfig(uint32_t waterMark)
{
	assert_param(IS_QSPI_WATERMARK(waterMark));

	WRITE_REG(QSPI->FWM_bit.RHEC, waterMark);
}

/**
  * @brief   Установка уровня порогового заполнения приемника, по достижени. которого будет выставлен флаг TWRIS
  * @param   waterMark Уровень порогового заполнения
  * @retval  void
  */
__STATIC_INLINE void QSPI_TxWaterMarkConfig(uint32_t waterMark)
{
	assert_param(IS_QSPI_WATERMARK(waterMark));

	WRITE_REG(QSPI->FWM_bit.TLEC, waterMark);
}


/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __PLIB015_QSPI_H */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

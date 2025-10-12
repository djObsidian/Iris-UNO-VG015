/**
  ******************************************************************************
  * @file    plib015_gpio.c
  *
  * @brief   Файл содержит реализацию функций для работы с GPIO
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

/* Includes ------------------------------------------------------------------*/
#include "plib015_gpio.h"

/** @addtogroup Peripheral
  * @{
  */

/** @addtogroup GPIO
  * @{
  */

/** @defgroup GPIO_Private Приватные данные
  * @{
  */

/** @defgroup GPIO_Private_Defines Приватные константы
  * @{
  */

/**
  * @}
  */

/** @defgroup GPIO_Private_Functions Приватные функции
  * @{
  */

/**
  * @brief   Записывает необходимое 2-битное значение режима в регистр порта для всех выбранных пинов
  * @param   Reg  Указатель на изменяемый регистр
  * @param   Pin  Выбор пинов. Любая совокупность значений GPIO_Pin_x (@ref GPIO_Pin_Define).
  * @param   Val  Конфигурация пинов (2-битное значение)
  * @retval  void
  */
static void modeConfig(volatile uint32_t* Reg, uint32_t Pin, uint32_t Val)
{
    uint32_t reg_temp = *Reg;

    for (uint32_t i = 0; i < 16; i++) {
        if (Pin & (1 << i)) {
            reg_temp &= ~(0x3UL << i * 0x2UL);
            reg_temp |= Val << i * 0x2UL;
        }
    }

    WRITE_REG(*Reg, reg_temp);
}

/**
  * @brief   Настройка режима работы выходного каскада
  * @param   GPIOx  Выбор порта, где x=A|B|C
  * @param   Pin  Выбор пинов. Любая совокупность значений GPIO_Pin_x (@ref GPIO_Pin_Define).
  * @param   OutMode  Режим работы
  * @retval  void
  */
void GPIO_OutModeConfig(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIO_OutMode_TypeDef OutMode)
{
    assert_param(IS_GPIO_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));
    assert_param(IS_GPIO_OUT_MODE(OutMode));

    modeConfig(&(GPIOx->OUTMODE), Pin, (uint32_t)OutMode);
}

/**
  * @brief   Настройка режима работы подтяжек пинов
  * @param   GPIOx  Выбор порта, где x=A|B|C
  * @param   Pin  Выбор пинов. Любая совокупность значений GPIO_Pin_x (@ref GPIO_Pin_Define).
  * @param   PullMode  Режим работы
  * @retval  void
  */
void GPIO_PullModeConfig(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIO_PullMode_TypeDef PullMode)
{
    assert_param(IS_GPIO_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));
    assert_param(IS_GPIO_PULL_MODE(PullMode));

    MODIFY_REG(GPIOx->PULLMODE, Pin, (uint32_t)PullMode);
}

/**
  * @brief   Устнановка номера альтернативной функции для выбранных пинов
  * @param   GPIOx  Выбор порта, где x=A|B|C
  * @param   Pin  Выбор пинов. Любая совокупность значений GPIO_Pin_x (@ref GPIO_Pin_Define).
  * @param   AltFuncNum  Номер функции
  * @retval  void
  */
void GPIO_AltFuncNumConfig(GPIO_TypeDef* GPIOx, uint32_t Pin, GPIO_AltFuncNum_TypeDef AltFuncNum)
{
    assert_param(IS_GPIO_PERIPH(GPIOx));
    assert_param(IS_GPIO_PIN(Pin));
    assert_param(IS_GPIO_ALT_FUNC_NUM(AltFuncNum));

    uint32_t temp;

    temp = GPIOx->ALTFUNCNUM;

    for (uint32_t i = 0; i < 16; i++) {
    	if (Pin & (1 << i))
    	{
    		temp &= ~(0x3UL << i * 0x2UL);
    		temp |= (uint32_t)AltFuncNum << i * 0x2UL;
    	}
//        if (i < 8) {
//            if (Pin & (1 << i)) {
//                temp0 &= ~(0xFUL << i * 0x4UL);
//                temp0 |= (uint32_t)AltFuncNum << i * 0x4UL;
//            }
//        } else {
//            if (Pin & (1 << i)) {
//                temp1 &= ~(0xFUL << (i - 8) * 0x4UL);
//                temp1 |= (uint32_t)AltFuncNum << (i - 8) * 0x4UL;
//            }
//        }
    }

    GPIOx->ALTFUNCNUM = temp;
}

/**
  * @brief   Устанавливает все регистры выбранного GPIOx значениями по умолчанию
  * @param   GPIOx  Выбор порта, где x=A|B|C
  * @retval  void
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
    uint32_t GPIO_rst;

    assert_param(IS_GPIO_PERIPH(GPIOx));

    if (GPIOx == GPIOA)
        GPIO_rst = RCU_AHBRst_GPIOA;
    else if (GPIOx == GPIOB)
        GPIO_rst = RCU_AHBRst_GPIOB;
    else  if (GPIOx == GPIOC)
        GPIO_rst = RCU_AHBRst_GPIOC;

    RCU_AHBRstCmd(GPIO_rst, DISABLE);
    RCU_AHBRstCmd(GPIO_rst, ENABLE);
}

/**
  * @brief   Инициализирует модуль GPIOx согласно параметрам структуры InitStruct.
  *          Порт не начнет функционировать, пока не будет разрешена цифровая работа пина @ref GPIO_DigitalCmd .
  * @param   GPIOx  Выбор порта, где x=A|B|C
  * @param   InitStruct  Указатель на структуру типа @ref GPIO_Init_TypeDef,
  *                      которая содержит конфигурационную информацию
  * @retval  void
  */
void GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_Init_TypeDef* InitStruct)
{
    GPIO_OutCmd(GPIOx, InitStruct->Pin, InitStruct->Out);
    GPIO_AltFuncNumConfig(GPIOx, InitStruct->Pin, InitStruct->AltFuncNum);
    GPIO_AltFuncCmd(GPIOx, InitStruct->Pin, InitStruct->AltFunc);
    GPIO_OutModeConfig(GPIOx, InitStruct->Pin, InitStruct->OutMode);
    GPIO_PullModeConfig(GPIOx, InitStruct->Pin, InitStruct->PullMode);
}

/**
  * @brief   Заполнение каждого члена структуры InitStruct значениями по умолчанию
  * @param   InitStruct  Указатель на структуру типа @ref GPIO_Init_TypeDef,
  *                      которую необходимо проинициализировать
  * @retval  void
  */
void GPIO_StructInit(GPIO_Init_TypeDef* InitStruct)
{
    InitStruct->Pin = GPIO_Pin_All;
    InitStruct->Out = DISABLE;
    InitStruct->AltFuncNum = GPIO_AltFuncNum_None;
    InitStruct->AltFunc = DISABLE;
    InitStruct->OutMode = GPIO_OutMode_PP;
    InitStruct->PullMode = GPIO_PullMode_Disable;
}

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/******************* (C) COPYRIGHT 2024 NIIET *****END OF FILE****/

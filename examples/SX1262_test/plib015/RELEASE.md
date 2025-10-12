# История изменений

# v1.0.0
- Добавлены файлы для doxygen-гененирации документации

# v1.0.4
- Исправлены ошибки в файле plib015_tmr32.h (функции TMR32_ADCReqCmd, TMR32_DMAReqCmd).
- Исправлены ошибки в файле plib015_tmr.h (функция TMR_ADCReqCmd). 
- Исправлены ошибки в файле plib015_rcu.c (функция RCU_GetIWDTClkFreq).
- Исправлены ошибки в файле plib015_crc.c (функция CRC_GetPolysize).

# v1.0.5
- Удалил несуществующий регистр INMODE в файлах plib015_gpio.h и plib015_gpio.с. 

# v1.0.6
- Исправил ошибку в функции CMP_DAC_Cmd() в файле plib015_cmp.h. 

# v1.0.7
- Исправил ошибки в функциях RCU_SYSPLL0_OutCmd(), RCU_SYSPLL1_OutCmd(), RCU_SYSPLL0_BypassCmd(), RCU_SYSPLL1_BypassCmd(), RCU_USBPLL_BypassCmd() в файле plib015_rcu.h.
- Доработал функцию RCU_GetHsiClkFreq() в файле plib015_rcu.c для возврата значения HSI в зависимости от значения PMURTC->HSI_TRIM. 
- В функции RCU_GetSysPLL0ClkFreq(), RCU_GetSysPLL1ClkFreq() в файле plib015_rcu.c добавил дробный делитель в формулу вычисления частоты.

# v1.0.8
- Убрал префиксный декремент из функции HASH_GetHashBuffer() файла plib015_hash.c.
- Обернул в кавычки версию в макросе PLIB015_VERSION в файле plib015_version.h
- Заменил вызов фукнции modeConfig на макрос MODIFY_REG в функции GPIO_PullModeConfig() в файле plib015_gpio.c
- В функция ADCSAR_AM_GetResolution заменил тип возвращаемого значения на ADCSAR_AM_Resolution_TypeDef в файле plib015_adcsar.h
- Добавил типы данных ADCSD_MainDiv_TypeDef и ADCSD_SamleDiv_TypeDef в файле plib015_adsd.h

# v1.0.9
- Исправил ошибки в макросе IS_RCU_PERIPH_CLK() и функции RCU_UARTClkConfig() в файле plib015_rcu.h.
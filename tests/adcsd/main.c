/*==============================================================================
 * Пример работы с АЦП сигма-дельта для K1921VG015
 *   Измерения каналов АЦП с 0 по 7
 *------------------------------------------------------------------------------
 * НИИЭТ, Александр Дыхно <dykhno@niiet.ru>
 *==============================================================================
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
 *                              2025 АО "НИИЭТ"
 *==============================================================================
 */

//-- Includes ------------------------------------------------------------------
#include <K1921VG015.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <system_k1921vg015.h>
#include "retarget.h"

//-- Defines -------------------------------------------------------------------
#define GPIOA_ALL_Msk	0xFFFF
#define GPIOB_ALL_Msk	0xFFFF

#define LEDS_MSK	0xFF00
#define LED0_MSK	(1 << 8)
#define LED1_MSK	(1 << 9)
#define LED2_MSK	(1 << 10)
#define LED3_MSK	(1 << 11)
#define LED4_MSK	(1 << 12)
#define LED5_MSK	(1 << 13)
#define LED6_MSK	(1 << 14)
#define LED7_MSK	(1 << 15)

//Значение источника опорного напряжения в Вольтах
#define BG_SDADC_CAP	1.285f

void TMR32_IRQHandler();

void BSP_led_init()
{
	//Разрешаем тактирование GPIOA
	RCU->CGCFGAHB_bit.GPIOAEN = 1;
	//Включаем  GPIOA
	RCU->RSTDISAHB_bit.GPIOAEN = 1;
	GPIOA->OUTENSET = LEDS_MSK;
	GPIOA->DATAOUTSET = LEDS_MSK;
}

void TMR32_init(uint32_t period)
{
  RCU->CGCFGAPB_bit.TMR32EN = 1;
  RCU->RSTDISAPB_bit.TMR32EN = 1;

  //Записываем значение периода в CAPCOM[0]
  TMR32->CAPCOM[0].VAL = period-1;
  //Выбираем режим счета от 0 до значения CAPCOM[0]
  TMR32->CTRL_bit.MODE = 1;

  //Разрешаем прерывание по совпадению значения счетчика и CAPCOM[0]
  TMR32->IM = 2;

  // Настраиваем обработчик прерывания для TMR32
  PLIC_SetIrqHandler (Plic_Mach_Target, IsrVect_IRQ_TMR32, TMR32_IRQHandler);
  PLIC_SetPriority   (IsrVect_IRQ_TMR32, 0x1);
  PLIC_IntEnable     (Plic_Mach_Target, IsrVect_IRQ_TMR32);
}

void adcsd_init()
{
    //Инициализация тактирования блока ADC
    RCU->ADCSDCLKCFG_bit.CLKSEL = 1;
    RCU->ADCSDCLKCFG_bit.DIVEN = 0;
    RCU->ADCSDCLKCFG_bit.CLKEN = 1;
    RCU->ADCSDCLKCFG_bit.RSTDIS = 1;

    //инициализация тактирования и сброса логики АЦП
    RCU->CGCFGAPB_bit.ADCSDEN = 1;
    RCU->RSTDISAPB_bit.ADCSDEN = 1;

    //Включаем модуль АЦП
    ADCSD->CTRL_bit.MDC = 0;
    ADCSD->CTRL_bit.DR = 0;
    ADCSD->CTRL_bit.ENB = 1;
    ADCSD->CTRL_bit.PUREF = 1;
    ADCSD->CTRL_bit.WTCYC = 3;

    //Настраиваем канал 0
    ADCSD->MODE_bit.CH0 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH0 = 1;
    ADCSD->AMPL_bit.CH0 = 0; // Усиление 0дБ

    //Настраиваем канал 1
    ADCSD->MODE_bit.CH1 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH1 = 1;
    ADCSD->AMPL_bit.CH1 = 0; // Усиление 0дБ

    //Настраиваем канал 2
    ADCSD->MODE_bit.CH2 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH2 = 1;
    ADCSD->AMPL_bit.CH2 = 0; // Усиление 0дБ

    //Настраиваем канал 3
    ADCSD->MODE_bit.CH3 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH3 = 1;
    ADCSD->AMPL_bit.CH3 = 0; // Усиление 0дБ

    //Настраиваем канал 4
    ADCSD->MODE_bit.CH4 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH4 = 1;
    ADCSD->AMPL_bit.CH4 = 0; // Усиление 0дБ

    //Настраиваем канал 5
    ADCSD->MODE_bit.CH5 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH5 = 1;
    ADCSD->AMPL_bit.CH5 = 0; // Усиление 0дБ

    //Настраиваем канал 6
    ADCSD->MODE_bit.CH6 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH6 = 1;
    ADCSD->AMPL_bit.CH6 = 0; // Усиление 0дБ

    //Настраиваем канал 7
    ADCSD->MODE_bit.CH7 = 3; // Режим канала - циклический
    ADCSD->ENB_bit.CH7 = 1;
    ADCSD->AMPL_bit.CH7 = 0; // Усиление 0дБ
}

//-- Peripheral init functions -------------------------------------------------
void periph_init()
{
	SystemInit();
	SystemCoreClockUpdate();
	BSP_led_init();
	retarget_init();
	adcsd_init();
	printf("K1921VG015 SYSCLK = %d MHz\n",(int)(SystemCoreClock / 1E6));
	//printf("  UID[0] = 0x%X  UID[1] = 0x%X  UID[2] = 0x%X  UID[3] = 0x%X\n",
	//		        PMUSYS->UID[0],PMUSYS->UID[1],PMUSYS->UID[2],PMUSYS->UID[3]);
	printf("  Start ADCSAR CH0 - CH7\n");
}

float ADCSD_Get_Volt(uint16_t a)
{
	float res;
	if(a>0x7FFF){
		res = (float)((float)(a-65536)/(float)65536);
	} else {
		res = (float)((float)a/(float)65536);
	}
	return BG_SDADC_CAP * (1 + 1.2f*res);
}

//--- USER FUNCTIONS ----------------------------------------------------------------------

volatile uint32_t led_shift;
//-- Main ----------------------------------------------------------------------
int main(void)
{
	uint8_t adc_ch;
	uint16_t adc_data,adc_volt_frac,adc_volt_int;
	uint32_t i;
	float tmp2f, tmpf,adc_volt;
	periph_init();
	TMR32_init(SystemCoreClock>>2);
	InterruptEnable();
	led_shift = LED0_MSK;
	while(1)
	{
	  for(adc_ch=0;adc_ch<8;adc_ch++){
		  if(ADCSD->DATAUPD & (1 << adc_ch)) {
			  adc_data = (uint16_t)ADCSD->DATA[adc_ch].DATA;
			  adc_volt = ADCSD_Get_Volt(adc_data);
			  tmp2f = modff(adc_volt,&tmpf)*1000;
			  adc_volt_frac = (uint16_t)tmp2f;
			  adc_volt_int = (uint16_t)tmpf;
			  printf("CH%02d - 0x%03x - %u.%u V\n\r", adc_ch, adc_data,adc_volt_int,adc_volt_frac);
			  ADCSD->DATAUPD = (1 << adc_ch);
		  }
	  }
	  i=650000;
	  while(i--);
	}

	return 0;
}


//-- IRQ INTERRUPT HANDLERS ---------------------------------------------------------------
void TMR32_IRQHandler()
{
	GPIOA->DATAOUTTGL = led_shift;
	led_shift = led_shift << 1;
    if(led_shift > LED7_MSK) led_shift = LED0_MSK;
    //Сбрасываем флаг прерывания таймера
    TMR32->IC = 3;
}

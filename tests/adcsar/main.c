/*==============================================================================
 * Пример работы с АЦП последовательного приближения для K1921VG015
 *   Измерения каналов АЦП с 0 по 7 с помощью секвенсора 0
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
 *                              2022 АО "НИИЭТ"
 *==============================================================================
 */

//-- Includes ------------------------------------------------------------------
#include <K1921VG015.h>
#include <stdint.h>
#include <stdio.h>
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

void adcsar_init()
{
	// настройка питания ADC
    PMUSYS->ADCPWRCFG_bit.LDOEN = 1;
    PMUSYS->ADCPWRCFG_bit.LVLDIS = 0;

    //Инициализация тактирвоания блока ADC
    RCU->ADCSARCLKCFG_bit.CLKSEL = 1;
    RCU->ADCSARCLKCFG_bit.DIVEN = 0;
    RCU->ADCSARCLKCFG_bit.CLKEN = 1;
    RCU->ADCSARCLKCFG_bit.RSTDIS = 1;

    //инициализация тактирования и сброса логики АЦП
    RCU->CGCFGAPB_bit.ADCSAREN = 1;
    RCU->RSTDISAPB_bit.ADCSAREN = 1;

    //Настройка модуля АЦП
    //12бит и калибровка при включении
    ADCSAR->ACTL_bit.SELRES = ADCSAR_ACTL_SELRES_12bit;
    ADCSAR->ACTL_bit.CALEN = 1;
    ADCSAR->ACTL_bit.ADCEN = 1;

    //Настройка секвенсора 0: CH0 - CH7
    ADCSAR->EMUX_bit.EM0 = ADCSAR_EMUX_EM0_SwReq;
    //ADCSAR->EMUX = 0x0F;
    ADCSAR->SEQ[0].SCCTL_bit.ICNT = 0;
    ADCSAR->SEQ[0].SCCTL_bit.RCNT = 0;
    ADCSAR->SEQ[0].SRTMR = 0x0;
    ADCSAR->SEQ[0].SRQCTL_bit.QAVGVAL = ADCSAR_SEQ_SRQCTL_QAVGVAL_Disable;
    ADCSAR->SEQ[0].SRQCTL_bit.QAVGEN = 0;
    ADCSAR->SEQ[0].SRQCTL_bit.RQMAX = 7;
    ADCSAR->SEQ[0].SCCTL_bit.RAVGEN = 0;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ0 = 0;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ1 = 1;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ2 = 2;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ3 = 3;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ4 = 4;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ5 = 5;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ6 = 6;
    ADCSAR->SEQ[0].SRQSEL_bit.RQ7 = 7;

    //Включаем секвенсоры
    ADCSAR->SEQSYNC = ADCSAR_SEQSYNC_SYNC0_Msk;
    ADCSAR->SEQEN = ADCSAR_SEQEN_SEQEN0_Msk;

    //Ждем пока АЦП пройдут инициализацию, начатую в самом начале
    while (!(ADCSAR->ACTL_bit.ADCRDY)) {
    };
}

//-- Peripheral init functions -------------------------------------------------
void periph_init()
{
	SystemInit();
	SystemCoreClockUpdate();
	BSP_led_init();
	retarget_init();
	adcsar_init();
	printf("K1921VG015 SYSCLK = %d MHz\n",(int)(SystemCoreClock / 1E6));
	printf("  UID[0] = 0x%X  UID[1] = 0x%X  UID[2] = 0x%X  UID[3] = 0x%X\n",
			        (unsigned int)PMUSYS->UID[0],(unsigned int)PMUSYS->UID[1],(unsigned int)PMUSYS->UID[2],(unsigned int)PMUSYS->UID[3]);
	printf("  Start ADCSAR CH0 - CH7\n");
}

//--- USER FUNCTIONS ----------------------------------------------------------------------

volatile uint32_t led_shift;
//-- Main ----------------------------------------------------------------------
int main(void)
{
  periph_init();
  TMR32_init(SystemCoreClock>>4);
  InterruptEnable();
  led_shift = LED0_MSK;
  while(1)
  {
	 ADCSAR->SEQSYNC_bit.GSYNC = 1;
	 while ((ADCSAR->BSTAT));
	 while (!(ADCSAR->RIS_bit.SEQRIS0))
       for (int chn = 0; chn < 8; chn++) {
         int ch_res = ADCSAR->SEQ[0].SFIFO;
         printf("CH%02d - 0x%03x\n",
                chn, ch_res);
       }
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

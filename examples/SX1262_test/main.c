/*==============================================================================
 * Реализация "бегущего огня" на старшей части GPIOC для K1921VG015
 * с использованием библиотеки plib015. Фиксы
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
 *                              2024 АО "НИИЭТ"
 *==============================================================================
 */

//-- Includes ------------------------------------------------------------------
#include "main.h"
#include "sx126x.h"

//-- Defines -------------------------------------------------------------------

// Assume context is initialized
const void* context;

// Payload
const uint8_t payload[] = { 'H', 'e', 'l', 'l', 'o', 'W', 'o', 'r', 'l', 'd' };
const uint8_t payload_len = sizeof(payload);

// RF frequency (e.g., 433 MHz)
const uint32_t rf_freq_hz = 868000000;

// Modulation params (LoRa SF9, BW 125 kHz, CR 4/5, LDRO off)
sx126x_mod_params_lora_t mod_params = {
    .sf = SX126X_LORA_SF9,
    .bw = SX126X_LORA_BW_125,
    .cr = SX126X_LORA_CR_4_5,
    .ldro = 0
};

// Packet params (8 symbols preamble, explicit header, CRC on, no IQ invert)
sx126x_pkt_params_lora_t pkt_params = {
    .preamble_len_in_symb = 8,
    .header_type = SX126X_LORA_PKT_EXPLICIT,
    .pld_len_in_bytes = payload_len,
    .crc_is_on = true,
    .invert_iq_is_on = false
};

// PA config (for SX1262, 22 dBm example; adjust device_sel for SX1261/2)
sx126x_pa_cfg_params_t pa_cfg = {
    .pa_duty_cycle = 0x04,
    .hp_max = 0x07,
    .device_sel = 0,  // 0 for SX1262, 1 for SX1261
    .pa_lut = 1
};

// TX params (20 dBm power, 200 us ramp time)
const int8_t tx_power_dbm = 20;
const sx126x_ramp_time_t ramp_time = SX126X_RAMP_200_US;

// IRQ mask for TX done
const uint16_t irq_mask = SX126X_IRQ_TX_DONE | SX126X_IRQ_TIMEOUT;

void TMR32_IRQHandler();
void SPI0_IRQHandler();
void GPIO_IRQHandler();

void gpio_init()
{
    RCU_AHBClkCmd(RCU_AHBClk_GPIOC, ENABLE);
    RCU_AHBRstCmd(RCU_AHBRst_GPIOC, ENABLE);
    GPIO_OutCmd(GPIOC, GPIO_Pin_All, ENABLE);

    RCU_AHBClkCmd(RCU_AHBClk_GPIOB, ENABLE);
    RCU_AHBRstCmd(RCU_AHBRst_GPIOB, ENABLE);
    GPIO_SyncCmd(GPIOB, GPIO_Pin_12, ENABLE);
    GPIO_PullModeConfig(GPIOB, GPIO_Pin_12, GPIO_PullMode_PU);

    GPIO_OutCmd(NSSPort, NSSPin, ENABLE);

    GPIO_ITTypeConfig(DIO1Port, DIO1Pin, GPIO_IntType_Edge);
    GPIO_ITCmd(DIO1Port, DIO1Pin, ENABLE);

    PLIC_SetIrqHandler (Plic_Mach_Target, IsrVect_IRQ_GPIO, GPIO_IRQHandler);
	PLIC_SetPriority   (IsrVect_IRQ_GPIO, 0x3);
	PLIC_IntEnable     (Plic_Mach_Target, IsrVect_IRQ_GPIO);

}

void TMR32_init(uint32_t period)
{
  RCU_APBClkCmd(RCU_APBClk_TMR32, ENABLE);
  RCU_APBRstCmd(RCU_APBRst_TMR32, ENABLE);

  //Записываем значение периода в CAPCOM[0]
  TMR32_CAPCOM_SetComparator(TMR32_CAPCOM_0,period-1);
  //Выбираем режим счета от 0 до значения CAPCOM[0]
  TMR32_SetMode(TMR32_Mode_Capcom_Up);

  //Разрешаем прерывание по совпадению значения счетчика и CAPCOM[0]
  TMR32_ITCmd(TMR32_IT_CAPCOM_0, ENABLE);

  // Настраиваем обработчик прерывания для TMR32
  PLIC_SetIrqHandler (Plic_Mach_Target, IsrVect_IRQ_TMR32, TMR32_IRQHandler);
  PLIC_SetPriority   (IsrVect_IRQ_TMR32, 0x1);
  PLIC_IntEnable     (Plic_Mach_Target, IsrVect_IRQ_TMR32);
}

void SPI0_init() {
	RCU_AHBClkCmd(RCU_AHBClk_GPIOB, ENABLE); //включение тактования порта B и вывод из состояния сброса
	RCU_AHBRstCmd(RCU_AHBRst_GPIOB, ENABLE);

	RCU_AHBClkCmd(RCU_AHBClk_SPI0, ENABLE); //включение тактования SPI0 и вывод из состояния сброса
	RCU_AHBRstCmd(RCU_AHBClk_SPI0, ENABLE);

	RCU_SPIClkConfig(SPI0_Num, RCU_PeriphClk_HseClk, 2, DISABLE); //тактование от внешнего кварца
	RCU_SPIClkCmd(SPI0_Num, ENABLE); //разрежение тактования
	RCU_SPIRstCmd(SPI0_Num, ENABLE); //снятие состояния сброса

	SPI0->CPSR_bit.CPSDVSR = 6;//Коэффициент деления первого делителя
	// Я хз почему в plib15 этого нет
	// Итого частота работы 12/6 = 2 МГц, кварц - 12 МГц

	SPI_Init_TypeDef spi_struct; // объявление и инициализация структуры настройки SPI

	SPI_StructInit(&spi_struct);

	SPI_Init(SPI0, &spi_struct); // настройка режима работы SPI

	GPIO_AltFuncCmd(
			GPIOB,
			GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
			ENABLE
			); // Включение альтернативной функции пинов PB0-PB3

	GPIO_AltFuncNumConfig(
			GPIOB,
			GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3,
			GPIO_AltFuncNum_1
			); //Выбор альтернативной функции

	SPI_ITCmd(SPI0, SPI_ITSource_RecieveOverrun, ENABLE); //Разрешаем прерывания по переполнению приемного буфера

	PLIC_SetIrqHandler (Plic_Mach_Target, IsrVect_IRQ_SPI0, SPI0_IRQHandler);
	PLIC_SetPriority   (IsrVect_IRQ_SPI0, 0x2);
	PLIC_IntEnable     (Plic_Mach_Target, IsrVect_IRQ_SPI0);

	SPI_Cmd(SPI0, ENABLE); //Включение SPI0


}


//-- Peripheral init functions -------------------------------------------------
void periph_init()
{
	SystemInit();
	SystemCoreClockUpdate();

	gpio_init();
	SPI0_init();
	retarget_init();
}

//--- USER FUNCTIONS ----------------------------------------------------------------------


volatile uint32_t led_shift;
BitState pb12_state;
//-- Main ----------------------------------------------------------------------
int main(void)
{
  periph_init();
  //TMR32_init(SystemCoreClock>>5);
  InterruptEnable();
  GPIO_ClearBits(GPIOC, GPIO_Pin_All);
  led_shift = GPIO_Pin_10;

  sx126x_status_t status;
  sx126x_chip_status_t chip_status;
  uint16_t irq_status;

  printf("Starting SX126x TX sequence\n");

  // 1. Get initial status
  status = sx126x_get_status(context, &chip_status);
  if (status == SX126X_STATUS_OK) {
	  printf("Initial chip mode: %d, cmd status: %d\n", chip_status.chip_mode, chip_status.cmd_status);
  } else {
	  printf("Get status failed: %d\n", status);
  }

  // 2. Set standby RC mode
  status = sx126x_set_standby(context, SX126X_STANDBY_CFG_RC);
  printf("Set standby RC: %d\n", status);

  // 3. Calibrate all blocks
  status = sx126x_cal(context, SX126X_CAL_ALL);
  printf("Calibrate all: %d\n", status);

  // 4. Set packet type to LoRa
  status = sx126x_set_pkt_type(context, SX126X_PKT_TYPE_LORA);
  printf("Set LoRa packet type: %d\n", status);

  // 5. Set RF frequency
  status = sx126x_set_rf_freq(context, rf_freq_hz);
  printf("Set RF freq %u Hz: %d\n", rf_freq_hz, status);

  // 6. Set LoRa modulation params
  status = sx126x_set_lora_mod_params(context, &mod_params);
  printf("Set LoRa mod params (SF%d, BW%d, CR%d/ %d): %d\n", mod_params.sf, mod_params.bw, mod_params.cr + 4, mod_params.cr + 5, status);

  // 7. Set LoRa packet params
  status = sx126x_set_lora_pkt_params(context, &pkt_params);
  printf("Set LoRa pkt params (preamble %d, explicit header, CRC %s): %d\n", pkt_params.preamble_len_in_symb, pkt_params.crc_is_on ? "on" : "off", status);

  // 8. Set PA config
  status = sx126x_set_pa_cfg(context, &pa_cfg);
  printf("Set PA config: %d\n", status);

  // 9. Set TX params
  status = sx126x_set_tx_params(context, tx_power_dbm, ramp_time);
  printf("Set TX params (%d dBm, ramp %d): %d\n", tx_power_dbm, ramp_time, status);



  while(1)
  {
	  pb12_state = GPIO_ReadBit(GPIOB, GPIO_Pin_12);

	  if (pb12_state == SET) {
		  GPIO_SetBits(GPIOC, GPIO_Pin_10);
	  } else {
		  GPIO_ClearBits(GPIOC, GPIO_Pin_10);
	  }

  }

  return 0;
}


//-- IRQ INTERRUPT HANDLERS ---------------------------------------------------------------
void TMR32_IRQHandler()
{
	GPIO_ToggleBits(GPIOC,led_shift);
	led_shift = led_shift << 1;
    if(led_shift >= GPIO_Pin_15) led_shift = GPIO_Pin_10;
    //Сбрасываем флаг прерывания таймера
    TMR32_ITClear(TMR32_IT_TimerUpdate | TMR32_IT_CAPCOM_0);
    //printf("0x%04x\n", led_shift);
}

void SPI0_IRQHandler(){

	SPI_ITStatusClear(SPI0, SPI_ITSource_RecieveOverrun);

}

void GPIO_IRQHandler() {

	GPIO_ITStatusClear(DIO1Port, DIO1Pin);

}

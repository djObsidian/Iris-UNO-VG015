/*
 * sx126x_hal.c
 *
 * Hardware Abstraction Layer implementation for SX126x using plib015
 *
 * Adapted for K1921VK015 MCU
 */

#include "sx126x_hal.h"
#include "main.h"
#include "plib015_spi.h"
#include "plib015_gpio.h"
#include "plib015.h"

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE CONSTANTS -------------------------------------------------------
 */

#define SX126X_TIMEOUT_COUNT    1000000  // Approximate timeout loop count for SPI operations (adjust based on clock)

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE TYPES -----------------------------------------------------------
 */

typedef enum
{
    RADIO_SLEEP,
    RADIO_AWAKE
} radio_sleep_mode_t;

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE VARIABLES -------------------------------------------------------
 */

static radio_sleep_mode_t radio_mode = RADIO_AWAKE;
static const void* hal_radio_ctx = NULL;  // Use void* to match sx126x_hal.h signature

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DECLARATION -------------------------------------------
 */

/**
 * @brief Approximate delay in microseconds (simple loop-based, calibrate as needed)
 */
static void hal_mcu_wait_us(uint32_t us);

/**
 * @brief Wait until radio busy pin returns to 0
 */
static void sx126x_hal_wait_on_busy(const void* context);

/**
 * @brief Check if device is ready to receive spi transaction.
 * @remark If the device is in sleep mode, it will awake it and wait until it is ready
 */
static void sx126x_hal_check_device_ready(const void* context);

static void sx126x_hal_nss_low(const void* context);
static void sx126x_hal_nss_high(const void* context);

/**
 * @brief Transmit a buffer over SPI
 */
static sx126x_hal_status_t spi_transmit(const void* context, const uint8_t* buffer, uint16_t length);

/**
 * @brief Receive a buffer over SPI (transmits NOP for clock)
 */
static sx126x_hal_status_t spi_receive(const void* context, uint8_t* buffer, uint16_t length);

/*
 * -----------------------------------------------------------------------------
 * --- PUBLIC FUNCTIONS DEFINITION ---------------------------------------------
 */

sx126x_hal_status_t sx126x_hal_write(const void* context, const uint8_t* command, const uint16_t command_length,
                                     const uint8_t* data, const uint16_t data_length)
{
    const void* ctx = hal_radio_ctx;

    sx126x_hal_check_device_ready(ctx);


    // Activate NSS (CS low)
    sx126x_hal_nss_low(ctx);

    // Transmit command
    if (command_length > 0) {
        if (spi_transmit(ctx, command, command_length) != SX126X_HAL_STATUS_OK) {
            sx126x_hal_nss_high(ctx);
            return SX126X_HAL_STATUS_ERROR;
        }
    }

    // Transmit data
    if (data_length > 0) {
        if (spi_transmit(ctx, data, data_length) != SX126X_HAL_STATUS_OK) {
            sx126x_hal_nss_high(ctx);
            return SX126X_HAL_STATUS_ERROR;
        }
    }

    // Deactivate NSS (CS high)
    sx126x_hal_nss_high(ctx);

    if (command_length > 0 && command[0] != 0x84) {
        sx126x_hal_check_device_ready(ctx);
    } else {
        radio_mode = RADIO_SLEEP;
    }

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_read(const void* context, const uint8_t* command, const uint16_t command_length,
                                    uint8_t* data, const uint16_t data_length)
{
    const void* ctx = hal_radio_ctx;

    sx126x_hal_check_device_ready(ctx);


    // Activate NSS (CS low)
    sx126x_hal_nss_low(ctx);

    // Transmit command
    if (command_length > 0) {
        if (spi_transmit(ctx, command, command_length) != SX126X_HAL_STATUS_OK) {
            sx126x_hal_nss_high(ctx);
            return SX126X_HAL_STATUS_ERROR;
        }
    }

    // Receive data
    if (data_length > 0) {
        if (spi_receive(ctx, data, data_length) != SX126X_HAL_STATUS_OK) {
            sx126x_hal_nss_high(ctx);
            return SX126X_HAL_STATUS_ERROR;
        }
    }

    // Deactivate NSS (CS high)
    sx126x_hal_nss_high(ctx);

    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_reset(const void* context)
{
    // No reset pin available, skip reset sequence
    // Optionally, implement software reset if supported by SPI commands
    radio_mode = RADIO_AWAKE;
    return SX126X_HAL_STATUS_OK;
}

sx126x_hal_status_t sx126x_hal_wakeup(const void* context)
{
    const void* ctx = hal_radio_ctx;

    sx126x_hal_check_device_ready(ctx);

    return SX126X_HAL_STATUS_OK;
}

void sx126x_context_init(const void* ctx)
{
    hal_radio_ctx = ctx;
}

/*
 * -----------------------------------------------------------------------------
 * --- PRIVATE FUNCTIONS DEFINITION --------------------------------------------
 */

static void hal_mcu_wait_us(uint32_t us)
{
    // Simple loop-based delay (calibrate based on system clock, e.g., for 100 MHz ~ 100 cycles/us)
    volatile uint32_t count = us * 50;  // Adjust multiplier based on clock
    while (count--) {
        __asm("nop");
    }
}

static void sx126x_hal_wait_on_busy(const void* context) {
    volatile uint32_t timeout = SX126X_TIMEOUT_COUNT;  // ~1M циклов, калибруйте под AHB-clock (100-200 MHz)
    while (GPIO_ReadBit(BUSYPort, BUSYPin) == SET && --timeout > 0) {
        // Опционально: __asm("nop"); для точной задержки
    }
    if (timeout == 0) {
        // Обработка ошибки: assert или return в HAL (не hang'ните систему)
        // e.g., #ifdef DEBUG assert(0 && "Busy timeout"); #endif
    }
}

static void sx126x_hal_check_device_ready(const void* context)
{
    if (radio_mode != RADIO_SLEEP) {
        sx126x_hal_wait_on_busy(context);
    } else {
        // Busy is HIGH in sleep mode, wake-up the device
        sx126x_hal_nss_low(context);
        sx126x_hal_wait_on_busy(context);
        sx126x_hal_nss_high(context);
        radio_mode = RADIO_AWAKE;
    }
}

static void sx126x_hal_nss_low(const void* context)
{
    // Use globals from main.h
    GPIO_WriteBit(NSSPort, NSSPin, CLEAR);
}

static void sx126x_hal_nss_high(const void* context)
{
    // Use globals from main.h
    GPIO_WriteBit(NSSPort, NSSPin, SET);
}

static sx126x_hal_status_t spi_transmit(const void* context, const uint8_t* buffer, uint16_t length)
{
    volatile uint32_t timeout = SX126X_TIMEOUT_COUNT;
    uint16_t i;

    // Ensure SPI is enabled and configured (assume done externally)
    // SPI0 is master, etc.

    for (i = 0; i < length; i++) {
        SPI_SendData(SPI0, buffer[i]);  // Send byte (8-bit width assumed)
    }

    // Wait for transmission complete (Busy flag clear)
    timeout = SX126X_TIMEOUT_COUNT;
    while (SPI_FlagStatus(SPI0, SPI_Flag_Busy) == SET) {
        if (--timeout == 0) return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}

static sx126x_hal_status_t spi_receive(const void* context, uint8_t* buffer, uint16_t length)
{
    volatile uint32_t timeout = SX126X_TIMEOUT_COUNT;
    uint16_t i;

    for (i = 0; i < length; i++) {
        // Transmit NOP to generate clock
        SPI_SendData(SPI0, SX126X_NOP);

        // Wait for Rx data available
        timeout = SX126X_TIMEOUT_COUNT;
        while (SPI_FlagStatus(SPI0, SPI_Flag_RxFIFONotEmpty) == CLEAR) {
            if (--timeout == 0) return SX126X_HAL_STATUS_ERROR;
        }
        buffer[i] = (uint8_t)SPI_RecieveData(SPI0);  // Read byte
    }

    // Wait for Busy clear
    timeout = SX126X_TIMEOUT_COUNT;
    while (SPI_FlagStatus(SPI0, SPI_Flag_Busy) == SET) {
        if (--timeout == 0) return SX126X_HAL_STATUS_ERROR;
    }

    return SX126X_HAL_STATUS_OK;
}





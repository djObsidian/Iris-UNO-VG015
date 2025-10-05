/// @file
/// @brief platform specific configurations

#ifndef PLATFORM_ARTY100_SCR1_H
#define PLATFORM_ARTY100_SCR1_H

#ifndef PLF_SYS_CLK
#define PLF_SYS_CLK 25000000
#endif

#define PLF_CORE_VARIANT_SCR 1
#define PLF_CORE_VARIANT_SCR1 1
#define PLF_CORE_VARIANT SCR1

#define PLF_IMPL_STR "NIIET PROJECT"

// memory configuration
//----------------------

#define PLF_MEM_BASE     (0)
#define PLF_MEM_SIZE     (256*1024*1024)
#define PLF_MEM_ATTR     0
#define PLF_MEM_NAME     "DDR"

#define PLF_TCM_BASE     (0xf0000000)
#define PLF_TCM_SIZE     (64*1024)
#define PLF_TCM_ATTR     0
#define PLF_TCM_NAME     "TCM"

#define PLF_MTIMER_BASE  (0xf0040000)
#define PLF_MTIMER_SIZE  (0x1000)
#define PLF_MTIMER_ATTR  0
#define PLF_MTIMER_NAME  "MTimer"

#define PLF_MMIO_BASE    (0xff000000)
#define PLF_MMIO_SIZE    (0x100000)
#define PLF_MMIO_ATTR    0
#define PLF_MMIO_NAME    "MMIO"

#define PLF_OCRAM_BASE   (0xffff0000)
#define PLF_OCRAM_SIZE   (64*1024)
#define PLF_OCRAM_ATTR   0
#define PLF_OCRAM_NAME   "On-Chip RAM"

// FPGA UART port
#define PLF_UART0_BASE   (PLF_MMIO_BASE + 0x10000)
//#define PLF_UART0_16550
// FPGA build ID
#define PLF_BLD_ID_ADDR  (PLF_MMIO_BASE)

// LEDs
#define PLF_PINLED_ADDR  (PLF_MMIO_BASE + 0x20000)
#define PLF_PINLED_PORT_WIDTH 4
#define PLF_PINLED_INV   0
#define PLF_PINLED_NUM   12

// buttons
#define PLF_BTN_ADDR     (PLF_MMIO_BASE + 0x21000)
#define PLF_BTN_NUM      4
// DIP switches
#define PLF_DIP_ADDR     (PLF_MMIO_BASE + 0x21008)
#define PLF_DIP_NUM      4

// external interrupt lines
#define PLF_INTLINE_ALT_UART 0

#endif // PLATFORM_ARTY100_SCR1_H

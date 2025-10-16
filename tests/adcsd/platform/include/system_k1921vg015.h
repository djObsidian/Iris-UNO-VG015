/*==============================================================================
 * Инициализация K1921VG015
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

#ifndef SYSTEM_K1921VG015_H
#define SYSTEM_K1921VG015_H

#ifdef __cplusplus
extern "C" {
#endif

//-- Includes ------------------------------------------------------------------
#include <stdint.h>
#include "csr.h"
#include "arch.h"
#include "plic.h"

//-- Defines -------------------------------------------------------------------
#ifndef HSECLK_VAL
#define HSECLK_VAL 0
#endif

#define OSECLK_STARTUP_TIMEOUT 0x100000
#define SYSCLK_SWITCH_TIMEOUT 0x100000
#ifndef HSICLK_VAL
    #define HSICLK_VAL 1000000
#endif
#ifndef LSICLK_VAL
    #define LSICLK_VAL 32768
#endif


// machine irq handler
#define MCAUSE_INTERRUPT_FLAG           (1<<31)
#define MCAUSE_EXCEPT_MASK              0xF
#define MCAUSE_EXCEPT_INSTRADDRMISALGN  0x0
#define MCAUSE_EXCEPT_INSTRACCSFAULT    0x1
#define MCAUSE_EXCEPT_INSTRILLEGAL      0x2
#define MCAUSE_EXCEPT_BREAKPNT          0x3
#define MCAUSE_EXCEPT_LOADADDRMISALGN   0x4
#define MCAUSE_EXCEPT_LOADACCSFAULT     0x5
#define MCAUSE_EXCEPT_STAMOADDRMISALGN  0x6
#define MCAUSE_EXCEPT_STAMOACCSFAULT    0x7
#define MCAUSE_EXCEPT_ECALLFRM_M_MODE   0xB

#define MIER_MEIE_BITMASK       (1<<11)
#define MSTATUSR_MIE_BITMASK    (1<<3)


//-- Variables -----------------------------------------------------------------
extern uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
extern uint32_t SystemPll0Clock; // System PLL0Clock Frequency
extern uint32_t SystemPll1Clock; // System PLL1Clock Frequency
extern uint32_t USBClock; 		 // USB Clock Frequency (USB PLL Clock)

//-- Functions -----------------------------------------------------------------
// Interrupt Enable
void InterruptEnable(void);
// Interrupt Disable
void InterruptDisable(void);
// Initialize the System
void SystemInit(void);
// Updates the SystemCoreClock with current core Clock retrieved from registers
void SystemCoreClockUpdate(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_K1921VG015_H

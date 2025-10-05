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

//-- Includes ------------------------------------------------------------------
#include "system_k1921vg015.h"
#include "plic.h"
#include "K1921VG015.h"

//-- Variables -----------------------------------------------------------------
uint32_t SystemCoreClock; // System Clock Frequency (Core Clock)
uint32_t SystemPll0Clock; // System PLL0Clock Frequency
uint32_t SystemPll1Clock; // System PLL1Clock Frequency
uint32_t USBClock; 		  // USB Clock Frequency (USB PLL Clock)

//-- Functions -----------------------------------------------------------------
void SystemCoreClockUpdate(void)
{
    uint32_t current_sysclk;
    uint32_t pll_refclk, pll_refdiv, pll_frac, pll_fbdiv, pll_pd0a, pll_pd0b, pll_pd1a, pll_pd1b = 1;
    current_sysclk = RCU->CLKSTAT_bit.SRC;
  	pll_refclk = HSECLK_VAL;
   	pll_fbdiv = RCU->PLLSYSCFG2_bit.FBDIV;
   	pll_refdiv = RCU->PLLSYSCFG0_bit.REFDIV;
   	pll_pd0a = RCU->PLLSYSCFG0_bit.PD0A;
   	pll_pd0b = RCU->PLLSYSCFG0_bit.PD0B;
   	pll_pd1a = RCU->PLLSYSCFG0_bit.PD1A;
   	pll_pd1b = RCU->PLLSYSCFG0_bit.PD1B;
   	if (RCU->PLLSYSCFG0_bit.DSMEN) pll_frac = RCU->PLLSYSCFG1_bit.FRAC;
   	else pll_frac = 0;

   	SystemPll0Clock = (pll_refclk * (pll_fbdiv+pll_frac/(1 << 24))) / (pll_refdiv * (1+pll_pd0a) * (1+pll_pd0b));
   	SystemPll1Clock = (pll_refclk * (pll_fbdiv+pll_frac/(1 << 24))) / (pll_refdiv * (1+pll_pd1a) * (1+pll_pd1b));
    switch (current_sysclk) {
    case RCU_CLKSTAT_SRC_HSICLK:
        SystemCoreClock = HSICLK_VAL;
        break;
    case RCU_CLKSTAT_SRC_HSECLK:
        SystemCoreClock = HSECLK_VAL;
        break;
    case RCU_CLKSTAT_SRC_SYSPLL0CLK:
    	SystemCoreClock = SystemPll0Clock;
    	break;
    case RCU_CLKSTAT_SRC_LSICLK:
    	SystemCoreClock = LSICLK_VAL;
        break;
    }

}

void ClkInit()
{
    uint32_t timeout_counter = 0;
    uint32_t sysclk_source;

    //clockout control
    #ifndef CKO_NONE
        //C7 clockout
        RCU->CGCFGAHB_bit.GPIOCEN = 1;
        RCU->RSTDISAHB_bit.GPIOCEN = 1;
        GPIOC->ALTFUNCNUM_bit.PIN7 = 3;
        GPIOC->ALTFUNCSET_bit.PIN7 = 1;
    #endif

    #if defined CKO_HSI
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_HSI << RCU_CLKOUTCFG_CLKSEL_Pos) |
        				  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
        				  RCU_CLKOUTCFG_RSTDIS_Msk | RCU_CLKOUTCFG_CLKEN_Msk; //CKO = HSICLK
    #elif defined CKO_HSE
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_HSE << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_RSTDIS_Msk | RCU_CLKOUTCFG_CLKEN_Msk; //CKO = HSECLK
    #elif defined CKO_PLL0
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_PLL0 << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (1 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_RSTDIS_Msk | RCU_CLKOUTCFG_CLKEN_Msk; //CKO = PLL0CLK
    #elif defined CKO_LSI
        RCU->CLKOUTCFG = (RCU_CLKOUTCFG_CLKSEL_LSI << RCU_CLKOUTCFG_CLKSEL_Pos) |
				  	  	  (1 << RCU_CLKOUTCFG_DIVN_Pos) |
						  (0 << RCU_CLKOUTCFG_DIVEN_Pos) |
						  RCU_CLKOUTCFG_RSTDIS_Msk | RCU_CLKOUTCFG_CLKEN_Msk; //CKO = LSICLK
    #endif

//select system clock
#ifdef SYSCLK_PLL
	//PLLCLK = REFCLK * (FBDIV+FRAC/2^24) / (REFDIV*(1+PD0A)*(1+PD0B))
	
	//select HSE as source system clock while config PLL
	RCU->SYSCLKCFG = (RCU_SYSCLKCFG_SRC_HSECLK << RCU_SYSCLKCFG_SRC_Pos);
    // Wait switching done
    timeout_counter = 0;
    while ((RCU->CLKSTAT_bit.SRC != RCU->SYSCLKCFG_bit.SRC) && (timeout_counter < 100)){ //SYSCLK_SWITCH_TIMEOUT))
        timeout_counter++;
    }  						  
#if (HSECLK_VAL == 10000000)
// Fout0 = 50 000 000 Hz
// Fout1 = 10 000 000 Hz
	RCU->PLLSYSCFG0 =( 9 << RCU_PLLSYSCFG0_PD1B_Pos) |  //PD1B
					 ( 4 << RCU_PLLSYSCFG0_PD1A_Pos) |  //PD1A
					 ( 4 << RCU_PLLSYSCFG0_PD0B_Pos) |  //PD0B
					 ( 1 << RCU_PLLSYSCFG0_PD0A_Pos) |  //PD0A
					 ( 2 << RCU_PLLSYSCFG0_REFDIV_Pos) 	  |  //refdiv
					 ( 0 << RCU_PLLSYSCFG0_FOUTEN_Pos)    |  //fouten
					 ( 0 << RCU_PLLSYSCFG0_DSMEN_Pos)     |  //dsmen
					 ( 0 << RCU_PLLSYSCFG0_DACEN_Pos)     |  //dacen
					 ( 3 << RCU_PLLSYSCFG0_BYP_Pos)       |  //bypass
					 ( 1 << RCU_PLLSYSCFG0_PLLEN_Pos);       //en
	RCU->PLLSYSCFG1 = 0;          //FRAC = 0					 
	RCU->PLLSYSCFG2 = 100;         //FBDIV
#elif (HSECLK_VAL == 12000000)
// Fout0 = 50 000 000 Hz
// Fout1 = 25 000 000 Hz
	RCU->PLLSYSCFG0 =( 5 << RCU_PLLSYSCFG0_PD1B_Pos) |  //PD1B
					 ( 3 << RCU_PLLSYSCFG0_PD1A_Pos) |  //PD1A
					 ( 3 << RCU_PLLSYSCFG0_PD0B_Pos) |  //PD0B
					 ( 2 << RCU_PLLSYSCFG0_PD0A_Pos) |  //PD0A
					 ( 2 << RCU_PLLSYSCFG0_REFDIV_Pos) 	  |  //refdiv
					 ( 0 << RCU_PLLSYSCFG0_FOUTEN_Pos)    |  //fouten
					 ( 0 << RCU_PLLSYSCFG0_DSMEN_Pos)     |  //dsmen
					 ( 0 << RCU_PLLSYSCFG0_DACEN_Pos)     |  //dacen
					 ( 3 << RCU_PLLSYSCFG0_BYP_Pos)       |  //bypass
					 ( 1 << RCU_PLLSYSCFG0_PLLEN_Pos);       //en
	RCU->PLLSYSCFG1 = 0;          //FRAC = 0					 
	RCU->PLLSYSCFG2 = 100;         //FBDIV
#elif (HSECLK_VAL == 16000000)
// Fout0 = 50 000 000 Hz
// Fout1 = 12 500 000 Hz
	RCU->PLLSYSCFG0 =( 7 << RCU_PLLSYSCFG0_PD1B_Pos) |  //PD1B
					 ( 7 << RCU_PLLSYSCFG0_PD1A_Pos) |  //PD1A
					 ( 1 << RCU_PLLSYSCFG0_PD0B_Pos) |  //PD0B
					 ( 3 << RCU_PLLSYSCFG0_PD0A_Pos) |  //PD0A
					 ( 2 << RCU_PLLSYSCFG0_REFDIV_Pos) 	  |  //refdiv
					 ( 0 << RCU_PLLSYSCFG0_FOUTEN_Pos)    |  //fouten
					 ( 0 << RCU_PLLSYSCFG0_DSMEN_Pos)     |  //dsmen
					 ( 0 << RCU_PLLSYSCFG0_DACEN_Pos)     |  //dacen
					 ( 3 << RCU_PLLSYSCFG0_BYP_Pos)       |  //bypass
					 ( 1 << RCU_PLLSYSCFG0_PLLEN_Pos);       //en
	RCU->PLLSYSCFG1 = 0;          //FRAC = 0					 
	RCU->PLLSYSCFG2 = 50;         //FBDIV
#elif (HSECLK_VAL == 20000000)
// Fout0 = 50 000 000 Hz
// Fout1 = 25 000 000 Hz
	RCU->PLLSYSCFG0 =( 7 << RCU_PLLSYSCFG0_PD1B_Pos) |  //PD1B
					 ( 4 << RCU_PLLSYSCFG0_PD1A_Pos) |  //PD1A
					 ( 4 << RCU_PLLSYSCFG0_PD0B_Pos) |  //PD0B
					 ( 3 << RCU_PLLSYSCFG0_PD0A_Pos) |  //PD0A
					 ( 2 << RCU_PLLSYSCFG0_REFDIV_Pos) 	  |  //refdiv
					 ( 0 << RCU_PLLSYSCFG0_FOUTEN_Pos)    |  //fouten
					 ( 0 << RCU_PLLSYSCFG0_DSMEN_Pos)     |  //dsmen
					 ( 0 << RCU_PLLSYSCFG0_DACEN_Pos)     |  //dacen
					 ( 3 << RCU_PLLSYSCFG0_BYP_Pos)       |  //bypass
					 ( 1 << RCU_PLLSYSCFG0_PLLEN_Pos);       //en
	RCU->PLLSYSCFG1 = 0;          //FRAC = 0					 
	RCU->PLLSYSCFG2 = 100;         //FBDIV
#elif (HSECLK_VAL == 24000000)
// Fout0 = 50 000 000 Hz
// Fout1 = 30 000 000 Hz
	RCU->PLLSYSCFG0 =( 7 << RCU_PLLSYSCFG0_PD1B_Pos) |  //PD1B
					 ( 4 << RCU_PLLSYSCFG0_PD1A_Pos) |  //PD1A
					 ( 2 << RCU_PLLSYSCFG0_PD0B_Pos) |  //PD0B
					 ( 3 << RCU_PLLSYSCFG0_PD0A_Pos) |  //PD0A
					 ( 2 << RCU_PLLSYSCFG0_REFDIV_Pos) 	  |  //refdiv
					 ( 0 << RCU_PLLSYSCFG0_FOUTEN_Pos)    |  //fouten
					 ( 0 << RCU_PLLSYSCFG0_DSMEN_Pos)     |  //dsmen
					 ( 0 << RCU_PLLSYSCFG0_DACEN_Pos)     |  //dacen
					 ( 3 << RCU_PLLSYSCFG0_BYP_Pos)       |  //bypass
					 ( 1 << RCU_PLLSYSCFG0_PLLEN_Pos);       //en
	RCU->PLLSYSCFG1 = 0;          //FRAC = 0					 
	RCU->PLLSYSCFG2 = 65;         //FBDIV
#else
#error "Please define HSECLK_VAL with correct values!"
#endif
	RCU->PLLSYSCFG0_bit.FOUTEN = 1; 	// Fout0 Enable
	timeout_counter = 1000;
	while(timeout_counter) timeout_counter--;
	while((RCU->PLLSYSSTAT_bit.LOCK) != 1)
	{}; 								// wait lock signal
	RCU->PLLSYSCFG0_bit.BYP = 2; 		// Bypass for Fout1
	//select PLL as source system clock
	sysclk_source = RCU_SYSCLKCFG_SRC_SYSPLL0CLK;
    // FLASH control settings
    FLASH->CTRL_bit.LAT = 3;
    FLASH->CTRL_bit.CEN = 1;
#elif defined SYSCLK_HSI
    sysclk_source = RCU_SYSCLKCFG_SRC_HSICLK;
#elif defined SYSCLK_HSE
    sysclk_source = RCU_SYSCLKCFG_SRC_HSECLK;
#elif defined SYSCLK_LSI
    sysclk_source = RCU_SYSCLKCFG_SRC_LSICLK;
#else
#error "Please define SYSCLK source (SYSCLK_PLL | SYSCLK_HSE | SYSCLK_HSI | SYSCLK_LSI)!"
#endif

    //switch sysclk
    RCU->SYSCLKCFG = (sysclk_source << RCU_SYSCLKCFG_SRC_Pos);
    // Wait switching done
    timeout_counter = 0;
    while ((RCU->CLKSTAT_bit.SRC != RCU->SYSCLKCFG_bit.SRC) && (timeout_counter < 100)) //SYSCLK_SWITCH_TIMEOUT))
        timeout_counter++;
/*    if (timeout_counter == SYSCLK_SWITCH_TIMEOUT) //SYSCLK failed to switch
        while (1) {
        };*/

}

void InterruptEnable()
{
	//allow all interrupts in machine mode
	PLIC_SetThreshold (Plic_Mach_Target, 0); //allow all interrupts in machine mode
    // disable timer interrupt
    clear_csr(mie, MIE_MTIMER);
    // enable machine external interrupt
    set_csr(mie, MIE_MEXTERNAL);
    // enable global interrupts
    set_csr(mstatus, MSTATUS_MIE);
}

void InterruptDisable()
{
	//disable all interrupts in machine mode
	PLIC_SetThreshold (Plic_Mach_Target, 7); //Disable all interrupts in machine mode
    // disable machine external interrupt
    clear_csr(mie, MIE_MEXTERNAL);
    // disable global interrupts
    clear_csr(mstatus, MSTATUS_MIE);
}

void SystemInit(void)
{
	// PLIC configuration
	// disable timer interrupt
//	clear_csr(mie, MIE_MTIMER);
	// enable machine external interrupt
//	set_csr(mie, MIE_MEXTERNAL);
	// enable global interrupts
//	set_csr(mstatus, MSTATUS_MIE);
	ClkInit();
}


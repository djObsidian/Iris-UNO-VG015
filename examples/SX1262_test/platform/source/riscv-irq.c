#include "plic.h"
#include "riscv-irq.h"
#include "riscv-csr.h"
#include <stdint.h>

// machine irq handler
static void irq_entry(void)
    __attribute__((interrupt("machine"), optimize("align-functions=4")));

irqfunc_t* riscv_handler_map[RISCV_IRQ_NUMS];

void riscv_irq_init(void) { 
	riscv_irq_global_disable(); 
	csr_write_mtvec((uint_xlen_t)irq_entry);
	riscv_irq_global_enable(); 
}

void riscv_irq_enable(unsigned int irq_num){
	
    csr_set_bits_mie(1 << irq_num);
}

void riscv_irq_disable(unsigned int irq_num){
	csr_clr_bits_mie(1 << irq_num);
}

void riscv_irq_set_handler(unsigned int irq_num, irqfunc_t *handler){
  riscv_handler_map[irq_num] = handler;
}

void riscv_irq_global_enable(void)
{
    //clear_csr(mstatus, MSTATUS_MPIE);
    csr_set_bits_mstatus(MSTATUS_MIE_BIT_MASK); 

}

void riscv_irq_global_disable(void)
{
    //clear_csr(mstatus, MSTATUS_MPIE);
    csr_clr_bits_mstatus(MSTATUS_MIE_BIT_MASK);
}

// #pragma GCC push_options
// // Force the alignment for mtvec.BASE. A 'C' extension program could be aligned to to bytes.

void irq_entry (void)
{
	uint_xlen_t this_cause = csr_read_mcause();

	if((this_cause & MCAUSE_INTERRUPT_BIT_MASK) == 0) {
		// handle exception
		switch (this_cause & MCAUSE_EXCEPTION_CODE_BIT_MASK)
		{
			case RISCV_EXCP_INSTRUCTION_ADDRESS_MISALIGNED:
				break;
			case RISCV_EXCP_INSTRUCTION_ACCESS_FAULT:
				break;
			case RISCV_EXCP_ILLEGAL_INSTRUCTION:
				break;
			case RISCV_EXCP_BREAKPOINT:
				break;
			case RISCV_EXCP_LOAD_ADDRESS_MISALIGNED :
				break;
			case RISCV_EXCP_LOAD_ACCESS_FAULT:
				break;
			case RISCV_EXCP_STORE_AMO_ADDRESS_MISALIGNED:
				break;
			case RISCV_EXCP_STORE_AMO_ACCESS_FAULT:
				break;
			case RISCV_EXCP_ENVIRONMENT_CALL_FROM_U_MODE:
				break;

			default: // MCAUSE_EXCEPT UNKNOWN

				break;
		}

		while(1) {}; //TRAP
	} else {
		//handle interrupt
		this_cause &= 0xFF;
		if(riscv_handler_map[this_cause] != 0) {
                  riscv_handler_map[this_cause]();
		}else{
			while(1) {}; //NO handler
		}
	}
}
//#pragma GCC pop_options

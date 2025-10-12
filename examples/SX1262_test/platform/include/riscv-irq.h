#ifndef RISCV_IRQ_H
#define RISCV_IRQ_H

typedef void irqfunc_t(void);
enum {
    RISCV_IRQ_MSI = 3,
    RISCV_IRQ_MTI = 7,
    RISCV_IRQ_MEI = 11,
    RISCV_IRQ_SSI = 1,
    RISCV_IRQ_STI = 5,
    RISCV_IRQ_SEI = 9,
    RISCV_IRQ_USI = 0,
    RISCV_IRQ_UTI = 4,
    RISCV_IRQ_UEI = 8,
};

#define RISCV_IRQ_NUMS (RISCV_IRQ_MEI+1)

enum {
    RISCV_IRQ_MASK_MSI = (1UL<<RISCV_IRQ_MSI),
    RISCV_IRQ_MASK_MTI = (1UL<<RISCV_IRQ_MTI),
    RISCV_IRQ_MASK_MEI = (1UL<<RISCV_IRQ_MEI),
    RISCV_IRQ_MASK_SSI = (1UL<<RISCV_IRQ_SSI),
    RISCV_IRQ_MASK_STI = (1UL<<RISCV_IRQ_STI),
    RISCV_IRQ_MASK_SEI = (1UL<<RISCV_IRQ_SEI),
    RISCV_IRQ_MASK_USI = (1UL<<RISCV_IRQ_USI),
    RISCV_IRQ_MASK_UTI = (1UL<<RISCV_IRQ_UTI),
    RISCV_IRQ_MASK_UEI = (1UL<<RISCV_IRQ_UEI),
};

enum {
    RISCV_EXCP_INSTRUCTION_ADDRESS_MISALIGNED=0,	/* Instruction address misaligned */
    RISCV_EXCP_INSTRUCTION_ACCESS_FAULT=1,	/* Instruction access fault	*/
    RISCV_EXCP_ILLEGAL_INSTRUCTION=2,	/* Illegal instruction */
    RISCV_EXCP_BREAKPOINT=3,	/* Breakpoint */
    RISCV_EXCP_LOAD_ADDRESS_MISALIGNED=4,	/* Load address misaligned */
    RISCV_EXCP_LOAD_ACCESS_FAULT=5,	/* Load access fault */
    RISCV_EXCP_STORE_AMO_ADDRESS_MISALIGNED	=6,	/* Store/AMO address misaligned	 */
    RISCV_EXCP_STORE_AMO_ACCESS_FAULT=7,	/* Store/AMO access fault */
    RISCV_EXCP_ENVIRONMENT_CALL_FROM_U_MODE=8,	/* Environment call from U-mode	*/
    RISCV_EXCP_ENVIRONMENT_CALL_FROM_S_MODE=9,	/* Environment call from S-mode	*/
    RISCV_EXCP_RESERVED10=10,	/* Reserved	*/
    RISCV_EXCP_ENVIRONMENT_CALL_FROM_M_MODE=11,	/* Environment call from M-mode	*/
    RISCV_EXCP_INSTRUCTION_PAGE_FAULT=12,	/* Instruction page fault */
    RISCV_EXCP_LOAD_PAGE_FAULT=13,	/* Load page fault */
    RISCV_EXCP_RESERVED14=14,	/* Reserved	*/
    RISCV_EXCP_STORE_AMO_PAGE_FAULT=15,	/* Store/AMO page fault */
};

void riscv_irq_init(void);
void riscv_irq_enable(unsigned int irq);
void riscv_irq_disable(unsigned int irq);
void riscv_irq_set_handler(unsigned int irq, irqfunc_t *handler);
void riscv_irq_global_enable(void);
void riscv_irq_global_disable(void);

#endif /* RISCV_IRQERRUPTS_H */

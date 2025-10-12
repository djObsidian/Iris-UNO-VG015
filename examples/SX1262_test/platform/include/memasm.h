/// -*- mode:asm -*-
/// @file
/// @brief assembler memory operations macros


#ifndef SCR_INFRA_MEMASM_H
#define SCR_INFRA_MEMASM_H

#ifndef __riscv_32e
#define TRAP_REGS_SPACE (4*__riscv_xlen)
#else // !__riscv_32e
#define TRAP_REGS_SPACE (4*16)
#endif // !__riscv_32e

#ifdef __ASSEMBLER__

.altmacro

.macro save_reg_offs reg, offs, save_mem_base=zero
#if __riscv_xlen == 32
    sw   \reg, \offs*4(\save_mem_base)
#else // __riscv_xlen == 32
    sd   \reg, \offs*8(\save_mem_base)
#endif // __riscv_xlen == 32
.endm

.macro load_reg_offs reg, offs, load_mem_base=zero
#if __riscv_xlen == 32
    lw   \reg, \offs*4(\load_mem_base)
#else // __riscv_xlen == 32
    ld   \reg, \offs*8(\load_mem_base)
#endif // __riscv_xlen == 32
.endm

.macro save_reg regn, save_mem_base=zero
    save_reg_offs x\regn, \regn, \save_mem_base
.endm

.macro load_reg regn, load_mem_base=zero
    load_reg_offs x\regn, \regn, \load_mem_base
.endm

.macro save_regs reg_first, reg_last, save_mem_base=zero
    LOCAL regn
    regn = \reg_first
    .rept \reg_last - \reg_first + 1
    save_reg %(regn), \save_mem_base
    regn = regn+1
    .endr
.endm

.macro load_regs reg_first, reg_last, load_mem_base=zero
    LOCAL regn
    regn = \reg_first
    .rept \reg_last - \reg_first + 1
    load_reg %(regn), \load_mem_base
    regn = regn+1
    .endr
.endm

.macro init_regs_const reg_first, reg_last, const_val=0
    LOCAL regn
    regn = \reg_first
    .rept \reg_last - \reg_first + 1
    li %(regn), \const_val
    regn = regn+1
    .endr
.endm

.macro memcpy src_beg, src_end, dst, tmp_reg
    LOCAL memcpy_1, memcpy_2
    j     memcpy_2
    memcpy_1:
#if __riscv_xlen == 32
    lw    \tmp_reg, (\src_beg)
    sw    \tmp_reg, (\dst)
    add   \src_beg, \src_beg, 4
    add   \dst, \dst, 4
#else // __riscv_xlen == 32
    ld    \tmp_reg, (\src_beg)
    sd    \tmp_reg, (\dst)
    add   \src_beg, \src_beg, 8
    add   \dst, \dst, 8
#endif // __riscv_xlen == 32
memcpy_2:
    bltu  \src_beg, \src_end, memcpy_1
.endm

.macro memset dst_beg, dst_end, val_reg
    LOCAL memset_1, memset_2
    j     memset_2
memset_1:
#if __riscv_xlen == 32
    sw    \val_reg, (\dst_beg)
    add   \dst_beg, \dst_beg, 4
#else // __riscv_xlen == 32
    sd    \val_reg, (\dst_beg)
    add   \dst_beg, \dst_beg, 8
#endif // __riscv_xlen == 32
memset_2:
    bltu  \dst_beg, \dst_end, memset_1
.endm

.macro context_save
#if PLF_TRAP_STACK
    LOCAL _init_trap_stack, _use_trap_stack
    csrrw tp, mscratch, tp
    save_reg_offs t0, -1, tp // save original t0 (x5)
    // check trap stack is used
    bge   sp, tp, _init_trap_stack
    li    t0, PLF_TRAP_STACK
    sub   t0, tp, t0
    blt   sp, t0, _init_trap_stack
/*
    // check trap stack overflow
    addi  t0, t0, TRAP_REGS_SPACE
    blt   sp, tp, 3f         // trap stack overflow
*/
    // make new trap stack frame
    mv    t0, sp             // t0 = original sp
    addi  sp, sp, -TRAP_REGS_SPACE
    j     _use_trap_stack
/*
3:  j     plf_trap_stack_overflow
*/
_init_trap_stack:
    // sp not in trap stack area, init trap stack
    mv    t0, sp             // t0 = original sp
    addi  sp, tp, -(TRAP_REGS_SPACE + 0x10)
_use_trap_stack:
    andi  sp, sp, -0x10      // align callee SP by 16
    save_reg 1, sp           // save ra (x1)
    save_reg_offs t0, 2, sp  // save original sp (x2)
    load_reg_offs t0, -1, tp // restore original t0 (x5)
    csrrw tp, mscratch, tp   // restore original tp (x4)
#else // PLF_TRAP_STACK
    // save context without trap stack
    save_reg_offs t0, -1, sp // save original t0 (x5)
    mv    t0, sp             // t0 = original sp
    addi  sp, sp, -TRAP_REGS_SPACE
    andi  sp, sp, -0x10      // align callee SP by 16
    save_reg 1, sp           // save ra (x1)
    save_reg_offs t0, 2, sp  // save original sp (x2)
    load_reg_offs t0, -1, t0 // restore original t0 (x5)
#endif // PLF_TRAP_STACK
#if PLF_SAVE_RESTORE_REGS331_SUB
    jal   plf_save_regs331_sub
#else // PLF_SAVE_RESTORE_REGS331_SUB
    save_regs 3, 15, sp      // save x3 - x15
#ifndef __riscv_32e
    save_regs 16, 31, sp     // save x16 - x31
#endif //  __riscv_32e
#endif // PLF_SAVE_RESTORE_REGS331_SUB
    csrr tp, mscratch        // load tp
    csrr t1, mepc
    save_reg_offs t1, 0, sp  // save original pc
.endm // context_save

.macro context_restore
    load_reg_offs t1, 0, sp  // restore original pc
    csrw mepc, t1
#if PLF_SAVE_RESTORE_REGS331_SUB
    jal   plf_restore_regs331_sub
#else // PLF_SAVE_RESTORE_REGS331_SUB
    load_regs 3, 15, sp      // restore x3 - x15
#ifndef __riscv_32e
    load_regs 16, 31, sp     // restore x16 - x31
#endif //  __riscv_32e
#endif // PLF_SAVE_RESTORE_REGS331_SUB
    load_reg 1, sp           // restore ra (x1)
    load_reg 2, sp           // restore original sp
.endm // context_restore

### ##############################
### addr load/read/write routines

.macro read_pcrel_addrword reg, sym
    LOCAL pcrel_addr
    .option push
    .option norelax
pcrel_addr:
    auipc \reg, %pcrel_hi(\sym)
#if __riscv_xlen == 32
    lw  \reg, %pcrel_lo(pcrel_addr)(\reg)
#elif __riscv_xlen == 64
    ld  \reg, %pcrel_lo(pcrel_addr)(\reg)
#else // __riscv_xlen
#error read_pcrel_addrword is not implemented for xlen
#endif // __riscv_xlen
    .option pop
.endm // read_pcrel_addrword

.macro write_pcrel_addrword reg, sym
    LOCAL pcrel_addr
    .option push
    .option norelax
pcrel_addr:
    auipc \reg, %pcrel_hi(\sym)
#if __riscv_xlen == 32
    sw  \reg, %pcrel_lo(pcrel_addr)(\reg)
#elif __riscv_xlen == 64
    sd  \reg, %pcrel_lo(pcrel_addr)(\reg)
#else // __riscv_xlen
#error write_pcrel_addrword is not implemented for xlen
#endif // __riscv_xlen
.endm // write_pcrel_addrword

### load 32 bit (sign extended) constant
.macro load_const_int32 reg, sym
    .option push
    .option norelax
    lui \reg, %hi(\sym)
    addi \reg, \reg, %lo(\sym)
    .option pop
.endm // load_const_int32

.macro load_addrword_abs reg, sym
#if __riscv_xlen == 32
    load_const_int32 \reg, \sym
#elif __riscv_xlen == 64
    LOCAL _addrword
    .subsection 8 // subsection for local constants
    .align 3
_addrword:
    .dword \sym
    .previous
     read_pcrel_addrword \reg, _addrword
#else // __riscv_xlen
#error load_addrword_abs is not implemented for xlen
#endif // __riscv_xlen
.endm // load_addrword_abs

.macro load_addrword_pcrel reg, sym
    LOCAL _pcrel_addr
    .option push
    .option norelax
_pcrel_addr:
    auipc \reg, %pcrel_hi(\sym)
    addi \reg, \reg, %pcrel_lo(_pcrel_addr)
    .option pop
.endm // load_addrword_pcrel

.macro load_addrword reg, sym
#if __riscv_xlen == 32
    load_addrword_abs \reg, \sym
#elif __riscv_xlen == 64
#if PLF_SPARSE_MEM
    load_addrword_abs \reg, \sym
#else // PLF_SPARSE_MEM
    load_addrword_pcrel \reg, \sym
#endif // PLF_SPARSE_MEM
#else // __riscv_xlen
#error load_addrword is not implemented for xlen
#endif // __riscv_xlen
.endm // load_addrword

    // sections
#define __INIT       ".init.text","ax",@progbits
#define __INITDATA   ".init.data","aw",@progbits
#define __INITRODATA ".init.rodata","a",@progbits

#else // __ASSEMBLER__

#define __init      __attribute__((__section__(".init.text")))
#define __initdata  __attribute__((__section__(".init.data")))
#define __initconst __attribute__((__section__(".init.rodata")))

#endif // __ASSEMBLER__
#endif // SCR_INFRA_MEMASM_H

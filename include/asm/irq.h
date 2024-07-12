#ifndef _IRQ_ABLE_RISCV_H
#define _IRQ_ABLE_RISCV_H

#include "asm/csr.h"

static unsigned long sstatus;

/* 全局使能S模式中断 */
static inline void local_irq_enable(void)
{
    csr_set(sstatus, SSTATUS_SIE);
}

/* 全局禁用S模式中断 */
static inline void local_irq_disable(void)
{
    csr_clear(sstatus, SSTATUS_SIE);
}

#endif /* _IRQ_ABLE_RISCV_H */
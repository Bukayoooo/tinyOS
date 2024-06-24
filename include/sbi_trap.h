#ifndef _RISCV_SBI_TRAP_H
#define _RISCV_SBI_TRAP_H

/* SBI规范：系统调用的异常编码为9 */
#define CAUSE_SUPERVISOR_ECALL  9

struct sbi_trap_regs;

void sbi_trap_init();
void sbi_trap_handler(struct sbi_trap_regs *regs);

#endif /* _RISCV_SBI_TRAP_H */
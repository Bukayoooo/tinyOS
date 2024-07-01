#ifndef _RISCV_SBI_TRAP_H
#define _RISCV_SBI_TRAP_H

/**** mideleg寄存器字段，用来设置中断委托 ****/
/* SSIP字段：将软件中断委托给S模式 */
#define IRQ_SSIP_SOFT 0x1
/* STIP字段：将时钟中断委托给S模式 */
#define IRQ_STIP_TIMER 0x5
/* SEIP字段：将外部中断委托给S模式 */
#define IRQ_SEIP_EXTERNAL 0x9


/**** medeleg寄存器字段，用来设置异常委托 ****/
/* bit[0]：用于将未对齐的指令访问委托给S模式  */
#define CAUSE_MISALIGNED_FETCH 0x0
/* bit[1]：将指令访问异常委托给S模式 */
#define CAUSE_INSTRUCTION_FETCH 0x1
/* bit[2]：将无效指令异常委托给S模式 */
#define CAUSE_ILLEGAL_INSTRUCTION 0x2
/* bit[3]：将断点异常委托给S模式 */
#define CAUSE_BREAKPOINT 0x3
/* bit[4]：将未对齐加载访问异常委托给S模式 */
#define CAUSE_MISALIGNED_LOAD 0x4
/* bit[5]：将加载访问异常委托给S模式 */
#define CAUSE_LOAD_ACESS      0x5
/* bit[6]：将未对齐存储/AMO访问异常委托给S模式 */
#define CAUSE_AMO_MISALIGNED_STORE 0x6
/* bit[7]：将存储/AMO访问异常委托给S模式 */
#define CAUSE_AMO_STORE_ACESS 0x7
/* bit[8]：将U模式的系统调用处理委托给S模式 */
#define CAUSE_USER_ECALL 0X8
/* bit[9]：将S模式的系统调用处理委托给S模式 */
#define CAUSE_SUPERVISOR_ECALL  0x9
/* bit[12]：将指令缺页异常委托给S模式 */
#define CAUSE_FETCH_PAGE_FAULT  0xc
/* bit[13]：将加载缺页异常委托给S模式 */
#define CAUSE_LOAD_PAGE_FAULT 0xd
/* bit[15]：将存储/AMO缺页异常委托给S模式 */
#define CAUSE_AMO_STORE_PAGE_FAULT 0xf

struct sbi_trap_regs;

void sbi_trap_init();
void sbi_trap_handler(struct sbi_trap_regs *regs);

#endif /* _RISCV_SBI_TRAP_H */
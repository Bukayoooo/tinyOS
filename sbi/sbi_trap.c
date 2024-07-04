#include "sbi_trap.h"
#include "uart.h"
#include "asm/csr.h"
#include "sbi_trap_regs.h"
#include "asm/sbi.h"
#include "sbi_trap.h"


/* disable vscode error */
static long mtvec;  /* 异常向量地址寄存器 */
static long mie;    /* 中断使能寄存器 */
static unsigned long mideleg;
static unsigned long medeleg;

extern void sbi_exception_vector(void);

/*
 * 初始化异常
 * 设置异常向量表地址
 */
void sbi_trap_init(void)
{
    /* 设置异常向量表地址 */
    write_csr(mtvec, sbi_exception_vector);
    /* 关闭所有中断 */
    write_csr(mie, 0x0);
}

/**
 * S模式系统调用处理函数
 * int ecall_id: 系统调用号
 * struct sbi_trap_regs *regs：上下文寄存器
 */
int sbi_ecall_handle(int ecall_id, struct sbi_trap_regs *regs)
{
    int ret = 0;

    switch(ecall_id)
    {
        case SBI_CONSOLE_PUTCHAR:
            putchar(regs->a0);
            ret = 0;
            break;
        case SBI_CONSOLE_GETCHAR:
            regs->a0 = getchar();
            ret = 0;
            break;
    }

    if(!ret)
    {
        /* mret 返回异常发生的下一条指令 */
        regs->mepc += 4;
    }

    return ret;
}

/**
 * S模式陷入M模式异常处理函数
 * struct sbi_trap_regs *regs: 保存在栈中的寄存器值
 */
void sbi_trap_handler(struct sbi_trap_regs *regs)
{

    unsigned long mcause = read_csr(mcause);
    int ecall_id = regs->a7;

    switch(mcause)
    {
        case CAUSE_SUPERVISOR_ECALL:
                sbi_ecall_handle(ecall_id, regs);
                break;
        default:
                break;
    }

}

/*
 * M模式异常委托S模式函数
 */
void delegate_trap(void)
{
    unsigned long interrupts;
    unsigned long exceptions;

    /* 委托M模式软件、时钟、外部中断给S模式 */
    interrupts = IRQ_SSIP_SOFT | IRQ_STIP_TIMER | IRQ_SEIP_EXTERNAL;
    exceptions = (1UL << CAUSE_MISALIGNED_FETCH) |
                (1UL << CAUSE_FETCH_PAGE_FAULT) |
                (1UL << CAUSE_BREAKPOINT) |
                (1UL << CAUSE_LOAD_PAGE_FAULT) |
                (1UL << CAUSE_AMO_STORE_PAGE_FAULT) |
                (1UL << CAUSE_USER_ECALL) |
                (1UL << CAUSE_LOAD_ACESS) |
                (1UL << CAUSE_AMO_STORE_ACESS) |
                (1UL << CAUSE_ILLEGAL_INSTRUCTION);

    write_csr(mideleg, interrupts);
    write_csr(medeleg, exceptions);
}
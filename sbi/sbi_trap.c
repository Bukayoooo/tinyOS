#include "sbi_trap.h"
#include "uart.h"
#include "asm/csr.h"
#include "sbi_trap_regs.h"
#include "asm/sbi.h"


/* disable vscode error */
unsigned long mtvec;  /* 异常向量地址寄存器 */
unsigned long mie;    /* 中断使能寄存器 */
extern void sbi_exception_vector();

void sbi_trap_init()
{
    /* 设置异常向量表地址 */
    write_csr(mtvec, sbi_exception_vector);
    /* 关闭所有中断 */
    write_csr(mie, 0x0);
}

/**
 * int ecall_id: 系统调用号
 * struct sbi_trap_regs *regs：寄存器
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
    }

    if(!ret)
    {
            // mret 返回异常发生的下一条指令
            regs->mepc += 4;
    }

    return ret;
}

/**
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
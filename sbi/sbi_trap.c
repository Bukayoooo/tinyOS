#include "sbi_trap.h"
#include "uart.h"
#include "asm/csr.h"


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

void sbi_trap_handler()
{
    uart_init();
	uart_send_string("Welcome RISC-V!\r\n");

}
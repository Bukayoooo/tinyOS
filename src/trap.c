/*
 * S模式异常处理代码
 */
#include "printk.h"

unsigned long ssrcatch;
unsigned long stvec;
unsigned long sie;
extern void do_exception_vector();

void trap_init(void)
{
    /* 清空ssrcatch寄存器 => 目的？ */
    write_csr(ssrcatch, 0);
    /* 写入异常向量表地址 */
    write_csr(stvec, do_exception_vector);
    printk("stvec=0x%x, 0x%x\n", read_csr(stvec), do_exception_vector);
    /* 使能所有中断 => TODO: 使能中断的目的？ */
    write_csr(sie, -1);
}
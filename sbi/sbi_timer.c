#include "io.h"
#include "sbi_trap.h"
#include "asm/clint.h"
#include "asm/csr.h"

/**
 * 时钟中断系统调用处理函数,将预设的定时器时间写入mtimecmp寄存器里
 * if mtime > mtimecmp: trigger timer interrupt
 */
void clint_timer_event_start(unsigned long next_event)
{
    /*将预设定时器时间写入mtimecmp里, 到时间就触发时钟中断*/
    writeq(next_event, VIRT_CLINT_TIMER_CMP);
    /*TODO: 清除S模式timer pending中断：MIP_STIP*/
    csr_clear(mip, MIP_STIP);
    /*TODO: 使能M模式中断*/
    csr_set(mie, MIE_MTIE);
}

/**
 * 时钟中断处理函数
 */
void sbi_timer_process(void)
{
    /*关闭M模式下的时钟中断*/
    csr_clear(mie, MIE_MTIE);
    /* 通过mip寄存器的STIP字段定时器等待中断注入S模式 */
    csr_set(mip, MIP_STIP);
}
#include "asm/sbi.h"
#include "asm/csr.h"
#include "asm/clint.h"
#include "io.h"
#include "type.h"

/**
 * CLINT_TIMERBASE_FREQ/HZ : 每次中断的时钟周期数
 */
#define CLINT_TIMERBASE_FREQ 10000000   /* mtimer频率 */
#define HZ 1               /*每秒触发时钟中断的次数*/

static unsigned long sie;
static unsigned long volatile cacheline_aligned jiffy;

/* 获取mtime当前的时钟周期数，就是当前时间 */
static inline unsigned long get_cycles(void)
{
    unsigned long current_mtime;
    /*从mtimer寄存器中获取当前时间*/
    current_mtime = readq(VIRT_CLINT_TIMER_VAL);
    return current_mtime;
}

/* 设置时钟中断 */
void reset_timer()
{
    /* 发起时钟中断系统调用 */
    sbi_set_timer(get_cycles() + CLINT_TIMERBASE_FREQ/HZ);
    /* 打开S模式时钟中断->sie寄存器 */
    csr_set(sie, SIE_STIE);
}

/* 初始化时钟中断 */
void timer_init()
{
    reset_timer();
}

/* S模式时钟中断处理函数 */
void handle_timer_interrupt()
{
    /* 关闭S模式时钟中断 */
    csr_clear(sie, SIE_STIE);
    /* 再次触发时钟中断系统调用 */
    reset_timer();
    /* 计时器+1 */
    jiffy++;
    /* 打印定时器中断输出 */
    printk("core0 timer interrupt recived, jiffy=%lu\r\n", jiffy);
}
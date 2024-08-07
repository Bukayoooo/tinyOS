#ifndef _ASM_RISCV_SBI_H
#define _ASM_RISCV_SBI_H

#include "printk.h"

/* 根据SBI规范设置系统调用号 */
#define SBI_SET_TIMER 0x0           /* 时钟中断 */
#define SBI_CONSOLE_PUTCHAR 0x1     /* 串口输出 */
#define SBI_CONSOLE_GETCHAR 0x2     /* 串口输入 */


/**
 * 实现ecall的sbi接口
 * which: sbi extension id (eid -> system call id) => a7
 * arg0, arg1, arg2 => a0, a1, a2 (three params while ecall)
 */
#define SBI_ECALL(which, arg0, arg1, arg2) ({  \
    register unsigned long a0 asm ("a0") = (unsigned long) (arg0);  \
    register unsigned long a1 asm ("a1") = (unsigned long) (arg1);  \
    register unsigned long a2 asm ("a2") = (unsigned long) (arg2);  \
    register unsigned long a7 asm ("a7") = (unsigned long) (which);  \
    asm volatile("ecall"    \
                :"+r"(a0)   \
                :"r" (a1), "r" (a2), "r" (a7) \
                : "memory"); \
    a0; \
})

/**
 * 定义宏调用SBI_ECALL
 */
#define SBI_ECALL0(which) SBI_ECALL(which, 0, 0, 0)
#define SBI_ECALL1(which, arg0) SBI_ECALL(which, arg0, 0, 0)
#define SBI_ECALL2(which, arg0, arg1) SBI_ECALL(which, arg0, arg1, 0)
#define SBI_ECALL3(which, arg0, arg1, arg2) SBI_ECALL(which, arg0, arg1, arg2)

/**
 * 串口输出系统调用, 调用sbi接口M模式下打印一个字符
 */
static inline void sbi_putchar(char c)
{
    SBI_ECALL1(SBI_CONSOLE_PUTCHAR, c);
}

static inline void sbi_putstring(char *str)
{
    for(int i = 0; str[i] != 0; i++)
    {
        sbi_putchar(str[i]);
    }
}

/**
 * 串口输入系统调用
 */
static inline char sbi_getchar(void)
{
    return SBI_ECALL0(SBI_CONSOLE_GETCHAR);
}

static inline char isprint(char c)
{
    return (c >= 32 && c <= 126);
}

/**
 * 时钟中断系统调用，调用sbi接口定时打印
 */
static inline void sbi_set_timer(unsigned long stime_value)
{
    SBI_ECALL1(SBI_SET_TIMER, stime_value);
}

static inline void sbi_inputchar()
{
	while(1)
	{
		char c = sbi_getchar();
		if(c != -1 && isprint(c))
		{
			printk("%c", c);
		}
		else if(c == '\r')
		{
			printk("\n");
		}
		
	}
}

#endif /* _ASM_RISCV_SBI_H */
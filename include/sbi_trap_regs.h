

/** 
 * 异常上下文需要保存的33个寄存器
 * 共 33 * 8 = 264 byte
 */
struct sbi_trap_regs
{   
    /* mepc + mstatus + 31个通用寄存器 */
    unsigned long mepc;     /* M模式异常PC指针寄存器 */
    
    /* x1-x4寄存器 */
    unsigned long ra;       /* x1: 函数返回地址寄存器 */
    unsigned long sp;       /* x2: 栈指针寄存器 */
    unsigned long gp;       /* x3: 全局寄存器 */
    unsigned long tp;       /* x4: 线程寄存器*/
    /* t0-t6临时寄存器 */
    unsigned long t0;       /* x5 */
    unsigned long t1;       /* x6 */
    unsigned long t2;       /* x7 */
    unsigned long t3;       /* x28 */
    unsigned long t4;       /* x29 */
    unsigned long t5;       /* x30 */
    unsigned long t6;       /* x31 */
    /* s0-s11保存寄存器 */
    unsigned long s0;       /* x8/fp:保存寄存器/栈帧指针寄存器 */
    unsigned long s1;       /* x9 */
    unsigned long s2;       /* x18 */
    unsigned long s3;       /* x19 */
    unsigned long s4;       /* x20 */
    unsigned long s5;       /* x21 */
    unsigned long s6;       /* x22 */
    unsigned long s7;       /* x23 */
    unsigned long s8;       /* x24 */
    unsigned long s9;       /* x25 */
    unsigned long s10;      /* x26 */
    unsigned long s11;      /* x27 */
    /* a0-a7寄存器 */
    unsigned long a0;       /* x10: 函数参数/返回值 */
    unsigned long a1;       /* x11: 函数参数/返回值 */
    unsigned long a2;       /* x12: 函数参数 */
    unsigned long a3;       /* x13: 函数参数 */
    unsigned long a4;       /* x14: 函数参数 */
    unsigned long a5;       /* x15: 函数参数 */
    unsigned long a6;       /* x16: 函数参数 */
    unsigned long a7;       /* x17: 函数参数 */
    
    unsigned long mstatus;  /* M模式异常原因寄存器 */

};

/*
 * 通过fp寄存器实现函数调用栈的打印
 */
#include "printk.h"
#include "type.h"

struct stackframe
{
    unsigned long s_fp;     /* 栈帧指针 */
    unsigned long s_ra;     /* 返回地址 */
};

extern char _text[];
extern char _etext[];

/* 检查地址是否在代码段 */
static int kernel_next(unsigned long addr)
{
    if(addr >= _text && addr <= _etext)
    {
        return 1;
    }

    return 0;
}

/* TODO */
static void walk_stackframe(void)
{
    unsigned long sp, fp, pc;
    unsigned long bottom;
    struct stackframe *frame;
    
    
    /* 取出当前函数pc值 */
    pc = (unsigned long) walk_stackframe;
    /* 内联汇编获取sp指针 */
    const register unsigned long current_sp __asm__ ("sp");
    sp = current_sp;
    /* 使用gcc内建函数获取fp指针 */
    fp = (unsigned long) __builtin_frame_address(0);

    while (1)
    {
        if(!kernel_next(pc))
        {   /* 地址不在代码段 */
            break;
        }

        bottom = sp + sizeof(struct stackframe);
        if(fp < bottom || fp & 0xf) {
            /* fp - sp > 16 || fp按16字节对齐？这里不应该是 && ？ */
            break;
        }

        /* fp指向栈底, fp-16: [s_fp, sp_ra]  */
        frame = (struct stackframe *) (fp -16);
        sp = fp;        /* 当前栈的栈底fp, 就是上一个栈的栈顶sp */
        fp = frame->s_fp;       /* 当前栈的s_fp记录着上一个栈的栈底fp  */

        /* 这个时调用函数的地址，并不是函数的地址，不能根据该pc值确认函数名称 */
        pc = frame->s_ra - 4;   /* 函数调用地址，返回地址-4, riscv一条指令占4字节 */

        if(kernel_next(pc))
        {
                /* %016lx: 0->前面填充0, 16->16位宽显示, x->16进制  */
                printk("[0x%016lx - 0x%016lx] pc 0x%016lx\n", sp, fp, pc);
        }

    }

}

/**/
void dump_stack()
{
    printk("call frame:\n");
    walk_stackframe();
}
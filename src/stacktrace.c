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
        



    }
    



}

/**/
void dump_stack()
{
    printk("call frame:\n");
    walk_stackframe();
}
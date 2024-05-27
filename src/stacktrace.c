/*
 * 通过fp寄存器实现函数调用栈的打印
 */
#include "printk.h"
#include "type.h"

struct stackframe
{
    unsigned long s_fp;     /* 栈帧指针 */
    unsigned long s_ra;     /* 返回地址： */
};


/* TODO */
static void walk_stackframe(void)
{

}

/**/
void dump_stack()
{
    printk("call frame:\n");
    walk_stackframe();
}
/*
 * S模式异常处理代码
 */
#include "printk.h"
#include "asm/csr.h"
#include "trap_regs.h"

unsigned long ssrcatch;
unsigned long stvec;
unsigned long sie;
extern void do_exception_vector();

struct fault_info
{
    int (*fn) (struct pt_regs *, const char *);
    char *name;
};

void panic(void)
{
    printk("kernel panic\n");
    while (1)
    {
    }
}

/**
 * 打印异常状态下寄存器信息与异常原因
 * regs: 寄存器信息
 * str：异常产生原因
 */
static void do_trap_error(struct pt_regs *regs, const char *str)
{
    printk("Oops, %s\n", str);

    panic();
}


#define DO_ERROR_INFO(name)     \
int name(struct pt_regs *regs, const char *str)     \
{           \
    do_trap_error(regs, str);        \
    return 0;        \
}           

/**** 各个异常对应的异常处理函数 ****/
DO_ERROR_INFO(do_trap_misaligned_fetch);
DO_ERROR_INFO(do_trap_instruction_fetch);
DO_ERROR_INFO(do_trap_illegal_instruction);
DO_ERROR_INFO(do_trap_breakpoint);
DO_ERROR_INFO(do_trap_misaligned_load);
DO_ERROR_INFO(do_trap_load_acess);
DO_ERROR_INFO(do_trap_amo_misaligned_store);
DO_ERROR_INFO(do_trap_amo_store_acess);
DO_ERROR_INFO(do_trap_user_ecall);
DO_ERROR_INFO(do_trap_supervisor_ecall);
DO_ERROR_INFO(do_trap_unknown);
DO_ERROR_INFO(do_trap_fetch_page_fault);
DO_ERROR_INFO(do_trap_load_page_fault);
DO_ERROR_INFO(do_trap_amo_store_page_fault);

static const struct fault_info fault_info[] ={
    {do_trap_misaligned_fetch, "instruction address misaligned"},
    {do_trap_instruction_fetch, "instruction acess fault"},
    {do_trap_illegal_instruction, "illegal instruction fault"},
    {do_trap_breakpoint, "breakpoint fault"},
    {do_trap_misaligned_load, "misaligned load fault"},
    {do_trap_load_acess, "load acess fault"},
    {do_trap_amo_misaligned_store, "amo or misaligned_store fault"},
    {do_trap_amo_store_acess, "amo store acess fault"},
    {do_trap_user_ecall, "user ecall"},
    {do_trap_supervisor_ecall, "supervisor ecall"},
    {do_trap_unknown, "unknow fault 10"},
    {do_trap_unknown, "unknow fault 11"},
    {do_trap_fetch_page_fault, "fetch page fault"},
    {do_trap_load_page_fault, "load page fault"},
    {do_trap_unknown, "unknow fault 14"},
    {do_trap_amo_store_page_fault, "amo store page fault"}
};

/**
 * 异常处理函数
 */
void trap_handler(struct trap_regs* regs, unsigned long scause)
{
    printk("%s, scause:0x%lx\n", __func__, scause);

    if(is_interrupt_fault(scause)) {
        /* 中断异常 */
        // TODO
    }
    else 
    {
        /* 普通异常 */
        
    }

}

/*
 * 异常初始化
 */
void trap_init(void)
{
    /* 清空ssrcatch寄存器 => 目的？ */
    write_csr(sscratch, 0);
    /* 写入异常向量表地址 */
    write_csr(stvec, do_exception_vector);
    printk("stvec=0x%x, exception vector address: 0x%x\n", read_csr(stvec), do_exception_vector);
    /* 使能所有中断 => TODO: 使能中断的目的？ */
    write_csr(sie, -1);
}
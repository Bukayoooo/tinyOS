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
    int (*fn) (struct trap_regs *, const char *);
    char *name;
};

void panic(void)
{
    printk("kernel panic\n");
    while (1)
    {
    }
}

void print_regs(struct trap_regs *regs)
{
    printk("sepc:0x%016lx sstatus:0x%016lx stvec:0x%016lx\n",
            regs->sepc, regs->sstatus, regs->stvec);
    printk("ra:0x%016lx sp:0x%016lx gp:0x%016lx tp:0x%016lx\n",
        regs->ra, regs->sp, regs->gp, regs->tp);
    printk("t0:0x%016lx t1:0x%016lx t2:0x%016lx t3:0x%016lx\n",
        regs->t0, regs->t1, regs->t2, regs->t3);
    printk("t4:0x%016lx t5:0x%016lx t6:0x%016lx s0:0x%016lx\n",
        regs->t4, regs->t5, regs->t6, regs->s0);
    printk("s1:0x%016lx s2:0x%016lx s3:0x%016lx s4:0x%016lx\n",
        regs->s1, regs->s2, regs->s3, regs->s4);
    printk("s5:0x%016lx s6:0x%016lx s7:0x%016lx s8:0x%016lx\n",
        regs->s5, regs->s6, regs->s7, regs->s8);
    printk("s9:0x%016lx s10:0x%016lx s11:0x%016lx a0:0x%016lx\n",
        regs->s9, regs->s10, regs->s11, regs->a0);
    printk("a1:0x%016lx a2:0x%016lx a3:0x%016lx a4:0x%016lx\n",
        regs->a1, regs->a2, regs->a3, regs->a4);
    printk("a5:0x%016lx a6:0x%016lx a7:0x%016lx scause:0x%016lx\n",
        regs->a5, regs->a6, regs->a7, regs->scause);
}

/**
 * 打印异常状态下寄存器信息与异常原因
 * regs: 寄存器信息
 * str：异常产生原因
 */
static void do_trap_error(struct trap_regs *regs, const char *str)
{
    printk("Oops, %s\n", str);
    print_regs(regs);
    panic();
}


#define DO_ERROR_INFO(name)     \
int name(struct trap_regs *regs, const char *str)     \
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
 * 根据异常处理原因scause查询异常处理表fault_info，以及调用异常处理函数
 */
const struct fault_info* ec_to_fault_info(unsigned long scause)
{
    return fault_info + (scause & SCAUSE_EC_NUMS);
}

/**
 * 异常处理函数
 */
void trap_handler(struct trap_regs* regs, unsigned long scause)
{

    const struct fault_info* inf;

    /* printk("%s, scause:0x%lx\n", __func__, scause); */

    if(is_interrupt_fault(scause)) {
        switch(scause & ~SCAUSE_INT)
        {
            case INTERRUPT_CAUSE_TIMER:
                /* 处理时钟中断 */
                handle_timer_interrupt();
                break;
            case INTERRUPT_CAUSE_SOFTWARE:
                /* TODO: 处理IPI中断 */
                break;
            case INTERRUPT_CAUSE_EXTERNAL:
                /* TODO: 处理IRQ中断 */
                break;
            default:
                printk("unexpected interrupt scause");
                break;

        }
    }
    else
    {
        /* 普通异常 */
        inf = ec_to_fault_info(scause);
        if(!inf->fn(regs, inf->name))
        {
                return;
        }
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
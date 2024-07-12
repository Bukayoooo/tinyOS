#ifndef _ASM_RISCV_CSR_H
#define _ASM_RISCV_CSR_H

#define INSERT_FIELD(val, which, fieldval) \
	(((val) & ~(which)) | ((fieldval) * ((which) & ~((which)-1))))

#define PRV_U				(0UL)
#define PRV_S				(1UL)
#define PRV_M				(3UL)

#define MSTATUS_MPP_SHIFT	11
#define MSTATUS_MPP	(3UL << MSTATUS_MPP_SHIFT)
#define MSTATUS_MPIE	0x00000080UL

#define SCAUSE_INT (1UL << 63)
#define is_interrupt_fault(reg) (reg & SCAUSE_INT)

#define SCAUSE_EC_NUMS (0xf)    /* 目前支持15个异常 */

/* 中断使能寄存器SIE标志位 */
#define SIE_SSIE 0x2UL      /* IPI软件中断使能 */
#define SIE_STIE 0x20UL     /* 时钟中断使能 */
#define SIE_SEIE 0x200UL    /* 外部中断使能 */

/* sstatus寄存器使能s模式中断*/
#define SSTATUS_SIE 0x2UL   /* S模式中断使能 */

/* scause寄存器Exception Code */
#define INTERRUPT_CAUSE_SOFTWARE 0x1    /* 软件中断 */
#define INTERRUPT_CAUSE_TIMER    0x5    /* 时钟中断 */
#define INTERRUPT_CAUSE_EXTERNAL 0x9    /* 外部中断 */


/*
 * 在带参数的宏，#号作为一个预处理运算符,
 * 可以把记号转换成字符串
 *
 * 下面这句话会在预编译阶段变成：
 *  asm volatile("csrr %0, " "reg" : "=r" (__val)); __val; });
 */
#define read_csr(csr)						\
({								\
	register unsigned long __v;				\
	__asm__ __volatile__ ("csrr %0, " #csr			\
			      : "=r" (__v) :			\
			      : "memory");			\
	__v;							\
})

#define write_csr(csr, val)					\
({								\
	unsigned long __v = (unsigned long)(val);		\
	__asm__ __volatile__ ("csrw " #csr ", %0"		\
			      : : "rK" (__v)			\
			      : "memory");			\
})

#define csr_set(csr, val)                               \
({                                                      \
    unsigned long __v = (unsigned long)(val);           \
    __asm__ __volatile__ ("csrs " #csr ", %0"           \
                          : : "rK" (__v) : "memory");   \
})

#define csr_clear(csr, val)                             \
({                                                      \
    unsigned long __v = (unsigned long)(val);           \
    __asm__ __volatile__ ("csrc " #csr ", %0"           \
                          : : "rK" (__v) : "memory");   \
})

#endif /*_ASM_RISCV_CSR_H*/

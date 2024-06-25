/**
 * S模式异常处理入口
 */

/* 异常入口：保存异常上下文 */
.macro exception_entry
    addi sp, sp, -(PT_SIZE)
    
    sd x1, PT_RA(sp)
	sd x3, PT_GP(sp)
	sd x4, PT_TP(sp)
	sd x5, PT_T0(sp)
	sd x6, PT_T1(sp)
	sd x7, PT_T2(sp)
	sd x8, PT_S0(sp)
	sd x9, PT_S1(sp)
	sd x10, PT_A0(sp)
	sd x11, PT_A1(sp)
	sd x12, PT_A2(sp)
	sd x13, PT_A3(sp)
	sd x14, PT_A4(sp)
	sd x15, PT_A5(sp)
	sd x16, PT_A6(sp)
	sd x17, PT_A7(sp)
	sd x18, PT_S2(sp)
	sd x19, PT_S3(sp)
	sd x20, PT_S4(sp)
	sd x21, PT_S5(sp)
	sd x22, PT_S6(sp)
	sd x23, PT_S7(sp)
	sd x24, PT_S8(sp)
	sd x25, PT_S9(sp)
	sd x26, PT_S10(sp)
	sd x27, PT_S11(sp)
	sd x28, PT_T3(sp)
	sd x29, PT_T4(sp)
	sd x30, PT_T5(sp)
	sd x31, PT_T6(sp)


.endm

/* 异常出口：恢复异常上下文 */
.macro exception_exit

.endm


/*
 * do_exception_vector 必须以4byte对齐，否则写入stvec寄存器失败
 * .align 2 => 以2^2=4 byte对齐，末尾为0，所以写入stvec一定是直接访问模式
 */
.align 2
.global do_exception_vector
do_exception_vector:
    /* 保存异常上下文 */
    exception_entry

    /* 调用异常处理函数 */
    mv a0, sp
    call trap_handler

    /* 恢复异常上下文 */
    exception_exit

    sret
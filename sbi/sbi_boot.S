.section ".text.boot"

.globl _start
_start:

	/* 关闭M模式的中断 */
	csrw mie, zero

	/* setup stack with 4KB size */
	la sp, stacks_start
	li t0, 4096
	add sp, sp, t0

	/*
	 * 将M模式的栈指针保存到异常临时寄存器mscratch中
	 * 下次异常陷入M模式，即可获取sp
	 */
	csrw mscratch, sp
	
	/* goto C */
	tail sbi_main

.section .data
.align  12
.global stacks_start
stacks_start:
	.skip 4096

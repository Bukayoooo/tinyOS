.section ".text.boot"

.global _start
_start:
	/* Mask all interrupts */
	csrw sie, zero

	/************************/
	/* add booting message */
	call __init_uart
	call print_asm

	/***********************/

	/* set the stack of SP, size 4KB */
	la sp, stacks_start
	li t0, 4096
	add sp, sp, t0

	/* goto C */
	tail kernel_main

print_asm:
	addi sp, sp, -32
	sd ra, 24(sp)

	la a0, boot_string

	call put_string_uart

	ld ra, 24(sp)
	addi sp, sp, 32

	ret

.section .data
.align  12
.global stacks_start
stacks_start:
	.skip 4096

.section .rodata
.align 3
.global boot_string
boot_string:	/* pagga */
	.string "target remote localhost:1234\n
░▀█▀░▀█▀░█▀█░█░█░█▀█░█▀▀
░░█░░░█░░█░█░░█░░█░█░▀▀█
░░▀░░▀▀▀░▀░▀░░▀░░▀▀▀░▀▀▀                    
			 \n"
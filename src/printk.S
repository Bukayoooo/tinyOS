#include "asm/uart.h"

.align 2
.globl __init_uart
__init_uart:
        /* disable interrupt */
        la t0, UART_IER
        sb x0, (t0)

        /* Enable DLAB (set baud rate divisor)*/
        la t0, UART_LCR
        li t1, 0x80
        sb t1, (t0)

        la t0, UART_DLL
        li t1, 1
        sb t1, (t0)

        la t0, UART_DLM
        sb x0, (t0)

        /*8 bits, no parity, one stop bit*/
        la t0, UART_LCR
        li t1, 3
        sb t1, (t0)

        /* 使能FIFO，清空FIFO，设置14字节threshold*/
        la t0, UART_FCR
        li t1, 0xc7
        sb t1, (t0)

        ret

/* void put_uart(char *) */
.global put_uart
put_uart:
    addi sp, sp, -32
    sd ra, 24(sp)

.loop:
    la t0, UART_LSR    /* UART_LSR:线路状态寄存器 */
    lbu t1, (t0)

    andi t1, t1, 0x40   /* 检查UART_LSR第6位，1->uart发送保存寄存器空闲，0->不空闲 */
    beqz t1, .loop      /* THR不空闲，循环等待知道t0=1 THR寄存器空闲 */

    la t0, UART_DAT     /* UART_DAT:数据寄存器 */
    sb a0, (t0)         /* 将1byte数据写入UART_DAT寄存器中 */

    ld ra, 24(sp)
    # addi sp, sp, -32  /* 这里写成-32了，找半天-_- */
    addi sp, sp, 32

    ret

/*
 * void put_string_uart(void *);
 */
.global put_string_uart
put_string_uart:
    addi sp, sp, -32
    sd ra, 24(sp)

    /*eg. a0=['h','e','l','l','o','\0']*/
    mv a5, a0

.loop1:
    lbu a0, (a5)
    beqz a0, .L2    /* a0 == '\0', string ends */
    call put_uart
    addi a5, a5, 1
    j .loop1

.L2:
    ld ra, 24(sp)
    # addi sp, sp, -32  * 这里也写成-32了-_- */
    addi sp, sp, 32

    ret

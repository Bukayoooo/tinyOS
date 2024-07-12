#ifndef _CLINT_RISCV_H
#define _CLINT_RISCV_H

/**
 * CLINT中断地址与大小可在qemu源码中查到
 * qemu hw/riscv64/virt.c
 * [VIRT_CLINT] =        {  0x2000000,       0x10000 },
 */
#define VIRT_CLINT_ADDR 0x2000000                          /* CLINT中断基地址 */
#define VIRT_CLINT_TIMER_CMP (VIRT_CLINT_ADDR + 0x4000)     /*mtimercmp寄存器地址*/
#define VIRT_CLINT_TIMER_VAL (VIRT_CLINT_ADDR + 0xbff8)     /*mtimer寄存器地址*/

#endif /* _CLINT_RISCV_H */

#ifndef _RISCV_PRINTK_H
#define _RISCV_PRINTK_H

void init_printk_done(void (*fn)(char c));
int printk(const char *fmt, ...);

#endif /* _RISCV_PRINTK_H */
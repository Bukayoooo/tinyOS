#include "memset.h"

extern void *__memset_16bytes_asm(char *, unsigned long , size_t);

/* memset with c */
static void *__memset_1bytes(void *s, int c, size_t count)
{
    char *ts = s;
    while(count > 0)
    {
        *ts = c;
        ts++;
        count--;
    }

    return s;
}

/* memset with riscv asm */
static void *__memset(char *s, int c, size_t count)
{
        unsigned long data = 0UL;
        unsigned long addr = (unsigned long) s;
        unsigned long align = 16;
        char *p = s;
        size_t size, left = 0UL;
        size_t n = 0UL;

        /* 将c扩展至64位，如果写入0xAB,那么data=0xABABABABABABABAB */
        for(int i = 0; i < 8; i++)
        {
                data |= ((unsigned long) c & 0xff) << (i * 8);
        }

        /* 检查addr是否是16位对齐的 */
        if(addr & (align - 1))
        {
                size_t size = addr & (align - 1);
                size = align - size;

                __memset_1bytes(p, c, size);

                p += size;
                left = count - size;
        }

        if(left > align)
        {
                n = left / align;
                left = left % align;
        }

        __memset_16bytes_asm(p, data, align * n);

        if(left)
        {
                __memset_1bytes(p + align * n, data, left);
        }
}


void *memset_test(void *s, int c, size_t count)
{
    __memset(s, c, count);
}
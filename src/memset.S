/*
 * void *__memset_16bytes_asm(void *s, unsigned long data, size_t count);
 * a0 = s; a1 = data; a2 = count
 */

.global __memset_16bytes_asm
__memset_16bytes_asm:
        li t0, 0        /* counter */

.loop:
        sd a1, (a0)             /* store first 8 bytes */
        sd a1, 8(a0)    /* store second 8 bytes */
        addi t0, t0, 16
        addi a0, a0, 16
        blt t0, a2, .loop

        ret
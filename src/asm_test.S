.global memcpy_test
memcpy_test:
    li t0, 0x80200000
    li t1, 0x80210000
    addi t2, t0, 32

.loop:
    ld t3, (t0)
    sd t3, (t1)
    addi t0, t0, 8
    addi t1, t1, 8
    blt t0, t2, .loop

    ret
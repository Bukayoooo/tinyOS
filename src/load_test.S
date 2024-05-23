.align 3
.global my_test_data
my_test_data:
    .dword 0x123456789abcd

.global load_store_test      
load_store_test:
    li a0, 0x80200000
    li a1, 16

    lw t0, (a0)
    ld t1, 16(a0)

    lui t2, 0x8034f
    lui t3, 0x400

    ret
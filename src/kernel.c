#include "uart.h"
#include "memset.h"
#include "asm/sbi.h"
#include "printk.h"

extern void load_store_test(void);
extern void load_test(void);
extern void memcpy_test(void);
extern void trap_init(void);
extern void trigger_fault(void);

void asm_test()
{
	load_store_test();
	memcpy_test();
	memset_test((void *)0x80210005, 0x88, 40);

}

extern char _text_boot[], _etext_boot[];
extern char _text[], _etext[];
extern char _rodata[], _erodata[];
extern char _data[], _edata[];
extern char _bss[], _ebss[];

/* print tinyos image layout */
static void print_mem()
{
	printk("tinyos image layout:\n");
	printk("  .text.boot: 0x%08lx - 0x%08lx (%6ld B)\n",
					(unsigned long) _text_boot, (unsigned long) _etext_boot,
					(unsigned long) (_etext_boot - _text_boot));
	printk("       .text: 0x%08lx - 0x%08lx (%6ld B)\n",
					(unsigned long) _text, (unsigned long) _etext,
					(unsigned long) (_etext - _text));
	printk("     .rodata: 0x%08lx - 0x%08lx (%6ld B)\n",
					(unsigned long) _rodata, (unsigned long) _erodata,
					(unsigned long) (_erodata - _rodata));
	printk("       .data: 0x%08lx - 0x%08lx (%6ld B)\n",
					(unsigned long) _data, (unsigned long) _edata,
					(unsigned long) (_edata - _data));
	printk("        .bss: 0x%08lx - 0x%08lx (%6ld B)\n",
					(unsigned long) _bss, (unsigned long) _ebss,
					(unsigned long) (_ebss - _bss));
}

/* target remote localhost:1234 */
void kernel_main(void)
{
	// uart_init();
	// uart_send_string("Welcome RISC-V!\r\n");
	sbi_putstring("Welcome RISC-V!\r\n");
	init_printk_done(sbi_putchar);


	/* 初始化S模式异常  */
	trap_init();

	
	/* 打印image layout */
	print_mem();

	asm_test();
	/* 触发地址访问异常 */
	trigger_fault();


	while (1) {
			;
	}
}
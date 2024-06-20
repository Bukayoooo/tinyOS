#include "uart.h"
#include "memset.h"
#include "asm/sbi.h"

extern void load_store_test(void);
extern void load_test(void);
extern void memcpy_test(void);

void asm_test()
{
	load_store_test();
	memcpy_test();
	memset_test((void *)0x80210005, 0x88, 40);

}


/* target remote localhost:1234 */
void kernel_main(void)
{
	// uart_init();
	// uart_send_string("Welcome RISC-V!\r\n");
	sbi_putstring("Welcome RISC-V!\r\n");

	asm_test();

	while (1) {
		;
	}
}

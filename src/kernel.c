#include "uart.h"

extern void load_store_test(void);
extern void memcpy_test(void);

void load_test()
{
	load_store_test();
}


void kernel_main(void)
{
	uart_init();
	uart_send_string("Welcome RISC-V!\r\n");

	load_test();
	memcpy_test();

	while (1) {
		;
	}
}

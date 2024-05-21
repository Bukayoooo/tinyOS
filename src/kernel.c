#include "uart.h"

void load_test()
{
	load_store_test();
}


void kernel_main(void)
{
	uart_init();
	uart_send_string("Welcome RISC-V!\r\n");

	load_test();

	while (1) {
		;
	}
}

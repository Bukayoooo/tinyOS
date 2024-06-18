#include "uart.h"
#include "memset.h"
#include "printk.h"

int add_c(int a, int b)
{
	dump_stack();
	return a + b;
}


int func1(void)
{
	int a = 1;
	int b = 2;

	return add_c(a, b);
}


/* target remote localhost:1234 */
void kernel_main(void)
{
	uart_init();
	uart_send_string("Welcome RISC-V!\r\n");
	init_printk_done();

	func1();

	while (1) {
		;
	}
}

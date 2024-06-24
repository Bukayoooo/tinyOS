SECTIONS
{
	. = 0x80200000,

	/* text.boot: tinyos启动指令 */
	_text_boot = .;
	.text.boot : { *(.text.boot) }
	_etext_boot = .;

	. = ALIGN(8);
	_text = .;
	.text : { *(.text) }
	_etext = .;

	_rodata = .;
	.rodata : { *(.rodata) }
	_erodata = .;

	_data = .;
	.data : { *(.data) }
	_edata = .;

	. = ALIGN(0x8);

	_bss = .;
	.bss : { *(.bss*) }
	_ebss = .;
}


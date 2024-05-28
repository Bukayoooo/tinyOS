SECTIONS
{
	/* tinyos加载入口地址, .代表当前位置 */
	. = 0x80200000,

	/* 第一个段text.boot，起始地址就是0x80200000
     * 这个段存放了benos的第一条指令 */
	 _text.boot = .;
	.text.boot : { *(.text.boot) }

	/* text代码段 */
	. = .ALIGN(8)
	_text = .;		/* text段开始 */
	.text : { *(.text) }
	_etext = .;		/* text段结束 */

	/* 只读数据段 */
	.rodata : { *(.rodata) }

	/* 数据段 */
	.data : { *(.data) }
	
	/* bss段 */
	. = ALIGN(0x8);
	bss_begin = .;
	.bss : { *(.bss*) }
	bss_end = .;
}
/*
 * GENERATED FILE - DO NOT EDIT
 * (C) Code Red Technologies Ltd, 2008-2013
 * Generated linker script file for LPC1769
 * Created from generic_c.ld (vLPCXpresso v5.0 (14 [Build 1109] [2012-12-19] ))
 * By LPCXpresso v5.0.14 [Build 1109] [2012-12-19]  on Sun Feb 24 06:50:54 PST 2013
 */


INCLUDE "led_array_arm_Debug_lib.ld"
INCLUDE "led_array_arm_Debug_mem.ld"

ENTRY(ResetISR)

SECTIONS
{

	/* MAIN TEXT SECTION */	
	.text : ALIGN(4)
	{
		FILL(0xff)
		KEEP(*(.isr_vector))
		
		/* Global Section Table */
		. = ALIGN(4) ;
		__section_table_start = .;
		__data_section_table = .;
		LONG(LOADADDR(.data));
		LONG(    ADDR(.data)) ;
		LONG(  SIZEOF(.data));
		LONG(LOADADDR(.data_RAM2));
		LONG(    ADDR(.data_RAM2)) ;
		LONG(  SIZEOF(.data_RAM2));
		__data_section_table_end = .;
		__bss_section_table = .;
		LONG(    ADDR(.bss));
		LONG(  SIZEOF(.bss));
		LONG(    ADDR(.bss_RAM2));
		LONG(  SIZEOF(.bss_RAM2));
		__bss_section_table_end = .;
		__section_table_end = . ;
		/* End of Global Section Table */
		

		*(.after_vectors*)
		
		*(.text*)
		*(.rodata .rodata.*)
		. = ALIGN(4);
		
	} > MFlash512

	/*
	 * for exception handling/unwind - some Newlib functions (in common
	 * with C++ and STDC++) use this. 
	 */
	.ARM.extab : ALIGN(4)
	{
		*(.ARM.extab* .gnu.linkonce.armextab.*)
	} > MFlash512
	__exidx_start = .;
	
	.ARM.exidx : ALIGN(4)
	{
		*(.ARM.exidx* .gnu.linkonce.armexidx.*)
	} > MFlash512
	__exidx_end = .;
	
	_etext = .;
		
	
	.data_RAM2 : ALIGN(4)
	{
	   FILL(0xff)
		*(.data.$RAM2*)
		*(.data.$RamAHB32*)
	   . = ALIGN(4) ;
	} > RamAHB32 AT>MFlash512
	
	/* MAIN DATA SECTION */

	.uninit_RESERVED : ALIGN(4)
	{
		KEEP(*(.bss.$RESERVED*))
		. = ALIGN(4) ;
		_end_uninit_RESERVED = .;
	} > RamLoc32

	.data : ALIGN(4)
	{
		FILL(0xff)
		_data = .;
		*(vtable)
		*(.data*)
		. = ALIGN(4) ;
		_edata = .;
	} > RamLoc32 AT>MFlash512

	
	.bss_RAM2 : ALIGN(4)
	{
		*(.bss.$RAM2*)
		*(.bss.$RamAHB32*)
	   . = ALIGN(4) ;
	} > RamAHB32

	/* MAIN BSS SECTION */
	.bss : ALIGN(4)
	{
		_bss = .;
		*(.bss*)
		*(COMMON)
		. = ALIGN(4) ;
		_ebss = .;
		PROVIDE(end = .);
	} > RamLoc32
		
	
	.noinit_RAM2 (NOLOAD) : ALIGN(4)
	{
		*(.noinit.$RAM2*)
		*(.noinit.$RamAHB32*)
	   . = ALIGN(4) ;
	} > RamAHB32 
	
	/* DEFAULT NOINIT SECTION */
	.noinit (NOLOAD): ALIGN(4)
	{
		_noinit = .;
		*(.noinit*) 
	 	. = ALIGN(4) ;
		_end_noinit = .;
	} > RamLoc32
	
	PROVIDE(_pvHeapStart = .);
	PROVIDE(_vStackTop = __top_RamLoc32 - 0);
}

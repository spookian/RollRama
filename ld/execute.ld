OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc", "elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

"__start" = 0x80006310;
ENTRY(__start)

SECTIONS
{
	rtdl : { KEEP(link.o(rtdl) ) }
	detour = .;
	
	. = 0x00000008;
	dol_toffset2 : { KEEP(*(dol_toffset2)) }
	
	. = 0x808D120C;
	.text : 
	{
		KEEP(*(.text .text.*)) 
	}
	
	.data : 
	{
		KEEP(*(.rodata .rodata.*))
		KEEP(*(.data .data.*)) 
		KEEP(*(.sdata .sdata.* ))

	}
}

"TXT3_FOFFSET" = detour;
"TXT3_MOFFSET" = 0x808D120C;
"TXT3_SIZE" = SIZEOF(.text);

"DAT7_SIZE" = SIZEOF(.data);
"DAT7_FOFFSET" = detour + TXT3_SIZE;
"DAT7_MOFFSET" = TXT3_MOFFSET + TXT3_SIZE;
OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc", "elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

INCLUDE ./ld/symbols/new.ld

"__start" = 0x80006310;
ENTRY(__start)

SECTIONS
{
	rtdl : { KEEP(link.o(rtdl) ) }
	detour = .;
	
	. = 0x00000008;
	dol_toffset2 :	{ KEEP(*(dol_toffset2)) }
	
	. = 0x0000001C+0x20;
	dol_doffset8 :	{ KEEP(*(dol_doffset8)) }
	
	. = 0x00000048+0x8; 
	dol_taddr2 :	{ KEEP(*(dol_taddr2)) }
	
	. = 0x00000048+0x3C;
	dol_daddr8 : 	{ KEEP(*(dol_daddr8)) }
	
	. = 0x00000008;
	dol_tsize2 :	{ KEEP(*(dol_tsize2)) }
	
	. = 0x00000008;
	dol_dsize8 :	{ KEEP(*(dol_dsize8)) }
	
	TXT2_OFFSET = .;
	. = 0x808D120C;
	TXT2_ADDRESS = .;
	.text : 
	{
		KEEP(*(.text .text.*)) 
	}
	
	DAT8_ADDRESS = .;
	.data : 
	{
		KEEP(*(.bss .bss.*))
		KEEP(*(.rodata .rodata.*))
		KEEP(*(.data .data.*)) 
		KEEP(*(.sdata .sdata.* ))

	}
}

"TXT2_SIZE" = SIZEOF(.text);

"DAT8_SIZE" = SIZEOF(.data);
"DAT8_OFFSET" = detour + TXT3_SIZE;
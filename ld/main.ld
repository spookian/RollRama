OUTPUT_FORMAT("elf32-powerpc", "elf32-powerpc", "elf32-powerpc")
OUTPUT_ARCH(powerpc:common)

INCLUDE ./ld/symbols/new.ld
INCLUDE ./ld/symbols/fixedstring.ld
INCLUDE ./ld/symbols/g3d.ld
INCLUDE ./ld/symbols/math.ld
INCLUDE ./ld/symbols/gx.ld
INCLUDE ./ld/symbols/file.ld
INCLUDE ./ld/symbols/app.ld
INCLUDE ./ld/symbols/hid.ld
INCLUDE ./ld/symbols/lyt.ld

"__start" = 0x80006310;
ENTRY(__start)

SECTIONS
{
	rtdl : { KEEP(link.o(rtdl) ) }
	TXT2_OFFSET = .;
	
	. = 0x00000008;
	dol_toffset2 :	{ KEEP(*(dol_toffset2)) }
	
	. = 0x0000003C;
	dol_doffset8 :	{ KEEP(*(dol_doffset8)) }
	
	. = 0x00000048+0x8; 
	dol_taddr2 :	{ KEEP(*(dol_taddr2)) }
	
	. = 0x00000048+0x3C;
	dol_daddr8 : 	{ KEEP(*(dol_daddr8)) }
	
	. = 0x00000090+0x08;
	dol_tsize2 :	{ KEEP(*(dol_tsize2)) }
	
	. = 0x00000090+0x3C;
	dol_dsize8 :	{ KEEP(*(dol_dsize8)) }
	
	. = 0x808D120C;
	TXT2_ADDRESS = .;
	.text : 
	{
		KEEP(*(.text .text.*)) 
	}
	
	DAT8_ADDRESS = .;
	.data : 
	{
		KEEP(*(.rodata .rodata.*))
		KEEP(*(.data .data.*)) 
		KEEP(*(.sdata .sdata.* ))
	}
	
	. = 0x806f9e2c;
	__006F5C6C :	{ KEEP(*(__006F5C6C)) }
	
	. = 0x808c529c;
	__007E393C :	{ KEEP(*(__007E393C)) }
}

"TXT2_SIZE" = SIZEOF(.text);

"DAT8_SIZE" = SIZEOF(.data);
"DAT8_OFFSET" = TXT2_OFFSET + TXT2_SIZE;
# data sections
.section dol_doffset8, "awx", @progbits
.long DAT8_OFFSET

.section dol_dsize8, "awx", @progbits
.long DAT8_SIZE

.section dol_daddr8, "awx", @progbits
.long DAT8_ADDRESS


# file sections
.section dol_toffset2, "awx", @progbits
.long TXT2_OFFSET

.section dol_tsize2, "awx", @progbits
.long TXT2_SIZE

.section dol_taddr2, "awx", @progbits
.long TXT2_ADDRESS

.section __006F5C6C, "awx", @progbits
hook_sequenceroot:
	li %r3, 0x4
	#let us hope to GOD this fucking class never changes otherwise i'm dragging all of you into hell with me
	bl __nw__Q23seq9ISequenceFUl
	cmpwi %r3, 0
	beq 0x8
	bl __ct__Q23seq17SequenceTiltStartFv

.section __007E393C, "awx", @progbits
.long 0x00000000
.long 0x00000000
.long 0x44200000
.long 0x43e40000

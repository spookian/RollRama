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
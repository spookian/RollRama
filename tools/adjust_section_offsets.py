from elf import *
import argparse
import os

END_RTDL_DOL = 0x808D120C
END_RTDL_FILE = 0x7EF860

def parse_elf(bfile):
    elf = ELFFile(bfile)
    for x in elf.sections:
        print(x.name)
        if (x.sh_addr >= END_RTDL_DOL):
            #do some bullshit here with calculating the end of file
            new_addr = ((x.sh_addr - END_RTDL_DOL) + END_RTDL_FILE).to_bytes(4, byteorder='big')
            bfile.seek(x.header_offset + 0xC)
            bfile.write(new_addr)
        elif (x.name[:2] == "__"): # name of section is an indicator for hooks
            new_addr = (int(x.name[2:10], 16)).to_bytes(4, byteorder='big')
            bfile.seek(x.header_offset + 0xC)
            bfile.write(new_addr)
            

if __name__ == "__main__":
    parser = argparse.ArgumentParser(prog='adjust_section_offsets.py',
                                     description='A small script to aid me',
                                     epilog='Do not use with object files.')

    parser.add_argument('path_to_elf')
    args = parser.parse_args()
    file = open(args.path_to_elf, "rb+")
    parse_elf(file)
    

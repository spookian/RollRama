import argparse
import os

MAX_TEXT_SECTIONS = 7
MAX_DATA_SECTIONS = 11
DATA_FILE_OFFSET = 0x1C
TEXT_SIZE_OFFSET = 0x90
DATA_SIZE_OFFSET = 0xAC

cmdpath = os.getcwd() + '\\'

# takes a main.dol
# splits it into x amount of text bin files and y amount of data bin files
def split_bin(num: int, text: bool, file: bytes, offset: int, size: int) -> None:
    if offset == 0:
        return
    
    string = "data_"
    if text == True:
        string = "text_"
    result = open(cmdpath + string + str(num) + ".bin", "xb")
    byte_string = file[offset:(offset+size)]
    result.write(byte_string)
    result.close()
    return

def parse_dol(byte_string: bytes):
    for n in range(MAX_TEXT_SECTIONS):
        j = n*4
        k = TEXT_SIZE_OFFSET + j
        bin_offset = int.from_bytes(byte_string[j:j+4], byteorder='big')
        size = int.from_bytes(byte_string[k:k+4], byteorder='big')
        split_bin(n, True, byte_string, bin_offset, size)
    #loop through all text sections

    for n in range(MAX_DATA_SECTIONS):
        i = n*4
        j = DATA_FILE_OFFSET + i
        k = DATA_SIZE_OFFSET + i
        bin_offset = int.from_bytes(byte_string[j:j+4], byteorder='big')
        size = int.from_bytes(byte_string[k:k+4], byteorder='big')
        split_bin(n, False, byte_string, bin_offset, size)
    #loop through all data sections
    return

def main():
    # kind of irresponsible of me to load an entire 8mb dol file into memory but whatever, my computer's nasa tier
    parser = argparse.ArgumentParser(description="Splits up a dol executable for the GameCube.")
    parser.add_argument("filename")
    arg = parser.parse_args()
    dol = open(arg.filename, "rb")
    raw_data = dol.read()
    dol.close()

    parse_dol(raw_data)
    return

if __name__ == "__main__":
    main()

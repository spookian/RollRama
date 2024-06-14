# wiener script to turn .raw files into .bwav for wii and wiimotes
# takes 16-bit mono channel .raw files with 6000 hz sample rate
import argparse
import os
import math

parser = argparse.ArgumentParser(prog='bwavcreator.py',
                                 description='Turns raw audio files into bwavs',
                                 epilog='i love wieners')
parser.add_argument('i')
parser.add_argument('o')
args = parser.parse_args()

output = None
if (args.o): output = args.o
else: output = "output.bwav"

rawfile = open(args.i, "rb+")
newfile = open(args.o, "wb")

filesize = os.path.getsize(args.i)
new_filesize = math.ceil(filesize / 80) * 80
padding_size = new_filesize - filesize

og_data = rawfile.read()
newfile.write(og_data)
for i in range(padding_size):
    newfile.write(b'\0')

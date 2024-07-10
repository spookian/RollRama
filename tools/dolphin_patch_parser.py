import os
patch_list = list()

class Patch:
    def __init__(self, string):
        x = string.split(":dword:")
        self.addr = int(x[0], 16)
        self.patch = int(x[1], 16)
        return

mf_patch = open("tools/metafortress.txt", "r")
s = mf_patch.readline()
while (s != ""):
    patch_list.append( Patch(s) )
    s = mf_patch.readline()

if (os.path.exists("RTDLBASE.dol") == False):
    print("RTDLBASE.dol not in main folder!")
    sys.exit(1)

maindol = open("RTDLBASE.dol", "rb")
maindata = maindol.read()
maindol.close()
# note: .init and .text are often treated as text sections
# the gamecube/wii dol files can support up to 8 text sections, but no game takes advantage of this fact

text_offset = int.from_bytes(maindata[0x4:0x8])
text_address = int.from_bytes(maindata[0x4C:0x50])

newdol = open("RTDLBASE_patched.dol", "wb")
newdol.write(maindata)

for i in patch_list:
    offset = (i.addr - text_address) + text_offset
    newdol.seek(offset)
    newdol.write( i.patch.to_bytes(4, 'big') )
newdol.close()

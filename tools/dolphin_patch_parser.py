from cw_symmap import *

patch_list = list()

class Patch:
    def __init__(self, string):
        x = string.split(":dword:")
        self.addr = int(x[0], 16)
        self.patch = int(x[1], 16)
        return

iuk = open("C:\\base rtdl\\DATA\\files\\iuk.map", "rb") # must be rb because codewarrior uses \r escapes
load_symbols(iuk)

mf_patch = open("metafortress.txt", "r")
s = mf_patch.readline()
while (s != ""):
    patch_list.append( Patch(s) )
    s = mf_patch.readline()

maindol = open("../rtdlbase.dol", "rb")
maindata = maindol.read()
newdol = open("mainmeta.dol", "wb")
newdol.write(maindata)
maindol.close()

for i in patch_list:
    offset = 0
    for j in symbol_list:
        if (j.check_address( i.addr )):
            offset = j.file_offset + (i.addr - j.virtual_addr)
            break
    newdol.seek(offset)
    newdol.write( i.patch.to_bytes(4, 'big') )
    print(f"{j.name} : {offset:08x} : {i.addr:08x} patched!")
newdol.close()

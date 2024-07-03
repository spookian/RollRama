import os
symbol_list = list()

class CWSymbol:
    def __init__(self, string):
        number = 4
        l = list(filter(None, string.split(" ")))
        if (l[0] == "UNUSED"):
            self.exists = False
            return

        if (l[5] == ".text" or "*fill*" in l[5]):
            self.exists = False
            return
        
        self.exists = True
        self.file_offset = int(l[3], 16)
        self.size = int(l[1], 16)
        self.virtual_addr = int(l[2], 16)
        if (l[number].isnumeric()):
            number += 1
        self.name = l[number]
        return

    def check_address(self, x):
        return (x >= self.virtual_addr) and (x <= (self.virtual_addr + self.size))

def load_symbols(file):
    file.seek(0x55318A)
    check_str = file.readline()
    while (check_str != b'\r\n'):
        sym = CWSymbol( check_str.decode("UTF-8") )
        if (sym.exists):
            symbol_list.append(sym)
        check_str = file.readline()
    return

if __name__ == "__main__":
    path = input("Give me the path of iuk.map: ")
    if os.path.exists(path):
        iuk_map = open(path, "rb")
        load_symbols(iuk_map)
       
    

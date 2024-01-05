SECTIONHEADER_OFFSET = 0x10 

class ELFFile:
    def __init__(self, stream):
        if (stream.read(4) != b'\x7fELF'):
            raise Exception("This file is not an ELF file.")
        
        self.stream = stream
        self.sections = list()
        # create list of sections

        stream.seek(0x20)
        self.e_shoff = int.from_bytes(stream.read(4))

        stream.seek(0x2e)
        self.e_shentsize = int.from_bytes(stream.read(2))
        self.e_shnum = int.from_bytes(stream.read(2))
        self.e_shstrndx = int.from_bytes(stream.read(2))

        stream.seek(self.e_shoff + (self.e_shstrndx * self.e_shentsize) + SECTIONHEADER_OFFSET)
        strtb_offset = int.from_bytes(stream.read(4))
        for x in range(self.e_shnum):
            offset = self.e_shoff + (self.e_shentsize * x)
            stream.seek(offset)
            self.sections.append(ELFSection(stream, strtb_offset))

        return

class ELFSection:
    def __init__(self, stream, stroff: int):
        start = stream.tell()
        stream.seek(stroff + int.from_bytes(stream.read(4)))
        self.name = get_string_with_bytestream(stream)
        self.header_offset = start

        stream.seek(start + 4)
        
        self.sh_type = int.from_bytes(stream.read(4))
        self.sh_flags = int.from_bytes(stream.read(4))
        self.sh_addr = int.from_bytes(stream.read(4))
        self.sh_offset = int.from_bytes(stream.read(4))
        self.sh_size = int.from_bytes(stream.read(4))
        return

def get_string_with_bytestream(stream):
    x = bytearray()
    while(int.from_bytes(x[-1:]) != 0):
        x.extend(stream.read(1))

    result = x.decode(encoding='ascii')
    return result

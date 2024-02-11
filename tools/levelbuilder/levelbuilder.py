import struct

class CollisionCore:
    size = 4 + 2 + 2 + 4 + 4
    magic = "ROLL"
    
    def __init__(self):
        self.triangle_list = []
        self.vector_list = []
        return

    def create_header_bytes(self):
        magicbytes = bytes(magic, 'utf-8')
        num_vectors = len(self.vector_list)
        num_triangles = len(self.triangle_list)
        vectorlist_offset = CollisionCore.size
        trianglelist_offset = vectorlist_offset + (Vector3.sizeof() * num_vectors)
        
        if (num_vectors == 0): vectorlist_offset = -1
        if (num_triangles == 0): trianglelist_offset = -1
        return struct.pack(">4pHHHLL", magicbytes, startpos_idx, num_vectors, num_triangles, vectorlist_offset, trianglelist_offset)

    def create_triangle_bytes_from_list(self):
        x = b''
        for tri in self.triangle_list:
            x = x + bytes(tri)
        return x

    def create_vector_bytes_from_list(self):
        x = b''
        for vec in self.vector_list:
            x = x + bytes(vec)
        return x
    
    def create_file_bytes(self):
        return self.create_header_bytes() + self.create_vector_bytes_from_list() + self.create_triangle_bytes_from_list()

class Triangle:
    def __init__(self, core):
        self.core = core

        self.v0 = None
        self.v1 = None
        self.v2 = None
        self.nrm = None
        self.d = 0.0 #plane equation

        #connected tris
        self.e0 = None
        self.e1 = None
        self.e2 = None
        
        return

    def find_tri_id_in_list(self, tri):
        x = 0
        if (tri == None): return -1
        for _tri in self.core.triangle_list:
            if (tri == _tri):
                return x
            x += 1
        return -1

    def find_vec_id_in_list(self, vec):
        x = 0
        if (vec == None): return -1
        for _vec in self.core.vector_list:
            if (vec == _vec):
                return x
            x += 1
        return -1

    def __bytes__(self):
        v0 = self.find_vec_id_in_list(self.v0)
        v1 = self.find_vec_id_in_list(self.v1)
        v2 = self.find_vec_id_in_list(self.v2)
        nrm = self.find_vec_id_in_list(self.nrm)

        e0 = self.find_tri_id_in_list(self.e0)
        e1 = self.find_tri_id_in_list(self.e1)
        e2 = self.find_tri_id_in_list(self.e2)
        return struct.pack(">HHHHfHHH", v0, v1, v2, nrm, self.d, e0, e1, e2)

class Vector3:
    def __init__(self, _x = 0, _y = 0, _z = 0):
        self.x = _x
        self.y = _y
        self.z = _z

    def sizeof():
        return 12

    def __bytes__(self):
        return struct.pack(">fff", self.x, self.y, self.z)
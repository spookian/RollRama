import bpy
import os
import struct

METERS_TO_CENTIMETERS = 100
FILE_PATH = "C:/C++ projects/RollRama/data/STAGE.roll"

#triangle flags
TRIANGLE_FLAG_ZHEAVY = 1
HEADER_SIZE = 12

triangle_file_data = bytes()
vertexes = 0
vertex_file_data = bytes()

#vertices and triangles will be separated because i am lazy
#verts will be 3 floats

#triangles will be three short indices, a short consisting of 16 flags, and one vector3 for the normal

def create_triangle_data(tri):
    return struct.pack(">HHHBfff", tri.vertices[0], tri.vertices[1], tri.vertices[2], False, tri.normal.x, tri.normal.z, tri.normal.y)

def create_vert_data(vert):
    c = vert.co * METERS_TO_CENTIMETERS
    return struct.pack(">fff", c.x, c.z, c.y) #z up to y up

def check_if_all_triangles(obj):
    for ngon in obj.data.polygons:
        if (len(ngon.vertices) != 3):
            return False
        
    return True

x = bpy.data.objects.get('Stage')
if x:
    if check_if_all_triangles(x):
        print("Triangle check finished...")
        for vert in x.data.vertices:
            #store all vertex data
            vertex_file_data = vertex_file_data + create_vert_data(vert)
        print("Vertices packed...")
        #for every face
        for tri in x.data.polygons:          
            triangle_file_data = triangle_file_data + create_triangle_data(tri)
        print("Triangles packed...")
        #write header
        header = "ROLL".encode(encoding="ascii") # create magic
        header += struct.pack(">LL", HEADER_SIZE, HEADER_SIZE + len(vertex_file_data)) # then add rest of header
        
        f = os.open(FILE_PATH, os.O_WRONLY | os.O_CREAT | os.O_TRUNC)
        os.write(f, vertex_file_data)
        os.close(f)
        print("File written!")
    else: #halt
        print("ERROR: Mesh is not fully triangulated! Apply a Triangulate modifier or select all faces in edit mesh and press CTRL+T.")
        
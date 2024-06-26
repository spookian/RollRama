import bpy
import mathutils
import os
import struct

METERS_TO_CENTIMETERS = 100
FILE_PATH = "C:/C++ projects/RollRama/datastuff/STAGE.roll"
HEADER_SIZE = 16 + 12 + 12

triangle_file_data = bytes()
vertexes = 0
vertex_file_data = bytes()

#vertices and triangles will be separated because i am lazy
#verts will be 3 floats

#triangles will be three short indices, a short consisting of 16 flags, and one vector3 for the normal

def create_triangle_data(tri):
    x = tri.normal.x
    if (x == -0): x = 0
    y = tri.normal.y
    if (y == -0): y = 0
    z = tri.normal.z
    if (z == -0): z = 0
    return struct.pack(">HHHHfff", tri.vertices[0], tri.vertices[1], tri.vertices[2], 0, x, z, y)

# 18 bytes a triangle?

def create_vert_data(vert):
    c = vert.co * METERS_TO_CENTIMETERS
    print(c)
    
    x = vert.co.x * METERS_TO_CENTIMETERS
    if (x == -0): x = 0
    y = vert.co.y * METERS_TO_CENTIMETERS
    if (y == -0): y = 0
    z = vert.co.z * METERS_TO_CENTIMETERS
    if (z == -0): z = 0
    return struct.pack(">fff", x, z, y) #z up to y up

def check_if_all_triangles(obj):
    for ngon in obj.data.polygons:
        if (len(ngon.vertices) != 3):
            return False
        
    return True

x = bpy.data.objects.get('Stage')
bound_center = mathutils.Vector()
bound_center.resize_3d()

for corner in x.bound_box:
    bound_center += mathutils.Vector(corner)
bound_center = bound_center * (1/8) * 100
dimensions = x.dimensions * 100
print(bound_center)

if x:
    if check_if_all_triangles(x):
        print("Triangle check finished...")
        for vert in x.data.vertices:
            #store all vertex data
            vertex_file_data = vertex_file_data + create_vert_data(vert)
        print("Vertices packed...\n")
        #for every face
        for tri in x.data.polygons:          
            triangle_file_data = triangle_file_data + create_triangle_data(tri)
        print("Triangles packed...\n")
        #write header
        header = "ROLL".encode(encoding="ascii") # create magic
        num_triangles = len(triangle_file_data) / 20
        print("num triangles: " + str(num_triangles) )
        header += struct.pack(">LLL", HEADER_SIZE, int(num_triangles), HEADER_SIZE + len(vertex_file_data)) # then add rest of header
        header += struct.pack(">ffffff", bound_center.x, bound_center.z, bound_center.y, dimensions.x, dimensions.z, dimensions.y)
        
        
        f = open(FILE_PATH, mode="wb")
        f.write(header + vertex_file_data + triangle_file_data)
        f.close()
        print("File written!\n\n")
    else: #halt
        print("ERROR: Mesh is not fully triangulated! Apply a Triangulate modifier or select all faces in edit mesh and press CTRL+T.")
        
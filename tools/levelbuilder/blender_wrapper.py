import bpy
import bmesh
from sys import path
path.append(r'C:\C++ projects\RollRama\tools\levelbuilder')

from levelbuilder import Vector3

def create_vec3_from_bmesh_vert(vert, unit_size  = 1): #
    return Vector3(vert.co.x * unit_size, vert.co.y * unit_size, vert.co.z * unit_size)

def get_bmesh_face_index(faceset, face):
    x = 0
    for f in faceset:
        if (f == face):
            return x
        x++
    return -1

def create_tri_from_bmesh_face(tri):
    t = Triangle()
    if (tri.verts)
    return t
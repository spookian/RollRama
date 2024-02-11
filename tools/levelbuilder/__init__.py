import bpy
import bmesh
from sys import path
path.append(r'C:\C++ projects\RollRama\tools\levelbuilder')

from levelbuilder import *

collcore = CollisionCore()

for obj in bpy.data.objects:
    if (obj.type == 'MESH'):
        bm = bmesh.new()
        bm.from_mesh(obj.data)
        
        bm.verts.ensure_lookup_table()
        for v in bm.verts:
            vert = create_vec3_from_bmesh_vert(v, 100)
            collcore.vector_list.append(vert)
            
        print(collcore.vector_list[0].x)
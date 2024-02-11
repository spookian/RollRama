import bpy
import bmesh
from . levelbuilder import CollisionCore
from . levelbuilder import Vector3

collcore = CollisionCore()

def create_vec3_from_bmesh_vert(vert, unit_size): #
    return Vector3(vert.co.x * unit_size, vert.co.y * unit_size, vert.co.z * unit_size)

for obj in bpy.data.objects:
    if (obj.type == 'MESH'):
        bm = bmesh.new()
        bm.from_mesh(obj.data)
        
        bm.verts.ensure_lookup_table()
        for v in bm.verts:
            vert = create_vec3_from_bmesh_vert(v, 100)
            collcore.vector_list.append(vert)
            
        print(collcore.vector_list[0].x)
import bpy
import mathutils
import struct

pstar_data = bytes()

def convertVector(vector):
    v = vector.xzy
    v.z = -v.z
    return v

def packVector(vector):
    return struct.pack(">fff", vector.x, vector.y, vector.z)

for obj in bpy.data.collections['PointStars'].all_objects:
    print(obj.location)
    pstar_data = pstar_data + packVector( convertVector(obj.location) )

f = open("C:/C++ projects/RollRama/data/stars.bin", mode="wb")
f.write(pstar_data)
f.close()
import bpy
import enum
import struct

entityCounter = 0

class RollEntities:
	POINTSTAR = 0
	DEE = 1
	GORDO = 2
	JUMPHOLE = 3

def create_entity_list():
	return

def create_entity_header():
	# header contains number of entities and a whole list
	# s

	#also later on for octree baking include all blocks in file and generate a pointer array runtime to store all of them, loop through using pointer shenanigans
	return	
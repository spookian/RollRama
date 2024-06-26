#pragma once 
#include "math/Vector3.h"
#include "common/List.h"

const GlobalObject<const hel::math::Vector3, float> aabbMultipliers[8] = {
	{{-0.5, 0.5, -0.5}},
	{{0.5, 0.5, -0.5}},
	{{-0.5, 0.5, 0.5}},
	{{0.5, 0.5, 0.5}},
	
	{{-0.5, -0.5, -0.5}},
	{{0.5, -0.5, -0.5}},
	{{-0.5, -0.5, 0.5}},
	{{0.5, -0.5, 0.5}}
};

enum OctreeType
{
	OCTREE_BRANCH,
	OCTREE_LEAF,
	OCTREE_NODE // this should not exist
};

namespace scn
{
	
	namespace roll
	{
		
		struct AABB
		{
			hel::math::Vector3 position;
			hel::math::Vector3 bounds; // should be used for cubes only in this case;
			
			static AABB CreateCube(float width, hel::math::Vector3& position)
			{
				AABB result;
				result.bounds.x = width;
				result.bounds.y = width;
				result.bounds.z = width;
				result.position = position;
				
				return result;
			}
			
			bool Contains(hel::math::Vector3& otherPos)
			{
				float halfx = bounds.x / 2.0f;
				float halfy = bounds.y / 2.0f;
				float halfz = bounds.z / 2.0f;
				
				float lx = position.x - halfx;
				float hx = position.x + halfx;
				float ly = position.y - halfy;
				float hy = position.y + halfy;
				float lz = position.z - halfz;
				float hz = position.z + halfz;
				
				if (otherPos.x >= lx && otherPos.x <= hx)
				{
					if (otherPos.y >= ly && otherPos.y <= hy)
					{
						if (otherPos.z >= lz && otherPos.z <= hz) return true;
					}
				}
				return false;
			}
			
			void getVertices(hel::math::Vector3 arr[8]) // requires an array of 8
			{
				for (int i = 0; i < 8; i++)
				{
					hel::math::Vector3 curMultiplier = aabbMultipliers[i];
					hel::math::Vector3 add( curMultiplier.x * bounds.x, curMultiplier.y * bounds.y, curMultiplier.z * bounds.z );
					arr[i] = position + add;
				}
			}
		};
		
		template <typename T>
		struct Octree
		{
			struct OctreeNode 
			{
				int type;
				OctreeNode *parent;
				AABB box;
			};
			
			struct OctreeBranch : public OctreeNode
			{
				OctreeNode *branches[8];
				
				OctreeBranch()
				{
					type = OCTREE_BRANCH;
					for (int i = 0; i < 8; i++)
					{
						branches[i] = (OctreeNode*)0;
					}
				}
				
				OctreeNode* GetSector(hel::math::Vector3& position)
				{
					// lol im gonna assume that position is in octree to save on speed
					unsigned char idx = 0;
					if (position.x >= this->box.position.x) idx |= 1;
					if (position.z >= this->box.position.z) idx |= 2;
					if (position.y >= this->box.position.y) idx |= 4;
					
					return branches[idx];
				}
			};
			
			struct OctreeLeaf : public OctreeNode
			{
				T obj;
				
				OctreeLeaf()
				{
					type = OCTREE_LEAF;
				}
			};
			
			OctreeNode *startBranch;
			
			// idk if this function is even needed
			OctreeNode* TraverseOctree(hel::math::Vector3& position)
			{
				OctreeNode* currentNode = &startBranch;
				
				while (currentNode != 0 && currentNode->type != OCTREE_LEAF)
				{
					OctreeBranch *curBranch = currentNode;
					currentNode = curBranch->GetSector(position);
				}
				return currentNode;
			}
		};
	}
}
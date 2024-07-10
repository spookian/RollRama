#pragma once 
#include "math/Vector3.h"
#include "common/List.h"
#include "scn/game/BoxCollider.h"

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
		template <typename T>
		struct Octree
		{
			struct OctreeNode 
			{
				int type;
				OctreeNode *parent;
				AABB box;
				
				virtual ~OctreeNode()
				{
					
				}
			};
			
			struct OctreeBranch : public OctreeNode
			{
				OctreeNode *branches[8];
				
				OctreeBranch()
				{
					type = OCTREE_BRANCH;
					for (int i = 0; i < 8; i++)
					{
						branches[i] = 0;
					}
				}
				
				~OctreeBranch()
				{
					for (int i = 0; i < 8; i++)
					{
						if (branches[i]) delete branches[i];
					}
				}
				
				OctreeNode* GetSector(hel::math::Vector3& position)
				{
					// lol im gonna assume that position is in octree to save on speed
					unsigned char idx = 0;
					if (position.x > this->box.position.x) idx |= 1;
					if (position.z > this->box.position.z) idx |= 2;
					if (position.y < this->box.position.y) idx |= 4;
					
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
			
			Octree()
			{
				startBranch = 0;
			}
			
			~Octree()
			{
				if (startBranch)
				{
					delete startBranch;
				}
			}
			
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
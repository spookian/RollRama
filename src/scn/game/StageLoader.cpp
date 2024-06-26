#include "scn/game/rollgame.h"
#include "file/FileAccessor.h"

#include "common/List.h"
#include "scn/game/Octree.h"

#define ROLL_SIGNATURE 0x524F4C4C
#define MAX_CUBE_VERTICES 8
#define MAX_TRIANGLE_VERTICES 3
#define MAX_TRIANGLES_OCTREE 32
//duh.

const GlobalObject<const hel::math::Vector3, float> cubeAxes[3] = {
	{{1.0f, 0.0f, 0.0f}},
	{{0.0f, 1.0f, 0.0f}},
	{{0.0f, 0.0f, 1.0f}}
};

using namespace hel::math;
typedef scn::roll::Octree< hel::common::List<scn::roll::TriangleWrapper> > TriOctree;

struct RollHeader
{
	unsigned long MAGIC;

	unsigned long vertices_offset;
	unsigned long num_triangles;
	unsigned long triangles_offset;
	scn::roll::AABB bounding_box;
	
	inline Vector3* getVertices()
	{
		return (Vector3*)(reinterpret_cast<unsigned long>(this) + vertices_offset);
	}
	
	inline scn::roll::TriangleData* getTriangles()
	{
		return (scn::roll::TriangleData*)(reinterpret_cast<unsigned long>(this) + triangles_offset);
	}
};

namespace scn
{
	namespace roll
	{
		// UNTESTED!!!! test all of these at a later date
		bool intersects(float aa, float ab, float ba, float bb)
		{
			if (ba > ab || aa > bb) return false;
			return true;
		}
		
		bool testSeparatingAxis(const hel::math::Vector3& axis, hel::math::Vector3 *aVerts, hel::math::Vector3 **bVerts)
		{
			float maxA = -9999999.0, minA = 9999999.0;
			float maxB = -9999999.0, minB = 9999999.0;
			
			for (int i = 0; i < MAX_CUBE_VERTICES; i++)
			{
				float projection = aVerts[i].dot(axis);
				if (projection > maxA) maxA = projection;
				if (projection < minA) minA = projection;
			}
			
			for (int i = 0; i < MAX_TRIANGLE_VERTICES; i++)
			{
				float projection = (bVerts[i])->dot(axis);
				if (projection > maxB) maxB = projection;
				if (projection < minB) minB = projection;
			}
			
			return intersects(minA, maxA, minB, maxB);
		}
		
		bool checkTriangleinOctreeBounds(AABB& bounds, const TriangleData* triangle, hel::math::Vector3* triangleVertices)
		{
			// setup
			hel::math::Vector3 boxVerts[8];
			bounds.getVertices(boxVerts);
			hel::math::Vector3 *triVerts[3] = {
				&triangleVertices[triangle->v0],
				&triangleVertices[triangle->v1],
				&triangleVertices[triangle->v2]
			};
			
			// three box axes
			for (int i = 0; i < 3; i++)
			{
				if (!testSeparatingAxis( cubeAxes[i], (Vector3*)boxVerts, triVerts)) return false;
			}
			// one triangle axis
			if (!testSeparatingAxis( triangle->normal, boxVerts, triVerts )) return false;
			
			// box axes crossed with triangle axis
			for (int i = 0; i < 3; i++)
			{
				hel::math::Vector3 crossed_axis = ((hel::math::Vector3)cubeAxes[i]).cross(triangle->normal);
				if (!testSeparatingAxis(crossed_axis, boxVerts, triVerts)) return false;
				
				/* since the cross product is non commutative technically i should cross the triangle normal with each cube normal as well,
				but as you can see with both this and the box axis tests earlier, you don't have to repeat the test for vectors with the same 
				magnitude and direction but different signs (technically they'd be different directions but you know)
				
				the cross product is ANTI commutative, so A x B would equal -(B x A), meaning the rule above still applies for this use case
				*/
			}
			
			return true;
		}
		
		Vector3 multiplyVectors(const Vector3& v0, const Vector3& v1)
		{
			Vector3 result(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
			return result;
		}
		
		void buildOctreeBranch(TriOctree::OctreeNode** node, TriOctree::OctreeNode* parent, AABB& box, TriangleData* triangles, hel::math::Vector3* vertices, int numTriangles)
		{
			int triCount = 0;
			
			for (int i = 0; i < numTriangles; i++)
			{
				if (checkTriangleinOctreeBounds(box, &triangles[i], vertices)) triCount++;
				if (triCount > MAX_TRIANGLES_OCTREE)
				{
					*node = new TriOctree::OctreeBranch();
					(*node)->box = box;
					(*node)->parent = parent;
					
					for (int i = 0; i < 8; i++)
					{
						// split bounds code works, but the octree seems to be multiplying without cause
						AABB new_box;
						hel::math::Vector3 dimensions = box.bounds / 2.0f;
						new_box.bounds = dimensions;
						Vector3 multiplier = aabbMultipliers[i];

						Vector3 oldCorner = multiplyVectors(box.bounds, multiplier) + box.position;
						Vector3 newCorner = multiplyVectors(dimensions, multiplier) + box.position;
						
						Vector3 difference = oldCorner - newCorner;
						new_box.position = box.position + difference;
						buildOctreeBranch(&(((TriOctree::OctreeBranch*)*node)->branches[i]), *node, new_box, triangles, vertices, numTriangles);
					}
					return;
				}
			}
			
			if (triCount == 0) return;
			*node = new TriOctree::OctreeLeaf();
			(*node)->box = box;
			(*node)->parent = parent;
			
			for (int i = 0; i < numTriangles; i++)
			{
				// this is shit. HOWEVER, my other idea involved using a list, and allocating heap with stack recursion sounds like a recipe for failure
				// i'd happily trade speed (IN A LOADING SCREEN MIND YOU NOT GAME LOOP) over the possibility of shitting my wii's memory
				if (checkTriangleinOctreeBounds(box, &triangles[i], vertices))
				{
					TriangleWrapper tri(vertices, &triangles[i]);
					((TriOctree::OctreeLeaf*)*node)->obj.append(tri);
				}
			}
			
			return;
		}
		
		bool StageController::CreateStage(file::FileData& stageFile)
		{
			RollHeader *header = reinterpret_cast<RollHeader*>(stageFile.file_data);
			if (header->MAGIC != ROLL_SIGNATURE)
			{
				return false;
			}
			
			Vector3 *vertexList = header->getVertices();
			TriangleData *triangleDataList = header->getTriangles();
			
			float maxDimension = header->bounding_box.bounds.x;
			if (header->bounding_box.bounds.y > maxDimension) maxDimension = header->bounding_box.bounds.y;
			if (header->bounding_box.bounds.z > maxDimension) maxDimension = header->bounding_box.bounds.z;
			Vector3 one(1,1,1);
			
			AABB beginningBox;
			beginningBox.position = header->bounding_box.position;
			beginningBox.bounds = one * maxDimension;
			
			buildOctreeBranch(&collisionData.startBranch, (TriOctree::OctreeNode*)0, beginningBox, triangleDataList, vertexList, header->num_triangles);
			
			for (int i = 0; i < header->num_triangles; i++)
			{
				TriangleWrapper triangle(vertexList, &triangleDataList[i]);
				triangleList.append(triangle);
			}
			return true;
		}
	}
}
#include "scn/game/rollgame.h"
#include "file/FileAccessor.h"

#include "common/List.h"

#define ROLL_SIGNATURE 0x524F4C4C
#define MAX_CUBE_VERTICES 8
#define MAX_TRIANGLE_VERTICES 3
#define MAX_TRIANGLES_OCTREE 128
//duh.

const GlobalObject<const hel::math::Vector3, float> cubeAxes[3] = {
	{{1.0f, 0.0f, 0.0f}},
	{{0.0f, 1.0f, 0.0f}},
	{{0.0f, 0.0f, 1.0f}}
};

using namespace hel::math;

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
			
			for (int i = 0; i < header->num_triangles; i++)
			{
				TriangleWrapper triangle(vertexList, &triangleDataList[i]);
				triangleList.append(triangle);
			}
			return true;
		}
	}
}
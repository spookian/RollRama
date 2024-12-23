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
			collisionData = header;
			
			for (int i = 0; i < header->num_triangles; i++)
			{
				TriangleWrapper triangle(vertexList, &triangleDataList[i]);
				triangleList.append(triangle);
			}
			safe = true;
			return true;
		}
	}
}
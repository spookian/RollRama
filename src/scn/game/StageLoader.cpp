#include "scn/game/rollgame.h"
#include "file/FileAccessor.h"

#define ROLL_SIGNATURE 0x524F4C4C

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		struct RollHeader
		{
			unsigned long MAGIC;
		
			unsigned long vertices_offset;
			unsigned long num_triangles;
			unsigned long triangles_offset;
			
			inline Vector3* getVertices()
			{
				return (Vector3*)(reinterpret_cast<unsigned long>(this) + vertices_offset);
			}
			
			inline TriangleData* getTriangles()
			{
				return (TriangleData*)(reinterpret_cast<unsigned long>(this) + triangles_offset);
			}
		};
		
		bool StageController::CreateStage(file::FileData& stageFile)
		{
			RollHeader *header = reinterpret_cast<RollHeader*>(stageFile.file_data);
			if (header->MAGIC != ROLL_SIGNATURE)
			{
				return false;
			}
			
			Vector3 *vertexList = header->getVertices();
			TriangleData *triangleDataList = header->getTriangles();
			
			for (int i = 0; i < header->num_triangles; i++)
			{
				TriangleWrapper triangle(vertexList, &triangleDataList[i]);
				triangleList.append(triangle);
			}
			return true;
		}
	}
}
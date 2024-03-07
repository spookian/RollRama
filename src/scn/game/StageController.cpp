#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/Math.h"

#define nullptr (Vector3*)0
using namespace hel::math;
namespace scn
{
	namespace roll
	{
		TriangleWrapper::TriangleWrapper(Vector3* vertexList, TriangleData* data)
		{
			v0 = &vertexList[data->v0];
			v1 = &vertexList[data->v1];
			v2 = &vertexList[data->v2];
			
			normal = &data->normal;
			d = -(v0->x * normal->x + v0->y * normal->y + v0->z * normal->z);
		}
		
		TriangleWrapper::TriangleWrapper()
		{
			v0 = nullptr;
			v1 = nullptr;
			v2 = nullptr;
			
			normal = nullptr;
			d = 0.0f;
			
		}
		
		void TriangleWrapper::RecalculateD()
		{
			if (v0 && normal)
			{
				d = -(v0->x * normal->x + v0->y * normal->y + v0->z * normal->z);
			}
		};
		
		Vector3 TriangleWrapper::ClosestPointOnPlane(const hel::math::Vector3& point)
		{
			// function stolen from the RTCD book
			float unsignedDistance = normal->dot(point) - d;
			return point - ((*normal) * unsignedDistance);
		}
		
		//
		inline float getTriangleArea2D(float x0, float y0, float x1, float y1, float x2, float y2) // jus checking to make sure i dont fit in.... even though you know where i got this from
		{
			return (x0 - x1) * (y1 - y2) - (x1 - x2) * (y0 - y1);
		} // isn't this like a 2d cross product
		
		inline unsigned long checkProjectionTriangle(TriangleWrapper& triangle)
		{
			unsigned long result = PROJECTION_X;
			float x = Math::AbsF32(triangle.normal->x);
			float y = Math::AbsF32(triangle.normal->y);
			float z = Math::AbsF32(triangle.normal->z);
			
			if ((y > x) && (y > z))
			{
				result = PROJECTION_Y;
			}
			else if ((z > x) && (z > y))
			{
				result = PROJECTION_Z;
			}
			return result;
		}
		
		bool TriangleWrapper::CheckPointInTriangle(const Vector3& point)
		{
			unsigned long largestProj = checkProjectionTriangle(*this);
			Vector3& A = *v0;
			Vector3& B = *v1;
			Vector3& C = *v2;
			
			float regionU, regionV, regionW;
			
			switch (largestProj)
			{
				default:
				case PROJECTION_X: // x heavy, so yz plane
				regionU = getTriangleArea2D(point.y, point.z, B.y, B.z, C.y, C.z); // PBC
				regionV = getTriangleArea2D(point.y, point.z, C.y, C.z, A.y, A.z); // PCA
				regionW = getTriangleArea2D(point.y, point.z, A.y, A.z, B.y, B.z); // PAB
				break;
				
				case PROJECTION_Y: // y heavy, so xz plane
				regionU = getTriangleArea2D(point.x, point.z, B.x, B.z, C.x, C.z); // PBC
				regionV = getTriangleArea2D(point.x, point.z, C.x, C.z, A.x, A.z); // PCA
				regionW = getTriangleArea2D(point.x, point.z, A.x, A.z, B.x, B.z); // PAB
				break;
				
				case PROJECTION_Z: // z heavy, so xy plane
				regionU = getTriangleArea2D(point.x, point.y, B.x, B.y, C.x, C.y); // PBC
				regionV = getTriangleArea2D(point.x, point.y, C.x, C.y, A.x, A.y); // PCA
				regionW = getTriangleArea2D(point.x, point.y, A.x, A.y, B.x, B.y); // PAB
				break;
			}
			
			return (regionU >= 0) && (regionV >= 0) && (regionW >= 0);
			
		} // fucked up barycentric coords
	}
}
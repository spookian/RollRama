#pragma once
#define POINTSTAR_RADIUS 20.0f

using hel::math;
namespace scn
{
	namespace roll
	{
		class PointStar
		{
			Vector3 position;
			Matrix34 rotation;
			unsigned long score;
			
			g3d::CharaModel *model;
		public:
			PointStar();
			~PointStar();
			
			void UpdateModel();
			Vector3 GetPosition();
		};
	}
}
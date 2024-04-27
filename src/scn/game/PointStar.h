#pragma once
#define POINTSTAR_RADIUS 15.0f

#include "scn/game/Collision.h"
#include "math/math.h"
#include "g3d/Model.h"

class Chowder;

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		class PointStar : public SphereCollider
		{
			Matrix34 rotation;
			unsigned long score;
			
			g3d::CharaModel *model;
		public:
			PointStar(Chowder& parent, Vector3 position);
			~PointStar();
			
			void UpdateModel(g3d::Root& root, Matrix34& worldRotation);
		};
	}
}
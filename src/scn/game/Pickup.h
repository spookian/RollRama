#pragma once
#define POINTSTAR_RADIUS 10.0f

#include "scn/game/Collision.h"
#include "math/math.h"
#include "g3d/Model.h"

class Chowder;

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		class Pickup : public SphereCollider
		{
		protected:
			g3d::CharaModel *model;
		public:
			Pickup(float c) : SphereCollider(c)
			{
			}
			
			virtual void Update()
			{
				return;
			}
			
			virtual void UpdateModel(g3d::Root& root, Matrix34& worldRotation)
			{
				return;
			}
		};
		
		class Balloon : public Pickup
		{
			int time;
		public:
			void Update();
		};
		
		class PointStar : public Pickup
		{
			Vector3 rotation;
			
		public:
			PointStar(Vector3 position);
			~PointStar();
			
			void UpdateModel(g3d::Root& root, Matrix34& worldRotation);
		};
	}
}
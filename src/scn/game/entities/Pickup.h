#pragma once

#include "scn/game/collision/Collision.h"
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
			bool active;
			
			Pickup(float c) : SphereCollider(c)
			{
				active = true;
			}
			
			virtual void Update() {}
			virtual void UpdateModel(g3d::Root& root, Matrix34& worldRotation) {}
		};
		
		class Balloon : public Pickup
		{
			bool bossFight;
			int state;
			int time;
		public:
			Balloon(const Vector3& position, bool __bossFight);
			~Balloon();
			
			void Update(); // only updates itself
			void UpdateModel(g3d::Root& root, Matrix34& worldRotation);
		};
		
		class PointStar : public Pickup
		{
			Vector3 rotation;
			
		public:
			PointStar(const Vector3& position); // kills itself once it detects the player
			~PointStar();
			
			void Update();
			void UpdateModel(g3d::Root& root, Matrix34& worldRotation);
		};
		
		class Clock : public Pickup
		{
		public:
		};
	}
}
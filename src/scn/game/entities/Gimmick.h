#pragma once
#include "math/math.h"
#include "g3d/Model.h"
#include "common/List.h"
#include "scn/game/Path.h"

//cpp
#include "scn/Chowder.h"
#include "g3d/ResFileHelper.h"

namespace scn
{
	namespace roll
	{
		class Gimmick
		{
		protected:
			g3d::CharaModel *model;
			
		public:
			virtual void updateModel(g3d::Root& root)
			{
				model->updateWorldMtx();
				model->registerToRoot(root);
			}
		};
		
		class Capturable : Gimmick
		{
		protected:
			float verticalLaunchSpeed;
			float horizontalLaunchSpeed;
		public:
			virtual void update();
		};
		
		class JumpHole : public Capturable
		{ /* let a be the gravity constant, and b be the launch speed of kirby.
			if the formula for gravity distance is -0.5at^2 + bt assuming you start at ground level, then
			t(-0.5at + b) = 0
			-0.5at = -b
			t = b/0.5a
			or t = 2b/a, being the formula for air time
			
			next, we can get horizontal speed by getting our wanted distance and simply dividing it by air time.
			launch speed and horizontal distance are independent variables, but horizontal speed is dependent
		*/
		protected:
			float verticalLaunchSpeed;
			float horizontalLaunchSpeed;
			
		public:
			JumpHole(const hel::math::Vector3& position, float horizontalDistance, float startingVerticalSpeed);
			void update();
		};
		
		class 
		
		class Cloud : public Capturable
		{
			hel::math::Vector3 initialPosition;
		public:
			Path pathSystem;
			
			Cloud(const hel::math::Vector3& position);
			void update();
		};
	}
}
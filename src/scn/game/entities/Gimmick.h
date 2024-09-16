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
		{
		protected:
			float verticalLaunchSpeed;
			float horizontalLaunchSpeed;
			
		public:
			JumpHole(const hel::math::Vector3& position);
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
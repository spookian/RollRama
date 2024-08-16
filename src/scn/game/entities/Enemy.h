#pragma once
#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/Path.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		class Enemy : public SphereCollider
		{	
		public:
			g3d::CharaModel *model;
			Path pathSystem;
			
			virtual void Update()
			{
				return;
			}
			
			virtual void UpdateModel(g3d::Root& root)
			{
				model->registerToRoot(root);
				return;
			}
		};
		
		class Gordo : public Enemy
		{
		
		};
		
		class Dee : public Enemy
		{
			
		};
	}
}
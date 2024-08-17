#pragma once
#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/collision/Collision.h"
#include "scn/game/collision/Path.h"

namespace scn
{
	namespace roll
	{
		class Enemy : public SphereCollider
		{	
		protected:
			g3d::CharaModel *model;
			bool playerOverlap;
		public:
			Path pathSystem;
			
			Enemy();
			virtual ~Enemy();
			virtual void Update();
			virtual void UpdateModel(g3d::Root& root, hel::math::Matrix34 worldRotation);
			void SearchAndHurtPlayer();
		};
		
		class Gordo : public Enemy
		{
		
		};
		
		class Dee : public Enemy
		{
			
		public:
			Dee(hel::math::Vector3 pos);
			virtual ~Dee();
			void Update();
			void UpdateModel(g3d::Root& root, hel::math::Matrix34 worldRotation);
		};
	}
}
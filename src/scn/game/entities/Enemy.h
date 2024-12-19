#pragma once
#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/collision/Collision.h"
#include "scn/game/collision/Path.h"
#include "scn/game/collision/BoxCollider.h"

namespace scn
{
	namespace roll
	{
		class Enemy : public SphereCollider
		{	
		protected:
			g3d::CharaModel *model;
			bool playerOverlap;
			unsigned long state;
			
		public:
			bool active;
			Path pathSystem;
			
			Enemy();
			virtual ~Enemy();
			virtual void update();
			virtual void updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation);
			
			bool searchAndHurtPlayer(bool);
			bool checkFlickRadius(); // checks if the player flicked the wiimote and if the enemy is close enough to the player
			void moveAlongPath(); // moves along path
			bool searchAndCapturePlayer(); // for capturable enemies
		};
		
		class Gordo : public Enemy
		{
		
		};
		
		class Dee : public Enemy
		{
			unsigned long timer;
			float oldHeight;
			
		public:
			Dee();
			virtual ~Dee();
			void update();
			void updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation);
		};
		
		class CircleBumper : public Enemy
		{
			bool animationPlaying;
			int timer;
			
		public:
			CircleBumper();
			void update();
			void updateModel(g3d::Root& root);
		};
		
		class EndZone : public Enemy
		{
			/*
				quick collision with cylinder and aabb cube
				aabb cube:
					get xyz depth penetration by comparing kirby position with cube center
					select the dimension that has the lowest penetration and push kirby out that way
					
				cylinder:
					
			*/
		public:
			void updateUpper();
			void updateLower();
			
			void update();
		};
		
		class JumpHole : public Enemy
		{
			float direction;
			hel::math::Vector3 arrowPos;
			
			float verticalLaunchSpeed;
			float horizontalDistance;
			
			g3d::CharaModel *arrowModel;
			
		public:
			static const float arrowDistance;
		
			JumpHole(float, float);
			void update();
			void updateModel(g3d::Root&, hel::math::Matrix34);
		};
		
		class Cloud : public Enemy
		{
			
		};
	}
}
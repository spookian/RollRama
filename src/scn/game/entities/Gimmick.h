#pragma once
#include "math/math.h"
#include "g3d/Model.h"
#include "common/List.h"
#include "scn/game/Path.h"

//cpp
#include "scn/Chowder.h"
#include "g3d/ResFileHelper.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		class Gimmick
		{
		protected:
			Vector3 position;
			g3d::CharaModel *model;
			
		public:
			virtual void update()
			{
				
			}
			
			virtual void updateModel(g3d::Root& root)
			{
				Matrix34 translate = Matrix34::CreateTrans(position);
				model->setModelRTMtx( translate );
				model->updateWorldMtx();
				model->registerToRoot(root);
			}
		};
		
		class Bumper : Gimmick
		{
			SphereCollider hitbox;
			bool check; // used to make sure Update() doesn't update player more than once
			
			bool animationPlaying;
			int timer;
			
			const float bumperStrength = 4.0;
			const float bumperRadius = 25.0f;
			const int animationLength = 60; // in frames
			
		public:
			Bumper(const Vector3& position) : hitbox(bumperRadius)
			{
				model = InitResModel(parent.FileRepository, "step/AmigaSphere");
			}
			
			void update()
			{
				PlayerController* player = engineSingleton->stage->player;
				
				if (hitbox.isCollide(*player))
				{
					if (!check)
					{
						Vector3 newDir = (player.GetPosition() - this->position);
						newDir.y = 0.0f;
						newDir.normalize();
						newDir.y = 0.25f;
						
						player.ZeroVelocity();
						player.AddImpulse(newDir * bumperStrength);
						animationPlaying = true;
						timer = -1;
					}
					check = true;
				}
				else
				{
					check = false;
				}
				
				if (animationPlaying)
				{
					timer++;
					if (timer > animationLength)
					{
						animationPlaying = false;
					}
				}
			}
			
			void updateModel(g3d::Root& root)
			{
				// set scale;
				if (!animationPlaying)
				{
				}
				else
				{
					// cosine scale
				}
				
				model->setModelScale(Vector3::ALL_ONE * 50);
				Gimmick::updateModel(root);
			}
		};
		
		class Capturable : Gimmick
		{
		protected:
			float verticalLaunchSpeed;
			float horizontalLaunchSpeed;
		public:
			virtual Vector3 getPosition();
		};
		
		class JumpHole : public Capturable
		{
		protected:
			float verticalLaunchSpeed;
			float horizontalLaunchSpeed;
			
		public:
			JumpHole(const Vector3& position);
			void update();
		};
		
		class 
		
		class Cloud : public Capturable
		{
		public:
			Path pathSystem;
			
			Cloud();
			void update();
		};
	}
}
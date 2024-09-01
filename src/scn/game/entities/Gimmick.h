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
			g3d::CharaModel *model;
			
		public:
			virtual void updateModel(g3d::Root& root)
			{
				model->updateWorldMtx();
				model->registerToRoot(root);
			}
		};
		
		class SphereBumper : Gimmick
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
			virtual void update();
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
			Vector3 initialPosition;
		public:
			Path pathSystem;
			
			Cloud(Vector3 position);
			void update();
		};
	}
}
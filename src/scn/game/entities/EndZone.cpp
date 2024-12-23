#include "scn/game/entities/Enemy.h"
#include "scn/Chowder.h"
#include "g3d/ResFileHelper.h"
#include "scn/game/PlayerController.h"
#include "scn/game/PhysicsConstants.h"

namespace
{
	const float endRadius = 134.313f;
	const GlobalObject<const hel::math::Vector3, float> pos = {{ 498.572f, -958.03f, -10940.0f }};
}

using namespace hel::math;
namespace scn
{
	namespace roll
	{	
		EndZone::EndZone()
		{
			model = InitResModel( engineSingleton->FileRepository, "step/EndPlat" );
			position = pos;
			enable = true;
		}
		
		void EndZone::update()
		{
			PlayerController *player = engineSingleton->stage->player;
			if (enable)
			{
				// get player
				
				Vector3 flatPlayerPos = player->position;
				flatPlayerPos.y = 0.0f;
				
				Vector3 flatPos = position;
				flatPos.y = 0.0f;
				
				if ((flatPlayerPos - flatPos).length() <= endRadius)
				{
					// check if player at y
					if (player->position.y < (position.y + PLAYER_RADIUS))
					{
						engineSingleton->state = 6;
						player->linear_velocity = Vector3::ZERO;
						player->position.y = position.y + PLAYER_RADIUS;
						engineSingleton->fStar.activate(6.0f, 0.0f, 300);
						enable = false;
					}
				}
			}
			else
			{
				player->position.y = position.y + PLAYER_RADIUS;
			}
			
			return;
		}
		
		void EndZone::updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			Matrix34 translation = Matrix34::CreateTrans(position);
			model->setModelRTMtx(worldRotation * translation);
			model->updateWorldMtx();
			model->registerToRoot(root);
		}
	}
}
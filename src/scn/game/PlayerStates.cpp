#include "scn/game/PlayerStates.h"
#include "scn/game/PlayerController.h"
#include "scn/game/rollgame.h"
#include "scn/Chowder.h"
#include "hid/hid.h"

#define FLOAT_MOVEMENT_MULTIPLIER 3.0f

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		StateNormal::StateNormal(PlayerController& player)
		{
			// idk setup nodes n gears n shizz
			this->player = &player;
			g3d::ModelAccessor playerModel = player.model->model();
			playerModel.nodeByName("KirbyBodyBig3M").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBigM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBlowM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyDrawM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyFlightM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyM").setVisibility(true);
			
			g3d::ResFileAccessor animFile(engineSingleton->FileRepository.get("step/chara/hero/kirby/normal/Motion", false));
			player.model->setAnim( 0, animFile, "Copy" );
			g3d::ModelAnimAccessor animation = player.model->anim(0);
			animation.start(false);
		}
		
		void StateNormal::Update()
		{
			unsigned short checkFlick = engineSingleton->input.flick;
			if (checkFlick && player->isOnGround())
			{
				player->linear_velocity = PlayerController::jumpLinearImpulses[checkFlick - 1];
				player->angular_velocity = PlayerController::jumpAngularImpulses[checkFlick - 1];
			}
			player->PhysicsUpdate(engineSingleton->stage, player->currentOctreeNode);
		}
		
		StateFloat::StateFloat(PlayerController& player)
		{
			Matrix34 identity;
			this->player = &player;
			player.rotation = identity;
			
			player.linear_velocity = Vector3::ZERO;
			player.angular_velocity = Vector3::ZERO;
		}
		
		void StateFloat::Update()
		{
			Vector3 displacement(-engineSingleton->input.tilt.z, 0, engineSingleton->input.tilt.x);
			displacement = displacement * FLOAT_MOVEMENT_MULTIPLIER;
			player->position += displacement;
		}
	}
}
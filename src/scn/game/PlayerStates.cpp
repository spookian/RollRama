#include "scn/game/PlayerStates.h"
#include "scn/game/PlayerController.h"
#include "scn/game/PhysicsConstants.h"
#include "scn/game/misc/CameraController.h"
#include "scn/game/rollgame.h"
#include "scn/Chowder.h"
#include "hid/hid.h"

#define FLOAT_MOVEMENT_MULTIPLIER 3.0f

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		PlayerState::PlayerState(PlayerController *player)
		{
			this->player = player;
		}
		
		void PlayerState::update()
		{
			return;
		}
		void PlayerState::updateModel()
		{
			return;
		}
		
		StateNormal::StateNormal(PlayerController *player) : PlayerState(player)
		{

		}
		
		StateNormal::~StateNormal()
		{
			return;
		}
		
		void StateNormal::update() 
		{
			unsigned short checkFlick = engineSingleton->input.flick;
			if (checkFlick && player->isOnGround())
			{
				player->linear_velocity = PlayerController::jumpLinearImpulses[checkFlick - 1];
				player->angular_velocity = PlayerController::jumpAngularImpulses[checkFlick - 1];
			}
			
			Vector2 horizontalVelo;
			horizontalVelo.x = player->linear_velocity.x;
			horizontalVelo.y = player->linear_velocity.z;
			
			if (horizontalVelo.length() > 25.0f)
			{
				horizontalVelo.normalize();
				horizontalVelo = horizontalVelo * 25.0f;
			}
			player->linear_velocity.x = horizontalVelo.x;
			player->linear_velocity.z = horizontalVelo.y;
			
			player->physicsUpdate();
			
			if (!player->isOnGround())
			{
				// create air input handling and restrict air movement
				RotationResult result = obtainWiimoteRotation(0.0f);
				Vector3 accelVector(-result.vector.z, 0.0f, result.vector.x);
				
				player->linear_velocity += accelVector * 10.0f * DELTATIME;
			}
			player->model->updateFrame();
		}
		
		StateFloat::StateFloat(PlayerController *player) : PlayerState(player)
		{
			Matrix34 identity;
			player->rotation = identity;
			
			player->linear_velocity = Vector3::ZERO;
			player->angular_velocity = Vector3::ZERO;
		}
		
		void StateFloat::update()
		{
			Vector3 displacement(-engineSingleton->input.tilt.z, 0, engineSingleton->input.tilt.x);
			displacement = displacement * FLOAT_MOVEMENT_MULTIPLIER;
			player->position += displacement;
		}
		
		StateCapture::StateCapture(PlayerController *player) : PlayerState(player)
		{
			player->linear_velocity = Vector3::ZERO;
			player->angular_velocity = Vector3::ZERO;
		}
		
		StateDeath::StateDeath(PlayerController *player) : PlayerState(player)
		{
			timer = 0;
			
			Matrix34 id;
			Vector3 newPos(0.0f, 0.0f, -336.3406f); // calculated average distance from camera
			player->rotation = id;
			deathPosition = newPos;
			player->hideModel = true;
			
			engineSingleton->state = 5;
			engineSingleton->cam.state = CAMERA_LOCK;
			
			g3d::ModelAccessor playerModel = player->model->model();
			playerModel.nodeByName("KirbyBodyBig3M").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBigM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBlowM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyDrawM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyFlightM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyM").setVisibility(true);
			
			player->model->interpolationReset();
			g3d::ResFileAccessor animFile( player->normalAnim );
			player->model->setAnim( 0, animFile, "DeadFall" );
			g3d::ModelAnimAccessor animation = player->model->anim(0);
			animation.start(true);
			animation.setFrameRate(1.0);
			
			return;
		}
		
		void StateDeath::update()
		{
			deathPosition.y = -5 * (timer * timer * 0.0166f) + 300 * (timer * 0.0166f);
			player->model->updateFrame();
			timer++;
			return;
		}
		
		void StateDeath::updateModel()
		{
			Matrix34 translation = Matrix34::CreateTrans(deathPosition);
			player->model->setModelRTMtx(translation * player->rotation);
			player->model->updateWorldMtx();
			
			player->model->registerToRoot( *engineSingleton->secondRoot );
			return;
		}
	}
}
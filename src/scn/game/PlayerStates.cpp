#include "scn/game/PlayerStates.h"
#include "scn/game/PlayerController.h"
#include "scn/game/PhysicsConstants.h"
#include "scn/game/misc/CameraController.h"
#include "scn/game/rollgame.h"
#include "scn/Chowder.h"
#include "hid/hid.h"
#include "snd/snd.h"

#define FLOAT_MOVEMENT_MULTIPLIER 3.0f
#define DEATH_WAIT_TIME 60
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
				Vector3 p(0.0f, 0.0f, player->linear_velocity.z / 2);
				player->linear_velocity = (Vector3::BASIS_Y * 7.0f) + p;
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
				
				player->linear_velocity += accelVector * 20.0f * DELTATIME;
			}
			
			if (player->position.y < -1819.81f)
			{
				player->setState(PLAYER_DEAD);
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
			
			engineSingleton->enableTimer = false;
			
			//player->model->interpolationReset();
			g3d::ResFileAccessor animFile( player->normalAnim );
			player->model->setAnim( 0, animFile, "DeadFall" );
			g3d::ModelAnimAccessor animation = player->model->anim(0);
			animation.start(true);
			animation.setFrameRate(1.0);
			snd::SoundManager::object()->bgm().stop();
			
			enable = true;
			engineSingleton->sndReq.start(0xD8);
			return;
		}
		
		void StateDeath::update()
		{
			if (enable)
			{
				if (timer > DEATH_WAIT_TIME)
				{
					unsigned long adjTime = timer - DEATH_WAIT_TIME;
					deathPosition.y = -5 * (adjTime * adjTime * 0.0166f) + 300 * (adjTime * 0.0166f);
					if (deathPosition.y < -300.0f)
					{
						enable = false;
						engineSingleton->state = 3;
						g3d::ModelAnimAccessor animation = player->model->anim(0);
						animation.stop();
					}
					
					player->model->updateFrame();
					
				} // else apply screen shake to camera
				timer++;
				if (timer == DEATH_WAIT_TIME)
				{
					snd::SoundManager::object()->bgm().start(0x7);
				}
			}
			return;
		}
		
		void StateDeath::updateModel()
		{
			Matrix34 translation = Matrix34::CreateTrans(deathPosition);
			if (timer > DEATH_WAIT_TIME)
			{
				unsigned long adjTime = timer - DEATH_WAIT_TIME;
				//float a = Math::FloorF(adjTime / 8.0f) * 8 * PI;
				float a = adjTime * PI * DELTATIME;
				player->rotation = Matrix34::CreateRotAxisRad(Vector3::BASIS_Z, a);
			}
			Matrix34 rtdlOffset = Matrix34::CreateTrans(rtdlModelTransOffset);
			player->model->setModelRTMtx(translation * player->rotation * rtdlOffset);
			player->model->updateWorldMtx();
			
			player->model->registerToRoot( *engineSingleton->secondRoot );
			return;
		}
		
		StateAirlock::StateAirlock(PlayerController *player) : PlayerState(player)
		{
		}
		
		void StateAirlock::update()
		{
			player->physicsUpdate();
			
			if (player->isOnGround())
			{
				player->setState(PLAYER_NORMAL);
			}
		}
	}
}
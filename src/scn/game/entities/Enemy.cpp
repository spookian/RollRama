#include "scn/game/entities/Enemy.h"
#include "g3d/Model.h"
#include "scn/game/collision/Collision.h"
#include "scn/game/collision/Path.h"
#include "scn/game/PlayerController.h"
#include "scn/Chowder.h"

#define FLICK_RADIUS 200.0f

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		Enemy::Enemy() : SphereCollider::SphereCollider(40.0f)
		{
			playerOverlap = false;
		}
		
		Enemy::~Enemy()
		{
			delete model; // don't ever create a base Enemy object; this is purely an interface kinda class
		}
		
		void Enemy::update()
		{
			return;
		}
		
		void Enemy::updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			model->updateWorldMtx();
			model->registerToRoot(root);
			return;
		}
		
		bool Enemy::searchAndHurtPlayer(bool hurtPlayer)
		{
			PlayerController* pl = engineSingleton->stage->player;
			if ( pl->isCollide( *this ) )
			{
				if (playerOverlap)
				{
					return false;
				}
				
				// confine both vectors to xz plane
				Vector3 plPosition = pl->position;
				plPosition.y = 0;
				Vector3 emPosition = position;
				emPosition.y = 0;
				
				Vector3 impulseNormal = plPosition - emPosition;
				impulseNormal.normalize();
				Vector3 impulse = impulseNormal * 4;
				// give the impulse a y component
				impulse.y = 3;
				
				// take initial vectors so player doesn't just teleport to enemy's side when landing on top
				Vector3 penetrationNormal = position - pl->position;
				float penetrationDepth = penetrationNormal.length() - (radius + pl->radius) + 0.01;
				penetrationNormal.normalize();
				
				pl->position += (penetrationNormal * penetrationDepth);
				pl->linear_velocity = impulse;
				
				Vector3 angularImpulse(impulse.z / pl->radius, 0.0, -impulse.x / pl->radius); // angular velocity = linear velocity / radius
				pl->angular_velocity = angularImpulse;
				playerOverlap = true;
				if (engineSingleton->health) engineSingleton->health--;
				return true;
			}
			else
			{
				playerOverlap = false;
			}
			return false;
		}
		
		bool Enemy::searchAndCapturePlayer()
		{
			PlayerController* pl = engineSingleton->stage->player;
			if ( pl->isCollide(*this) )
			{
				if (playerOverlap)
				{
					return false;
				}
				
				pl->setState(PLAYER_CAPTURE);
				Vector3 correctPosition(position.x, pl->position.y, position.z);
				pl->position = correctPosition;
				playerOverlap = true;
				return true;
			}
			else
			{
				playerOverlap = false;
			}
			return false;
		}
		
		bool Enemy::checkFlickRadius()
		{
			if (engineSingleton->input.flick)
			{
				float radiusToPlayer = (engineSingleton->stage->player->position - position).length();
				if (radiusToPlayer <= FLICK_RADIUS)
				{
					return true;
				}
			}
			return false;
		}
	}
}
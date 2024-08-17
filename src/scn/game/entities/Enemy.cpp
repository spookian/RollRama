#include "scn/game/entities/Enemy.h"
#include "g3d/Model.h"
#include "scn/game/collision/Collision.h"
#include "scn/game/collision/Path.h"
#include "scn/game/PlayerController.h"
#include "scn/Chowder.h"

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
		
		void Enemy::Update()
		{
			return;
		}
		
		void Enemy::UpdateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			model->updateWorldMtx();
			model->registerToRoot(root);
			return;
		}
		
		void Enemy::SearchAndHurtPlayer()
		{
			PlayerController* pl = engineSingleton->stage->player;
			if ( pl->isCollide( *this ) )
			{
				if (playerOverlap)
				{
					return;
				}
				
				// confine both vectors to xz plane
				Vector3 plPosition = pl->getPosition();
				plPosition.y = 0;
				Vector3 emPosition = position;
				emPosition.y = 0;
				
				Vector3 impulseNormal = plPosition - emPosition;
				impulseNormal.normalize();
				Vector3 impulse = impulseNormal * 3;
				// give the impulse a y component
				impulse.y = 3;
				
				// take initial vectors so player doesn't just teleport to enemy's side when landing on top
				Vector3 penetrationNormal = position - pl->getPosition();
				float penetrationDepth = penetrationNormal.length() - (radius + pl->getRadius()) + 0.01;
				penetrationNormal.normalize();
				
				pl->addDisplacement(penetrationNormal * penetrationDepth);
				pl->addImpulse( -pl->getLinearVelocity() );
				pl->addImpulse(impulse);
				playerOverlap = true;
			}
			else
			{
				playerOverlap = false;
			}
		}
	}
}
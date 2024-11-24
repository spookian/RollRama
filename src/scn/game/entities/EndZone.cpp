#include "scn/game/entities/Enemy.h"
#include "math/Vector3.h"
#include "scn/Chowder.h"
#include "scn/game/PlayerController.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		const float cylinderHalfHeight = 121.18f;
		const float cylinderRadius = 170.48f;
		
		void applyForceToPlayer(PlayerController *pl, Vector3 force, bool impulse)
		{
			Vector3 nForce = force;
			if (!impulse) nForce = nForce * DELTATIME;
			
			pl->linear_velocity += nForce;
		}
		
		void EndZone::updateUpper()
		{
			PlayerController *player = engineSingleton->stage->player;
			// most use cases
			Vector2 flatPlayerPosition(player->position.x, player->position.z);
			Vector2 flatCirclePosition(position.x, position.z);
			float heightDifference = player->position.y - (this->position.y + cylinderHalfHeight);
			
			float distance = (flatPlayerPosition - flatCirclePosition).length();
			if (distance <= cylinderRadius && heightDifference < 50.0f)
			{
				// you win the game
				Vector3 nVelocity = player->linear_velocity;
				nVelocity.y = 0.0f;
				player->linear_velocity = nVelocity;
				player->position += Vector3::BASIS_Y * (50.0f - heightDifference);
				
				// tell the stage the player won
			}
		}
		
		void EndZone::update()
		{
			// get player
			PlayerController *player = engineSingleton->stage->player;
			bool computePlane = player->position.y >= (this->position.y + cylinderHalfHeight); // the cutoff point for collision is halfway 
			if (computePlane) updateUpper();
			
			return;
		}
	}
}
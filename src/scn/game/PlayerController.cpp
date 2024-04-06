#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/Math.h"

#define FRICTION_CONST 0.05

using namespace hel::math;
namespace scn
{
	namespace roll
	{	
		PlayerController::PlayerController(g3d::CharaModel *model, StageController *stage)
		{
			playerModel = model;
			this->stage = stage;
			mass = 1.0f;
		}

		void PlayerController::IntegrateForces()
		{
			this->position += this->velocity;
			this->net_force = Vector3::ZERO;
		}
		
		void PlayerController::AddTorque(const hel::math::Vector3& torque)
		{
			angularVelocity += torque * DELTATIME;
		}

		void PlayerController::PhysicsUpdate()
		{
			// two different friction subroutines; one for inclined planes and the other for flat ground
			Vector3 weight(0.0, -GRAVITY * mass, 0.0);
			AddForce(weight);
			
			IntegrateForces();
			if (ResolveAllCollisions())
			{
				//friction
				Vector3 friction = velocity;
				friction.normalize();
				friction = friction * -FRICTION_CONST;
				
				if ((velocity + friction).length() < 0.1)
				{
					velocity = Vector3::ZERO;
				}
				else
				{
					velocity += friction;
				}
			}
		}

		bool PlayerController::ResolveAllCollisions()
		{
			bool result = false;
			for (int i = 0; i < stage->numTriangles; i++)
			{
				CollisionResult collisionData = ResolveCollision(*stage->triangleList[i]);
				result = result || collisionData.collided;
				
				if (collisionData.collided)
				{
					position += collisionData.displacement;
					velocity += collisionData.impulse;
					AddForce(stage->gameRotation.mul(collisionData.surface_normal) * GRAVITY * mass );
				}
			}
			
			return result;
		}

		void PlayerController::AddForce(const hel::math::Vector3& force)
		{
			this->velocity += (force * DELTATIME) / this->mass;
			this->net_force += force;
		}
		
		void PlayerController::UpdateModel(g3d::Root& root)
		{	
			//Vector3 slopeForward = -Vector3::BASIS_Y + *debugTriangle.normal;
			//Vector3 rotAxis(-slopeForward.z, slopeForward.y, slopeForward.x);
			//float magnitude = velocity.length();
			//if (slopeForward.x < 0 || slopeForward.z < 0) magnitude = -magnitude;
			//rotationMatrix = Matrix34::CreateRotAxisDeg(rotAxis, magnitude) * rotationMatrix; 
			// rework rotation based on slope normal
			
			Matrix34 translationMatrix = Matrix34::CreateTrans(position);
		
			playerModel->setModelRTMtx(translationMatrix * rotationMatrix);
			playerModel->updateWorldMtx();
			
			Vector3 scale(50.0, 50.0, 50.0);
			playerModel->setModelScale(scale);
			playerModel->registerToRoot(root);
		}
		
		CollisionResult PlayerController::ResolveCollision(TriangleWrapper& plane) // returns position offset
		{
			CollisionResult result;
			Vector3 closestPoint = plane.ClosestPointOnPlane(position);
			Vector3 edgeVector = closestPoint - position;
			
			if (edgeVector.length() > PLAYER_RADIUS) return result; 
			if (!plane.CheckPointInTriangle(closestPoint)) return result; 
			//if (edgeVector.dot(*plane.normal) < 0.0f) return result; // untested
			
			result.displacement = edgeVector + (*(plane.normal) * PLAYER_RADIUS);
			result.collided = true;
			result.surface_normal = *plane.normal;
			
			float impulse_length = velocity.dot(*plane.normal);
			result.impulse = *plane.normal * -impulse_length;
			
			return result;
		}
		
		Vector3 PlayerController::GetPosition()
		{
			return position;
		}
	}
}
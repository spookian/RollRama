#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/Math.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		void GenerateDebugTriangle(TriangleWrapper& debug)
		{
			debug.v0 = new Vector3(-217.31, -100.0, -92.333);
			//debug.v1 = new Vector3(183.79, -100.0, -152.43);
			debug.v1 = new Vector3(183.79, -200.0, -152.43);
			debug.v2 = new Vector3(19.12, -100.0, 180.48);
			//debug.normal = new Vector3(0.0f, 1.0f, 0.0f);
			debug.normal = new Vector3(0.2161, 0.9582, -0.1873);
			
			debug.RecalculateD();
		}
		
		PlayerController::PlayerController(g3d::CharaModel *model)
		{
			playerModel = model;
			GenerateDebugTriangle(debugTriangle);
			mass = 1.0f;
			justGrounded = true;
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
			Vector3 weight(0.0, -9.81 * mass, 0.0);
			AddForce(weight);
			Vector3 collisionOffset = ResolveCollision(debugTriangle);
			if (collisionOffset.x + collisionOffset.y + collisionOffset.z)
			{
				if (justGrounded) 
				{
					justGrounded = false;
					velocity.y = 0.0;
				}
				position += collisionOffset;
				AddForce(*debugTriangle.normal * weight.length());
			}
			else
			{
				if (!debugTriangle.CheckPointInTriangle(position)) justGrounded = true;
			}
			IntegrateForces();
			
		}

		void PlayerController::AddForce(const hel::math::Vector3& force)
		{
			this->velocity += (force * DELTATIME) / this->mass;
			this->net_force += force;
		}
		
		void PlayerController::UpdateModel(g3d::Root& root)
		{	
			Vector3 slopeForward = -Vector3::BASIS_Y + *debugTriangle.normal;
			Vector3 rotAxis(-slopeForward.z, slopeForward.y, slopeForward.x);
			float magnitude = velocity.length();
			if (slopeForward.x < 0 || slopeForward.z < 0) magnitude = -magnitude;
				
			Matrix34 translationMatrix = Matrix34::CreateTrans(position);
			rotationMatrix = Matrix34::CreateRotAxisDeg(rotAxis, magnitude) * rotationMatrix; 
			// BUG: rotation is affected by y.
			// Potential solutions: have the surface normal be BASIS_Y in the air; add torque as well and retool above code
			// WORK ON LATER!!!!!!!
			playerModel->setModelRTMtx(translationMatrix * rotationMatrix);
			playerModel->updateWorldMtx();
			
			Vector3 scale(50.0, 50.0, 50.0);
			playerModel->setModelScale(scale);
			playerModel->registerToRoot(root);
		}
		
		Vector3 PlayerController::ResolveCollision(TriangleWrapper& plane) // returns position offset
		{
			Vector3 closestPoint = plane.ClosestPointOnPlane(position);
			Vector3 edgeVector = closestPoint - position;
			
			if (edgeVector.length() > PLAYER_RADIUS) return Vector3::ZERO; 
			if (!plane.CheckPointInTriangle(closestPoint)) return Vector3::ZERO; 
			
			return edgeVector + (*(plane.normal) * PLAYER_RADIUS);
		} // this is completely untested and wont be tested until like 3/10/24 or something
		
		Vector3 PlayerController::GetPosition()
		{
			return position;
		}
	}
}
#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		PlayerController::PlayerController(g3d::CharaModel *model)
		{
			playerModel = model;
		}

		void PlayerController::IntegrateForces()
		{
			this->position += this->velocity;
			this->net_force = Vector3::ZERO;
		}

		void PlayerController::PhysicsUpdate()
		{
			// two different friction subroutines; one for inclined planes and the other for flat ground
			IntegrateForces();
		}

		void PlayerController::AddForce(const hel::math::Vector3& force)
		{
			this->velocity += (force * DELTATIME) / this->mass;
			this->net_force += force;
		}

		void PlayerController::UpdateModel(g3d::Root& root)
		{
			Matrix34 translationMatrix = Matrix34::CreateTrans(position);
			Matrix34 rotationMatrix = Matrix34::CreateRotXYZDeg(rotation);
			
			playerModel->setModelRTMtx(translationMatrix * rotationMatrix);
			playerModel->registerToRoot(root);
		}
		
		Vector3 PlayerController::ResolveCollision(TriangleWrapper& plane) // returns position offset
		{
			Vector3 closestPoint = plane.ClosestPointOnPlane(position);
			Vector3 edgeVector = closestPoint - position;
			
			if (edgeVector.length() > DISTANCE_TO_PLANE) return Vector3::ZERO; // first check
			if (!plane.CheckPointInTriangle(closestPoint)) return Vector3::ZERO; // second check
			
			Vector3 normalizedEdge = edgeVector;
			normalizedEdge.normalize();
			if ( normalizedEdge.dot( *plane.normal ) > 0.0f) return Vector3::ZERO; // third check
			
			return edgeVector;
		} // this is completely untested and wont be tested until like 3/10/24 or something
	}
}
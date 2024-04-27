#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "scn/game/PlayerController.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/math.h"

#define FRICTION_CONST 0.015

using namespace hel::math;
namespace scn
{
	namespace roll
	{	
		SimpleRigidbody::SimpleRigidbody(float _mass, float _radius) :  SphereCollider(_radius)
		{
			mass = _mass;
		}

		void SimpleRigidbody::IntegrateForces()
		{
			this->position += this->velocity;
			this->net_force = Vector3::ZERO;
		}

		void SimpleRigidbody::PhysicsUpdate(StageController* stage)
		{
			Vector3 weight(0.0, -GRAVITY * mass, 0.0);
			AddForce(weight);
			
			IntegrateForces();
			if (ResolveAllCollisions(stage))
			{
				//friction
				Vector3 friction = velocity;
				friction.normalize();
				friction = friction * -FRICTION_CONST;
				
				if ((velocity + friction).length() < 0.12)
				{
					velocity = Vector3::ZERO;
				}
				else
				{
					velocity += friction;
				}
				
				//rotation 
				Vector3 rotAxis(velocity.z, 0.0f, -velocity.x);
				
				angularVelocity = Matrix34::CreateRotXYZRad(rotAxis / radius); // linear velocity = angular * radius... angular in radians/sec
			}
		}

		bool SimpleRigidbody::ResolveAllCollisions(StageController* stage)
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

		void SimpleRigidbody::AddForce(const hel::math::Vector3& force)
		{
			this->velocity += (force * DELTATIME) / this->mass;
			this->net_force += force;
		}
		
		CollisionResult SimpleRigidbody::ResolveCollision(TriangleWrapper& plane) // returns position offset
		{
			CollisionResult result;
			Vector3 closestPoint = plane.ClosestPointOnPlane(position);
			Vector3 edgeVector = closestPoint - position;
			
			if (edgeVector.length() > radius) return result; 
			if (!plane.CheckPointInTriangle(closestPoint)) return result; 
			//if (edgeVector.dot(*plane.normal) < 0.0f) return result; // untested
			
			result.displacement = edgeVector + (*(plane.normal) * radius);
			result.collided = true;
			result.surface_normal = *plane.normal;
			
			float impulse_length = velocity.dot(*plane.normal);
			result.impulse = *plane.normal * -impulse_length;
			
			return result;
		}
		
		Matrix34 SimpleRigidbody::GetAngularVelocity()
		{
			return angularVelocity;
		}
	}
}
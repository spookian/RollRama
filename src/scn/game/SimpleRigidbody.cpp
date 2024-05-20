#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "scn/game/PlayerController.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/math.h"

#define FRICTION_CONST 0.02

using namespace hel::math;
namespace scn
{
	namespace roll
	{	
		SimpleRigidbody::SimpleRigidbody(float _mass, float _radius) :  SphereCollider(_radius)
		{
			mass = _mass;
			grounded = false;
		}

		void SimpleRigidbody::IntegrateForces()
		{
			this->position += this->linear_velocity;
			this->net_force = Vector3::ZERO;
		}

		void SimpleRigidbody::PhysicsUpdate(StageController* stage)
		{
			grounded = false;
			Vector3 weight(0.0, -GRAVITY * mass, 0.0);
			AddForce(weight);
			
			IntegrateForces();
			if (ResolveAllCollisions(stage))
			{
				//friction
				Vector3 friction = linear_velocity;
				friction.normalize();
				friction = friction * -FRICTION_CONST;
				
				if ((linear_velocity + friction).length() < 0.12)
				{
					linear_velocity = Vector3::ZERO;
				}
				else
				{
					linear_velocity += friction;
				}
				
				//rotation 
				Vector3 rotAxis(linear_velocity.z, 0.0f, -linear_velocity.x);
				angular_velocity = Matrix34::CreateRotXYZRad(rotAxis / radius); // linear velocity = angular * radius... angular in radians/sec
			}
		}

		bool SimpleRigidbody::ResolveAllCollisions(StageController* stage)
		{
			bool result = false;
			for (int i = 0; i < stage->triangleList.getSize(); i++)
			{
				TriangleWrapper tri = stage->triangleList[i]; // optimize?
				CollisionResult collisionData = ResolveCollision( tri );
				result = result || collisionData.collided;
				
				if (collisionData.collided)
				{
					if (collisionData.surface_normal.dot(Vector3::BASIS_Y) > 0.15) grounded = true; // magic number i came up with on the spot
					
					position += collisionData.displacement;
					linear_velocity += collisionData.impulse;
					AddForce(stage->gameRotation.mul(collisionData.surface_normal) * GRAVITY * mass );
				}
			}
			
			return result;
		}

		void SimpleRigidbody::AddForce(const hel::math::Vector3& force)
		{
			this->linear_velocity += (force * DELTATIME) / this->mass;
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
			
			float impulse_length = linear_velocity.dot(*plane.normal);
			result.impulse = *plane.normal * -impulse_length;
			
			return result;
		}
		
		Matrix34 SimpleRigidbody::GetAngularVelocity()
		{
			return angular_velocity;
		}
		
		bool SimpleRigidbody::IsOnGround()
		{
			return grounded;
		}
	}
}
#pragma once

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "g3d/Model.h"
#include "scn/game/Collision.h"
#include "scn/game/rollgame.h"

class Chowder;
// messy class prototype 

namespace scn
{
	namespace roll
	{
		class SimpleRigidbody : public SphereCollider
		// This is a simple spherical rigidbody.
		{
			// physics settings
			float mass;	
			
			hel::math::Vector3 velocity;
			hel::math::Vector3 net_force; // gets flushed every frame; representation of net force upon object that isn't actually used in velocity or position calculations
			hel::math::Matrix34 angularVelocity;
			
		public:
			SimpleRigidbody(float _mass, float _radius);
			void PhysicsUpdate(StageController* stage);
			void AddForce(const hel::math::Vector3& force); // velocity += force*dt / m 
			void AddTorque(const hel::math::Matrix34& torque); // euler
			
			CollisionResult ResolveCollision(TriangleWrapper& plane); // returns a position offset after colliding with a triangle; if the algorithm breaks early, Vector3.Zero is returned
			bool ResolveAllCollisions(StageController *stage);
			
			void IntegrateForces();
			
			void UpdateModel(g3d::Root& root); // updates position. save last.
			hel::math::Matrix34 GetAngularVelocity();
			
			void SetRadius(float new_radius);
			void SetMass(float new_mass);
		};
		
		class PlayerController // we're making a pseudo physics simulation because i came to the realization that the inclined plane problem solves itself if you have the normal vector of a plane
		{
			g3d::CharaModel *model;
			SimpleRigidbody *rb;
			hel::math::Matrix34 rotation;
			
		public:
			PlayerController(Chowder& parent);
			~PlayerController();
			
			void Update(StageController* stage);
			void UpdateModel(g3d::Root& root); // updates position. save last.
			hel::math::Vector3 GetPosition()
			{
				return rb->GetPosition();
			}
		};
	}
}
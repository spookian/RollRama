#pragma once

#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/collision/Collision.h"
#include "scn/game/collision/Octree.h"
#include "scn/game/rollgame.h"
#include "scn/game/PlayerStates.h"

namespace scn
{
	namespace roll
	{
		class SimpleRigidbody : public SphereCollider
		// This is a simple spherical rigidbody.
		{
		protected:
			// physics settings
			float mass;	
			hel::math::Vector3 net_force; // gets flushed every frame; representation of net force upon object that isn't actually used in velocity or position calculations
			bool grounded;
			TriOctree::OctreeNode *currentOctreeNode;
			
			CollisionResult resolveCollision(TriangleWrapper& plane); // returns a position offset after colliding with a triangle; if the algorithm breaks early, Vector3.Zero is returned
			bool resolveAllCollisions(StageController* stage, TriangleList& triangleList);		
			void integrateForces();
			
		public:
			hel::math::Vector3 linear_velocity;
			hel::math::Vector3 angular_velocity;
			hel::math::Matrix34 rotation;
			
			SimpleRigidbody(float _mass, float _radius);
			void physicsUpdate();
			void addForce(const hel::math::Vector3& force); // velocity += force*dt / m 
			void addTorque(const hel::math::Vector3& torque); // euler
			bool isOnGround();
		};
		
		class PlayerController : public SimpleRigidbody// we're making a pseudo physics simulation because i came to the realization that the inclined plane problem solves itself if you have the normal vector of a plane
		{
			PlayerState *state;
			
		public:
			g3d::CharaModel *model;
			bool captured;
			
			static GlobalObject<const hel::math::Vector3, float> jumpLinearImpulses[2];
			static GlobalObject<const hel::math::Vector3, float> jumpAngularImpulses[2];

			PlayerController();
			~PlayerController();

			void update(StageController* stage);
			void updateModel(g3d::Root& root, hel::math::Matrix34& worldRotation); // updates position. save last.
			void powerUp(bool); // i wrote myself into a corner, okay? don't judge me
			
			void debugDrawOctreeBlock();
		};
	}
}
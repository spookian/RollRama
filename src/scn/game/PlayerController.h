#pragma once

#include "math/math.h"

#include "g3d/Model.h"
#include "nw4r/ResFile.h"

#include "scn/game/collision/Collision.h"
#include "scn/game/rollgame.h"
#include "scn/game/PlayerStates.h"

enum PlayerStates
{
	PLAYER_NORMAL,
	PLAYER_DEAD,
	PLAYER_AIRLOCK,
	PLAYER_FLOAT,
	PLAYER_CAPTURE,
	PLAYER_START,
	PLAYER_WIN
};

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
			
			CollisionResult resolveCollision(TriangleWrapper& plane); // returns a position offset after colliding with a triangle; if the algorithm breaks early, Vector3.Zero is returned
			bool resolveAllCollisions(TriangleList& triangleList);		
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
			nw4r::g3d::ResFile* normalAnim;
			nw4r::g3d::ResFile* gcnAnim;
		
			int health;
			g3d::CharaModel *model;
			bool captured;
			bool hideModel;
			
			static GlobalObject<const hel::math::Vector3, float> jumpLinearImpulses[2];
			static GlobalObject<const hel::math::Vector3, float> jumpAngularImpulses[2];

			PlayerController();
			~PlayerController();

			void update(StageController* stage);
			void updateModel(g3d::Root& root, hel::math::Matrix34& worldRotation); // updates position. save last.
			void setState(PlayerStates states);
			void getHurt();
		};
	}
}

extern GlobalObject<const hel::math::Vector3, float> rtdlModelTransOffset;
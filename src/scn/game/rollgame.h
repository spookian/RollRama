#pragma once

#include "math/Vector3.h"
#include "g3d/Model.h"

namespace scn
{
	namespace roll
	{
		struct TriangleData
		{
			unsigned short v0;
			unsigned short v1;
			unsigned short v2;
			
			unsigned char flags;
			hel::math::Vector3 normal;
		};
		
		enum TriangleProjection
		{
			PROJECTION_X,
			PROJECTION_Y,
			PROJECTION_Z
		};
		
		struct TriangleWrapper // used to parse and calculate 
		{
			hel::math::Vector3 *v0;
			hel::math::Vector3 *v1;
			hel::math::Vector3 *v2;
			
			hel::math::Vector3 *normal;
			float d;
			
			TriangleWrapper(hel::math::Vector3* vertexList, TriangleData* data);
			hel::math::Vector3 ClosestPointOnPlane(const hel::math::Vector3& point);
			bool CheckPointInTriangle(const hel::math::Vector3& point);
			
			// for debug purposes
			void RecalculateD(); 
			TriangleWrapper();
		};
		
		class StageController
		{
			TriangleData *triangleSoup;
			hel::math::Vector3 *vertexList;
			g3d::CharaModel *stageModel; // i only decompiled one type of model, okay? cut me some slack
		};
		
		/*
			stage_position = -player_position; use for translation matrix since the stage will always be centered at 0,0,0
		*/

		class PlayerController // we're making a pseudo physics simulation because i came to the realization that the inclined plane problem solves itself if you have the normal vector of a plane
		{
			float mass;	
			hel::math::Vector3 position;
			hel::math::Vector3 velocity;
			hel::math::Vector3 net_force; // gets flushed every frame; representation of net force upon object that isn't actually used in velocity or position calculations
			hel::math::Vector3 rotation; // euler
			
			g3d::CharaModel *playerModel;
			StageController *stage;
			
		public:
			PlayerController(g3d::CharaModel *model);
			void PhysicsUpdate();
			void AddForce(const hel::math::Vector3& force); // velocity += force*dt / m 
			void AddImpulse(const hel::math::Vector3& force); // velocity += force/m
			hel::math::Vector3 ResolveCollision(TriangleWrapper& plane); // returns a position offset after colliding with a triangle; if the algorithm breaks early, Vector3.Zero is returned
			void IntegrateForces();
			
			void UpdateModel(g3d::Root& root); // updates position. save last.
			
			/*														Collision Detection Algorithm But Awesome: Made by Shinton, age 12
			Broad-phase:
				This game will be using the uniform cells broad-phase of collision detection as seen in Super Mario 64, and the book Real Time Collision Detection, authored by Christer Ericson. Buy it, it's worth the read!
				The uniform grid will be built in runtime using a collision soup of triangles and vertices built into the executable.
				The grid is 16x16 cells, and it divides the level into a giant 2D rectangle that takes the maximum and minimum x and z values from every vertex in the stage to use as the rectangle's base (x) and height (y) respectively.
				
			Narrow-phase:
				The player is treated as a sphere that collides with triangles using an algorithm to get the closest point on the plane containing the triangle and return if the point lies inside of the triangle. (Latter test is a tiny bit complicated due to using a 2D barycentric triangle algorithm with the largest axis projection of the triangle's normal affecting the variables being tested.) (I love you Real Time Collision Detection book)
				If the second test passes then the distance between the triangle point and the player's position is checked to be below or equal to a constant. If the check fails, then the player is nowhere near close enough for the actual collision resolution to occur.
				Finally, the edge vector between the triangle point and the player position has the dot product performed on it and the normal vector of the triangle. If the two vectors are (somewhat) in the same direction, then the algorithm will stop.
				Now that all of the tests have been passed, we can complete collision resolution and add the triangle's surface normal multiplied by the length of the edge vector to the player's position.
				
			Physics simulation:
				The position has been corrected but the velocity remains the same, AND is growing at a constant rate if gravity is accounted for. To solve this, we must implement Newton's three basic laws (the most important being the third).
				In accordance with the Inclined Plane problem, the weight force may be split up into two component vectors. One has the same direction as the normal force, and the other is the perpendicular force which pushes the object on an inclined plane down.
				Since we already have the surface normal which is in the same direction as the normal force, we can multiply it by the same magnitude as the weight force and simply compute the net force.
				Friction will be computed by taking the normalized net force and multiplying it with the friction constant. On flat ground, a different friction function will be used.
				
				Acceleration has been taken care of, but what about velocity?
				1. Directly proportional to steepness (found by performing the dot product with a surface normal and the up vector), the momentum from pre-collision velocity would be transformed into an initial velocity with the same direction as the current net force vector
				The magnitude of the vector would be the magnitude of the pre-collision velocity vector multiplied by the steepness variable.
				
				A similar method will be employed when moving from one plane (triangle) to another, except the magnitude of the vector would stay the same.
				
				2. will write later
			*/
		};
	}
}
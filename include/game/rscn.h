/*
phase 1 (late dec - mid january):
have camera object be behind player obj at all times ()
control player object with d-pad (decompile input? use libogc or wii sdk functions?)
	later on use wii sdk or libogc functions, need to get wiimote's accelerometer for motion controls
	have player follow basic laws of physics
		inertia, gravity and friction

have player object include a model struct (either g3d::Model or g3d::StdModel for animation functions)

phase 2 (mid january - mid february):
implement collision (wip)
implement items and enemies
recruit a dude or two. dunno what for, level coll or something? level design? 

phase 3 (mid-late february):
the octree problem
	figure out how kcl blocks work
	if not enough, write a script to generate your own octree data
		each octree block should have an int for the parent node
		each octree block should have 4-8 ground tris and 4-8 wall tris

	figure out if you need enemies and entities to be in octree or if you want to micromanage them via screen borders

get levels modelled out

phase 4 (all of march):
hurry hurry hurryyy!!!! implement EVERYTHING GET EVERYTHING GOING MUSIC ITEMS ETC
WE NEED ATLEAST ONE OR TWO LEVELS FOR APRIL FOOLS

*/

#include "math/Vector3.h"

namespace rcoll
{
	class Interval {
		public:
		static bool intersects(float aa, float ab, float ba, float bb); 
	};

	// interface used for collision 
	class CollShape
	{
		public:
		// members
		hel::math::Vector3* position; // here's the deal, you supply the vector, 

		// structs & classes
		struct CollPointList {
			// it's not really my problem if you're idiotic enough to modify the members of a CollPointList object
			int num_points;
			hel::math::Vector3 points[15]; //magic number ftw
		};
		
		struct CollisionInfo {
			bool collided;
			hel::math::Vector3 MTV;
			// idk what else to add i didn't think i'd get this far
		};

		// virtual functions
		virtual CollPointList getPoints(const CollShape& other); 
		virtual CollPointList getNormals(const CollShape& other); // a normal array (should be 30 at the very most but functionally we'll only need like 6)

		// normal functions
		CollisionInfo checkCollision(const CollShape& other); // get minimum translation vector and whatnot
	};

	class Sphere : public CollShape
	{
		public:
		Sphere(float radius, const Vector3& position);
	};
}
// i'm making this way more complex than it needs to be, but such is the life of a c++ dev. i need simplicity

namespace rscn { // roll scn
	class Entity {
		public:
		virtual void update();
		virtual void preDraw(); // get ready to draw, update matrices and whatnot
		virtual void draw();	
		virtual void endScene(); // tells all entities present to kill themselves right before the list is cleared.
	};
	
	class Player : public Entity {
		private:
		g3d::Model* player_model;
		rcoll::Sphere coll_sphere; // either a collision sphere or a collision aabb cube

		hel::math::Vector3 position; // 
		hel::math::Vector3 velocity; // add to position at the end of each frame.

		public:
		~Player();

		// organize game logic here
		override void update();
		override void draw(); 
	};
}

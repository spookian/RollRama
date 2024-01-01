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
		g3d::StdModel* player_model; // 428 bytes - 0x804739f4
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

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
		Sphere(float radius, const hel::math::Vector3& position);
	};
}
// i'm making this way more complex than it needs to be, but such is the life of a c++ dev. i need simplicity
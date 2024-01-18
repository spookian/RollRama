#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"

namespace scn
{
	class AMIGADemo
	{
	private:
		g3d::CameraAccessor 	camera;
		g3d::CharaModel*		sphere;
		hel::math::Vector3		spherePosition;
		hel::math::Vector3		sphereVelocity;
		hel::math::Vector3		sphereAngles; // euler
		
	public:
		AMIGADemo(g3d::CharaModel* _sphere, g3d::CameraAccessor* _cam);
		void updateMain();
		void registerToRoot(g3d::Root& root);
	};
}
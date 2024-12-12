#pragma once
#include "math/Vector3.h"
#include "math/Matrix34.h"

namespace scn
{
	namespace roll
	{
		enum CameraStates
		{
			CAMERA_NORMAL,
			CAMERA_FALL,
			CAMERA_TRANSITION_LOCK,
			CAMERA_TRANSITION_UNLOCK,
			CAMERA_LOCK
		};
		
		class CameraController // the camera will always lag one frame behind
		{
		public:
			int state; // end of stage, death or normal
			hel::math::Vector3 position;
			
			int timer;
			hel::math::Vector3 oldPosition;
			hel::math::Vector3 lockPosition;
			
			CameraController();
			void update();
		};
	}
}
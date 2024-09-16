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
			CAMERA_DEATH,
			CAMERA_FREELOOK,
			CAMERA_FINISH
		};
		
		class CameraController
		{
			int timer;
		public:
			int state; // end of stage, death or normal
			
			CameraController();
			void update();
			hel::math::Matrix34 getViewMtx();
		};
	}
}
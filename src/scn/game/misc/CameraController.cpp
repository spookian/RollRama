#include "math/math.h"
#include "scn/game/misc/CameraController.h"
#include "scn/Chowder.h"
#include "scn/game/PlayerController.h"
#include "g3d/Model.h"

namespace
{
	const GlobalObject<const hel::math::Vector3, float> cameraOffset = { {0.0f, 250.0f, 225.0f} };
}

namespace scn
{
	namespace roll
	{
		CameraController::CameraController()
		{
			state = 0;
			timer = 0;
			return;
		}
		
		void CameraController::update()
		{
			switch (state)
			{
				default:
				break;
				
				case CAMERA_NORMAL:
				{
					PlayerController *player = engineSingleton->stage->player;
					position = player->position + cameraOffset;
					
					hel::math::Vector3 screenShake; // create screenshake later
					hel::math::Matrix34 shakeMatrix = hel::math::Matrix34::CreateTrans(screenShake);
					
					g3d::CameraAccessor fCamera = engineSingleton->modelRoot->currentCamera();
					
					hel::math::Matrix34 viewMatrix = hel::math::Matrix34::CreateLookAt( position, hel::math::Vector3::BASIS_Y, player->position );
					
					fCamera.setViewMtx(shakeMatrix * viewMatrix);
					
					break;
				}
			}
			return;
		}
	}
}
#include "scn/game/entities/Enemy.h"
#include "scn/game/PhysicsConstants.h"
#include "g3d/ResFileHelper.h"
#include "hid/hid.h"
#include "nw4r/Math.h"

#include "scn/Chowder.h"
#include "scn/game/PlayerController.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		const float JumpHole::arrowDistance = 100.0f;
		
		JumpHole::JumpHole(float _horizontalDistance, float _verticalLaunchSpeed)
		{
			horizontalDistance  =_horizontalDistance;
			verticalLaunchSpeed = _verticalLaunchSpeed;
			direction = 0.0f;
			
			arrowModel = InitResModel(engineSingleton->FileRepository, "step/effect/JumpArrow");
			state = 0;
		}
		
		float getAirTime(float yVelo)
		{
			/* let a be the gravity constant, and b be the launch speed of kirby.
			if the formula for gravity distance is -0.5at^2 + bt assuming you start at ground level, then
			t(-0.5at + b) = 0
			-0.5at = -b
			t = b/0.5a
			or t = 2b/a, being the formula for air time
			
			next, we can get horizontal speed by getting our wanted distance and simply dividing it by air time.
			launch speed and horizontal distance are independent variables, but horizontal speed is dependent
			*/
			return (2 * yVelo) / GRAVITY;
		}
		
		void JumpHole::update()
		{
			switch (state)
			{
				case 0:
				if (searchAndCapturePlayer()) state = 1;
				break;
				
				case 1:
				{
					RotationResult result = obtainWiimoteRotation(0.0f);
					direction = nw4r::math::Atan2FIdx(result.accelY, result.accelX);
					
					// poll buttons
					if ( (engineSingleton->input.buttons & WPAD_BUTTON_2) && !(engineSingleton->input.buttons_held & WPAD_BUTTON_2) )
					{
						Vector3 velocity = ( Matrix34::CreateRotAxisDeg(Vector3::BASIS_Y, direction).mul( Vector3::BASIS_Z ) ) * (horizontalDistance / getAirTime(verticalLaunchSpeed));
						velocity.y = verticalLaunchSpeed;
						state = 0;
						// player stops being captured;
						engineSingleton->stage->player->linear_velocity = velocity;
						engineSingleton->stage->player->setState(PLAYER_NORMAL);
					}
				
					break;
				}
			}
		}
		
		void JumpHole::updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			if (state)
			{
				Matrix34 rotationMtx = Matrix34::CreateRotAxisDeg(Vector3::BASIS_Y, direction);
				Vector3 arrowPos = position + (rotationMtx.mul(Vector3::BASIS_Z) * arrowDistance);
				Matrix34 translationMtx = Matrix34::CreateTrans(arrowPos);
				//render arrow
				arrowModel->setModelScale(Vector3::ALL_ONE * 50.0f);
				arrowModel->setModelRTMtx( translationMtx * (worldRotation * rotationMtx) );
				//arrowModel->setModelRTMtx( translationMtx );
				arrowModel->updateWorldMtx();
				arrowModel->registerToRoot(root);
			}
			//Enemy::updateModel(root, worldRotation);
		}
	}
}
#include "scn/game/entities/Enemy.h"
#include "g3d/ResFileHelper.h"
#include "scn/Chowder.h"
#include "scn/game/PhysicsConstants.h"
#include "scn/game/PlayerController.h"
#include "hid/hid.h"

#define CLOUD_MODEL_SCALE 90.0f
#define PLAYER_CLOUD_OFFSET 12.291f

const float timeMultiplier = PI * DELTATIME * 2;
const GlobalObject<const hel::math::Vector3, float> cloudFlingVelocity = {{ 0.0f, 5.0f, -10.0f }};
using namespace hel::math;
namespace scn
{
	namespace roll
	{
		// scale of 80?
		Cloud::Cloud()
		{
			model = InitResModel( engineSingleton->FileRepository, "step/Cloud" );
			radius = 40.0f;
			timer = 0;
			hasCaptured = false;
		}
		
		void Cloud::update()
		{
			PlayerController *player = engineSingleton->stage->player;
			if (hasCaptured)
			{
				pathSystem.update();
				position = pathSystem.currentOffset;

				player->position = this->position;
				player->position.y += PLAYER_CLOUD_OFFSET;
				// create player air lock state where they cant move in air
				if ((engineSingleton->input.buttons & WPAD_BUTTON_2) && !(engineSingleton->input.buttons_held & WPAD_BUTTON_2))
				{
					player->linear_velocity = cloudFlingVelocity;
					player->setState(PLAYER_NORMAL);
					hasCaptured = false;
					//player->linear_velocity.x = 0.0f;
					//player->linear_velocity.y = 5.0f;
					//player->linear_velocity.z = 10.0f;
					//808d8df4 - this function
					// crash at 
				}
			}
			else
			{
				hasCaptured = searchAndCapturePlayer();
			}
			timer++;
		}
		
		void Cloud::updateModel(g3d::Root& root, Matrix34 worldRotation)
		{
			model->setModelRTMtx( worldRotation * Matrix34::CreateTrans(position) );
			
			Vector3 scaleOffset;
			float theta = (timer * timeMultiplier);
			scaleOffset.x = Math::SinFIdx(theta);
			scaleOffset.y = -scaleOffset.x;
			scaleOffset.z = scaleOffset.x;
			scaleOffset *= 30.0f; // the lumpytouch effect
			
			model->setModelScale( (Vector3::ALL_ONE * CLOUD_MODEL_SCALE) + scaleOffset );
			model->updateWorldMtx();
			model->registerToRoot(root);
			return;
		}
	}
}


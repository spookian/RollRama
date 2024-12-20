#include "scn/game/entities/Enemy.h"
#include "g3d/ResFileHelper.h"
#include "scn/Chowder.h"
#include "scn/game/PlayerController.h"

#define FLICK_START_POS 100.0f

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		FlickZone::FlickZone()
		{
			radius = 150.0f;
			timer = 0;
			model = InitResModel( engineSingleton->FileRepository, "step/FlickIndicator" );
		}
		
		void FlickZone::update()
		{
			if ( engineSingleton->stage->player->isCollide(*this) )
			{
				playerOverlap = true;
				timer++;
			}
			else
			{
				playerOverlap = false;
				timer = 0;
			}
		}
		
		void FlickZone::updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			PlayerController *player = engineSingleton->stage->player;
			if (playerOverlap)
			{
				Vector3 flickPos = player->position;
				flickPos.y += FLICK_START_POS + Math::AbsF32( Math::SinFIdx(timer * PI / 30.0f) ) * 10.0f;
				
				Matrix34 translation = Matrix34::CreateTrans(flickPos);
				
				Vector3 camFlickThing = (flickPos - engineSingleton->cam.position);
				camFlickThing.normalize();
				float c = acos(camFlickThing.dot(-Vector3::BASIS_Z));
				// we have billboarding at home
				// billboarding at home:
				
				model->setModelScale(Vector3::ALL_ONE * 40.0f);
				model->setModelRTMtx(translation * Matrix34::CreateRotAxisRad(Vector3::BASIS_X, -c) );
				model->updateWorldMtx();
				model->registerToRoot(root);
			}
		}
	}
}
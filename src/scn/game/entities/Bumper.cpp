#include "scn/game/entities/Gimmick.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		Bumper::Bumper(const Vector3& position)
		{
			model = InitResModel(parent.FileRepository, "step/RollChar");
			radius = bumperRadius;
		}

		void Bumper::update()
		{
			if (searchAndHurtPlayer(false))
			{
				// restart animation
				animationPlaying = true;
				timer = 0;
			}
		}

		void Bumper::updateModel(g3d::Root& root)
		{
			model->updateFrame();
			// set scale;
			
			model->setModelScale(Vector3::ALL_ONE * 50);
			Gimmick::updateModel(root);
		}
	}
}
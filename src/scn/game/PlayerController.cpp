#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "scn/game/PointStar.h"
#include "scn/game/PlayerController.h"
#include "scn/Chowder.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		PlayerController::PlayerController(Chowder& parent)
		{
			rb = new SimpleRigidbody(1.0f, PLAYER_RADIUS);
			model = InitResModel(parent.FileRepository, "step/RollChar");
		}
		
		PlayerController::~PlayerController()
		{
			delete rb;
			delete model;
		}
		
		void PlayerController::Update(StageController* stage)
		{
			rb->PhysicsUpdate(stage);
			for (int i = 0; i < stage->pstarList.getSize(); i++)
			{
				PointStar* cur_star = stage->pstarList[i];
				if (rb->isCollide(*cur_star))
				{
					//stage->parent->addScore(); not implemented yet
					delete cur_star;
					stage->pstarList.remove(i);
				}
			}
		}

		void PlayerController::UpdateModel(g3d::Root& root)
		{	
			rotation = rb->GetAngularVelocity() * rotation;
			Matrix34 translation = Matrix34::CreateTrans(rb->GetPosition());
		
			model->setModelRTMtx(translation * rotation);
			model->updateWorldMtx();
			
			Vector3 scale(50.0, 50.0, 50.0);
			model->setModelScale(scale);
			model->registerToRoot(root);
		}
	}
}
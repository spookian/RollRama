#include "scn/game/PointStar.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"

const GlobalObject<const hel::math::Vector3, float> deltaRot = { {0.0, 5.0, 0.0} };
const GlobalObject<const hel::math::Vector3, float> scale = { {30.0f, 30.0f, 30.0f} };

namespace scn
{
	namespace roll
	{
		PointStar::PointStar(Chowder& parent, Vector3 position) : SphereCollider(POINTSTAR_RADIUS)
		{
			this->position = position;
			model = InitResModel(parent.FileRepository, "step/CollectStar");
		}
		
		PointStar::~PointStar()
		{
			delete model;
		}
		
		void PointStar::UpdateModel(g3d::Root& root, hel::math::Matrix34& worldRotation)
		{
			// note to self: start using constants soon
			rotation = rotation * hel::math::Matrix34::CreateRotXYZDeg(deltaRot);
			hel::math::Matrix34 translation = hel::math::Matrix34::CreateTrans(position);
			
			model->setModelRTMtx((worldRotation * translation) * rotation);
			model->setModelScale(scale);
			model->updateWorldMtx();
			model->registerToRoot(root);
		}
	}
}
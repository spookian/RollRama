#include "scn/game/PointStar.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"

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
			hel::math::Matrix34 translation = hel::math::Matrix34::CreateTrans(position);
			hel::math::Vector3 size(POINTSTAR_RADIUS * 2.0f, POINTSTAR_RADIUS * 2.0f, POINTSTAR_RADIUS * 2.0f);
			
			model->setModelRTMtx(worldRotation * translation);
			model->setModelScale(size);
			model->updateWorldMtx();
			model->registerToRoot(root);
		}
	}
}
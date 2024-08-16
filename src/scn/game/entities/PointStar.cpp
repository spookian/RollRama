#include "scn/game/entities/Pickup.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"

#define POINTSTAR_RADIUS 10.0f
#define STAR_POINTS 100

const GlobalObject<const hel::math::Vector3, float> deltaRot = { {0.0, 0.0872665, 0.0} };
const GlobalObject<const hel::math::Vector3, float> scale = { {30.0f, 30.0f, 30.0f} };

namespace scn
{
	namespace roll
	{
		PointStar::PointStar(const Vector3& position) : Pickup(POINTSTAR_RADIUS)
		{
			this->position = position;
			model = InitResModel(engineSingleton->FileRepository, "step/CollectStar");
		}
		
		PointStar::~PointStar()
		{
			delete model;
		}
		
		void PointStar::Update()
		{
			if ( isCollide( *(SphereCollider*)engineSingleton->stage->player ) )
			{
				engineSingleton->score += STAR_POINTS;
				// function to create particles when i have the time to implement
				active = false;
			}
		}
		
		void PointStar::UpdateModel(g3d::Root& root, hel::math::Matrix34& worldRotation)
		{
			// note to self: start using constants soon
			rotation += deltaRot;
			hel::math::Matrix34 rotationMtx = hel::math::Matrix34::CreateRotXYZRad(rotation);
			hel::math::Matrix34 translation = hel::math::Matrix34::CreateTrans(position);
			
			model->setModelRTMtx((worldRotation * translation) * rotationMtx);
			model->updateWorldMtx();
			
			model->setModelScale(scale); 
			model->registerToRoot(root);
		}
	}
}
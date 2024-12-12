#include "scn/game/entities/Enemy.h"
#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/collision/Path.h"
#include "scn/game/PhysicsConstants.h"
#include "scn/Chowder.h"

const GlobalObject<const hel::math::Vector3, float> deeScale = {
	{50.0, 50.0, 50.0}
};

const int airTime = 70;

using namespace hel::math;
namespace scn
{
	namespace roll
	{	
		g3d::CharaModelContext getWaddleDeeContext()
		{
			g3d::ResFileAccessor mFile( engineSingleton->FileRepository.get("step/chara/enemy/Dee", false) );
			g3d::ResModelContext mResContext(mFile, "Model");
			g3d::ModelBufferOption mOptions = g3d::ModelContext::DefaultModelBufferOption();
			hel::common::FixedString<32> mString("MdlAnm");
			
			g3d::CharaModelContext modelCntxt(mResContext, mOptions, 4, 2, 4, *g3d::ModelContext::DefaultAllocator(), true, 0x2000, mString);
			return modelCntxt;
		}
		
		Dee::Dee()
		{
			active = true;
			timer = 0;
			state = 0;
			model = new g3d::CharaModel(getWaddleDeeContext());
			
			g3d::ResFileAccessor deeAnim( engineSingleton->FileRepository.get("step/chara/enemy/Dee", false) );
			model->setAnim(0, deeAnim, "Wait2");
			g3d::ModelAnimAccessor animation = model->anim(0);
			animation.start(true);
		}
		
		Dee::~Dee()
		{
			return;
		}
		
		void Dee::update()
		{
			switch(state)
			{
				case 0:
				searchAndHurtPlayer(true);
				if (checkFlickRadius())
				{
					state = 1;
					oldHeight = position.y;
					
					g3d::ResFileAccessor deeAnim( engineSingleton->FileRepository.get("step/chara/enemy/Dee", false) );
					model->setAnim(0, deeAnim, "DamageEtc");
					g3d::ModelAnimAccessor animation = model->anim(0);
					animation.start(true);
					
				}
				pathSystem.update();
				position = pathSystem.currentOffset;
				break;
				
				case 1:
				{
				// have waddle dee get flicked up and then down
					timer++;
					float floatTimer = (float)timer / 7.0f;
					position.y = oldHeight + (0.5f * -GRAVITY * floatTimer * floatTimer) + (70.0f * floatTimer);
					
					if (timer >= airTime)
					{
						state = 2;
					}
					break;
				}
				
				case 2:
				active = false;
				PointStar *newStar = new PointStar(position);
				engineSingleton->stage->pickupList.append(newStar);
				break;
				
			}
			model->updateFrame();
			return;
		}
		
		void Dee::updateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			Matrix34 translation = Matrix34::CreateTrans(position);
			model->setModelRTMtx( worldRotation * translation );
			model->setModelScale(deeScale);
			Enemy::updateModel(root, worldRotation);
		}
	}
}
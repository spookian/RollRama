#include "scn/game/entities/Enemy.h"
#include "math/math.h"
#include "g3d/Model.h"
#include "scn/game/collision/Path.h"
#include "scn/Chowder.h"

const GlobalObject<const hel::math::Vector3, float> deeScale = {
	{50.0, 50.0, 50.0}
};

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
			
			g3d::CharaModelContext modelCntxt(mResContext, mOptions, 4, 2, 2, *g3d::ModelContext::DefaultAllocator(), true, 0x2000, mString);
			return modelCntxt;
		}
		
		Dee::Dee(Vector3 pos)
		{
			position = pos;
			model = new g3d::CharaModel(getWaddleDeeContext());
		}
		
		Dee::~Dee()
		{
			return;
		}
		
		void Dee::Update()
		{
			SearchAndHurtPlayer();
			return;
		}
		
		void Dee::UpdateModel(g3d::Root& root, hel::math::Matrix34 worldRotation)
		{
			Matrix34 translation = Matrix34::CreateTrans(position);
			model->setModelRTMtx( worldRotation * translation );
			model->setModelScale(deeScale);
			Enemy::UpdateModel(root, worldRotation);
		}
	}
}
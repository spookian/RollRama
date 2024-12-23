#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "scn/game/entities/Pickup.h"
#include "scn/game/PlayerController.h"
#include "scn/game/PlayerStates.h"
#include "scn/Chowder.h"
#include "g3d/Model.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/math.h"

GlobalObject<const hel::math::Vector3, float> playerScale = {{50.0f, 50.0f, 50.0f}};
GlobalObject<const hel::math::Vector3, float> scn::roll::PlayerController::jumpLinearImpulses[2] = {
	{{0.0f, 7.0f, -4.0f}},
	{{0.0f, 7.0f, 4.0f}}
};
GlobalObject<const hel::math::Vector3, float> scn::roll::PlayerController::jumpAngularImpulses[2] = {
	{{-3.0f/PLAYER_RADIUS, 0.0f, 0.0f}},
	{{3.0f/PLAYER_RADIUS, 0.0f, 0.0f}}
};

GlobalObject<const hel::math::Vector3, float> rtdlModelTransOffset = {
	{0, -25.0f, 0}
};

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		PlayerController::PlayerController() : SimpleRigidbody(1.0f, PLAYER_RADIUS)
		{
			g3d::ResFileAccessor mFile( engineSingleton->FileRepository.get("step/chara/hero/kirby/base/Pink", false) );
			normalAnim = engineSingleton->FileRepository.get("step/chara/hero/kirby/normal/Motion", true);
			gcnAnim = engineSingleton->FileRepository.get("step/GCNAnim", true);
			
			g3d::ResFileAccessor playerMotion( normalAnim );
			g3d::ResFileAccessor gcnMot( gcnAnim );
			
			g3d::ResModelContext mResContext(mFile, "Model");
			g3d::ModelBufferOption mOptions = g3d::ModelContext::DefaultModelBufferOption();
			hel::common::FixedString<32> mString("MdlAnm");
			g3d::CharaModelContext mContext(mResContext, mOptions, 8, 2, 4, *g3d::ModelContext::DefaultAllocator(), true, 0x1000, mString);
			this->model = new g3d::CharaModel(mContext);

			state = new StateNormal(this);
			captured = false;
			health = 6;
			hideModel = false;
			
			g3d::ModelAccessor playerModel = model->model();
			playerModel.nodeByName("KirbyBodyBig3M").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBigM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyBlowM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyDrawM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyFlightM").setVisibility(false);
			playerModel.nodeByName("KirbyBodyM").setVisibility(true);
			
			model->setAnim( 0, gcnMot, "Roll" );
			g3d::ModelAnimAccessor animation = model->anim(0);
			animation.start(true); // bool is loop
			animation.setFrameRate(1.0);
		}
		
		PlayerController::~PlayerController()
		{
			delete model;
			delete state;
			
			delete gcnAnim;
			delete normalAnim;
		}
		
		void PlayerController::update(StageController* stage)
		{
			// check for player death in engine singleton, then change state
			state->update();
		}

		void PlayerController::updateModel(g3d::Root& root, Matrix34& worldRotation)
		{	
			// use quaternions to multiply matrices
			if (!hideModel)
			{
				Quaternion r, ang, final;
				C_QUATMtx(&r, rotation.mtx);
				C_QUATMtx(&ang, Matrix34::CreateRotXYZRad(angular_velocity).mtx);
				PSQUATMultiply(&ang, &r, &final);
				PSMTXQuat(rotation.mtx, &final);
				
				Matrix34 translation = Matrix34::CreateTrans(position);
				Matrix34 rtdlOffset = Matrix34::CreateTrans(rtdlModelTransOffset);
				
				model->setModelRTMtx(translation * (worldRotation * rotation * rtdlOffset));
				model->updateWorldMtx();
				
				model->setModelScale(playerScale);
				model->registerToRoot(root);
			}
			
			state->updateModel();
		}
		
		void PlayerController::setState(PlayerStates states)
		{
			delete state;
			switch (states)
			{
				default:
				state = new StateNormal(this);
				break;
				
				case PLAYER_CAPTURE:
				state = new StateCapture(this);
				break;
				
				case PLAYER_DEAD:
				engineSingleton->stage->pauseForPlayerObject = true;
				state = new StateDeath(this);
				break;
				
				case PLAYER_AIRLOCK:
				state = new StateAirlock(this);
			}
			return;
		}
		
		void PlayerController::getHurt()
		{
			health--;
			if (health == 0) 
			{
				delete state;
				state = new StateDeath(this);
				
				engineSingleton->stage->pauseForPlayerObject = true;
			}
			// put in some visual bullshit to signify that you got hurt
		}
	}
}
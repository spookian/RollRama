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

enum PlayerStates
{
	PLAYER_NORMAL,
	PLAYER_DEAD,
	PLAYER_BOSSFIGHT,
	PLAYER_FLOAT,
	PLAYER_CAPTURE,
	PLAYER_START,
	PLAYER_WIN
};

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
			//g3d::ResFileAccessor playerMotion( engineSingleton->FileRepository.get("step/chara/hero/kirby/normal/Motion", true) );
			//playerMotion.bind(mFile, false);
			
			g3d::ResModelContext mResContext(mFile, "Model");
			g3d::ModelBufferOption mOptions = g3d::ModelContext::DefaultModelBufferOption();
			hel::common::FixedString<32> mString("Model");
			g3d::CharaModelContext mContext(mResContext, mOptions, 8, 2, 4, *g3d::ModelContext::DefaultAllocator(), true, 0x2000, mString);
			this->model = new g3d::CharaModel(mContext);
			//this->model = InitResModel(engineSingleton->FileRepository, "step/chara/hero/kirby/base/Pink");
			this->currentOctreeNode = 0;
			//position.y = 144.896;
			//position.z = -9628.0f;
			state = new StateNormal(*this);
			captured = false;
		}
		
		PlayerController::~PlayerController()
		{
			delete model;
			delete state;
		}
		
		struct OctreeInfo
		{
			TriOctree::OctreeNode *prev;
			TriOctree::OctreeNode *current;
		};
		
		// move octree crap to simplerigidbody
		OctreeInfo TraverseOctree(hel::math::Vector3& position, TriOctree::OctreeNode *node)
		{
			OctreeInfo result;
			TriOctree::OctreeNode *check = node;
			TriOctree::OctreeNode *cur = node;
			
			while (check && check->type != OCTREE_LEAF)
			{
				cur = check;
				if (cur->box.Contains(position))
				{
					TriOctree::OctreeBranch *branch = (TriOctree::OctreeBranch*)cur;
					check = branch->GetSector(position);
				}
				else
				{
					check = cur->parent;
				}
			}
			
			result.prev = cur;
			result.current = check;
			return result;
		}
		
		void PlayerController::update(StageController* stage)
		{
			if (currentOctreeNode == 0) currentOctreeNode = stage->collisionData.startBranch;
			if (!currentOctreeNode->box.Contains(position))
			{
				if (currentOctreeNode->parent != 0) currentOctreeNode = currentOctreeNode->parent;
			}
			if (currentOctreeNode->type != OCTREE_LEAF)
			{
				OctreeInfo info = TraverseOctree(position, currentOctreeNode);
				if (info.current) currentOctreeNode = info.current;
				else currentOctreeNode = info.prev;
			}
			
			// check for player death in engine singleton, then change state
			state->Update();
		}

		void PlayerController::updateModel(g3d::Root& root, Matrix34& worldRotation)
		{	
			// use quaternions to multiply matrices
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
		
		void PlayerController::debugDrawOctreeBlock()
		{
			if (currentOctreeNode == 0) return;
			
			hel::math::Matrix34 mtx;
			hel::math::Vector3 list[8];
			currentOctreeNode->box.getVertices(list);
			
			gfx::EasyRender3D::DrawQuadFill(mtx, list[0], list[1], list[5], list[4]);
			gfx::EasyRender3D::DrawQuadFill(mtx, list[1], list[3], list[5], list[7]);
			gfx::EasyRender3D::DrawQuadFill(mtx, list[2], list[3], list[7], list[6]);
			gfx::EasyRender3D::DrawQuadFill(mtx, list[0], list[2], list[6], list[4]);
		}
		
		void PlayerController::powerUp(bool isBoss)
		{
			delete state;
			state = new StateNormal(*this);
		}
	}
}
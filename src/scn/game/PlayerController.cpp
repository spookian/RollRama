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

GlobalObject<const hel::math::Vector3, float> playerScale = {{50.0f, 50.0f, 50.0f}};
GlobalObject<const hel::math::Vector3, float> scn::roll::PlayerController::jumpLinearImpulses[2] = {
	{{0.0f, 5.0f, -3.0f}},
	{{0.0f, 5.0f, 3.0f}}
};
GlobalObject<const hel::math::Vector3, float> scn::roll::PlayerController::jumpAngularImpulses[2] = {
	{{-3.0f/PLAYER_RADIUS, 0.0f, 0.0f}},
	{{3.0f/PLAYER_RADIUS, 0.0f, 0.0f}}
};

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		PlayerController::PlayerController(Chowder& component) : SimpleRigidbody(1.0f, PLAYER_RADIUS)
		{
			this->model = InitResModel(component.FileRepository, "step/RollChar");
			this->currentOctreeNode = 0;
		}
		
		PlayerController::~PlayerController()
		{
			delete model;
		}
		
		struct OctreeInfo
		{
			TriOctree::OctreeNode *prev;
			TriOctree::OctreeNode *current;
		};
		
		// this function
		OctreeInfo TraverseOctree(hel::math::Vector3& position, TriOctree::OctreeNode *node)
		{
			OctreeInfo result;
			TriOctree::OctreeNode *check = node;
			TriOctree::OctreeNode *cur = node;
			
			while (check && cur->type != OCTREE_LEAF)
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
			
			result.prev = check;
			result.current = cur;
			return result;
		}
		
		void PlayerController::Update(StageController* stage)
		{
			if (currentOctreeNode == 0) currentOctreeNode = stage->collisionData.startBranch;
			if (currentOctreeNode->type != OCTREE_LEAF || !currentOctreeNode->box.Contains(position) )
			{
				OctreeInfo info = TraverseOctree(position, currentOctreeNode);
				if (info.current) currentOctreeNode = info.current;
				else currentOctreeNode = info.prev;
			}
			TriOctree::OctreeLeaf *leaf = (TriOctree::OctreeLeaf*)currentOctreeNode;
			
			PhysicsUpdate(stage, leaf->obj);
			for (int i = 0; i < stage->pstarList.getSize(); i++)
			{
				PointStar* cur_star = stage->pstarList[i];
				if (isCollide(*cur_star))
				{
					//stage->parent->addScore(); not implemented yet
					delete cur_star;
					stage->pstarList.remove(i);
				}
			}
		}

		void PlayerController::UpdateModel(g3d::Root& root, Matrix34& worldRotation)
		{	
			// use quaternions to multiply matrices
			Quaternion r, ang, final;
			C_QUATMtx(&r, rotation.mtx);
			C_QUATMtx(&ang, Matrix34::CreateRotXYZRad(angular_velocity).mtx);
			PSQUATMultiply(&ang, &r, &final);
			PSMTXQuat(rotation.mtx, &final);
			
			Matrix34 translation = Matrix34::CreateTrans(position);
			
			model->setModelRTMtx(translation * (worldRotation * rotation));
			model->updateWorldMtx();
			
			model->setModelScale(playerScale);
			model->registerToRoot(root);
		}
		
		void PlayerController::AddImpulse(const hel::math::Vector3& impulse)
		{
			linear_velocity += impulse;
			return;
		}
		
		void PlayerController::AddAngularImpulse(const hel::math::Vector3& ang_impulse)
		{
			angular_velocity += ang_impulse;
			return;
		}
		
		void PlayerController::ZeroVelocity()
		{
			linear_velocity = Vector3::ZERO;
			angular_velocity = Vector3::ZERO;
		}
	}
}
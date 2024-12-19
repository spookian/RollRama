#include "scn/game/PhysicsConstants.h"
#include "scn/game/rollgame.h"
#include "g3d/Model.h"
#include "scn/game/PlayerController.h"
#include "scn/game/entities/Enemy.h"
#include "scn/game/collision/Path.h"

#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"
#include "scn/Chowder.h"

#define nullptr (Vector3*)0
#define NULL ((void*)0)
#define ROTATION_SHRINK 4.0f

const GlobalObject<const hel::math::Vector3, float> stagePos = { {0.0f, 0.0f, 150.0f} };

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		namespace 
		{
			struct JumpHoleSpawn
			{
				const GlobalObject<const Vector3, float> position;
				float horizontalDisplacement;
				float verticalVelocity;
			};
			
			JumpHoleSpawn holeSpawns[] = {
				{
					{{0.0f, -32.025f, -2669.5f}},
					760.0f,
					7.0f
				},
				
				{
					{{0.0f, -189.05f, -3575.4f}},
					760.0f,
					12.0f
				},
				
				{
					{{0.0f, 18.604f, -5006.7f}},
					481.0f,
					7.0f
				},
				
				{
					{{235.93f, 18.604f, -5442.6f}},
					431.0f,
					7.0f
				},
				
				{
					{{-101.65f, 18.604f, -5732.4f}},
					393.0f,
					7.0f
				},
				
				{
					{{214.15f, 18.604f, -5975.5f}},
					400.0f,
					7.0f
				}
			};
			
			void spawnHardcodedEntities(hel::common::List<Enemy*>& lst)
			{
				Enemy* e;
				for (int i = 0; i < ( sizeof(holeSpawns) / sizeof(JumpHoleSpawn) ); i++)
				{
					e = new JumpHole( holeSpawns[i].horizontalDisplacement, holeSpawns[i].verticalVelocity );
					e->position = holeSpawns[i].position;
					
					lst.append(e);
				}
			}
		}
		
		StageController::StageController(Chowder& parent)
		{	
			player = new PlayerController();
			spawnHardcodedEntities(enemyList);
			
			stageModel = InitResModel(parent.FileRepository, "step/MainStage");
			this->parent = &parent;
			
			pauseForPlayerObject = false;
		}
		
		StageController::~StageController()
		{
			delete player;
			// destroy all triangle wrappers
			for (int j = 0; j < pickupList.getSize(); j++)
			{
				delete pickupList[j];
			};
			
			for (int i = 0; i < enemyList.getSize(); i++)
			{
				delete enemyList[i];
			};
			
			delete stageModel; // remind me to add dl
		}
		
		void StageController::Update()
		{
			player->update(this);
			
			if (!pauseForPlayerObject)
			{
				for (int i = 0; i < pickupList.getSize(); i++)
				{
					Pickup* cur = pickupList[i];
					if (cur->active) cur->update();
					else
					{
						delete cur;
						pickupList.remove(i);
					}
				}
				
				for (int i = 0; i < enemyList.getSize(); i++)
				{
					Enemy* enm = enemyList[i];
					if (enm->active) enm->update();
					else
					{
						delete enm;
						enemyList.remove(i);
					}
				}
			}
		}
		
		void StageController::preDraw(g3d::Root& root)
		{
			// setup worldRotation
			Vector3 translation = -player->position;
			Matrix34 focalMatrix = Matrix34::CreateTrans(translation); // multiply translation first
			Matrix34 reverseMatrix = Matrix34::CreateTrans(-translation);
			Matrix34 worldRotation = reverseMatrix * (visualRotation * focalMatrix);
			
			Matrix34 stageTranslation = Matrix34::CreateTrans(stagePos);
			
			stageModel->setModelRTMtx(worldRotation);
			stageModel->updateWorldMtx();
			stageModel->registerToRoot(root);
			
			player->updateModel(root, visualRotation);
			for (int i = 0; i < pickupList.getSize(); i++)
			{
				pickupList[i]->updateModel(root, worldRotation);
			}
			for (int i = 0; i < enemyList.getSize(); i++)
			{
				enemyList[i]->updateModel(root, worldRotation);
			}
			return;
		}
		
		TriangleWrapper::TriangleWrapper(Vector3* vertexList, TriangleData* data)
		{
			v0 = &vertexList[data->v0];
			v1 = &vertexList[data->v1];
			v2 = &vertexList[data->v2];
			
			normal = &data->normal;
			d = (v0->x * normal->x + v0->y * normal->y + v0->z * normal->z);
		}
		
		TriangleWrapper::TriangleWrapper()
		{
			v0 = nullptr;
			v1 = nullptr;
			v2 = nullptr;
			
			normal = nullptr;
			d = 0.0f;
			
		}
		
		void TriangleWrapper::RecalculateD()
		{
			if (v0 && normal)
			{
				d = (v0->x * normal->x + v0->y * normal->y + v0->z * normal->z);
			}
		};
		
		Vector3 TriangleWrapper::ClosestPointOnPlane(const hel::math::Vector3& point) const
		{
			// function stolen from the RTCD book
			float signedDistance = normal->dot(point) - d;
			return point - ((*normal) * signedDistance);
		}
		
		//
		inline float getTriangleArea2D(float x0, float y0, float x1, float y1, float x2, float y2) // jus checking to make sure i dont fit in.... even though you know where i got this from
		{
			return (x0 - x1) * (y1 - y2) - (x1 - x2) * (y0 - y1);
		} // isn't this like a 2d cross product
		
		inline unsigned long checkProjectionTriangle(const TriangleWrapper& triangle)
		{
			unsigned long result = PROJECTION_X;
			float x = Math::AbsF32(triangle.normal->x);
			float y = Math::AbsF32(triangle.normal->y);
			float z = Math::AbsF32(triangle.normal->z);
			
			if ((y >= x) && (y >= z))
			{
				result = PROJECTION_Y;
			}
			if ((z >= x) && (z >= y))
			{
				result = PROJECTION_Z;
			}
			return result;
		}
		
		// shamelessly stolen from the book
		bool TriangleWrapper::CheckPointInTriangle(const Vector3& point) const
		{
			unsigned long largestProj = checkProjectionTriangle(*this);
			Vector3& A = *v0;
			Vector3& B = *v1;
			Vector3& C = *v2;
			
			float ood, regionU, regionV, regionW;
			
			switch (largestProj)
			{
				default:
				case PROJECTION_X: // x heavy, so yz plane
				regionU = getTriangleArea2D(point.y, point.z, B.y, B.z, C.y, C.z); // PBC
				regionV = getTriangleArea2D(point.y, point.z, C.y, C.z, A.y, A.z); // PCA
				regionW = getTriangleArea2D(point.y, point.z, A.y, A.z, B.y, B.z); // PAB
				ood = -normal->x;
				break;
				
				case PROJECTION_Y: // y heavy, so xz plane
				regionU = getTriangleArea2D(point.x, point.z, B.x, B.z, C.x, C.z); // PBC
				regionV = getTriangleArea2D(point.x, point.z, C.x, C.z, A.x, A.z); // PCA
				regionW = getTriangleArea2D(point.x, point.z, A.x, A.z, B.x, B.z); // PAB
				ood = normal->y;
				break;
				
				case PROJECTION_Z: // z heavy, so xy plane
				regionU = getTriangleArea2D(point.x, point.y, B.x, B.y, C.x, C.y); // PBC
				regionV = getTriangleArea2D(point.x, point.y, C.x, C.y, A.x, A.y); // PCA
				regionW = getTriangleArea2D(point.x, point.y, A.x, A.y, B.x, B.y); // PAB
				ood = -normal->z;
				break;
			}
			
			return (regionU * ood >= 0.0f) && (regionV * ood >= 0.0f) && (regionW * ood >= 0.0f);
			
		} // fucked up barycentric coords
		
		void TriangleWrapper::operator=(const TriangleWrapper& other)
		{
			v0 = other.v0;
			v1 = other.v1;
			v2 = other.v2;
			normal = other.normal;
			d = other.d;
		}
		
		Vector3 TriangleWrapper::GetMidpoint() const
		{
			return (*v0 + *v1 + *v2) / 3.0f;
		}
	}
}
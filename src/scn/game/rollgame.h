#pragma once

#include "math/Vector3.h"
#include "g3d/Model.h"
#include "file/FileAccessor.h"

#include "common/List.h"
#include "scn/game/entities/Pickup.h"
#include "scn/game/entities/Enemy.h"

class Chowder;

namespace scn
{
	namespace roll
	{	

		class PlayerController;
		struct TriangleData
		{
			unsigned short v0;
			unsigned short v1;
			unsigned short v2;
			
			hel::math::Vector3 normal;
		};
		
		enum TriangleProjection
		{
			PROJECTION_X,
			PROJECTION_Y,
			PROJECTION_Z
		};
		
		struct TriangleWrapper // used to parse and calculate 
		{
			hel::math::Vector3 *v0;
			hel::math::Vector3 *v1;
			hel::math::Vector3 *v2;
			
			hel::math::Vector3 *normal;
			float d;
			
			TriangleWrapper(hel::math::Vector3* vertexList, TriangleData* data);
			hel::math::Vector3 ClosestPointOnPlane(const hel::math::Vector3& point) const;
			bool CheckPointInTriangle(const hel::math::Vector3& point) const;
			hel::math::Vector3 GetMidpoint() const;
			
			void operator=(const TriangleWrapper& other);
			// for debug purposes
			void RecalculateD(); 
			TriangleWrapper();
		};
		
		typedef hel::common::List<TriangleWrapper> TriangleList;
		
		struct CollisionResult
		{
			inline CollisionResult()
			{
				collided = false;
				bounce = false;
			}
			
			hel::math::Vector3 displacement;
			hel::math::Vector3 impulse;
			hel::math::Vector3 surface_normal;
			
			bool collided; 
			bool bounce;
		};
		
		struct StageController
		{
			StageController(Chowder& parent);
			~StageController(); // clean up triangle list and model
			
			hel::common::List<scn::roll::TriangleWrapper> triangleList;
			hel::common::List<scn::roll::Pickup*> pickupList;
			hel::common::List<scn::roll::Enemy*> enemyList;
			
			Chowder *parent;
			
			bool pauseForPlayerObject;
			
			PlayerController *player;
			g3d::CharaModel *stageModel; // i only decompiled one type of model, okay? cut me some slack
			hel::math::Matrix34 gameRotation;
			hel::math::Matrix34 visualRotation;
			
			bool CreateStage(file::FileData& file);
			void Update();
			void preDraw(g3d::Root& root);
		};

		/*
			stage_position = -player_position; use for translation matrix since the stage will always be centered at 0,0,0
		*/
	}
}
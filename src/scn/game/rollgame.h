#pragma once

#include "math/Vector3.h"
#include "g3d/Model.h"
#include "file/FileAccessor.h"

namespace scn
{
	namespace roll
	{
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
			hel::math::Vector3 ClosestPointOnPlane(const hel::math::Vector3& point);
			bool CheckPointInTriangle(const hel::math::Vector3& point);
			
			// for debug purposes
			void RecalculateD(); 
			TriangleWrapper();
		};
		
		struct CollisionResult
		{
			inline CollisionResult()
			{
				collided = false;
			}
			
			hel::math::Vector3 displacement;
			hel::math::Vector3 impulse;
			hel::math::Vector3 surface_normal;
			
			bool collided; 
		};
		
		struct StageController
		{
			StageController();
			~StageController(); // clean up triangle list and model
			
			// implement some kind of linked list instead of array
			TriangleWrapper *triangleList[255];
			unsigned long numTriangles;
			g3d::CharaModel *stageModel; // i only decompiled one type of model, okay? cut me some slack
			hel::math::Matrix34 gameRotation;
			
			bool CreateStage(file::FileData& file);
			bool LoadModel(const char* path);
		};
		
		/*
			stage_position = -player_position; use for translation matrix since the stage will always be centered at 0,0,0
		*/
	}
}
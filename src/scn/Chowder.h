#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"
#include "scn/game/rollgame.h"
#include "common/List.h"
#include "lyt/lyt.h"
#include "gfx/FakeWriter.h"
#include "hid/hid.h"

#define DELTATILT_MIN 20
#define MAX_FRAME 2
#define PHYSICS_CONSTANT 1.0f
#define VISUAL_CONSTANT 0.25f

enum FlickType
{
	FLICK_NONE = 0,
	FLICK_FORWARD,
	FLICK_BACK
};

struct ControllerManager
{
	signed short prevAccelX;
	signed short prevAccelY;
	
	unsigned char timerX;
	unsigned short buttons;
	unsigned short flick;
	
	hel::math::Vector3 tilt;
	hel::math::Matrix34 visualRotation;
	hel::math::Matrix34 physicsRotation;
	
	ControllerManager();
	
	inline signed short sabs(signed short i)
	{
		if (i < 0) return -i;
		return i;
	}
	
	// very rudimentary
	void Update(const RotationResult& origin)
	{
		using namespace hel::math;
		
		tilt = origin.vector;
		buttons = origin.buttons;
		flick = FLICK_NONE;
		
		signed short deltaX = origin.accelX - prevAccelX;
		signed short deltaY = origin.accelY - prevAccelY;
		if (sabs(deltaX) >= DELTATILT_MIN) timerX++;
		else timerX = 0;
		
		prevAccelX = origin.accelX;
		prevAccelY = origin.accelY;
		
		if (timerX > MAX_FRAME)
		{
			timerX = 0;
			if (deltaX > 0) flick = FLICK_FORWARD;
			else flick = FLICK_BACK;
			// i can't test on my computer rn but just trust me okay
		}
		/*
		else if (timerY > MAX_FRAME)
		{
			timerX = 0;
			timerY = 0;
			if (deltaY > 0) return FLICK_RIGHT;
			return FLICK_LEFT;
		}*/
		
		Vector3 accel( asin(tilt.x), 0.0f, asin(tilt.z) );
		physicsRotation = Matrix34::CreateRotXYZRad(accel * PHYSICS_CONSTANT); // multiply by some arbitrary const whenever i fine tune physics
		visualRotation = Matrix34::CreateRotXYZRad(accel * VISUAL_CONSTANT);
		
		return;
	}
};

class Chowder
{
public:
	int score;
	int time;
	int health;

	g3d::Root *modelRoot;
	scn::roll::StageController *stage;
	ControllerManager input;
	
	Chowder();
	void SetupEasyRender3D();
	void updateMain();
	void drawDebug();
	void preDraw();
	void draw();
	
	g3d::ResFileRepository FileRepository;
};

extern Chowder *engineSingleton;
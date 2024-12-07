#pragma once

#include "g3d/Model.h"
#include "math/Math.h"
#include "scn/game/rollgame.h"
#include "common/List.h"
#include "lyt/lyt.h"
#include "hid/hid.h"
#include "scn/game/hud/FadeStar.h"
#include "scn/game/hud/NumberDisplay.h"
#include "scn/game/misc/PauseScreen.h"
#include "scn/game/hud/HUDController.h"

#define MAX_FORGIVENESS 5
#define MAX_FRAME 3
#define PHYSICS_CONSTANT 1.3f
#define VISUAL_CONSTANT 0.25f

#define SCORE_LIMIT 6
#define SCORE_START_X_STANDARD 100.0f
#define SCORE_START_X_WIDESCR 300.0f
#define SCORE_START_Y 100.0f

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
	signed short deltaAccel;
	signed short forgiveness;
	
	unsigned char timerX;
	unsigned short buttons;
	unsigned short buttons_held;
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
		buttons_held = buttons;
		buttons = origin.buttons;
		flick = FLICK_NONE;
		
		deltaAccel = (origin.accelX - prevAccelX);
		if (sabs(deltaAccel / 20)) 
		{
			timerX++;
			forgiveness = 0;
		}
		else
		{
			forgiveness++;
			if (forgiveness > MAX_FORGIVENESS)
			{
				forgiveness = 0;
				timerX = 0;
			}
		}
		
		prevAccelX = origin.accelX;
		prevAccelY = origin.accelY;
		
		if (timerX >= MAX_FRAME)
		{
			timerX = 0;
			forgiveness = 0;
			if (deltaAccel > 0) flick = FLICK_FORWARD;
			else flick = FLICK_BACK;
			// i can't test on my computer rn but just trust me okay
		}
		
		Vector3 accel( asin(tilt.x), 0.0f, asin(tilt.z) );
		physicsRotation = Matrix34::CreateRotXYZRad(accel * PHYSICS_CONSTANT); // multiply by some arbitrary const whenever i fine tune physics
		visualRotation = Matrix34::CreateRotXYZRad(accel * VISUAL_CONSTANT);
		
		return;
	}
};

struct Chowder
{
	int score;
	int time;
	int health;
	char stars;
	
	bool held_start;
	bool paused;
	bool can_pause;
	
	g3d::Root *modelRoot;
	scn::roll::StageController *stage;
	ControllerManager input;
	scn::roll::FadeStar fStar;
	scn::roll::HUDController hud;
	scn::roll::PauseScreen pause;
	
	Chowder();
	void SetupEasyRender3D();
	void updateMain();
	void drawDebug();
	void preDraw();
	void draw();
	void checkPause();
	
	g3d::ResFileRepository FileRepository;
};

extern Chowder *engineSingleton;
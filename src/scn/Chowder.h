#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"
#include "scn/game/rollgame.h"
#include "common/List.h"
#include "scn/game/PointStar.h"
#include "lyt/lyt.h"
#include "gfx/FakeWriter.h"

#define DELTATILT_MIN 13
#define MAX_FRAME 2

enum FlickType
{
	FLICK_NONE = 0,
	FLICK_FORWARD,
	FLICK_BACK
};

struct FlickTimer
{
	signed short prevAccelX;
	signed short prevAccelY;
	
	unsigned char timerX;
	unsigned char timerY;

	unsigned short buttons;
	
	inline signed short sabs(signed short i)
	{
		if (i < 0) return -i;
		return i;
	}
	
	// very rudimentary
	short Update(signed short accelX, signed short accelY)
	{
		signed short deltaX = accelX - prevAccelX;
		signed short deltaY = accelY - prevAccelY;
		if (sabs(deltaX) >= DELTATILT_MIN) timerX++;
		else timerX = 0;
		
		prevAccelX = accelX;
		prevAccelY = accelY;
		
		if (timerX > MAX_FRAME)
		{
			timerX = 0;
			timerY = 0;
			if (deltaX > 0) return FLICK_FORWARD;
			return FLICK_BACK;
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
		
		return FLICK_NONE;
	}
};

class Chowder
{
	g3d::Root *modelRoot;
	
	scn::roll::StageController *stage;
	
	FlickTimer flick;
	
	unsigned long score;
	unsigned long lives;
	unsigned char stars;
	lyt::Layout test;
	gfx::FakeWriter console;
	
public:

	Chowder();
	void SetupEasyRender3D();
	void updateMain();
	void drawDebug();
	void preDraw();
	void draw();
	
	void addScore(unsigned long offset);
	void addLives(signed int offset);
	void addStars(unsigned long offset);
	
	g3d::ResFileRepository FileRepository;
};
#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"
#include "scn/game/rollgame.h"
#include "common/List.h"
#include "scn/game/PointStar.h"

#define DELTATILT_MIN 14

struct FlickTimer
{
	unsigned short prevAccelX;
	unsigned short prevAccelY;
	
	unsigned char timerX;
	unsigned char timerY;
	
	signed short sabs(signed short i)
	{
		if (i < 0) return -i;
		return i;
	}
	
	// very rudimentary
	bool Update(signed short accelX, signed short accelY)
	{
		if (sabs(accelX - prevAccelX) >= DELTATILT_MIN) 
		{
			if (timerX == 0 && (accelX >= 80 || accelX <= -80)) timerX++;
			else if (timerX != 0) timerX++;
		}
		else timerX = 0;
		
		if (sabs(accelY - prevAccelY) >= DELTATILT_MIN)
		{
			if (timerY == 0 && (accelY >= 80 || accelY <= -80)) timerY++;
			else if (timerY != 0) timerY++;
		}
		else timerY = 0;
		
		prevAccelX = accelX;
		prevAccelY = accelY;
		
		if (timerX > 3 || timerY > 3)
		{
			timerX = 0;
			timerY = 0;
			
			return true;
		}
		return false;
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
#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"
#include "scn/game/rollgame.h"
#include "common/List.h"
#include "scn/game/PointStar.h"

class Chowder
{
	g3d::Root *modelRoot;
	
	scn::roll::StageController *stage;
	
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
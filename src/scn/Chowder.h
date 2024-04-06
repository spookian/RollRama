#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"
#include "scn/game/rollgame.h"

extern "C"
{
	extern void GXSetZMode(unsigned char unk0, unsigned long unk1, unsigned long unk2); // definition taken from doldecomp melee repo
}

class Chowder
{
	g3d::CameraAccessor camera;
	scn::roll::PlayerController *player;
	scn::roll::StageController *stage;
	
public:

	Chowder(g3d::CameraAccessor *cam, g3d::CharaModel *player);
	void SetupEasyRender3D();
	void DrawTriangleWireframe(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2);
	void updateMain();
	void drawDebug();
	void preDraw(g3d::Root& root);
};
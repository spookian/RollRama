#pragma once

#include "g3d/Model.h"
#include "math/Vector3.h"

extern "C"
{
	extern void GXSetZMode(unsigned char unk0, unsigned long unk1, unsigned long unk2); // definition taken from doldecomp melee repo
}

struct Triangle
{
	hel::math::Vector3 v0, v1, v2, normal;
	float d;
	unsigned long flags;
	
	Triangle(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2, const hel::math::Vector3& normal);
};

class Chowder
{
	g3d::CharaModel *playerModel;
	g3d::CameraAccessor camera;
	
public:
	Chowder(g3d::CameraAccessor *cam, g3d::CharaModel *player);
	void SetupEasyRender3D();
	void DrawTriangleWireframe(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2);
	void updateMain();
	void drawDebug();
};
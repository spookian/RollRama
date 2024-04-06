#include "g3d/Model.h"
#include "math/Vector3.h"
#include "gfx/EasyRender3D.h"
#include "math/Matrix44.h"
#include "math/Matrix34.h"
#include "scn/Chowder.h"

#include "app/app.h"
#include "hid/hid.h"
#include "common/ExplicitSingleton.h"
#include "math/Math.h"

#define MAX_HID_ACCEL 108.0f
#define MAX_ACCEL 50

inline float convertAccel(signed short accel)
{
	signed short clamp = accel;
	if (clamp > MAX_ACCEL) clamp = MAX_ACCEL;
	else if (clamp < -MAX_ACCEL) clamp = -MAX_ACCEL;
	
	return ((float)clamp) / MAX_HID_ACCEL;
}

hel::math::Matrix34 obtainWiimoteRotation()
{
	using namespace hel::math;
	hid::SimpleWRHID& wiimote = hel::common::ExplicitSingleton<app::Application>::object->hidManager()->getWiimoteArray()[0]; // wow.
	Matrix34 result;

	if (wiimote.isEnabled())
	{
		WPADStatus wpad_data;
		WPADRead(0, (void*)&wpad_data);
		
		float accelX = convertAccel(wpad_data.accelX);
		float accelY = convertAccel(-wpad_data.accelY);
		Vector3 accel;
		
		accel.x = asin(accelX);
		accel.z = asin(accelY);
		
		result = Matrix34::CreateRotXYZRad(accel);
	}
	
	return result;
}

// ONLY use these for debugging... due to the nature of file loading, TriangleWrapper objects do not clear the stored memory
void debugAddTriangles(scn::roll::StageController& stage)
{
	stage.numTriangles = 1;
	scn::roll::TriangleWrapper* t = new scn::roll::TriangleWrapper();
	t->v0 = new hel::math::Vector3(-300, -100, -300);
	t->v1 = new hel::math::Vector3( 300, -100, -300);
	t->v2 = new hel::math::Vector3( 0,   -100,  300);
	t->normal = new hel::math::Vector3(0, 1, 0);
	t->RecalculateD();
	
	stage.triangleList[0] = t;
	return;
}

Chowder::Chowder(g3d::CameraAccessor *cam, g3d::CharaModel *player)
{
	camera.unk = cam->unk;
	this->stage = new scn::roll::StageController();
	debugAddTriangles(*stage);
	
	this->player = new scn::roll::PlayerController(player, stage);
}

void Chowder::updateMain() // update physics and setup drawing
{
	hel::math::Vector3 offset(0.0f, 100.0f, -300.0f);
	hel::math::Vector3 offsetLook(0.0f, 100.0f, 0);
	
	hel::math::Matrix34 viewMatrix = hel::math::Matrix34::CreateLookAt(player->GetPosition() + offset, hel::math::Vector3::BASIS_Y, player->GetPosition() + offsetLook);
	camera.setViewMtx(viewMatrix);
	
	stage->gameRotation = obtainWiimoteRotation();
	player->PhysicsUpdate();
	return;
}

void Chowder::SetupEasyRender3D()
{
	float far = camera.getProjFar();
	float near = camera.getProjNear();
	float aspect_ratio = camera.getProjAspect();
	float fov = camera.getProjFovy();
	
	hel::math::Matrix44 perspective_matrix = hel::math::Matrix44::CreatePerspective(fov, aspect_ratio, near, far);
	hel::math::Matrix34 view_matrix = camera.viewMtx();
	
	gfx::EasyRender3D::SetupGX(perspective_matrix, true);
	gfx::EasyRender3D::SetViewMtx(view_matrix);
	
	GXSetZMode(1, 3, 1);
	
	/* According to Libogc/Devkitpro (which may or may not be illegally obtained but no one could prove it), their GX_SetZMode() function has three arguments:
	* u8 enable - a char (possibly boolean?) that enables the zbuffer
	* u8 func - an unsigned char that tells the gx what function to use for z comparisons
	* u8 update_enable - enables z-buffer updates when true;
	*
	* With that in mind, it would be best to use this function with the default settings found in RtDL's __GXInitGX()
	*/
	return;
}

void Chowder::DrawTriangleWireframe(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2)
{
	GXSetZMode(0, 1, 0); // ignore z buffer LMFAAAAO
	
	hel::math::Matrix34 basicMtx; // identity matrix; holds no transforms
	gfx::EasyRender3D::DrawLine(basicMtx, v0, v1, 3.0f);
	gfx::EasyRender3D::DrawLine(basicMtx, v1, v2, 3.0f);
	gfx::EasyRender3D::DrawLine(basicMtx, v2, v0, 3.0f);
	
	GXSetZMode(1, 3, 1); // restore z comparisons
	return;
}

void drawStageController(scn::roll::StageController& stage, hel::math::Vector3& focalPoint)
{
	using namespace hel::math;
	
	_GXColor blue = {0, 0, 255, 255};
	Vector3 translation = -focalPoint;
	Matrix34 focalMatrix = Matrix34::CreateTrans(translation); // multiply translation first
	Matrix34 reverseMatrix = Matrix34::CreateTrans(-translation);
	
	Matrix34 finalMatrix = reverseMatrix * (stage.gameRotation * focalMatrix);
	
	for (int i = 0; i < stage.numTriangles; i++)
	{
		scn::roll::TriangleWrapper& triangle = *stage.triangleList[i];
		Vector3& v0 = *(triangle.v0);
		Vector3& v1 = *(triangle.v1);
		Vector3& v2 = *(triangle.v2);
		
		gfx::EasyRender3D::SetColor(blue);
		gfx::EasyRender3D::DrawQuadFill(finalMatrix, v0, v1, v2, v2);
	}
}

void Chowder::drawDebug()
{
	using namespace hel::math;
	
	SetupEasyRender3D();
	Vector3 playerPos = player->GetPosition();
	_GXColor blue = {0, 0, 255, 255};
	_GXColor green = {0, 255, 0, 255};
	_GXColor yellow = {255, 255, 0, 255};

	drawStageController(*this->stage, playerPos);
	
	GXSetZMode(0, 1, 0);
	gfx::EasyRender3D::SetColor(yellow);
	gfx::EasyRender3D::DrawLine(obtainWiimoteRotation(), playerPos, playerPos + (Vector3::BASIS_Y * 50.0f), 6.0f);
	GXSetZMode(1, 3, 1);
	
	
}

void Chowder::preDraw(g3d::Root& root)
{
	player->UpdateModel(root);
}
#include "math/math.h"
#include "gfx/gfx.h"
#include "hid/hid.h"
#include "common/ExplicitSingleton.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"
#include "scn/game/PlayerController.h"
#include "mem/Memory.h"
#include "file/FileAccessor.h"

// split this poor fucking file into multiple
_GXColor red = {255, 0, 0, 255};
_GXColor blue = {0, 0, 255, 255};
_GXColor green = {0, 255, 0, 255};
// this function is needed
void adjustScreen(g3d::CameraAccessor& camera)
{
	using namespace hel::math;
	const _GXRenderModeObj *rmode = &hel::common::ExplicitSingleton<gfx::VISetting>::object->rmode;
	if (rmode->fbWidth == 608) return;
	float aspect_ratio = (16.0f/9.0f);
	
	float far = camera.getProjFar();
	float near = camera.getProjNear();
	float fov = camera.getProjFovy();
	
	camera.setProjPerspective(fov, aspect_ratio, near, far);
	
	return; 
}

// ONLY use these for debugging... due to the nature of file loading, TriangleWrapper objects do not clear the stored memory when deleted
void debugAddTriangles(scn::roll::StageController& stage)
{
	scn::roll::TriangleWrapper t;
	t.v0 = new hel::math::Vector3(-300, -100, -300);
	t.v1 = new hel::math::Vector3( 300, -100, -300);
	t.v2 = new hel::math::Vector3( 0,   -100,  300);
	t.normal = new hel::math::Vector3(0, 1, 0);
	t.RecalculateD();
	
	stage.triangleList.append(t);
	return;
}

Chowder::Chowder()
{
	// create root
	mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
	g3d::RootContext rootContext(*defAllocator, 32, 64, 8, 1);
	modelRoot = new g3d::Root(rootContext);
	g3d::CameraAccessor cam = modelRoot->currentCamera();
	
	// get rmode or enable progressive at start?
	adjustScreen(cam);
	this->stage = new scn::roll::StageController(*this);
	//debugAddTriangles(*stage);
	file::FileAccessor file("gcn/STAGE.roll", false);
	if (file.isLoaded()) 
	{
		file::FileData stage_data = file.block();
		stage->CreateStage(stage_data);
	}
	else debugAddTriangles(*stage);
	
	// note: move to stage controller object and/or abstract
	g3d::LightSetAccessor lightSet = modelRoot->lightSet(0);
	lightSet.disableLightObjAll();
	lightSet.enableAmbientLightObj(0);
	lightSet.enableLightObj(0, 0);
	
	nw4r::g3d::AmbLightObj ambColor = {{255, 255, 255, 255}};
	lightSet.setAmbientLightObj(ambColor);
}

void Chowder::updateMain() // update physics and setup drawing
{
	modelRoot->sceneClear();
	
	RotationResult rotation = obtainWiimoteRotation(0.25f); // magic number
	stage->gameRotation = rotation.actual;
	stage->visualRotation = rotation.visual;
	stage->Update();
	
	return;
}

void Chowder::SetupEasyRender3D()
{
	g3d::CameraAccessor camera = modelRoot->currentCamera();
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

void drawStageController(scn::roll::StageController& stage, hel::math::Vector3& focalPoint)
{
	using namespace hel::math;
	
	Vector3 translation = -focalPoint;
	Matrix34 focalMatrix = Matrix34::CreateTrans(translation); // multiply translation first
	Matrix34 reverseMatrix = Matrix34::CreateTrans(-translation);
	
	Matrix34 finalMatrix = reverseMatrix * (stage.gameRotation * focalMatrix);
	
	for (int i = 0; i < stage.triangleList.getSize(); i++)
	{
		const scn::roll::TriangleWrapper& triangle = stage.triangleList[i];
		Vector3& v0 = *(triangle.v0);
		Vector3& v1 = *(triangle.v1);
		Vector3& v2 = *(triangle.v2);
		
		gfx::EasyRender3D::SetColor(blue);
		gfx::EasyRender3D::DrawTriangleWireframe(finalMatrix, v0, v1, v2);
	}
}

void Chowder::drawDebug()
{
	using namespace hel::math;
	
	SetupEasyRender3D();
	
	Vector3 playerPos = stage->player->GetPosition();
	//drawStageController(*this->stage, playerPos);
	GXSetZMode(0, 1, 0);
	GXSetZMode(1, 3, 1);
}

void Chowder::preDraw()
{
	stage->preDraw(*modelRoot);
	
		// create lightset
	g3d::LightSetAccessor lightSet = modelRoot->lightSet(0);
	_GXColor white = {255, 255, 255, 255};
	
	nw4r::g3d::LightObj lobj;
	lobj.Clear();
	// curiously, the light won't render unless 0x3 is 5
	// this curious phenomenon can be seen in base rtdl as well. strange!
	lobj.InitLightColor(white);
	lobj.InitLightPos(0.0f, 700.0f, 300.0f);
	lobj.InitLightDir(-1.0f, 0.0f, 0.0f);
	lobj.InitLightAttnA(1.0f, 0.0f, 0.0f);
	lobj.InitLightAttnK(1.0f, 0.0f, 0.0f);
	
	lobj.unk = 5;
	lightSet.setLightObj(0, lobj);
}

void Chowder::draw()
{
	modelRoot->sceneCalcOnDraw();
	modelRoot->sceneDrawOpa();
	drawDebug();
}
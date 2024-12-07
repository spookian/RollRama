#include "scn/Chowder.h"
#include "gfx/gfx.h"
#include "common/Color.h"
#include "common/ExplicitSingleton.h"
#include "scn/game/PlayerController.h"
#include "mem/Memory.h"
#include "file/FileAccessor.h"

Chowder *engineSingleton;
const GlobalObject<const hel::math::Vector3, float> rectangle[4] = {
	{{ -300.0, -150.0, 0.0 }},
	{{ 300.0, -150.0, 0.0 }},
	{{ 300.0, 150.0, 0.0 }},
	{{ -300.0, 150.0, 0.0 }}
};

// turn into method function
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

ControllerManager::ControllerManager()
{
	prevAccelX = 0;
	prevAccelY = 0;
	forgiveness = 0;
	timerX = 0;
	buttons = 0;
	flick = FLICK_NONE;
}

Chowder::Chowder()
{
	engineSingleton = this;
	// create root
	g3d::RootContext rootContext( *g3d::ModelContext::DefaultAllocator(), 32, 64, 8, 1 );
	modelRoot = new g3d::Root(rootContext);
	g3d::CameraAccessor cam = modelRoot->currentCamera();
	
	// get rmode or enable progressive at start?
	adjustScreen(cam);
	
	this->stage = new scn::roll::StageController(*this);
	//debugAddTriangles(*stage);
	file::FileAccessor file("gcn/MAIN.roll", false);
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
	
	score = 0;
	health = 6;
	time = 255;
	stars = 0;
	
	paused = false;
	can_pause = true;
	held_start = false;
}

void Chowder::checkPause()
{
	if ((input.buttons & WPAD_BUTTON_PLUS & ~(input.buttons_held)) && can_pause)
	{
		paused = true;
		pause.activate();
	}
	return;
}

void Chowder::updateMain() // update physics and setup drawing
{
	input.Update( obtainWiimoteRotation(0.25f) );
	if ( (input.buttons & WPAD_BUTTON_PLUS) == 0) held_start = false;
	if (!paused)
	{
		modelRoot->sceneClear();
		
		stage->gameRotation = input.physicsRotation;
		stage->visualRotation = input.visualRotation;
		stage->Update();
		checkPause();
	}
	else pause.update();
	
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
		
		gfx::EasyRender3D::DrawTriangleWireframe(finalMatrix, v0, v1, v2);
	}
}

void Chowder::drawDebug()
{
	SetupEasyRender3D();
	GXSetZMode(0, 1, 0);
	Vector3 playPos = stage->player->position;
	Vector3 endPos(playPos.x, playPos.y + 20.0f, playPos.z);
	Matrix34 identity;
	
	if ((input.deltaAccel / 20) > 0) gfx::EasyRender3D::SetColor(hel::common::Color::RED);
	else if ((input.deltaAccel / 20) < 0) gfx::EasyRender3D::SetColor(hel::common::Color::GREEN);
	else gfx::EasyRender3D::SetColor(hel::common::Color::BLUE);
	
	gfx::EasyRender3D::DrawLine(input.visualRotation, playPos, endPos, 3.0f);
	GXSetZMode(1, 3, 1);	
}

void Chowder::preDraw()
{
	stage->preDraw(*modelRoot);
	Vector3 playerPos = stage->player->position;
	// create lightset
	g3d::LightSetAccessor lightSet = modelRoot->lightSet(0);
	
	nw4r::g3d::LightObj lobj;
	lobj.Clear();
	// curiously, the light won't render unless 0x3 is 5
	// this phenomenon can be seen in base rtdl as well. strange!
	lobj.InitLightColor(hel::common::Color::WHITE);
	lobj.InitLightPos(0.0f + playerPos.x, 700.0f + playerPos.y, -100.0f + playerPos.z);
	lobj.InitLightDir(-1.0f, 0.0f, 0.0f);
	lobj.InitLightAttnA(1.0f, 0.0f, 0.0f);
	lobj.InitLightAttnK(1.0f, 0.0f, 0.0f);
	
	lobj.unk = 5;
	lightSet.setLightObj(0, lobj);
}

void Chowder::draw()
{
	if (!paused)
	{
		modelRoot->sceneCalcOnDraw();
		modelRoot->sceneDrawOpa();
		fStar.updateAndDraw(*modelRoot);
		hud.draw();
		//drawDebug();
	}
	else pause.draw();
}
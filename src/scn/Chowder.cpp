#include "scn/Chowder.h"
#include "gfx/gfx.h"
#include "common/Color.h"
#include "common/ExplicitSingleton.h"
#include "scn/game/PlayerController.h"
#include "mem/Memory.h"
#include "file/FileAccessor.h"

Chowder *engineSingleton;
// turn into method function
void adjustScreen(g3d::CameraAccessor& camera)
{
	using namespace hel::math;
	const _GXRenderModeObj *rmode = &hel::common::ExplicitSingleton<gfx::VISetting>::object->rmode;
	
	float aspect_ratio;
	if (rmode->fbWidth == 608) aspect_ratio = camera.getProjAspect();
	else aspect_ratio = (16.0f/9.0f);
	
	float far = camera.getProjFar();
	float near = camera.getProjNear();
	float fov = camera.getProjFovy();
	
	camera.setProjPerspective(fov, aspect_ratio, 0.1, 3000);
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
	secondRoot = new g3d::Root(rootContext);
	
	this->stage = new scn::roll::StageController(*this);
	//debugAddTriangles(*stage);
	file::FileAccessor file("gcn/MAIN.roll", false);
	if (file.isLoaded()) 
	{
		file::FileData stage_data = file.block();
		stage->CreateStage(stage_data);
	}
	
	// note: move to stage controller object and/or abstract
	g3d::LightSetAccessor lightSet = modelRoot->lightSet(0);
	lightSet.disableLightObjAll();
	lightSet.enableAmbientLightObj(0);
	lightSet.enableLightObj(0, 0);
	
	nw4r::g3d::AmbLightObj ambColor = {{255, 255, 255, 255}};
	lightSet.setAmbientLightObj(ambColor);
	
	score = 0;
	time = 300;
	stars = 0;
	
	paused = false;
	can_pause = true;
	held_start = false;
	stopUpdatingInputs = true;
	enableTime = false;
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
	if (!stopUpdatingInputs) input.Update( obtainWiimoteRotation(0.25f) );
	if ( (input.buttons & WPAD_BUTTON_PLUS) == 0) held_start = false;
	if (!paused)
	{
		modelRoot->sceneClear();
		
		stage->gameRotation = input.physicsRotation;
		stage->visualRotation = input.visualRotation;
		stage->Update();
		cam.update();
		checkPause();
			
		if (time)
		{
			subTimer++;
			if (subTimer == 60)
			{
				time--;
				subTimer = 0;
				
				if (!time) stage->player->setState(PLAYER_DEAD);
			}
		}
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
	lobj.InitLightPos(cam.position.x, cam.position.y, playerPos.z);
	
	Vector3 camVector = (cam.position - playerPos);
	camVector.normalize();
	
	lobj.InitLightDir(camVector.x, camVector.y, camVector.z);
	lobj.InitLightAttnA(1.0f, 0.0f, 0.0f);
	lobj.InitLightAttnK(1.0f, 0.0f, 0.0f);
	
	lobj.unk = 5; // note: i still have no idea what this member does
	lightSet.setLightObj(0, lobj);
}

void Chowder::draw()
{
	if (!paused)
	{
		sky.draw();
		g3d::CameraAccessor fCam = modelRoot->currentCamera();
		g3d::CameraAccessor sCam = secondRoot->currentCamera();
		adjustScreen(fCam);
		adjustScreen(sCam);
		
		modelRoot->sceneCalcOnDraw();
		modelRoot->sceneDrawOpa();
		
		gfx::Utility::ClearZBuffer(1.0f);
		secondRoot->sceneCalcOnDraw();
		secondRoot->sceneDrawOpa();
		
		fStar.updateAndDraw(*modelRoot);
		hud.draw();
	}
	else pause.draw();
}
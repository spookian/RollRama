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
	g3d::RootContext sndContext( *g3d::ModelContext::DefaultAllocator(), 75, 64, 8, 1);
	
	modelRoot = new g3d::Root(rootContext);
	starRoot = new g3d::Root(sndContext);
	secondRoot = new g3d::Root(rootContext);
	
	this->stage = new scn::roll::StageController();
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
	
	nw4r::g3d::AmbLightObj ambColor = hel::common::Color::WHITE;
	lightSet.setAmbientLightObj(ambColor);
	
	score = 0;
	time = 300;
	stars = 0;
	
	paused = false;
	state = 0;
	stateTimer = 0;
	isEnd = false;
	enableTimer = false;
	fStar.activate(0.0f, 1.0f, 30);
	
	g3d::CameraAccessor fCam = modelRoot->currentCamera();
	g3d::CameraAccessor sCam = secondRoot->currentCamera();
	g3d::CameraAccessor tCam = starRoot->currentCamera();
	adjustScreen(fCam);
	adjustScreen(sCam);
	adjustScreen(tCam);
	
	snd::SoundManager::object()->bgm().start(0x617);
}

Chowder::~Chowder()
{
	delete stage;
	delete modelRoot;
	delete secondRoot;
	
	snd::SoundManager::object()->bgm().stop();
}

void Chowder::checkPause()
{
	if ((input.buttons & WPAD_BUTTON_PLUS & ~(input.buttons_held)) && (state == 2) )
	{
		paused = true;
		pause.activate();
	}
	return;
}

void Chowder::updateMain() // update physics and setup drawing
{
	switch (state)
	{
		case 0: // start
		if (fStar.finished)
		{
			if (stateTimer >= 60)
			{
				state = 1;
				fStar.activate(1.0f, 6.0f, 60);
			}
			stateTimer++;
		}
		break;
		
		case 1:
		if (fStar.finished) 
		{
			state = 2;
			enableTimer = true;
		}
		break;
		
		case 2: // normal play
		input.Update( obtainWiimoteRotation(0.25f) );
		break;
		
		case 3: // death reset beginning
		state = 4;
		fStar.activate(6.0, 0.0, 120);
		break;
		
		case 4: // death reset end
		if (fStar.finished)
		{
			stage->reset();
			fStar.activate(0.0f, 1.0f, 30);
			stateTimer = 0;
			
			score = 0;
			time = 300;
			stars = 0;
			
			state = 0;
			snd::SoundManager::object()->bgm().start(0x617);
			stage->pauseForPlayerObject = false;
		}
		break;
		
		case 6: // game ending
		enableTimer = false;
		if (fStar.finished)
		{
			isEnd = true;
		}
		break;
		
		default:
		break;
	}
	
	if (!paused)
	{
		modelRoot->sceneClear();
		starRoot->sceneClear();
		secondRoot->sceneClear();
		
		stage->gameRotation = input.physicsRotation;
		stage->visualRotation = input.visualRotation;
		stage->Update();
		cam.update();
		checkPause();
			
		if (time && enableTimer)
		{
			subTimer++;
			if (subTimer == 120)
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
		gfx::Utility::ClearZBuffer(1.0f);
		
		modelRoot->sceneCalcOnDraw();
		modelRoot->sceneDrawOpa();
		
		starRoot->sceneCalcOnDraw();
		starRoot->sceneDrawOpa();
		
		gfx::Utility::ClearZBuffer(1.0f);
		secondRoot->sceneCalcOnDraw();
		secondRoot->sceneDrawOpa();
		
		fStar.updateAndDraw(*modelRoot);
		hud.draw();
	}
	else pause.draw();
	

}
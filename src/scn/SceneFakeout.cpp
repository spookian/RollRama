#include "allocate.h"
#include "scn/IScene.h"
#include "scn/SceneFakeout.h"
#include "gfx/GXStructs.h"
#include "gfx/GXReimplementation.h"

namespace scn
{
	void SceneFakeout::rtti()
	{
		return;
	}
	
	SceneFakeout::SceneFakeout()
	{
		*(unsigned long*)(0x808c52c0) = 0x000000ff; // I'm not going to tell you what these magic numbers are for, nerd.
		// initialize root object
		isEnd = false;
		return;
	}
	
	SceneFakeout::~SceneFakeout()
	{
		*(unsigned long*)(0x808c52c0) = 0x808080ff;
		return;
	}
	
	void SceneFakeout::updateMain()
	{
		return;
	}
	
	void SceneFakeout::updateUseGPU()
	{
		return;
	}
	
	void SceneFakeout::updateDebug()
	{
		return;
	}
	
	void SceneFakeout::draw(const DrawReqInfo& info)
	{
		console.setPosition( GLYPH_XPOS(3), GLYPH_YPOS(1) );
		console.printString("fuuuuuuuck i'm so fucking freakyyyyy\ni need someone to \x02\xff\x00\x00\xfftouch my controller");
		return;
	}
	
	bool SceneFakeout::isSceneEnd() const
	{
		return isEnd;
	}
}
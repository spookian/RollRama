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
		console.setPosition( GLYPH_XPOS(3), GLYPH_YPOS(1) );
		*(unsigned long*)(0x8017ffac) = 0x4e800020; // fun is infinite
		*(unsigned long*)(0x808c52c0) = 0x000000ff; 

		isEnd = false;
		messageIdx = 0;
		return;
	}
	
	SceneFakeout::~SceneFakeout()
	{
		*(unsigned long*)(0x8017ffac) = 0x9421ffd0;
		*(unsigned long*)(0x808c52c0) = 0x808080ff;
		return;
	}
	
	void SceneFakeout::updateMain()
	{
		const MessageNode* cur_node = &messageTable[messageIdx];
		if ((timer >= cur_node->time) && (cur_node->time >= 0))
		{
			timer = 0;
			do {
				drawList.append(cur_node->string);
				messageIdx++;
				cur_node++; // risky pointer arithmetic
			} while (cur_node->time == 0);
			
			if (cur_node->time == -1) drawList.append(cur_node->string);
		}
		timer++;
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
		console.setCursor(0, 0);
		for (int i = 0; i < drawList.getSize(); i++)
		{
			console.printString(drawList[i]);
		}
		return;
	}
	
	bool SceneFakeout::isSceneEnd() const
	{
		return isEnd;
	}
}
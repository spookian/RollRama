#include "seq/ISequence.h"
#include "seq/SequenceTiltStart.h"

#include "scn/IScene.h"
#include "scn/SceneStart.h"
#include "scn/SceneTitle.h"
#include "scn/SceneResult.h"

#include "std/auto_ptr.h"
#include "allocate.h"

namespace seq
{
	SequenceTiltStart::SequenceTiltStart()
	{
		mode = MENU;
	}
	
	SequenceTiltStart::~SequenceTiltStart()
	{
	}
	
	long SequenceTiltStart::nextAction() const
	{
		return 2;
	}

	std::auto_ptr<ISequence> SequenceTiltStart::createChildSequence() const
	{
		std::auto_ptr<ISequence> result(new SequenceTiltStart());
		return result;
	}
	
	void SequenceTiltStart::onChildSequenceEnd() 
	{
		return;
	}
	
	std::auto_ptr<scn::IScene> SequenceTiltStart::createScene() const
	{
		scn::IScene* scene;
		switch(mode)
		{
			case FAKE_START:
			break;
			
			case MENU:
			scene = new scn::SceneTitle();
			break;
			
			case GAMEPLAY:
			scene = new scn::SceneStart();
			break;
			
			case END_CREDITS:
			scene = new scn::SceneResult();
			break;
		}
		std::auto_ptr<scn::IScene> result(scene);
		return result;
	}
	
	void SequenceTiltStart::onSceneEnd(scn::IScene& scene)
	{
		mode++;
		return;
	}
}


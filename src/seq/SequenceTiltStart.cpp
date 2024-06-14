#include "seq/ISequence.h"
#include "seq/SequenceTiltStart.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"
#include "scn/SceneFakeout.h"
#include "std/auto_ptr.h"
#include "allocate.h"

namespace seq
{
	SequenceTiltStart::SequenceTiltStart()
	{
		mode = GAMEPLAY;
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
			scene = new scn::SceneFakeout();
			
			case MENU:
			break;
			
			case GAMEPLAY:
			scene = new scn::SceneStart();
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


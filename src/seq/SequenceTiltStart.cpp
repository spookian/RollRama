#include "ISequence.h"
#include "SequenceTiltStart.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"
#include "std/auto_ptr.h"
#include "allocate.h"

namespace seq
{
	~SequenceTiltStart()
	{
	}
	
	long SequenceTiltStart::nextAction() const
	{
		return 2;
	}

	std::auto_ptr<ISequence> createChildSequence() const
	{
		auto_ptr<ISequence> result(new SequenceTiltStart());
		return result;
	}
	
	void onChildSequenceEnd() 
	{
		return;
	}
	
	std::auto_ptr<scn::IScene> createScene() const
	{
		auto_ptr<scn::IScene> result(new SceneStart());
		return result;
	}
	
	void onSceneEnd(scn::IScene& scene)
	{
		return;
	}
}


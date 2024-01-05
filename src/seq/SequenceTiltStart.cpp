#include "seq/ISequence.h"
#include "seq/SequenceTiltStart.h"
#include "scn/IScene.h"
#include "scn/SceneStart.h"
#include "std/auto_ptr.h"
#include "allocate.h"

namespace seq
{
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
		scn::SceneStart *scene = new scn::SceneStart();
		std::auto_ptr<scn::IScene> result(scene);
		return result;
	}
	
	void SequenceTiltStart::onSceneEnd(scn::IScene& scene)
	{
		return;
	}
}


#pragma once

#include "seq/ISequence.h"
#include "std/auto_ptr.h"

namespace seq
{
	enum TiltSequenceMode
	{
		FAKE_START,
		MENU,
		GAMEPLAY,
		END_CREDITS
	};

	class SequenceTiltStart : public ISequence
	{
		int mode;
	public:
		SequenceTiltStart();
		~SequenceTiltStart();
		long nextAction() const;
		std::auto_ptr<ISequence> createChildSequence() const;
		void onChildSequenceEnd();
		std::auto_ptr<scn::IScene> createScene() const;
		void onSceneEnd(scn::IScene& scene);
	};
}
#pragma once

#include "seq/ISequence.h"
#include "std/auto_ptr.h"

namespace seq
{
	enum TiltSequenceMode
	{
		FAKE_START,
		GAMEPLAY,
		END_CREDITS
	};

	class SequenceTiltStart : public ISequence
	{
	public:
		~SequenceTiltStart();
		long nextAction() const;
		std::auto_ptr<ISequence> createChildSequence() const;
		void onChildSequenceEnd();
		std::auto_ptr<scn::IScene> createScene() const;
		void onSceneEnd(scn::IScene& scene);
	};
}
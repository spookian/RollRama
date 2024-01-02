#pragma once

#include "ISequence.h"
#include "std/auto_ptr.h"

namespace seq
{
	class SequenceTiltStart : ISequence
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
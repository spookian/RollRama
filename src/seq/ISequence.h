#pragma once

#include "std/auto_ptr.h"
#include "scn/IScene.h"

namespace seq
{
	class ISequence
	{
	public:	
		virtual void rtti() {}
		virtual ~ISequence() {}
		virtual long nextAction() const 								= 0;
		virtual std::auto_ptr<ISequence> createChildSequence() const 	= 0;
		virtual void onChildSequenceEnd()		 						= 0;
		virtual std::auto_ptr<scn::IScene> createScene() const 			= 0;
		virtual void onSceneEnd(scn::IScene& scene) 					= 0;
		
		void* operator new(unsigned long); // __nw__Q23seq9ISequenceFUl
	};
}
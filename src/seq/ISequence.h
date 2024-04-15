#pragma once

#include "std/auto_ptr.h"
#include "scn/IScene.h"

namespace seq
{
	class ISequence
	{
	public:	
		virtual void rtti() {}
		// we don't do that stuff here
		virtual ~ISequence() {}
		virtual long nextAction() const 								= 0; 
		/* nextAction return values and what they do
			return 0 - the sequence restarts.
			return 1 - a child sequence is created. createChildSequence() is then called.
			return 2 - the game creates a scene using createScene() and loops through the newly created scene until it ends. then it calls this object's nextAction() method once again.
			return 3 - unknown.
		*/
		virtual std::auto_ptr<ISequence> createChildSequence() const 	= 0;
		virtual void onChildSequenceEnd()		 						= 0;
		virtual std::auto_ptr<scn::IScene> createScene() const 			= 0;
		virtual void onSceneEnd(scn::IScene& scene) 					= 0;
		
		void* operator new(unsigned long); // __nw__Q23seq9ISequenceFUl
	};
}
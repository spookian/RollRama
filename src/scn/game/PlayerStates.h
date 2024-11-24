#pragma once
#include "g3d/Model.h"

namespace scn
{
	namespace roll 
	{
		class PlayerController;
		
		struct PlayerState
		{
			PlayerController* player;
			
			PlayerState();
			virtual void update();
			virtual void updateModel(g3d::Root& root);
		};
		
		struct StateNormal : public PlayerState
		{
			StateNormal();
			void update();
		};
		
		struct StateFloat : public PlayerState
		{
			unsigned long timer;
			StateFloat();
			void update();
		};
		
		struct StateCapture : public PlayerState
		{
			StateCapture();
		};
		
		struct StateIntro : public PlayerState
		{
			unsigned long phase; // state.
			unsigned long timer;
			
			StateIntro();
			void update();
		};
		
		struct StateFinish : public PlayerState
		{
			StateFinish();
			void update();
		};
	}
}
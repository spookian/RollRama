#pragma once
#include "g3d/Model.h"

namespace scn
{
	namespace roll 
	{
		class PlayerController;
		
		struct PlayerState
		{
			PlayerController *player;
			PlayerState(PlayerController *player);
			virtual void update();
			virtual void updateModel(g3d::Root& root);
		};
		
		struct StateNormal : public PlayerState
		{
			StateNormal(PlayerController *player);
			void update();
		};
		
		struct StateFloat : public PlayerState
		{
			unsigned long timer;
			StateFloat(PlayerController *player);
			void update();
		};
		
		struct StateCapture : public PlayerState
		{
			StateCapture(PlayerController *player);
		};
		
		struct StateIntro : public PlayerState
		{
			unsigned long phase; // state.
			unsigned long timer;
			
			StateIntro(PlayerController *player);
			void update();
		};
		
		struct StateFinish : public PlayerState
		{
			StateFinish(PlayerController *player);
			void update();
		};
	}
}
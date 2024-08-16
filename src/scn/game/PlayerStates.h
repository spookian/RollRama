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
			virtual void Update() {}
			virtual void UpdateModel(g3d::Root& root) {}
		};
		
		struct StateNormal : public PlayerState
		{
			StateNormal(PlayerController& player);
			void Update();
		};
		
		struct StateFloat : public PlayerState
		{
			unsigned long timer;
			StateFloat(PlayerController& player);
			void Update();
		};
	}
}
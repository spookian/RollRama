#pragma once
#include "g3d/Model.h"
#include "math/math.h"

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
			virtual void updateModel();
		};
		
		struct StateNormal : public PlayerState
		{
			StateNormal(PlayerController *player);
			~StateNormal();
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
		
		struct StateDeath : public PlayerState
		{
			int timer;
			bool enable;
			hel::math::Vector3 deathPosition;
			
			StateDeath(PlayerController *player);
			void update();
			void updateModel();
		};
		
		struct StateAirlock : public PlayerState
		{
			StateAirlock(PlayerController *player);
			void update();
		};
		
		struct StateIntro : public PlayerState
		{
			unsigned long phase; // state machine
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
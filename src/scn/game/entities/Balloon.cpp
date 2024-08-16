#include "scn/game/Pickup.h"
#include "g3d/Model.h"
#include "scn/Chowder.h"
#include "math/math.h"
#include "g3d/ResFileHelper.h"

#define BALLOON_POINTS 300
#define BLOWUP_TIME 35.0f
#define POP_TIME 17.5f;

const GlobalObject<const hel::math::Vector3, float> scale = { {30.0f, 30.0f, 30.0f} };

enum BalloonStates
{
	BALLOON_APPEAR,
	BALLOON_IDLE,
	BALLOON_DISAPPEAR
};

namespace scn
{
	namespace roll
	{
		Balloon::Balloon(const Vector3& position, bool __bossFight)
		{
			bossFight = __bossFight;
			this->position = position;
			state = BALLOON_APPEAR;
		}
		
		Balloon::~Balloon()
		{
			delete model;
		}
		
		void Balloon::Update()
		{
			switch(state)
			{
				case BALLOON_APPEAR
				{
					model->SetScale( scale * (time / BLOWUP_TIME) )
					if (time >= BLOWUP_TIME)
					{
						time = 0;
						state = BALLOON_IDLE;
						model->SetScale(scale);
					}
					break;
				}
				
				case BALLOON_IDLE
				{
					if (isCollides( *(SphereCollider*)engineSingleton->stage->player ))
					{
						engineSingleton->stage->player->Powerup(bossFight);
					}
					// do a little floaty squishy animation
					break;
				}
				
				case BALLOON_DISAPPEAR:
				active = false;
				break;
			}
			time++;
		}
		
	}
}
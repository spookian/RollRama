#pragma once
#include "common/List.h"
#include "lyt/lyt.h"
#include "app/app.h"
#include "hid/hid.h"
#include "math/Math.h"
#include "scn/game/PhysicsConstants.h"

#define PTCL_DIE_TIME 300
#define PTCL_SPAWN_TIME 30

using namespace hel::math;
namespace scn
{
	struct Particle
	{
		hel::math::Vector3 position;
		hel::math::Vector3 velocity;
		lyt::Layout layout;
		int lifeTime;
		
		bool enable;
		 // snowflakes
		Particle() : layout( lyt::LayoutContext::quickContext("gcntitle/GCNTitle", "Snowflake") )
		{
			velocity.y = -60.0f;
			layout.adjustFor4b3();
			position.y = 234.0f;
			lifeTime = 0;
			enable = true;
		}
		
		void update()
		{
			if (position.y < -234.0f) enable = true;
			if (position.x < -422.0f) position.x += 844.0f;
			if (position.x > 422.0f) position.x -= 844.0f;
			
			RotationResult r = obtainWiimoteRotation(0.0f);
			
			Vector3 tilt(-r.vector.z * 60.0f, 0.0f, 0.0f);
			position = position + (velocity + tilt) * DELTATIME;
			
			layout.paneByName("P_pict").setTrans(position);
			layout.updateMatrix();
			lifeTime++;
		}
		
		void draw()
		{
			layout.draw();
		}
	};
	
	class ParticleManager
	{
		hel::common::List<Particle*> ptclList;
		int spawnTimer;
	public:
		ParticleManager()
		{
			spawnTimer = 0;
		}
	
		~ParticleManager()
		{
			for (int i = 0; i < ptclList.getSize(); i++)
			{
				delete ptclList[i];
			}
			ptclList.clear();
		}
	
		void updateAndDraw()
		{
			if (spawnTimer >= PTCL_SPAWN_TIME)
			{
				Particle *p = new Particle();
				p->position.x = app::Random::Obj().RandF32(-1.0f, 1.0f) * 416;
				ptclList.append(p);
				spawnTimer = 0;
			}
				
			for (int i = 0; i < ptclList.getSize(); i++)
			{
				if (ptclList[i]->enable)
				{
					ptclList[i]->update();
					ptclList[i]->draw();
				}
				else
				{
					delete ptclList[i];
					ptclList.remove(i);
					i--;
				}
			}
			spawnTimer++;
		}
	};
}
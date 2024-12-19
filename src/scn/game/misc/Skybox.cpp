#include "scn/game/misc/Skybox.h"

namespace scn
{
	namespace roll
	{
		Skybox::Skybox() : sky( lyt::LayoutContext::quickContext("gcnstep/StageBackground", "Background") )
		{
			timer = 0;
		}
		
		void Skybox::draw()
		{
			lyt::Utility::SetupGX();
			
			sky.updateMatrix();
			sky.draw();
		}
	}
}
#include "scn/game/misc/Skybox.h"
#include "gfx/gfx.h"
#include "scn/Chowder.h"
#include "g3d/Model.h"
#include "math/Math.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		Skybox::Skybox() : sky( lyt::LayoutContext::quickContext("gcnstep/StageBackground", "Background") )
		{
			timer = 0;
			sky.adjustFor4b3();
		}
		
		void Skybox::draw()
		{
			lyt::Utility::SetupGX(); // too lazy to disable z buffer myself so i'll let my lackey function do it
			//g3d::CameraAccessor cam = engineSingleton->modelRoot->currentCamera();
			//Matrix44 perspectiveMatrix = Matrix44::CreatePerspective(40.0f, cam.getProjAspect(), 0.1, 1000);
			//gfx::EasyRender3D::SetupGX(perspectiveMatrix, true);
			
			//Vector3 p(0.0f, 0.0f, -700.0f);
			//sky.rootPane().setTrans(p);
			
			sky.updateMatrix();
			sky.draw();
		}
	}
}
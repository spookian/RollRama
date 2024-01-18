#include "scn/AmigaDemo.h"
#include "g3d/Model.h"
#include "math/Matrix34.h"
#include "math/Vector3.h"

namespace scn
{
	
	AMIGADemo::AMIGADemo(g3d::CharaModel* _sphere, g3d::CameraAccessor* _cam)
	{
		camera.unk = _cam->unk;
		sphere = _sphere;
		
		hel::math::Vector3 cameraPos(0.0f, -1.0f, 3.0f);
		hel::math::Vector3 up(0.0f, 1.0f, 0.0f);
		hel::math::Vector3 zero(0.0f, -1.0f, 0.0f);
		
		hel::math::Matrix34 viewMat = hel::math::Matrix34::CreateLookAt(cameraPos, up, zero);
		camera.setViewMtx(viewMat);
		
		sphereVelocity.x = 0.0125;
		turnAround = 1.0f;
	}
	
	void AMIGADemo::updateMain()
	{
		sphereVelocity.y -= 0.003125f;
		
		hel::math::Vector3 initRot(0.0f, 0.0f, -30.0f);
		hel::math::Matrix34 initSphereRot = hel::math::Matrix34::CreateRotXYZDeg(initRot);
		hel::math::Matrix34 actualSphereRot = hel::math::Matrix34::CreateRotXYZDeg(sphereAngles);
		
		hel::math::Matrix34 sphereTranslation = hel::math::Matrix34::CreateTrans(spherePosition);
		
		sphere->setModelRTMtx(sphereTranslation * (initSphereRot * actualSphereRot));
		sphere->updateWorldMtx();
		
		sphereAngles.y += (2.5f * turnAround);
		spherePosition += sphereVelocity;
		if (spherePosition.y <= -2.0f)
		{
			spherePosition.y = -2.0f;
			sphereVelocity.y = 0.1f;
		}
		
		if (spherePosition.x > 1.5f)
		{
			spherePosition.x = 1.5f;
			sphereVelocity.x = -sphereVelocity.x;
			turnAround = 1.0f;
		}
		else if (spherePosition.x < -1.5f)
		{
			spherePosition.x = -1.5f;
			sphereVelocity.x = -sphereVelocity.x;
			turnAround = -1.0f;
		}
		
		return;
	}
	
	void AMIGADemo::registerToRoot(g3d::Root& root)
	{
		sphere->registerToRoot(root);
		return;
	}
}
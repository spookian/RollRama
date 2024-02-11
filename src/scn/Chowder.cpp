#include "g3d/Model.h"
#include "math/Vector3.h"
#include "gfx/EasyRender3D.h"
#include "math/Matrix44.h"
#include "math/Matrix34.h"
#include "scn/Chowder.h"

Triangle::Triangle(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2, const hel::math::Vector3& normal)
{
	this->v0 = v0;
	this->v1 = v1;
	this->v2 = v2;
	this->normal = normal;
	
	hel::math::Vector3 dvec((v0.x + v1.x + v2.x)/3.0f * normal.x, (v0.y + v1.y + v2.y)/3.0f * normal.y, (v0.z + v1.z + v2.z)/3.0f * normal.z); // ax + by + cz = d
	this->d = dvec.x + dvec.y + dvec.z;
	this->flags = 0;
	
	return;
}

Chowder::Chowder(g3d::CameraAccessor *cam, g3d::CharaModel *player)
{
	camera.unk = cam->unk;
	playerModel = player;

	hel::math::Vector3 cameraPos(0.0f, 0.0f, -50.0f);
	hel::math::Vector3 up(0.0f, 1.0f, 0.0f);
	hel::math::Vector3 zero;
		
	hel::math::Matrix34 viewMat = hel::math::Matrix34::CreateLookAt(cameraPos, up, zero);
	camera.setViewMtx(viewMat);
}

void Chowder::updateMain()
{
	return;
}

void Chowder::SetupEasyRender3D()
{
	float far = camera.getProjFar();
	float near = camera.getProjNear();
	float aspect_ratio = camera.getProjAspect();
	float fov = camera.getProjFovy();
	
	hel::math::Matrix44 perspective_matrix = hel::math::Matrix44::CreatePerspective(fov, aspect_ratio, near, far);
	hel::math::Matrix34 view_matrix = camera.viewMtx();
	
	gfx::EasyRender3D::SetupGX(perspective_matrix, true);
	gfx::EasyRender3D::SetViewMtx(view_matrix);
	
	GXSetZMode(1, 3, 1);
	
	/* According to Libogc/Devkitpro (which may or may not be illegally obtained but no one could prove it), their GX_SetZMode() function has three arguments:
	* u8 enable - a char (possibly boolean?) that enables the zbuffer
	* u8 func - an unsigned char that tells the gx what function to use for z comparisons
	* u8 update_enable - enables z-buffer updates when true;
	*
	* With that in mind, it would be best to use this function with the default settings found in RtDL's __GXInitGX()
	*/
	return;
}

void Chowder::DrawTriangleWireframe(const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2)
{
	GXSetZMode(0, 1, 0); // ignore z buffer LMFAAAAO
	
	hel::math::Matrix34 basicMtx; // identity matrix; holds no transforms
	gfx::EasyRender3D::DrawLine(basicMtx, v0, v1, 3.0f);
	gfx::EasyRender3D::DrawLine(basicMtx, v1, v2, 3.0f);
	gfx::EasyRender3D::DrawLine(basicMtx, v2, v0, 3.0f);
	
	GXSetZMode(1, 3, 1); // restore z comparisons
	return;
}

void Chowder::drawDebug()
{
	SetupEasyRender3D();
	_GXColor red = {255, 0, 0, 255};
	gfx::EasyRender3D::SetColor(red);
	
	hel::math::Vector3 v0(-24.0f, -20.0f, 0.0f);
	hel::math::Vector3 v1(0.0f, 15.0f, 0.0f);
	hel::math::Vector3 v2(30.0f, -10.0f, 0.0f);
	
	DrawTriangleWireframe(v0, v1, v2);
}
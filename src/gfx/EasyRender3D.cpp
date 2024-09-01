#include "gfx/EasyRender3D.h"
#include "gfx/TexBuffer.h"
#include "gfx/GX.h"
#include "math/Math.h"

using namespace hel::math;

namespace gfx
{
	void EasyRender3D::DrawTriangleWireframe(const Matrix34 tfMatrix, const Vector3& v0, const Vector3& v1, const Vector3& v2)
	{
		GXSetZMode(0, 1, 0); // ignore z buffer LMFAAAAO
		
		gfx::EasyRender3D::DrawLine(tfMatrix, v0, v1, 3.0f);
		gfx::EasyRender3D::DrawLine(tfMatrix, v1, v2, 3.0f);
		gfx::EasyRender3D::DrawLine(tfMatrix, v2, v0, 3.0f);
		
		GXSetZMode(1, 3, 1); // restore z comparisons
		return;
	}
	
	// wip function for easy textured quad drawing
	void EasyRender3D::DrawTexturedQuad(const Matrix34& modelMat, const Vector3& v0, const Vector3& v1, const Vector3& v2, const Vector3& v3, const GXTexObj& texture)
	{
		//t_loadPosMtx(modelMat);
		
		//GXBegin();
	}
}
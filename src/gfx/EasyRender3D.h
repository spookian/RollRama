#pragma once
#include "math/Vector3.h"
#include "math/Matrix34.h"
#include "math/Matrix44.h"
#include "gfx/GXStructs.h"
#include "gfx/TexBuffer.h"

extern "C"
{
	extern void GXSetZMode(unsigned char unk0, unsigned long unk1, unsigned long unk2); // definition taken from doldecomp melee repo
}

namespace gfx
{
	class EasyRender3D
	{
	public:
		static void DrawQuadFill(const hel::math::Matrix34& worldmtx, const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2, const hel::math::Vector3& v3);
		static void DrawLine(const hel::math::Matrix34& worldmtx, const hel::math::Vector3& start, const hel::math::Vector3& end, float line_width);
		static void SetViewMtx(const hel::math::Matrix34& viewmtx);
		static void SetupGX(const hel::math::Matrix44& perspective, bool unk); // unk is usually true?
		static void SetColor(const _GXColor& color);
		static void DrawTriangleWireframe(const hel::math::Matrix34 tfMatrix, const hel::math::Vector3& v0, const hel::math::Vector3& v1, const hel::math::Vector3& v2);
		static void DrawTexturedQuad(const hel::math::Matrix34&, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&, const hel::math::Vector3&, const GXTexObj&);
	};
}
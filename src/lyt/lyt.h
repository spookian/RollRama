#pragma once
#include "mem/Memory.h"
#include "math/math.h"
#include "gfx/gfx.h"
#include "g3d/Model.h"
#include "common/ExplicitSingleton.h"
#include "defines.h"

#define EVILNUMBER (832.0f / 608.0f)

enum PaneVertices
{
	UPPER_LEFT,
	UPPER_RIGHT,
	LOWER_LEFT,
	LOWER_RIGHT
};

namespace lyt
{
	class LayoutContext
	{
		SET_OBJECT_SIZE(0x74);
	public:
		LayoutContext(const char* arcFilePath, const char* subFilePath, mem::IAllocator& allocator);
		// subfilepath takes brlyts only, and no file endings
		inline static LayoutContext quickContext(const char *arcFile, const char *subFile)
		{
			mem::IAllocator* defAllocator = g3d::ModelContext::DefaultAllocator();
			LayoutContext context(arcFile, subFile, *defAllocator);
			return context;
		}
	};
	
	class PaneAccessor
	{
		SET_OBJECT_SIZE(0x10);
		unsigned long panePtr;
	public:
		~PaneAccessor();
		
		void setText(const char* text) const;
		void setTrans(const hel::math::Vector3& transform) const;
		void setVisibility(bool visible) const;
		void setScale(const hel::math::Vector2& scale) const;
		void setSize(const hel::math::Vector2& size) const;
		void setAlpha(unsigned char alpha) const;
		
		void setVertexColor(_GXColor& col, int idx)
		{
			*reinterpret_cast<unsigned long*>(panePtr + 0xD8 + (idx << 2)) = *reinterpret_cast<unsigned long*>(&col); // this is insanely evil.
		}
		
		void setUV(float scaleX, float scaleY, float rotation, float transX, float transY)
		{
			float* UVs = reinterpret_cast<float*>(panePtr + 0x1d8);
			UVs[0] = transX;
			UVs[1] = transY;
			UVs[2] = rotation;
			UVs[3] = scaleX;
			UVs[4] = scaleY;
		}
		
		void setTexCoords(float u, float v, int idx)
		{
			float* texCoords = reinterpret_cast<float*>( panePtr + 0x100 + (idx << 3) );
			texCoords[0] = u;
			texCoords[1] = v;
			// note: texcoords aren't uvs, i just used them as convenient argument names. the y component of a text coord starts at the top unlike uvs
		}
		
		void show() const;
	};
	
	class Layout
	{
		//suspected to be 0xCC bytes, or 204 bytes long
		SET_OBJECT_SIZE(0x190);
	public:
		Layout(const LayoutContext& cntxt);
		Layout() {}
		
		~Layout();
		void draw() const;
		PaneAccessor paneByName(const char *name);
		PaneAccessor rootPane();
		
		void updateMatrix();
		void adjustFor4b3()
		{
			const _GXRenderModeObj *rmode = &hel::common::ExplicitSingleton<gfx::VISetting>::object->rmode;
			if (rmode->fbWidth == 608)
			{
				hel::math::Vector2 warningScale;
				warningScale.x = EVILNUMBER;
				warningScale.y = 1.0f;
				rootPane().setScale(warningScale);
			}
		}
	};
	
	class Utility
	{
	public:
		static void SetupGX(); 
	};
}
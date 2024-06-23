#pragma once
#include "mem/Memory.h"
#include "math/math.h"
#include "gfx/gfx.h"
#include "g3d/Model.h"
#include "common/ExplicitSingleton.h"
#include "defines.h"

#define EVILNUMBER (832.0f / 608.0f)

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
	
	class MaterialAccessor
	{
	public:
		
	};
	
	class PaneAccessor
	{
		SET_OBJECT_SIZE(0x14);
	public:
		~PaneAccessor();
		
		void setText(const char* text) const;
		void setTrans(const hel::math::Vector3& transform) const;
		void setVisibility(bool visible) const;
		void setScale(const hel::math::Vector2& scale) const;
		void setSize(const hel::math::Vector2& size) const;
		void setAlpha(unsigned char alpha) const;
		
		void show() const;
		MaterialAccessor material();
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
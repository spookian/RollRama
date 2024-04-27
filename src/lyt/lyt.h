#pragma once
#include "mem/Memory.h"
#include "math/math.h"

namespace lyt
{
	class LayoutContext
	{
		LayoutContext(const char* arcFilePath, const char* subFilePath, mem::IAllocator& allocator);
		// subfilepath takes brlyts only, and no file endings
	};
	
	class PaneAccessor
	{
		~PaneAccessor();
		
		void setText(const char* text) const;
		void setTrans(const hel::math::Vector3& transform) const;
		void setVisibility(bool visible) const;
		void setScale(const hel::math::Vector2& scale) const;
		void setSize(const hel::math::Vector2& size) const;
		
		bool show() const;
	};
	
	class Layout
	{
		//suspected to be 0xCC bytes, or 204 bytes long
	public:
		Layout(const LayoutContext& cntxt);
		~Layout();
		void draw() const;
	};
}
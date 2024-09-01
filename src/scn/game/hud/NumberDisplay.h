#pragma once
#include "lyt/lyt.h"
#include "gfx/gfx.h"
#include "math/math.h"

#define NUMBER_UV_SCALE (60.0f/64.0f)
#define NUMBER_TEXCOORD_SHIFT (34.0f / 352.0f)
#define NUMBER_TEXCOORD_ORIGINLEFT (4.0f / 352.0f)
#define NUMBER_TEXCOORD_ORIGINRIGHT (36.0f / 352.0f)

const GlobalObject<const hel::math::Vector3, float> averageShift = {{ 34.0, 0.0, 0.0 }};

// review code; something's happening that's causing it to crash
namespace scn
{
	namespace roll
	{
		struct NumberDisplay
		{
			lyt::Layout *numberLayout;
			hel::math::Vector2 scale;
			
			_GXColor top;
			_GXColor bottom;
		
			NumberDisplay(lyt::Layout& nLyt)
			{
				this->numberLayout = &nLyt;
				nLyt.adjustFor4b3();
			}
			
			void setTopColor(_GXColor& col);
			void setBottomColor(_GXColor& col);
			void draw(int idx, const hel::math::Vector2& pos);
		};
	}
}
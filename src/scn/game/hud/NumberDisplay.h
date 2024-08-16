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
		class NumberDisplay
		{
			lyt::Layout *numberLayout;
			
		public:
		
			NumberDisplay(lyt::Layout& nLyt)
			{
				this->numberLayout = &nLyt;
			}
			
			void draw(int idx, const hel::math::Vector3& pos, const hel::math::Vector2& scale, const _GXColor& top, const _GXColor& bottom)
			{
				lyt::PaneAccessor numberPane = numberLayout->paneByName("P_pict");
				numberPane.setScale(scale);
				numberPane.setTrans(pos);
				numberPane.setVertexColor(top, UPPER_LEFT);
				numberPane.setVertexColor(top, UPPER_RIGHT);
				numberPane.setVertexColor(bottom, LOWER_LEFT);
				numberPane.setVertexColor(bottom, LOWER_RIGHT);
				
				float shift = NUMBER_TEXCOORD_SHIFT * idx;
				numberPane.setTexCoords( NUMBER_TEXCOORD_ORIGINLEFT + shift, 0.0, UPPER_LEFT );
				numberPane.setTexCoords( NUMBER_TEXCOORD_ORIGINRIGHT + shift, 0.0, UPPER_RIGHT );
				numberPane.setTexCoords( NUMBER_TEXCOORD_ORIGINLEFT + shift, 1.0, LOWER_LEFT );
				numberPane.setTexCoords( NUMBER_TEXCOORD_ORIGINRIGHT + shift, 1.0, LOWER_RIGHT );
				
				numberLayout->updateMatrix();
				numberLayout->draw();
			}
		};
	}
}
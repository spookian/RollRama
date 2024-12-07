#include "scn/game/hud/NumberDisplay.h"
#include "common/Color.h"

using namespace hel::math;
namespace scn
{
	namespace roll
	{
		NumberDisplay::NumberDisplay()
		{
			numberLayout = new lyt::Layout( lyt::LayoutContext::quickContext("gcnstep/HUDNumber", "Number") );
			numberLayout->adjustFor4b3();
			
			this->setTopColor(hel::common::Color::WHITE);
			this->setBottomColor(hel::common::Color::WHITE);
		}
		
		NumberDisplay::~NumberDisplay()
		{
			delete numberLayout;
		}
		
		inline void NumberDisplay::setTopColor(const _GXColor& col)
		{
			*reinterpret_cast<unsigned long*>(&top) = *reinterpret_cast<const unsigned long*>(&col);
		}
		
		inline void NumberDisplay::setBottomColor(const _GXColor& col)
		{
			*reinterpret_cast<unsigned long*>(&bottom) = *reinterpret_cast<const unsigned long*>(&col);
		}
		
		void NumberDisplay::draw(unsigned long idx, const Vector2& pos)
		{
			Vector3 position(pos.x, pos.y, 0.0f);
			lyt::PaneAccessor numberPane = numberLayout->paneByName("P_pict");
			numberPane.setSize(scale);
			numberPane.setTrans(position);
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
	}
}
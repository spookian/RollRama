#include "gfx/EasyRender3D.h"
#include "math/Vector3.h"
#include "gfx/GXStructs.h"

namespace nw4r
{
	namespace g3d
	{
		class LightObj
		{
			unsigned long unk;
			_GXLightObj obj;
			
		public:
			void Clear(); // self explanatory
			void InitLightColor(_GXColor color);
			void InitLightDir(float x, float y, float z);
			void InitLightPos(float x, float y, float z);
			void InitLightShininess(float shininess);
			
			void operator=(const LightObj& other);
		};
	}
}

namespace g3d
{
	class LightSetAccessor
	{
		unsigned long unk;
	public:
		void enableLightObj(unsigned long idx, unsigned long enable) const;
		void enableAmbientLightObj(unsigned long enable) const;
		
		void setLightObj(unsigned long idx, const nw4r::g3d::LightObj& light_obj) const;
		void setAmbientLightObj(const nw4r::g3d::AmbientLightObj& ambient_obj) const;
	};
}
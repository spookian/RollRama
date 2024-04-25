#pragma once

#include "gfx/EasyRender3D.h"
#include "math/Vector3.h"
#include "gfx/GXStructs.h"

namespace nw4r
{
	namespace g3d
	{
		struct LightObj
		{
			unsigned long unk;
			_GXLightObj obj;
			
			LightObj();
		
			void Clear(); // self explanatory
			void InitLightColor(_GXColor color);
			void InitLightDir(float x, float y, float z);
			void InitLightPos(float x, float y, float z);
			void InitLightShininess(float shininess);
			void InitLightSpot(float angle, _GXSpotFn spot);
			void InitLightAttnA(float aa, float ab, float ac);
			void InitLightAttnK(float ka, float kb, float kc);
			
			void operator=(const LightObj& other);
		};
		
		struct AmbLightObj
		{
			_GXColor obj;
		};
	}
}

namespace g3d
{
	class LightSetAccessor
	{
		unsigned long unk[5];
	public:
		void enableLightObj(unsigned long idx, unsigned long enable) const;
		void enableAmbientLightObj(unsigned long enable) const;
		void disableLightObj(unsigned long idx) const;
		void disableLightObjAll() const;
		
		void setLightObj(unsigned long idx, const nw4r::g3d::LightObj& light_obj) const;
		void setAmbientLightObj(const nw4r::g3d::AmbLightObj& ambient_obj) const;
	};
}
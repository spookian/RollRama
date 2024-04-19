#include "gfx/EasyRender3D.h"
#include "math/Vector3.h"

extern "C"
{
	typedef _Vec3
	{
		float x;
		float y;
		float z;
	} Vec3;
	
	typedef struct _GXLightObj
	{
		char x0[0xC];  // at 0x00
		GXColor color; // at 0x0C
		f32 aa;        // at 0x10
		f32 ab;        // at 0x14
		f32 ac;        // at 0x18
		f32 ka;        // at 0x1C
		f32 kb;        // at 0x20
		f32 kc;        // at 0x24
		Vec3 pos;      // at 0x28
		Vec3 dir;      // at 0x34
	} GXLightObj;
}

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
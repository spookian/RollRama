#pragma once
extern "C"
{
	enum GXBlendMode
	{
		GX_BM_NONE,
		GX_BM_BLEND,
		GX_BM_LOGIC,
		GX_BM_SUBTRACT,
		GX_MAX_BLENDMODE
	};
	
	enum GXLogicOp
	{
		GX_LO_CLEAR = 0,
		GX_LO_AND,
		GX_LO_REVAND,
		GX_LO_COPY,
		GX_LO_INVAND,
		GX_LO_NOOP,
		GX_LO_XOR,
		GX_LO_OR,
		GX_LO_NOR,
		GX_LO_EQUIV,
		GX_LO_INV,
		GX_LO_REVOR,
		GX_LO_INVCOPY,
		GX_LO_INVOR,
		GX_LO_NAND,
		GX_LO_SET
	};
	
	enum GXBlendFactor
	{
		GX_BL_ZERO = 0,
		GX_BL_ONE,
		GX_BL_SRCCLR,
		GX_BL_INVSRCCLR,
		GX_BL_SRCALPHA,
		GX_BL_INVSRCALPHA,
		GX_BL_DSTALPHA,
		GX_BL_INVDSTALPHA,
		GX_BL_DSTCLR,
		GX_BL_INVDSTCLR
	};
	
	typedef struct _GXColor
	{
		unsigned char r;
		unsigned char g;
		unsigned char b;
		unsigned char a;
	} GXColor; 
	
	typedef struct _Vec3
	{
		float x;
		float y;
		float z;
	} Vec3;
	
	typedef struct _GXLightObj
	{
		char x0[0xC];  // at 0x00
		GXColor color; // at 0x0C
		float aa;        // at 0x10
		float ab;        // at 0x14
		float ac;        // at 0x18
		float ka;        // at 0x1C
		float kb;        // at 0x20
		float kc;        // at 0x24
		Vec3 pos;      // at 0x28
		Vec3 dir;      // at 0x34
	} GXLightObj;
	
	typedef struct _GXRenderModeObj
	{
		unsigned long viTVMode;
		
		unsigned short fbWidth;
		unsigned short efbHeight;
		unsigned short xfbHeight;
		
		unsigned short viXOrigin;
		unsigned short viYOrigin;
		unsigned short viWidth;
		unsigned short viHeight;
		
		unsigned long xfbMode;
		unsigned char field_rendering;
		unsigned char aa;
		unsigned char sample_pattern[12][2];
		unsigned char vfilter[7];
	} GXRenderModeObj;
	
	typedef enum _GXSpotFn
	{
		GX_SP_OFF,
		GX_SP_FLAT,
		GX_SP_COS,
		GX_SP_COS2,
		GX_SP_SHARP,
		GX_SP_RING1,
		GX_SP_RING2
	} GXSpotFn;
}
// all stolen (donated) from doldecomp.github.io
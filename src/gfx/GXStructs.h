#pragma once

// most of this header was derived from https://github.com/doldecomp/melee/blob/master/src/dolphin/gx/GXEnum.h
extern "C"
{
	typedef enum GXBlendMode
	{
		GX_BM_NONE,
		GX_BM_BLEND,
		GX_BM_LOGIC,
		GX_BM_SUBTRACT,
		GX_MAX_BLENDMODE
	} GXBlendMode;
	
	typedef enum GXLogicOp
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
	} GXLogicOp;
	
	typedef enum GXBlendFactor
	{
		GX_BL_ZERO,
		GX_BL_ONE,
		GX_BL_SRCCLR,
		GX_BL_INVSRCCLR,
		GX_BL_SRCALPHA,
		GX_BL_INVSRCALPHA,
		GX_BL_DSTALPHA,
		GX_BL_INVDSTALPHA,
		GX_BL_DSTCLR = GX_BL_SRCCLR,
		GX_BL_INVDSTCLR = GX_BL_INVSRCCLR
	} GXBlendFactor;
	
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
	
	typedef enum _GXTexFmt
	{
		GX_TF_I4,
		GX_TF_I8,
		GX_TF_IA4,
		GX_TF_IA8,
		GX_TF_RGB565,
		GX_TF_RGB5A3,
		GX_TF_RGBA8,
		GX_TF_CMPR = 0xE
	} GXTexFmt;
	
	typedef enum GXPrimitive
	{
		GX_QUADS = 0x80,
		GX_TRIANGLES = 0x90,
		GX_TRIANGLESTRIP = 0x98,
		GX_TRIANGLEFAN = 0xA0,
		GX_LINES = 0xA8,
		GX_LINESTRIP = 0xB0,
		GX_POINTS = 0xB8
	} GXPrimitive;
	
	typedef enum GXVtxFmt
	{
		GX_VTXFMT0,
		GX_VTXFMT1,
		GX_VTXFMT2,
		GX_VTXFMT3,
		GX_VTXFMT4,
		GX_VTXFMT5,
		GX_VTXFMT6,
		GX_VTXFMT7,
		GX_MAX_TEXFMT
	} GXVtxFmt;
	
	typedef enum GXAttr {
		GX_VA_PNMTXIDX,
		GX_VA_TEX0MTXIDX,
		GX_VA_TEX1MTXIDX,
		GX_VA_TEX2MTXIDX,
		GX_VA_TEX3MTXIDX,
		GX_VA_TEX4MTXIDX,
		GX_VA_TEX5MTXIDX,
		GX_VA_TEX6MTXIDX,
		GX_VA_TEX7MTXIDX,
		GX_VA_POS,
		GX_VA_NRM,
		GX_VA_CLR0,
		GX_VA_CLR1,
		GX_VA_TEX0,
		GX_VA_TEX1,
		GX_VA_TEX2,
		GX_VA_TEX3,
		GX_VA_TEX4,
		GX_VA_TEX5,
		GX_VA_TEX6,
		GX_VA_TEX7,
		GX_POS_MTX_ARRAY,
		GX_NRM_MTX_ARRAY,
		GX_TEX_MTX_ARRAY,
		GX_LIGHT_ARRAY,
		GX_VA_NBT,
		GX_VA_MAX_ATTR,
		GX_VA_NULL = 0xFF,
	} GXAttr;
	
	typedef enum GXTexWrapMode
	{
		GX_CLAMP,
		GX_REPEAT,
		GX_MIRROR,
		GX_MAX_TEXWRAPMODE
	} GXTexWrapMode;
	
	typedef struct GXTexObj 
	{
		unsigned char x0_pad[0x8];
		unsigned long dimensions;
		unsigned char xC_pad[0x8];
		GXTexFmt tex_fmt; // at 0x14
		unsigned char x18_pad[8];    // at 0x18
	} GXTexObj;
	
	typedef enum GXTexMapID
	{
		GX_TEXMAP0,
		GX_TEXMAP1,
		GX_TEXMAP2,
		GX_TEXMAP3,
		GX_TEXMAP4,
		GX_TEXMAP5,
		GX_TEXMAP6,
		GX_TEXMAP7,
		GX_MAX_TEXMAP,
		GX_TEXMAP_NULL = 0xFF,
		GX_TEX_DISABLE = 0x100,
	} GXTexMapID;
	
	typedef enum GXTexCoordID
	{
		GX_TEXCOORD0,
		GX_TEXCOORD1,
		GX_TEXCOORD2,
		GX_TEXCOORD3,
		GX_TEXCOORD4,
		GX_TEXCOORD5,
		GX_TEXCOORD6,
		GX_TEXCOORD7,
		GX_MAX_TEXCOORD,
		GX_TEXCOORD_NULL = 0xFF,
	} GXTexCoordID;
	
	typedef enum GXAttrType {
		GX_NONE,
		GX_DIRECT,
		GX_INDEX8,
		GX_INDEX16,
	} GXAttrType;
	
	typedef enum {
		GX_POS_XY = 0,
		GX_POS_XYZ = 1,
		GX_NRM_XYZ = 0,
		GX_NRM_NBT = 1,
		GX_NRM_NBT3 = 2,
		GX_CLR_RGB = 0,
		GX_CLR_RGBA = 1,
		GX_TEX_S = 0,
		GX_TEX_ST = 1,
	} GXCompCnt;

	typedef enum {
		GX_U8 = 0,
		GX_S8 = 1,
		GX_U16 = 2,
		GX_S16 = 3,
		GX_F32 = 4,
		GX_RGB565 = 0,
		GX_RGB8 = 1,
		GX_RGBX8 = 2,
		GX_RGBA4 = 3,
		GX_RGBA6 = 4,
		GX_RGBA8 = 5,
	} GXCompType;
}
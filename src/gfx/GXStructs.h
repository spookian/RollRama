#pragma once
extern "C"
{
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
}
// all stolen (donated) from doldecomp.github.io
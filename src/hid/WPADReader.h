#pragma once

#include "math/math.h"

#define MAX_HID_ACCEL 216.0f
#define MAX_ACCEL 100
#define WPAD_BUTTON_LEFT  0x0001
#define WPAD_BUTTON_RIGHT 0x0002
#define WPAD_BUTTON_DOWN  0x0004
#define WPAD_BUTTON_UP    0x0008
#define WPAD_BUTTON_PLUS  0x0010
#define WPAD_BUTTON_2     0x0100
#define WPAD_BUTTON_1     0x0200
#define WPAD_BUTTON_B     0x0400
#define WPAD_BUTTON_A     0x0800
#define WPAD_BUTTON_MINUS 0x1000
#define WPAD_BUTTON_Z     0x2000
#define WPAD_BUTTON_C     0x4000
#define WPAD_BUTTON_HOME  0x8000

extern "C"
{
	extern void WPADRead(unsigned long channel, void* buffer); // typecast buffer to WPADStatus
}

struct RotationResult
{
	hel::math::Matrix34 visual;
	hel::math::Matrix34 actual;
	
	unsigned short accelX;
	unsigned short accelY;
};

//https://wiiubrew.org/wiki/Padscore.rpl
struct IRObject
{
	unsigned short x;
	unsigned short y;
	unsigned short size;
	unsigned char ID;
	unsigned char pad;
};

struct WPADStatus
{
	unsigned short buttons;
	signed short accelX;
	signed short accelY;
	signed short accelZ;
	IRObject IR[4];
	unsigned char ext;
	unsigned char err;
};

RotationResult obtainWiimoteRotation(float size);
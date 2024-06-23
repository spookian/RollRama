#pragma once

#include "math/math.h"

#define MAX_HID_ACCEL 216.0f
#define MAX_ACCEL 100

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
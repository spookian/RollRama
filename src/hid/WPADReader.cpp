#include "hid/hid.h"
#include "app/app.h"
#include "common/ExplicitSingleton.h"

inline float convertAccel(signed short accel)
{
	signed short clamp = accel;
	if (clamp > MAX_ACCEL) clamp = MAX_ACCEL;
	else if (clamp < -MAX_ACCEL) clamp = -MAX_ACCEL;
	
	return ((float)clamp) / MAX_HID_ACCEL;
}

RotationResult obtainWiimoteRotation(float size)
{
	using namespace hel::math;
	hid::SimpleWRHID& wiimote = hel::common::ExplicitSingleton<app::Application>::object->hidManager()->getWiimoteArray()[0]; // wow.
	// placeholder code until i find out how to check for wpad conection in leftover sdk functions
	RotationResult result;

	if (wiimote.isEnabled())
	{
		WPADStatus wpad_data;
		WPADRead(0, (void*)&wpad_data);
		
		float accelX = convertAccel(-wpad_data.accelX);
		float accelY = convertAccel(wpad_data.accelY);
		Vector3 resultVec(accelX, 0.0f, accelY);
		
		result.vector = resultVec;
		result.buttons = wpad_data.buttons;
		result.accelX = wpad_data.accelX;
		result.accelY = wpad_data.accelY;
	}
	
	return result;
}
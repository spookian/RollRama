#pragma once
namespace hid
{
	struct Button
	{
		bool isHold() const;
		bool isTrigger() const;
		
		enum ButtonType
		{
			HID_BUTTON_UP = 1,
			HID_BUTTON_DOWN = 2,
			HID_BUTTON_LEFT = 4,
			HID_BUTTON_RIGHT = 8,
			
			HID_BUTTON_2 = 16,
			HID_BUTTON_1 = 32
		};
	};
	
	//struct DPD
	//{
	//};
	
	struct Accel
	{
		float x;
		float y;
		float z;
		
		hel::math::Vector3 rawVector3();
	};
	
	class HIDManager
	{
	public:
		inline hel::common::Array<SimpleWRHID, 4>& getWiimoteArray() // you can tell this is one of my functions because nintendo has a strict policy about calling the wii remotes "wiimotes"
		{
			unsigned long x = ((unsigned long)this) + 720;
			return *reinterpret_cast< hel::common::Array<SimpleWRHID, 4>* >(x);
		} // PSA: move to a cpp file when you get the chance
	};
	
	class SimpleWRHID
	{
	public:	
		bool isEnable();
		Accel accel() const;
		//DPD dpd(); used for pointing at screen
		Button button() const;
	};
}

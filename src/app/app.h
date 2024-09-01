#pragma once
#include "gfx/TexBuffer.h"
#include "hid/hid.h"

namespace app
{
	class Application
	{
	public:
		hid::HIDManager* hidManager();
		gfx::TexBuffer& fullScreenTexBuffer();
	};
}
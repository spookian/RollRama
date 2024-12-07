#pragma once

namespace snd
{
	class BgmPlayer;
	
	class SoundManager
	{
	public:
		BgmPlayer& bgm();
		static void load();
		static SoundManager *object()
		{
			return (SoundManager*)(0x808f1ccc);
		}
	};
}
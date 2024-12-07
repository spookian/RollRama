#pragma once
namespace snd
{
	class BgmPlayer
	{
	public:
		void setVolume(float); // i'm assuming 0.0 to 1.0
		void start(unsigned long);
		
		void stop(int);
		void stop();
	};
}
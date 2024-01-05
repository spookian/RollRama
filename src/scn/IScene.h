#pragma once

namespace scn
{
	class DrawReqInfo
	{
	};

	class IScene
	{
	public:	
		virtual void rtti() = 0;
		virtual ~IScene() {};
		virtual void updateMain() 							= 0;
		virtual void updateUseGPU() 						= 0;
		virtual void updateDebug() 							= 0;
		virtual void draw(const DrawReqInfo& info)		= 0;
		virtual bool isSceneEnd() const						= 0;
	};
}